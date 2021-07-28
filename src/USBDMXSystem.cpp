/*
* BuskMagic - Live lighting control system
* Copyright (C) 2019 Sauraen
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "USBDMXSystem.h"

namespace USBDMXSystem {

    bool loadmapmodetype;
    bool IsLoadMapModeType() { return loadmapmodetype; }
    void SetLoadMapMode(bool mapType) { loadmapmodetype = mapType; }
    String GetLoadMapModeHelpText(){
        return "This option specifies how communication is re-opened with "
               "USB-DMX devices when this showfile is loaded.\n\n"
               "Map by port: The devices are identified by their Bus "
               "and Device number for USB devices (which identify the "
               "physical USB port the device is connected to), or by "
               "the OS's device name for serial devices. This is best if "
               "you have multiple dongles of the same type. However, "
               "the devices must be manually remapped in this window "
               "if they are ever plugged into a different USB port, or "
               "in some cases if other USB devices are (dis)connected.\n\n"
               "Map by type: The devices are identified by their type. "
               "This is best if you only have one dongle of any type, "
               "since you can plug it into any USB port without having "
               "to remap. However, if you have multiple dongles of the "
               "same type, they will get mapped in a random order when "
               "the showfile is loaded.";
    }

    static ReadWriteLock devices_mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define DEVICES_LOCK_READ() const ScopedReadLock devlock(USBDMXSystem::devices_mutex)
    #define DEVICES_LOCK_WRITE() const ScopedWriteLock devlock(USBDMXSystem::devices_mutex)

    enum class LocalDeviceType : uint32_t {
        None,
        Unsupported,
        Serial,
        USB_uDMX,
    };
    static String TypeToString(LocalDeviceType t){
        switch(t){
            case LocalDeviceType::None: return "None";
            case LocalDeviceType::Unsupported: return "Unsupported";
            case LocalDeviceType::Serial: return "USB to Serial";
            case LocalDeviceType::USB_uDMX: return "uDMX or knockoff";
            default: return "ERROR";
        }
    }
    static LocalDeviceType TypeFromString(String s){
        String t = "";
        uint32_t i = 0;
        while(t != "ERROR"){
            t = TypeToString((LocalDeviceType)i);
            if(t == s) return (LocalDeviceType)i;
            ++i;
        }
        return LocalDeviceType::None;
    }

    class LocalDevice {
    public:
        LocalDevice() {}
        virtual ~LocalDevice() {}
        virtual LocalDeviceType GetType() const = 0;
        virtual String GetDescription() const = 0;
        virtual String GetFullInfo() const = 0;
        virtual bool IsSupported() const = 0;
        virtual void Map(uint32_t s) = 0;
        virtual void Unmap() = 0;
        virtual bool IsMapped() = 0;
        virtual String SendDMX(const uint8_t *buf512, uint16_t chans) = 0;
        virtual bool Matches(ValueTree node) = 0;
        virtual ValueTree Save() = 0;
    };

    struct UDSlot {
        LocalDevice *dev;
        String name;
        String status;
        uint16_t uni;
        uint16_t chans;

        UDSlot(){
            dev = nullptr;
            name = "unnamed";
            status = "Not yet started";
            uni = 0;
            chans = 512;
        }
    };

    static std::vector<LocalDevice*> devices;
    static std::vector<UDSlot> slots;


#ifdef BUSKMAGIC_LIBUSB

    //Partially based on uDMX.c from https://github.com/mirdej/udmx
    //which is in turn based on V-USB driver software (also GPL3 licensed)
    //by Objective Development Software GmbH <http://www.obdev.at/vusb/>

    #include "../external/usb/bm_usb.hpp"

    #define UDMX_USB_VID_VOTI 0x16C0 //Vendor ID, Van Ooijen Technische Informatica, www.voti.nl
    #define UDMX_USB_PID_LIBUSB 0x05DC //Vendor Class devices with libusb, free shared PID
    #define USB_LANGUAGE_ENGLISH 0x0409

    #define USB_TIMEOUT_DISCOVER 5000 //ms
    #define USB_TIMEOUT_RUN 200 //ms

    #define UDMX_CMD_SETCHANNELRANGE 2

    static String GetUSBErrorString(int res){
        if(res >= 0) return "OK (no error)";
    #if defined(JUCE_LINUX) || defined(JUCE_MAC)
        if(res == -EPERM) return "Permissions Error";
        if(res == -ETIMEDOUT) return "Timeout Error";
        if(res == -EOVERFLOW) return "Overflow Error";
    #else
        //libusb own errors
        if(res == -1) return "I/O Error";
        if(res == -3) return "Permissions Error";
        if(res == -7) return "Timeout Error";
    #endif
        return "Unknown Error";
    }

    static bool GetUSBStringEnglish(usb_dev_handle *device, int str_index, String &str_out){
        if(str_index < 0 || str_index > 0xFF){
            str_out = "Internal Error";
            return false;
        }
        //USB strings are UTF-16 encoded; fortunately Juce supports this
        uint8_t *recvbuf = new uint8_t[256];
        int res = usb_control_msg(device, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR,
                (USB_DT_STRING << 8) | str_index, USB_LANGUAGE_ENGLISH,
                (char*)recvbuf, 256, USB_TIMEOUT_DISCOVER);
        //res = number of bytes read
        if(res <= 1){
            str_out = (res >= 0) ? "(Blank)" : GetUSBErrorString(res);
            return false;
        }
        //Byte 1: descriptor type
        if(recvbuf[1] != USB_DT_STRING){
            str_out = "Data Error";
            return false;
        }
        //Byte 0: data length
        if(res != recvbuf[0]){
            std::cout << "Warning, USB string query received wrong length!\n";
            res = std::min((uint8_t)res, recvbuf[0]);
        }
        if(res & 1){
            std::cout << "Warning, USB string has odd number of bytes!\n";
            --res;
        }
        res = (res-2) >> 1; //Now number of chars
        //Remaining bytes are the string
        CharPointer_UTF16 strptr16 = CharPointer_UTF16((int16*)(&recvbuf[2]));
        str_out = String(strptr16, res);
        return true;
    }

    class USBDevice : LocalDevice {
    public:
        static void Init(){
            //usb_set_debug(2);
            usb_init();
        }
        static void RefreshDeviceList(){
            usb_find_busses();
            usb_find_devices();
            for(usb_bus *bus = usb_busses; bus != nullptr; bus = bus->next){
                for(struct usb_device *dev = bus->devices; dev != nullptr; dev = dev->next){
                    USBDevice *d = new USBDevice(dev, bus->location);
                    if(d->GetType() != LocalDeviceType::None){
                        devices.push_back(d);
                    }else{
                        delete d;
                    }
                }
            }
        }
        USBDevice(struct usb_device *dev, int busnum_) : LocalDevice() {
            //Defaults
            manu = product = sn = "Could not read\n";
            type = LocalDeviceType::None;
            //Query device
            vid = dev->descriptor.idVendor;
            pid = dev->descriptor.idProduct;
            busnum = busnum_;
            devnum = dev->devnum;
            handle = usb_open(dev);
            if(handle != nullptr){
                bool ok = true;
                if(!GetUSBStringEnglish(handle, dev->descriptor.iManufacturer, manu)) ok = false;
                if(!GetUSBStringEnglish(handle, dev->descriptor.iProduct, product)) ok = false;
                if(!GetUSBStringEnglish(handle, dev->descriptor.iSerialNumber, sn)) ok = false;
                if(manu == "www.anyma.ch" && product == "uDMX"){
                    type = LocalDeviceType::USB_uDMX;
                }else if(ok){
                    type = LocalDeviceType::Unsupported;
                }
                usb_close(handle);
                handle = nullptr;
            }
        }
        virtual ~USBDevice() {
            Unmap();
        }
        virtual LocalDeviceType GetType() const override {
            return type;
        }
        virtual String GetDescription() const override {
            return "USB: bus " + String(busnum) + " device " + hex(devnum, 24)
                + ": " + hex(vid) + ":" + hex(pid) + " " + product;
        }
        virtual String GetFullInfo() const override {
            return "Manufacturer: " + manu + "\nProduct: " + product + "\nSerial Number: " + sn
                + "\nBuskMagic recognizes this as: " + TypeToString(type);
        }
        virtual bool IsSupported() const override {
            return type != LocalDeviceType::None && type != LocalDeviceType::Unsupported;
        }
        virtual void Map(uint32_t s) override {
            if(slots[s].dev != nullptr){
                std::cout << "Slot already mapped!\n";
                return;
            }
            if(type != LocalDeviceType::USB_uDMX){
                std::cout << "Cannot map device of type " << TypeToString(type) << "!\n";
                return;
            }
            for(usb_bus *bus = usb_busses; bus != nullptr; bus = bus->next){
                for(struct usb_device *dev = bus->devices; dev != nullptr; dev = dev->next){
                    if(bus->location != busnum || dev->devnum != devnum) continue;
                    handle = usb_open(dev);
                    if(handle == nullptr){
                        std::cout << "Could not reopen bus " << busnum << " device " << hex(devnum, 24) << "!\n";
                        return;
                    }
                    String str;
                    if(!GetUSBStringEnglish(handle, dev->descriptor.iManufacturer, str)){
                        WarningBox("Error mapping device!");
                        usb_close(handle);
                        handle = nullptr;
                        return;
                    }
                    slots[s].dev = this;
                    slots[s].status = "Device opened";
                    return;
                }
            }
        }
        virtual void Unmap() override {
            if(handle == nullptr) return;
            usb_close(handle);
            handle = nullptr;
        }
        virtual bool IsMapped() override {
            return handle != nullptr;
        }
        virtual String SendDMX(const uint8_t *buf512, uint16_t chans) override {
            if(type != LocalDeviceType::USB_uDMX){
                return "Internal error";
            }
            uint8_t* tmpbuf = new uint8_t[chans];
            memcpy(tmpbuf, buf512, chans);
            int res = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
                UDMX_CMD_SETCHANNELRANGE, chans, 0, (char*)tmpbuf, chans, USB_TIMEOUT_RUN);
            String ret;
            if(res < 0){
                ret = GetUSBErrorString(res);
            }else if(res != chans){
                ret = "Wrong Size Returned";
            }else{
                if(memcmp(tmpbuf, buf512, chans) != 0){
                    ret = "Bad Data Returned";
                }else{
                    ret = "Communication OK";
                }
            }
            delete[] tmpbuf;
            return ret;
        }

        bool Matches(ValueTree node) override {
            jassert(node.isValid());
            return TypeToString(type) == node.getProperty(idType, "ERROR").toString()
                    && (int)busnum == (int)node.getProperty(idBusNum, 0)
                    && (int)devnum == (int)node.getProperty(idDevNum, 0);
        }
        ValueTree Save() override {
            ValueTree ret(idUSBDevice);
            ret.setProperty(idType, TypeToString(type), nullptr);
            ret.setProperty(idBusNum, (int)busnum, nullptr);
            ret.setProperty(idDevNum, (int)devnum, nullptr);
            return ret;
        }

    private:
        LocalDeviceType type;
        String manu, product, sn;
        uint16_t vid, pid;
        int32_t busnum;
        uint32_t devnum;
        usb_dev_handle *handle;
    };

#endif //BUSKMAGIC_LIBUSB

#ifdef BUSKMAGIC_SERIAL

#include <fcntl.h>
#include <sys/ioctl.h>
#ifdef JUCE_MAC
#include <termios.h>
#include <IOKit/serial/ioss.h>
#elif defined(JUCE_LINUX)
#include <asm/termbits.h>
#endif

//Partially based on bbb_artnet_dmx,
//https://github.com/sauraen/bbb_artnet_dmx
//by Sauraen and LukeNow
//(also GPL3 licensed)

#define DMX_BAUD 250000

    class SerialDevice : LocalDevice {
    public:
        static void Init(){
            ((void)0);
        }
        static void RefreshDeviceList(){
            String serialregex;
#if JUCE_MAC
            serialregex = "tty.usbserial-*";
#elif JUCE_LINUX
            serialregex = "ttyUSB*";
#endif
            Array<File> serdevfiles = File("/dev").findChildFiles(File::findFiles, false, serialregex);
            for(int i=0; i<serdevfiles.size(); ++i){
                devices.push_back(new SerialDevice(serdevfiles[i]));
            }
        }
        SerialDevice(File f) {
            name = f.getFullPathName();
            fd = -1;
        }
        virtual ~SerialDevice() {

        }
        virtual LocalDeviceType GetType() const override {
            return LocalDeviceType::Serial;
        }
        virtual String GetDescription() const override {
            return "Serial: " + name;
        }
        virtual String GetFullInfo() const override {
            return "USB-to-serial adapter\n" + name
                    + "\nBuskMagic hopes this is: USB to DMX dongle";
        }
        virtual bool IsSupported() const override {
            return true;
        }
        virtual void Map(uint32_t s) override {
            jassert(fd < 0);
            do{
                //Legacy comment from LukeNow:
                /* Opening devide as a transmitting */
                fd = open(name.toRawUTF8(), O_WRONLY | O_NOCTTY | O_NDELAY);
                if(fd < 0) {
                    std::cout << "SerialDevice::Map: TTY could not be opened!\n";
                    break;
                }
