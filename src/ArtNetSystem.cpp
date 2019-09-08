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

#include "ArtNetSystem.h"

#include "LightingSystem.h"

#include <cstring>

namespace ArtNetSystem {
    
    ReadWriteLock mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define AS_LOCK_READ() const ScopedReadLock aslock(ArtNetSystem::mutex)
    #define AS_LOCK_WRITE() const ScopedWriteLock aslock(ArtNetSystem::mutex)

    String ArtNetDevice::GetTableRow(){
        AS_LOCK_READ();
        String ret;
             if(mode == Mode::manual)       ret += "M";
        else if(mode == Mode::discovered)   ret += "D";
        else if(mode == Mode::lost)         ret += "?";
        else                                ret += "X";
        ret += " ";
             if(style == Style::node)       ret += "N";
        else if(style == Style::controller) ret += "C";
        else if(style == Style::media)      ret += "M";
        else if(style == Style::route)      ret += "R";
        else if(style == Style::backup)     ret += "B";
        else if(style == Style::config)     ret += "C";
        else if(style == Style::visual)     ret += "V";
        else                                ret += "X";
        ret += String::formatted(" %03d.%03d.%03d.%03d ", 
            ip.address[0], ip.address[1], ip.address[2], ip.address[3]);
        ret += hex(bindindex) + " ";
        ret += hex(map ? map_net : net) + ".";
        ret += hex(map ? map_subnet : subnet, 4) + " ";
        for(int i=0; i<4; ++i){
            uint8_t u = map ? map_inuni[i] : inuni[i];
            if(u > 0x0F) ret += "-";
            else ret += hex(u, 4);
            if(i != 3) ret += ",";
        }
        ret += "/";
        for(int i=0; i<4; ++i){
            uint8_t u = map ? map_outuni[i] : outuni[i];
            if(u > 0x0F) ret += "-";
            else ret += hex(u, 4);
            if(i != 3) ret += ",";
        }
        ret += " " + shortname;
        return ret;
    }
    
    String ArtNetDevice::GetDescription(){
        AS_LOCK_READ();
        String ret;
             if(mode == Mode::manual)       ret += "Manual";
        else if(mode == Mode::discovered)   ret += "Discovered";
        else if(mode == Mode::lost)         ret += "Lost";
        else                                ret += "Error";
        ret += " ";
             if(style == Style::node)       ret += "Node";
        else if(style == Style::controller) ret += "Controller";
        else if(style == Style::media)      ret += "Media Server";
        else if(style == Style::route)      ret += "Routing device";
        else if(style == Style::backup)     ret += "Backup device";
        else if(style == Style::config)     ret += "Configuration tool";
        else if(style == Style::visual)     ret += "Visualizer";
        else                                ret += "Error";
        return ret;
    }
    
    ArtNetDevice::ArtNetDevice() : mode(Mode::manual), style(Style::node),
        status{0xFF, 0xFF}, oem(0x0000), esta(0x4F4E), fw(0x0000),
        net(0x00), subnet(0x0), 
        inuni{0x7F, 0x7F, 0x7F, 0x7F}, outuni{0x7F, 0x7F, 0x7F, 0x7F},
        map(false), map_net(0x00), map_subnet(0x0), 
        map_inuni{0x7F, 0x7F, 0x7F, 0x7F}, map_outuni{0x7F, 0x7F, 0x7F, 0x7F},
        bindindex(0), artdmx_sequence(1), ip(), mac(),
        shortname("<Short name>"), 
        longname("<Device long name>"), 
        nodereport("(Have not received ArtPollReply from this device)") {}
        
