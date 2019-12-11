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

static String GetUSBStringEnglish(usb_dev_handle *device, int str_index){
    if(str_index < 0 || str_index > 0xFF) return "Internal Error";
    //USB strings are UTF-16 encoded; fortunately Juce supports this
    uint8_t *recvbuf = new uint8_t[256];
    int res = usb_control_msg(device, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR,
            (USB_DT_STRING << 8) | str_index, USB_LANGUAGE_ENGLISH,
            (char*)recvbuf, 256, USB_TIMEOUT_DISCOVER);
    //res = number of bytes read
    if(res <= 1){
        if(res >= 0) return "(Blank)";
        return GetUSBErrorString(res);
    }
    //Byte 1: descriptor type
    if(recvbuf[1] != USB_DT_STRING) return "Data Error";
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
    return String(strptr16, res);
}

#endif

namespace USBDMXSystem {

    static ReadWriteLock devices_mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define DEVICES_LOCK_READ() const ScopedReadLock devlock(USBDMXSystem::devices_mutex)
    #define DEVICES_LOCK_WRITE() const ScopedWriteLock devlock(USBDMXSystem::devices_mutex)

    enum class UDType : uint32_t {
        None,
        uDMX,
    };
    static String TypeToString(UDType t){
        switch(t){
            case UDType::None: return "None";
            case UDType::uDMX: return "uDMX or knockoff";
            default: return "ERROR";
        }
    }

    struct USBDevice {
        String manu, product, sn;
        uint16_t vid, pid;
        uint32_t bus;
        uint8_t devnum;
        UDType type;

        USBDevice(uint16_t v, uint16_t p, uint32_t b, uint8_t d)
                : vid(v), pid(p), bus(b), devnum(d){
            manu = "Could not read\n";
            product = "Could not read\n";
            sn = "Could not read\n";
            type = UDType::None;
        }
    };

    struct UDSlot {
        UDType type;
        String name;
        String status;
        uint16_t uni;
        uint16_t chans;
        uint32_t bus;
        uint8_t devnum;
        void *devhandle;

        UDSlot(){
            type = UDType::None;
            name = "unnamed";
            status = "Not yet started";
            uni = 0;
            chans = 512;
            devhandle = nullptr;
        }
    };

    static std::vector<USBDevice> devices;
    static std::vector<UDSlot> slots;

    uint32_t NumDevices() { return (uint32_t)devices.size(); }
    String DeviceDescription(uint32_t d){
        DEVICES_LOCK_READ();
        if(d >= devices.size()) return "ERROR";
        return "Bus " + String(devices[d].bus) + " device " + String(devices[d].devnum)
            + ": " + hex(devices[d].vid) + ":" + hex(devices[d].pid) + " " + devices[d].product;
    }
    String DeviceFullInfo(uint32_t d){
        if(d >= devices.size()) return "ERROR";
        return "Manufacturer: " + devices[d].manu
            + "\nProduct: " + devices[d].product
            + "\nSerial Number: " + devices[d].sn
            + "\nBuskMagic recognizes this as: " + TypeToString(devices[d].type);
    }
    bool DeviceIsSupported(uint32_t d){
        if(d >= devices.size()) return false;
        return devices[d].type != UDType::None;
    }

    void RefreshDeviceList(){
        DEVICES_LOCK_WRITE();
        devices.clear();
#ifdef BUSKMAGIC_LIBUSB
        usb_find_busses();
        usb_find_devices();
        for(usb_bus *bus = usb_busses; bus != nullptr; bus = bus->next){
            uint32_t busnum = bus->location;
            for(struct usb_device *dev = bus->devices; dev != nullptr; dev = dev->next){
                USBDevice d(dev->descriptor.idVendor, dev->descriptor.idProduct,
                        busnum, dev->devnum);
                usb_dev_handle *handle = usb_open(dev);
                if(handle != nullptr){
                    d.manu = GetUSBStringEnglish(handle, dev->descriptor.iManufacturer);
                    d.product = GetUSBStringEnglish(handle, dev->descriptor.iProduct);
                    d.sn = GetUSBStringEnglish(handle, dev->descriptor.iSerialNumber);
                    if(d.manu == "www.anyma.ch" && d.product == "uDMX"){
                        d.type = UDType::uDMX;
                    }
                    usb_close(handle);
                }
                devices.push_back(d);
            }
        }
#endif
    }
    void MapDevice(uint32_t d, uint32_t s){
        DEVICES_LOCK_WRITE();
        if(d >= devices.size() || s >= slots.size()) return;
#ifdef BUSKMAGIC_LIBUSB
        if(devices[d].type != UDType::uDMX){
            std::cout << "Cannot map device of type " << TypeToString(devices[d].type) << "!\n";
            return;
        }
        for(usb_bus *bus = usb_busses; bus != nullptr; bus = bus->next){
            uint32_t busnum = bus->location;
            for(struct usb_device *dev = bus->devices; dev != nullptr; dev = dev->next){
                if(busnum != devices[d].bus || dev->devnum != devices[d].devnum) continue;
                usb_dev_handle *handle = usb_open(dev);
                if(handle == nullptr){
                    std::cout << "Could not reopen bus " << busnum << " device " << (int)dev->devnum << "!\n";
                    return;
                }
                slots[s].type = devices[d].type;
                slots[s].status = "Device opened";
                slots[s].bus = busnum;
                slots[s].devnum = dev->devnum;
                slots[s].devhandle = handle;
                return;
            }
        }
#endif
    }
    void UnmapDevice(uint32_t s){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        if(slots[s].devhandle == nullptr) return;
#ifdef BUSKMAGIC_LIBUSB
        jassert(slots[s].type == UDType::uDMX);
        usb_close((usb_dev_handle*)slots[s].devhandle);
        slots[s].devhandle = nullptr;
        slots[s].type = UDType::None;
        slots[s].status = "Device closed";
#endif
    }