#ifdef JUCE_MAC
                struct termios ttyio;
                if(tcgetattr(fd, &ttyio) < 0){
                    std::cout << "SerialDevice::Map: failed to get serial port options\n";
                    break;
                }
#elif defined(JUCE_LINUX)
                struct termios2 ttyio;
                if(ioctl(fd, TCGETS2, &ttyio) < 0) {
                    std::cout << "SerialDevice::Map: failed to get termios2 for TTY\n";
                    break;
                }
#endif
                ttyio.c_cflag &= ~(CSIZE | PARENB); //Clear size, disable parity
                ttyio.c_cflag |= CS8; //8 bits
                ttyio.c_cflag |= CLOCAL; //Ignore control lines
                ttyio.c_cflag |= CSTOPB; //two stop bits set
                ttyio.c_oflag &= ~OPOST; //No output processing
                ttyio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
#ifdef JUCE_MAC
                if(tcsetattr(fd, TCSANOW, &ttyio) < 0){
                    std::cout << "SerialDevice::Map: failed to set serial port options\n";
                    break;
                }
                speed_t speed = DMX_BAUD;
                if(ioctl(fd, IOSSIOSPEED, &speed) < 0){
                    std::cout << "SerialDevice::Map: failed to set custom baud rate\n";
                    break;
                }