    #define LOAD_FOUR_UNI_VALUES(idSomething, somethinguni) { \
        ValueTree temp = dev_node.getChildWithName(idSomething); \
        if(!temp.isValid()) { jassertfalse; return; } \
        if(!(temp.getNumChildren() == 4)) { jassertfalse; return; } \
        for(int i=0; i<4; ++i) somethinguni[i] = (int)temp.getChild(i).getProperty(idUniverse, 0x7F); \
    } REQUIRESEMICOLON
    
    ArtNetDevice::ArtNetDevice(ValueTree dev_node) : ArtNetDevice() {
        if(!dev_node.isValid()) { jassertfalse; return; }
        mode = static_cast<Mode>((uint8_t)(int)dev_node.getProperty(idMode, 0));
        style = static_cast<Style>((uint8_t)(int)dev_node.getProperty(idStyle, 0));
        net = (int)dev_node.getProperty(idNet, 0);
        subnet = (int)dev_node.getProperty(idSubnet, 0);
        LOAD_FOUR_UNI_VALUES(idInUni, inuni);
        LOAD_FOUR_UNI_VALUES(idOutUni, outuni);
        map = dev_node.getProperty(idMap, false);
        map_net = (int)dev_node.getProperty(idMapNet, 0);
        map_subnet = (int)dev_node.getProperty(idMapSubnet, 0);
        LOAD_FOUR_UNI_VALUES(idMapInUni, map_inuni);
        LOAD_FOUR_UNI_VALUES(idMapOutUni, map_outuni);
        bindindex = (int)dev_node.getProperty(idBindIndex, 0);
        ip = IPAddress(dev_node.getProperty(idIP, "").toString());
        shortname = dev_node.getProperty(idShortName, "<Short name>").toString();
        longname = dev_node.getProperty(idLongName, "<Device long name>").toString();
    }
    
    #define SAVE_FOUR_UNI_VALUES(idSomething, somethinguni) { \
        ValueTree temp(idSomething); \
        for(int i=0; i<4; ++i){ \
            ValueTree temptemp(idSomething); \
            temptemp.setProperty(idUniverse, somethinguni[i], nullptr); \
            temp.addChild(temptemp, -1, nullptr); \
        } \
        ret.addChild(temp, -1, nullptr); \
    } REQUIRESEMICOLON
    
    ValueTree ArtNetDevice::Save(){
        ValueTree ret(idArtNetDevice);
        ret.setProperty(idMode, (int)static_cast<uint8_t>(mode), nullptr);
        ret.setProperty(idStyle, (int)static_cast<uint8_t>(style), nullptr);
        ret.setProperty(idNet, (int)net, nullptr);
        ret.setProperty(idSubnet, (int)subnet, nullptr);
        SAVE_FOUR_UNI_VALUES(idInUni, inuni);
        SAVE_FOUR_UNI_VALUES(idOutUni, outuni);
        ret.setProperty(idMap, map, nullptr);
        ret.setProperty(idMapNet, (int)map_net, nullptr);
        ret.setProperty(idMapSubnet, (int)map_subnet, nullptr);
        SAVE_FOUR_UNI_VALUES(idMapInUni, map_inuni);
        SAVE_FOUR_UNI_VALUES(idMapOutUni, map_outuni);
        ret.setProperty(idBindIndex, (int)bindindex, nullptr);
        ret.setProperty(idIP, ip.toString(), nullptr);
        ret.setProperty(idShortName, shortname, nullptr);
        ret.setProperty(idLongName, longname, nullptr);
        return ret;
    }
    
    static OwnedArray<ArtNetDevice> devices;
    
    int NumDevices() { return devices.size(); }
    ArtNetDevice *GetDevice(int d) {
        AS_LOCK_READ();
        if(d < 0 || d >= devices.size()){
            std::cout << "ArtNetSystem asked for device " << d << " out of " << devices.size() << "!\n";
            jassertfalse;
            return nullptr;
        }
        return devices[d];
    }
    
    void AddBlankDevice(){
        AS_LOCK_WRITE();
        devices.add(new ArtNetDevice());
    }
    void RemoveDevice(int d){
        AS_LOCK_WRITE();
        devices.remove(d);
    }
    
    Array<uint16_t> GetSortedListNeededUniverses(){
        AS_LOCK_READ();
        Array<uint16_t> ret;
        DefaultElementComparator<uint16_t> sorter;
        for(int d=0; d<devices.size(); ++d){
            ArtNetDevice *dev = devices[d];
            uint16_t netsubnet, universe;
            if(dev->map){
                netsubnet = ((uint16_t)dev->map_net << 8) | (dev->map_subnet << 4);
            }else{
                netsubnet = ((uint16_t)dev->net << 8) | (dev->subnet << 4);
            }
            for(int i=0; i<4; ++i){
                uint8_t outuni = dev->map ? dev->map_outuni[i] : dev->outuni[i];
                if(outuni > 0x0F) continue;
                universe = netsubnet | outuni;
                if(ret.indexOfSorted(sorter, universe) < 0){
                    ret.addSorted(sorter, universe);
                }
            }
        }
        return ret;
    }
    
    uint32_t ParseUniverseText(String unitxt){
        StringArray unis = StringArray::fromTokens(unitxt, ",", "");
        if(unis.size() != 4) return 0xFFFFFFFF;
        uint32_t ret = 0, thisuni;
        for(int i=0; i<4; ++i){
            String str = unis[i].trim();
            if(str == "-"){
                thisuni = 0x7F;
            }else if(isHex(str, false)){
                thisuni = str.getHexValue32();
                if(thisuni >= 0x10) return 0xFFFFFFFF;
            }else{
                return 0xFFFFFFFF;
            }
            ret |= (thisuni << (i << 3));
        }
        return ret;
    }
    String GetUniverseText(const uint8_t *uni){
        String ret;
        for(int i=0; i<4; ++i){
            if(uni[i] == 0x7F){
                ret += "-";
            }else if(uni[i] <= 0x0F){
                ret += hex(uni[i], 4);
            }else{
                ret += "E";
            }
            if(i != 3) ret += ",";
        }
        return ret;
    }
    IPAddress ParseIPAddress(String ipstr){
        StringArray bytes = StringArray::fromTokens(ipstr, ".", "");
        if(bytes.size() != 4) return IPAddress();
        IPAddress ret;
        for(int i=0; i<4; ++i){
            String str = bytes[i].trim();
            if(!isInt(str, false)) return IPAddress();
            int b = str.getIntValue();
            if(b < 0 || b > 255) return IPAddress();
            ret.address[i] = b;
        }
        return ret;
    }
    
    static DatagramSocket *sendsock = nullptr;
    
    static void SendArtNet(IPAddress dest, uint16_t opcode, const uint8_t *data, 
            int dlen, bool packetHasProtVer = true, 
            ArtNetDevice *optionalDevForStatus = nullptr){
        int hlen = packetHasProtVer ? 12 : 10;
        uint8_t *buf = new uint8_t[hlen+dlen];
        sprintf((char*)buf, "Art-Net");
        buf[7] = 0;
        *(uint16_t*)&buf[8] = opcode;
        if(packetHasProtVer){
            buf[10] = 0;
            buf[11] = 14;
        }
        memcpy(&buf[hlen], data, dlen);
        assert(sendsock != nullptr);
        int retrycount = 0;
        const int max_retries = 2;
        while(retrycount++ < max_retries){
            int res = sendsock->waitUntilReady(false, 5);
            if(res < 0){
                std::cout << "Socket state error!\n";
                break;
            }else if(res == 0){
                std::cout << "Socket not ready to write!\n";
            }else{
                res = sendsock->write(dest.toString(), 0x1936, buf, hlen+dlen);
                if(res <= 0){
                    std::cout << "Error sending packet!\n";
                }else if(res != hlen+dlen){
                    std::cout << "Failed to send whole packet!\n";
                }else{
                    //std::cout << "Sent Art-Net packet with opcode 0x" << hex(opcode) << " length " << hlen+dlen << "\n";
                }
                break;
            }
        }
        if(retrycount >= max_retries){
            std::cout << "Gave up waiting for socket to be ready! Dropping data!\n";
            if(optionalDevForStatus != nullptr){
                optionalDevForStatus->nodereport = String("Connection timed out!");
            }
        }
        delete[] buf;
    }
    
    void ChangeDeviceUniverses(int d, uint8_t net, uint8_t subnet, 
        const uint8_t *inuni, const uint8_t *outuni){
        AS_LOCK_READ();
        ArtNetDevice *dev = devices[d];
        if(dev == nullptr) return;
        //Change local knowledge of universes, in case device doesn't respond
        dev->net = net;
        dev->subnet = subnet;
        for(int i=0; i<4; ++i) dev->inuni[i] = inuni[i];
        for(int i=0; i<4; ++i) dev->outuni[i] = outuni[i];
        //Send ArtAddress to ask device to change its mapping
        uint8_t *data = new uint8_t[95];
        data[0] = 0x80 | net;
        data[1] = dev->bindindex;
        memset(&data[2], 0, 18+64); //Short name and long name
        for(int i=0; i<4; ++i){
            data[84+i] = 0x80 | inuni[i];
            data[88+i] = 0x80 | outuni[i];
        }
        data[92] = 0x80 | (subnet & 0xF);
        data[93] = 0; //SwVideo, reserved
        data[94] = 0; //Command
        SendArtNet(dev->ip, 0x6000, data, 95, true, dev);
        delete[] data;
    }
    
    void SendDMX512(uint16_t universe, const uint8_t *buf512){
        AS_LOCK_READ();
        uint8_t *data = new uint8_t[518];
        for(int d=0; d<devices.size(); ++d){
            ArtNetDevice *dev = devices[d];
            bool flag = false;
            uint16_t send_universe;
            if(dev->map){
                if(dev->map_net != universe >> 8) continue;
                if(dev->map_subnet != ((universe >> 4) & 0xF)) continue;
                for(int i=0; i<4; ++i){
                    if(dev->map_outuni[i] == (universe & 0xF)){
                        flag = true;
                        send_universe = (uint16_t)dev->net << 8;
                        send_universe |= dev->subnet << 4;
                        send_universe |= dev->outuni[i] <= 0xF ? 
                            dev->outuni[i] : dev->map_outuni[i];
                        break;
                    }
                }
            }else{
                if(dev->net != universe >> 8) continue;
                if(dev->subnet != ((universe >> 4) & 0xF)) continue;
                for(int i=0; i<4; ++i){
                    if(dev->outuni[i] == (universe & 0xF)){
                        flag = true;
                        send_universe = universe;
                        break;
                    }
                }
            }
            if(!flag) continue;
            data[0] = dev->artdmx_sequence;
            ++dev->artdmx_sequence;
            if(dev->artdmx_sequence == 0) dev->artdmx_sequence = 1;
            data[1] = 0; //Physical
            data[2] = send_universe & 0xFF;
            data[3] = (send_universe >> 8) & 0x7F;
            data[4] = 0x02; //LengthHi, 512
            data[5] = 0x00; //Length, 512
            memcpy(&data[6], buf512, 512);
            SendArtNet(dev->ip, 0x5000, data, 518, true, dev);
        }
        delete[] data;
    }
    
    static int pollmode; //0: disabled 1: static 2: DHCP
    int GetPollMode() { return pollmode; }
    void SetPollMode(int pmode) { pollmode = pmode; }
    
    const static IPAddress staticBroadcast(2, 255, 255, 255);
    static IPAddress dhcpBroadcast;
    IPAddress GetDHCPBroadcastAddress(){
        return dhcpBroadcast;
    }
    
    static bool isIPInSubnet(const IPAddress &target, const IPAddress &subnet){
        bool snmode = true;
        for(int i=3; i>=0; --i){
            if(subnet.address[i] != 0xFF) snmode = false;
            if(!snmode && subnet.address[i] != target.address[i]) return false;
        }
        return true;
    }
    
    class Poller : public Timer {
    public:
        Poller() { startTimer(2500); }
        virtual ~Poller() { stopTimer(); }
        virtual void timerCallback() override {
            if(pollmode == 0) return;
            uint16_t data = 0;
            IPAddress bcast = pollmode == 2 ? dhcpBroadcast : staticBroadcast;
            SendArtNet(bcast, 0x2000, (uint8_t*)&data, 2);
            AS_LOCK_READ();
            for(int d=0; d<devices.size(); ++d){
                const IPAddress &ip = devices[d]->ip;
                if(!ip.isNull() && !isIPInSubnet(ip, bcast)){
                    SendArtNet(ip, 0x2000, (uint8_t*)&data, 2, true, devices[d]);
                }
            }
        }
    };
    static Poller *poller = nullptr;
    
    void SendArtPollReply(IPAddress senderIP){
        IPAddress dest;
        if(pollmode == 2){
            dest = dhcpBroadcast;
        }else if(pollmode == 1){
            dest = staticBroadcast;
        }else if(!senderIP.isNull()){
            dest = senderIP;
        }else{
            return;
        }
        uint8_t *data = new uint8_t[229];
        IPAddress localIP = IPAddress::getLocalAddress();
        if(localIP == IPAddress(127, 0, 0, 1)){
            std::cout << "Sending ArtPollReply to localhost\n";
        }
        data[0] = localIP.address[0];
        data[1] = localIP.address[1];
        data[2] = localIP.address[2];
        data[3] = localIP.address[3];
        data[4] = 0x36; //Port LH
        data[5] = 0x19;
        data[6] = 0x00; //Firmware version HL
        data[7] = 0x01;
        data[8] = 0x00; //NetSwitch
        data[9] = 0x00; //SubSwitch
        data[10] = 0xFF; //OEM HL
        data[11] = 0xFF; 
        data[12] = 0; //UBEA
        data[13] = 0b11010000; //Status1
        data[14] = 0x00; //ESTA LH
        data[15] = 0x00;
        String ourname = "BuskMagic on " + SystemStats::getComputerName();
        memset((char*)&data[16], 0, 18+64+64);
        ourname.copyToUTF8((char*)&data[16], 18);
        ourname.copyToUTF8((char*)&data[34], 64);
        sprintf((char*)&data[98], "NodeReport not implemented yet");
        memset((char*)&data[162], 0, 28); //NumPorts HL, PortTypes, GoodInput,
        //GoodOutput, SwIn, SwOut, SwVideo, SwMacro, SwRemote, Spare(x3)
        data[190] = 1; //Style
        Array<MACAddress> macs = MACAddress::getAllAddresses();
        jassert(macs.size() >= 1);
        const uint8_t *ourmac = macs[0].getBytes();
        memcpy(&data[191], ourmac, 6); //MAC H----L
        data[197] = localIP.address[0]; //BindIP
        data[198] = localIP.address[1];
        data[199] = localIP.address[2];
        data[200] = localIP.address[3];
        data[201] = 0; //BindIndex
        data[202] = 0b00001110; //Status2
        memset(&data[203], 0, 26);
        //std::cout << "Sending ArtPollReply to " << dest.toString() << "\n";
        SendArtNet(dest, 0x2100, data, 229, false);
        if(pollmode >= 1 && !senderIP.isNull() && !isIPInSubnet(senderIP, dest)){
            //std::cout << "Also sending ArtPollReply to " << senderIP.toString() << "\n";
            SendArtNet(senderIP, 0x2100, data, 229, false);
        }
        delete[] data;
    }
    
    void ReceivedArtPollReply(IPAddress senderIP, uint8_t *pkt, int len){
        if(len < 213){
            std::cout << "ReceivedArtPollReply: packet too short!\n";
            return;
        }
        AS_LOCK_READ();
        ArtNetDevice *dev = nullptr;
        for(int i=0; i<devices.size(); ++i){
            if(devices[i]->ip == senderIP){
                dev = devices[i];
                break;
            }
        }
        if(dev == nullptr){
            AddBlankDevice();
            dev = devices[devices.size() - 1];
            dev->mode = ArtNetDevice::Mode::discovered;
            dev->ip = senderIP;
        }
        IPAddress pktsaysip(pkt[10], pkt[11], pkt[12], pkt[13]);
        if(pktsaysip != dev->ip){
            std::cout << "ReceivedArtPollReply: warning: from IP " << senderIP.toString()
                << " but claims to be device with IP " << pktsaysip.toString() << "!\n";
        }
        dev->fw = ((uint16_t)pkt[16] << 8) | pkt[17];
        dev->net = pkt[18];
        dev->subnet = pkt[19];
        dev->oem = ((uint16_t)pkt[20] << 8) | pkt[21];
        //pkt[22] == UBEA
        dev->status[0] = pkt[23];
        dev->esta = pkt[24] | ((uint16_t)pkt[25] << 8);
        dev->shortname = String((char*)&pkt[26], 18);
        dev->longname = String((char*)&pkt[44], 64);
        dev->nodereport = String((char*)&pkt[108], 64);
        //pkt[172:173] == NumPorts HL
        for(int p=0; p<4; ++p){
            dev->inuni[p]  = (pkt[174+p] & 0x40) ? (pkt[186+p] & 0x0F) : 0x7F;
            dev->outuni[p] = (pkt[174+p] & 0x80) ? (pkt[190+p] & 0x0F) : 0x7F;
        }
        //Ignoring PortTypes type information (other than I/O), GoodInput 178, GoodOutput 182
        //pkt[194:199] == SwVideo, SwMacro, SwRemote, Spare(x3)
        dev->style = static_cast<ArtNetDevice::Style>(pkt[200]);
        dev->mac = MACAddress(&pkt[201]);
        //pkt[207:210] == BindIp
        dev->bindindex = pkt[211];
        dev->status[1] = pkt[212];
    }
    
    class ArtNetReceiver : public Thread {
    public:
        ArtNetReceiver() : Thread("ArtNetReceiver") {}
        virtual ~ArtNetReceiver() {}
        virtual void run() override {
            const int maxpacketsize = 1024;
            uint8_t *packetbuf = new uint8_t[maxpacketsize];
            DatagramSocket recvsock(false);
            recvsock.bindToPort(0x1936);
            recvsock.setEnablePortReuse(true);
            while(!threadShouldExit()){
                while(!threadShouldExit() && recvsock.waitUntilReady(true, 1) == 0);
                if(threadShouldExit()) break;
                String senderIPstr; int port;
                int readbytes = recvsock.read(packetbuf, maxpacketsize, false, senderIPstr, port);
                IPAddress senderIP(senderIPstr);
                if(readbytes <= 0){
                    std::cout << "ArtNetSystem receive error!\n";
                    continue;
                }
                if(port != 0x1936){
                    std::cout << "ArtNetSystem receive: wrong port!\n";
                    continue;
                }
                if(readbytes < 12){
                    std::cout << "ArtNetSystem receive: packet too short!\n";
                    continue;
                }
                if(strncmp((char*)packetbuf, "Art-Net", 7) != 0 || packetbuf[7] != 0){
                    std::cout << "ArtNetSystem receive: bad Art-Net header!\n";
                    continue;
                }
                uint16_t opcode = *(uint16*)&packetbuf[8];
                if(opcode != 0x2100 && (packetbuf[10] != 0 || packetbuf[11] != 14)){
                    std::cout << "ArtNetSystem receive: bad protocol revision!\n";
                    continue;
                }
                //std::cout << "Received Art-Net packet opcode 0x" << hex(opcode) << "\n";
                if(opcode == 0x2000){
                    SendArtPollReply(senderIP);
                }else if(opcode == 0x2100){
                    ReceivedArtPollReply(senderIP, packetbuf, readbytes);
                }
            }
            delete[] packetbuf;
            recvsock.shutdown();
        }
    };
    static ArtNetReceiver *receiver = nullptr;
    
    void Init(ValueTree as_node){
        AS_LOCK_WRITE();
        if(sendsock != nullptr){
            std::cout << "ArtNetSystem nultiply initted!\n";
            jassertfalse;
            return;
        }
        pollmode = 2;
        if(as_node.isValid()){
            pollmode = as_node.getProperty(idPollMode, 2);
            for(int i=0; i<as_node.getNumChildren(); ++i){
                devices.add(new ArtNetDevice(as_node.getChild(i)));
            }
        }
        IPAddress localIP = IPAddress::getLocalAddress();
        dhcpBroadcast = IPAddress::getInterfaceBroadcastAddress(localIP);
        std::cout << "Local IP: " << localIP.toString() << ", broadcast " << dhcpBroadcast.toString() << "\n";
        //
        sendsock = new DatagramSocket(true);
        sendsock->bindToPort(0x1936);
        sendsock->setEnablePortReuse(true);
        receiver = new ArtNetReceiver();
        receiver->startThread();
        poller = new Poller();
        SendArtPollReply(IPAddress());
    }
    void Finalize(){
        AS_LOCK_WRITE();
        delete poller; poller = nullptr;
        receiver->stopThread(10);
        delete receiver; receiver = nullptr;
        sendsock->shutdown();
        delete sendsock; sendsock = nullptr;
        devices.clear();
    }
    
    ValueTree Save(){
        AS_LOCK_READ();
        ValueTree ret(idArtNetSystem);
        ret.setProperty(idPollMode, pollmode, nullptr);
        for(int i=0; i<devices.size(); ++i){
            ret.addChild(devices[i]->Save(), -1, nullptr);
        }
        return ret;
    }
    
}
