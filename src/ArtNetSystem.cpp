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
        ret += String::formatted(" %3d.%3d.%3d.%3d ", 
            ip.address[0], ip.address[1], ip.address[2], ip.address[3]);
        ret += String::toHexString(bindindex) + " ";
        ret += String::toHexString(map ? map_net : net) + ".";
        ret += String::toHexString(map ? map_subnet : subnet) + " ";
        for(int i=0; i<4; ++i){
            uint8_t u = map ? map_inuni[i] : inuni[i];
            if(u > 0x0F) ret += "-";
            else ret += String::toHexString(u);
            if(i != 3) ret += ",";
        }
        ret += "/";
        for(int i=0; i<4; ++i){
            uint8_t u = map ? map_outuni[i] : outuni[i];
            if(u > 0x0F) ret += "-";
            else ret += String::toHexString(u);
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
        inuni({0xFF, 0xFF, 0xFF, 0xFF}), outuni({0xFF, 0xFF, 0xFF, 0xFF}),
        map(false), bindindex(0), 
        shortname("<unset>"), longname("<unset>"), nodereport("<status>") {}
    
    void Init(){
        //TODO
    }
    void Finalize(){
        //TODO
    }
    
    void Load(ValueTree v){
        //TODO
    }
    ValueTree Save(){
        //TODO
    }
    
    static bool polling;
    bool IsPolling() { return polling; }
    void EnablePolling(bool enabled) { polling = enabled; /*TODO timer*/ }
    
    OwnedArray<ArtNetDevice> devices;
    int NumDevices() { return devices.size(); }
    ArtNetDevice *GetDevice(int d) { return devices[d]; }
    
    void AddBlankDevice(){
        devices.add(new ArtNetDevice());
    }
    void RemoveDevice(int d){
        devices.remove(d);
    }
}