#elif defined(JUCE_LINUX)
                ttyio.c_cflag &= ~CBAUD; //Ignoring baudrate
                ttyio.c_cflag |= BOTHER; //Other baud rate
                ttyio.c_ospeed = DMX_BAUD; //Setting output rate
                if(ioctl(fd, TCSETS2, &ttyio) < 0) {
                    std::cout << "SerialDevice::Map: failed to set termios2 for TTY\n";
                    break;
                }
#endif
                slots[s].dev = this;
                slots[s].status = "Device opened";
                return;
            }while(false);
            WarningBox("Failed to set up serial output on " + name + "!");
            if(fd >= 0) close(fd);
            fd = -1;
        }
        virtual void Unmap() override {
            if(fd < 0) return;
            close(fd);
            fd = -1;
        }
        virtual bool IsMapped() override {
            return fd >= 0;
        }
        virtual String SendDMX(const uint8_t *buf512, uint16_t chans) override {
            jassert(fd >= 0);
            jassert(chans >= 1 && chans <= 512);
            uint8_t sendbuf[chans+1];
            sendbuf[0] = 0; //DMX start byte
            memcpy(&sendbuf[1], buf512, chans);
            String ret;
            if(ioctl(fd, TIOCSBRK) < 0 && ret.isEmpty()) {
                ret = "Start of break failed";
            }
            usleep(100); //Break duration
            if(ioctl(fd, TIOCCBRK) < 0 && ret.isEmpty()) {
                ret = "End of break failed";
            }
            usleep(15); //Duration of mark after break
            if(write(fd, sendbuf, chans+1) < 0 && ret.isEmpty()) {
                ret = "Data write failed";
            }
            if(ret.isEmpty()){
                ret = "Serial write successful";
            }
            return ret;
        }

        bool Matches(ValueTree node) override {
            jassert(node.isValid());
            return name == node.getProperty(idName, "ERROR").toString();
        }
        ValueTree Save() override {
            ValueTree ret(idSerialDevice);
            ret.setProperty(idName, name, nullptr);
            return ret;
        }
    private:
        String name;
        int fd;
    };

