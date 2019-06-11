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

#include <cstring>

namespace ArtNetSystem {

    String ArtNetDevice::GetTableRow(){
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
    
    String ArtNetDevice::GetLongDescription(){
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
        ret += ": " + longname;
        return ret;
    }
    
    ArtNetDevice::ArtNetDevice() : mode(Mode::manual), style(Style::node),
        status{0xFF, 0xFF}, oem(0x0000), esta(0x4F4E), fw(0x0000),
        net(0x00), subnet(0x0), map_net(0x00), map_subnet(0x0), map(false), 
        inuni{0x7F, 0x7F, 0x7F, 0x7F}, outuni{0x7F, 0x7F, 0x7F, 0x7F},
        map_inuni{0x7F, 0x7F, 0x7F, 0x7F}, map_outuni{0x7F, 0x7F, 0x7F, 0x7F},
        bindindex(0), artdmx_sequence(1),
        shortname("<Device short name>"), 
        longname("<Device long name>"), 
        nodereport("(Have not received ArtPollReply from this device)") {}
    
    static OwnedArray<ArtNetDevice> devices;
    int NumDevices() { return devices.size(); }
    ArtNetDevice *GetDevice(int d) { return devices[d]; }
    
    void AddBlankDevice(){
        devices.add(new ArtNetDevice());
    }
    void RemoveDevice(int d){
        devices.remove(d);
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
    
    static DatagramSocket *sock = nullptr;
    
    class ArtNetReceiver : public Thread {
    public:
        ArtNetReceiver() : Thread("ArtNetReceiver") {}
        virtual ~ArtNetReceiver() {}
        virtual void run() override {
            const size_t maxpacketsize = 1024;
            uint8_t *packetbuf = new uint8_t[maxpacketsize];
            while(!threadShouldExit()){
                while(!threadShouldExit() && sock->waitUntilReady(true, 1) == 0);
                IPAddress senderIP; int port;
                int readbytes = sock->read(packetbuf, maxpacketsize, false, senderIP, port);
                if(readbytes <= 0){
                    std::cout << "ArtNetSystem receive error!\n";
                    continue;
                }
                if(port != 0x1936){
                    std::cout << "ArtNetSystem received data on wrong port!\n";
                    continue;
                }
                //TODO
            }
        }
    };
    static ArtNetReceiver *receiver = nullptr;
    
    static bool polling;
    bool IsPolling() { return polling; }
    void EnablePolling(bool enabled) { polling = enabled; /*TODO timer*/ }
    
    static void SendArtNet(IPAddress dest, uint16_t opcode, const uint8_t *data, size_t len){
        uint8_t *buf = new uint8_t[12+len];
        sprintf((char*)buf, "Art-Net");
        buf[7] = 0;
        *(uint16_t*)&buf[8] = opcode;
        buf[10] = 0;
        buf[11] = 14;
        memcpy(&buf[12], data, len);
        assert(sock != nullptr);
        int res = sock->waitUntilReady(false, 5);
        if(res != 1){
            std::cout << "Socket not ready to write!\n";
        }else{
            res = sock->write(dest, 0x1936, buf, 12+len);
            if(res <= 0){
                std::cout << "Error sending packet!\n";
            }else if(res != 12+len){
                std::cout << "Failed to send whole packet!\n";
            }
        }
        delete[] buf;
    }
    
    void ChangeDeviceUniverses(int d, uint8_t net, uint8_t subnet, 
        const uint8_t *inuni, const uint8_t *outuni){
        ArtNetDevice *dev = devices[d];
        if(dev == nullptr) return;
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
        SendArtNet(dev->ip, 0x6000, data, 95);
    }
    
    void SendDMX512(uint16_t universe, const uint8_t *buf512){
        for(int d=0; d<devices.size(); ++d){
            ArtNetDevice *dev = devices[d];
            uint8_t uni = universe & 0xF;
            bool flag = false;
            if(dev->map){
                if(dev->map_net != universe >> 8) continue;
                if(dev->map_subnet != (universe >> 4) & 0xF) continue;
                for(int i=0; i<4; ++i) if(dev->map_outuni[i] == uni) flag = true;
            }else{
                if(dev->net != universe >> 8) continue;
                if(dev->subnet != (universe >> 4) & 0xF) continue;
                for(int i=0; i<4; ++i) if(dev->outuni[i] == uni) flag = true;
            }
            if(!flag) continue;
            uint8_t *data = new uint8_t[518];
            data[0] = dev->artdmx_sequence;
            ++dev->artdmx_sequence;
            if(dev->artdmx_sequence == 0) dev->artdmx_sequence = 1;
            data[1] = 0; //Physical
            data[2] = universe & 0xFF;
            data[3] = (universe >> 8) & 0x7F;
            data[4] = 0x02; //LengthHi, 512
            data[5] = 0x00; //Length, 512
            memcpy(&data[6], buf512, 512);
            SendArtNet(dev->ip, 0x5000, data, 518);
        }
    }
    
    void Init(){
        if(sock != nullptr){
            std::cout << "ArtNetSystem already initted!\n";
            return;
        }
        sock = new DatagramSocket(true);
        sock->bindToPort(0x1936);
        sock->setEnablePortReuse(true);
        receiver = new ArtNetReceiver();
        receiver->startThread();
    }
    void Finalize(){
        receiver->stopThread(10);
        delete receiver; receiver = nullptr;
        sock->shutdown();
        delete sock; sock = nullptr;
    }
    
    void Load(ValueTree v){
        //TODO
    }
    ValueTree Save(){
        //TODO
        return ValueTree();
    }
    
}