    uint32_t NumSlots() { return (uint32_t)slots.size(); }
    void AddSlot(){
        DEVICES_LOCK_WRITE();
        slots.push_back(UDSlot());
    }
    void RemoveSlot(uint32_t s){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        if(slots[s].devhandle != nullptr){
            UnmapDevice(s);
        }
        slots.erase(slots.begin() + s);
    }
    String SlotType(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        return TypeToString(slots[s].type);
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
        return  "You can improve the low framerates obtained\n"
                "when using USB-DMX devices by sending\n"
                "fewer DMX channels\n"
                "(or by switching to Art-Net).";
    }
    String SlotDescription(uint32_t s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        String ret = slots[s].name + " (" + hex(slots[s].uni) + "/" + String(slots[s].chans) + "): ";
        if(slots[s].devhandle == nullptr){
            ret += " (unmapped)";
        }else{
            ret += "Bus " + String(slots[s].bus) + " Dev " + String(slots[s].devnum);
        }
        return ret;
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
            if(slots[s].uni != universe) continue;
            switch(slots[s].type){
                case UDType::uDMX: {
#ifdef BUSKMAGIC_LIBUSB
                    if(slots[s].devhandle == nullptr){
                        jassertfalse;
                        continue;
                    }
                    uint16_t chans = slots[s].chans;
                    uint8_t* tmpbuf = new uint8_t[chans];
                    memcpy(tmpbuf, buf512, chans);
                    int res = usb_control_msg((usb_dev_handle*)slots[s].devhandle,
                        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
                        UDMX_CMD_SETCHANNELRANGE, chans, 0, (char*)tmpbuf, chans, USB_TIMEOUT_RUN);
                    if(res < 0){
                        slots[s].status = GetUSBErrorString(res);
                    }else if(res != chans){
                        slots[s].status = "Wrong Size Returned";
                    }else{
                        if(memcmp(tmpbuf, buf512, chans) != 0){
                            slots[s].status = "Bad Data Returned";
                        }else{
                            slots[s].status = "Communication OK";
                        }
                    }
                    delete[] tmpbuf;
#else
                    std::cout << "uDMX slot type not supported!\n";
#endif
                    break; }
                case UDType::None:
                    continue;
            }
        }
    }

    bool loadmapmodetype;
    bool IsLoadMapModeType() { return loadmapmodetype; }
    void SetLoadMapMode(bool mapType) { loadmapmodetype = mapType; }
    String GetLoadMapModeHelpText(){
        return "This option specifies how communication is\n"
               "re-opened with USB-DMX devices when this showfile\n"
               "is loaded.\n\n"
               "Map by port: The devices are identified by their Bus\n"
               "and Device number, which together define the physical\n"
               "USB port the device is connected to. This is best if\n"
               "you have multiple dongles of the same type. However,\n"
               "the devices must be manually remapped in this window\n"
               "if they are ever plugged into a different USB port.\n\n"
               "Map by type: The devices are identified by their type.\n"
               "This is best if you only have one dongle of any type,\n"
               "since you can plug it into any USB port without having\n"
               "to remap. However, if you have multiple dongles of the\n"
               "same type, only the first one of each type will get\n"
               "mapped when the showfile is loaded.";
    }

    void Init(ValueTree us_node){
        loadmapmodetype = us_node.isValid() ? (bool)us_node.getProperty(idLoadMapMode, false) : false;
        //TODO
#ifdef BUSKMAGIC_LIBUSB
        usb_set_debug(1);
        usb_init();
#endif
        RefreshDeviceList();
    }
    void Finalize(){
        DEVICES_LOCK_WRITE();
        while(NumSlots() > 0) RemoveSlot(0); //This unmaps the devices too
    }

    ValueTree Save(){
        ValueTree ret(idUSBDMXSystem);
        ret.setProperty(idLoadMapMode, loadmapmodetype, nullptr);
        //TODO
        return ret;
    }

}