#endif //BUSKMAGIC_SERIAL

    uint32_t NumDevices() { return (uint32_t)devices.size(); }
    String DeviceDescription(uint32_t d){
        DEVICES_LOCK_READ();
        if(d >= devices.size()) return "ERROR";
        return devices[d]->GetDescription();
    }
    String DeviceFullInfo(uint32_t d){
        DEVICES_LOCK_READ();
        if(d >= devices.size()) return "ERROR";
        return devices[d]->GetFullInfo();
    }
    bool DeviceIsSupported(uint32_t d){
        DEVICES_LOCK_READ();
        if(d >= devices.size()) return false;
        return devices[d]->IsSupported();
    }

    void RefreshDeviceList(){
        DEVICES_LOCK_WRITE();
        devices.clear();
#ifdef BUSKMAGIC_LIBUSB
        USBDevice::RefreshDeviceList();
#endif
#ifdef BUSKMAGIC_SERIAL
        SerialDevice::RefreshDeviceList();
#endif
    }
    void MapDevice(uint32_t d, uint32_t s){
        DEVICES_LOCK_WRITE();
        if(d >= devices.size() || s >= slots.size()) return;
        devices[d]->Map(s);
    }
    void UnmapDevice(uint32_t s){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        if(slots[s].dev == nullptr) return;
        slots[s].dev->Unmap();
        delete slots[s].dev;
        slots[s].dev = nullptr;
        slots[s].status = "Device closed";
    }

    uint32_t NumSlots() { return (uint32_t)slots.size(); }
    void AddSlot(){
        DEVICES_LOCK_WRITE();
        slots.push_back(UDSlot());
    }
    void RemoveSlot(uint32_t s){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        if(slots[s].dev != nullptr){
            UnmapDevice(s);
        }
        slots.erase(slots.begin() + s);
    }
    String SlotType(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        if(slots[s].dev == nullptr) return "None";
        return TypeToString(slots[s].dev->GetType());
    }
    String SlotStatus(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        return slots[s].status;
    }
    String SlotName(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        return slots[s].name;
    }
    void SetSlotName(uint32_t s, String n){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        slots[s].name = n;
    }
    uint16_t SlotUni(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return 0x7FFF;
        return slots[s].uni;
    }
    void SetSlotUni(uint32_t s, uint16_t uni){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size() || uni >= 0x8000) return;
        slots[s].uni = uni;
    }
    uint16_t SlotChans(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return 0;
        return slots[s].chans;
    }
    void SetSlotChans(uint32_t s, uint16_t chans){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size() || chans > 512) return;
        slots[s].chans = chans;
    }
    String GetChansHelpText(){
        return  "You can improve the low framerates obtained when using "
                "USB-DMX devices by sending fewer DMX channels "
                "(or by switching to Art-Net).";
    }
    String SlotDescription(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        String ret = slots[s].name + " (" + hex(slots[s].uni) + "/" + String(slots[s].chans) + "): ";
        if(slots[s].dev == nullptr) return ret + " (unmapped)";
        return ret + slots[s].dev->GetDescription();
    }

    void GetNeededUniversesSorted(Array<uint16_t> &list){
        DEVICES_LOCK_READ();
        DefaultElementComparator<uint16_t> sorter;
        for(int s=0; s<slots.size(); ++s){
            uint16_t universe = slots[s].uni;
            if(list.indexOfSorted(sorter, universe) < 0){
                list.addSorted(sorter, universe);
            }
        }
    }

    void SendDMX512(uint16_t universe, const uint8_t *buf512){
        DEVICES_LOCK_READ();
        for(int s=0; s<slots.size(); ++s){
            if(slots[s].dev == nullptr) continue;
            if(slots[s].uni != universe) continue;
            slots[s].status = slots[s].dev->SendDMX(buf512, slots[s].chans);
        }
    }

    void Init(ValueTree us_node){
        DEVICES_LOCK_WRITE();
        loadmapmodetype = us_node.isValid() ? (bool)us_node.getProperty(idLoadMapMode, true) : true;
#ifdef BUSKMAGIC_LIBUSB
        USBDevice::Init();
#endif
#ifdef BUSKMAGIC_SERIAL
        SerialDevice::Init();
#endif
        RefreshDeviceList();
        if(!us_node.isValid()) return;
        for(int i=0; i<us_node.getNumChildren(); ++i){
            ValueTree slotnode = us_node.getChild(i);
            UDSlot s;
            s.name = slotnode.getProperty(idName, "ERROR");
            s.status = "Not yet started";
            s.uni = (int)slotnode.getProperty(idUniverse, 0);
            s.chans = (int)slotnode.getProperty(idChannels, 512);
            slots.push_back(s);
            LocalDeviceType type = TypeFromString(slotnode.getProperty(idType, "None"));
            if(type == LocalDeviceType::None) continue;
            jassert(type != LocalDeviceType::Unsupported);
            jassert(slotnode.getNumChildren() == 1);
            ValueTree devnode = slotnode.getChild(0);
            for(int i=0; i<devices.size(); ++i){
                if(devices[i]->GetType() != type) continue;
                if(devices[i]->IsMapped()) continue;
                if(!loadmapmodetype && !devices[i]->Matches(devnode)) continue;
                devices[i]->Map(slots.size()-1);
            }
        }
    }
    void Finalize(){
        DEVICES_LOCK_WRITE();
        while(NumSlots() > 0) RemoveSlot(0); //This unmaps the devices too
    }

    ValueTree Save(){
        DEVICES_LOCK_READ();
        ValueTree ret(idUSBDMXSystem);
        ret.setProperty(idLoadMapMode, loadmapmodetype, nullptr);
        for(int i=0; i<slots.size(); ++i){
            ValueTree slotnode(idSlot);
            slotnode.setProperty(idName, slots[i].name, nullptr);
            slotnode.setProperty(idUniverse, (int)slots[i].uni, nullptr);
            slotnode.setProperty(idChannels, (int)slots[i].chans, nullptr);
            slotnode.setProperty(idType, SlotType(i), nullptr);
            if(slots[i].dev != nullptr){
                slotnode.addChild(slots[i].dev->Save(), -1, nullptr);
            }
            ret.addChild(slotnode, -1, nullptr);
        }
        return ret;
    }

}
