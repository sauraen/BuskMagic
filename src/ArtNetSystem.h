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

#pragma once
#include "JuceHeader.h"

namespace ArtNetSystem {

    struct ArtNetDevice {
        enum class Mode : uint8_t { manual = 0, discovered = 1, lost = 2 };
        Mode mode;
        enum class Style : uint8_t { node = 0, controller = 1, media = 2, route = 3, backup = 4, config = 5, visual = 6 };
        Style style;
        
        uint8_t status[2];
        uint16_t oem;
        uint16_t esta;
        uint16_t fw;
        
        uint8_t net;
        uint8_t subnet;
        uint8_t inuni[4]; //0x7F for not present
        uint8_t outuni[4]; //0x7F for not present
        
        bool map;
        uint8_t map_net;
        uint8_t map_subnet;
        uint8_t map_inuni[4]; //0x7F for not present
        uint8_t map_outuni[4]; //0x7F for not present
        
        uint8_t bindindex;
        IPAddress ip;
        MACAddress mac;
        
        String shortname;
        String longname;
        String nodereport;
        
        void UpdateFromArtPollReply(const uint8_t *data, size_t len);
        String GetTableRow();
        String GetLongDescription();
        
        ArtNetDevice();
    };

    void Init();
    void Finalize();
    
    void Load(ValueTree v);
    ValueTree Save();
    
    bool IsPolling();
    void EnablePolling(bool enabled);
    
    int NumDevices();
    ArtNetDevice *GetDevice(int d);
    void AddBlankDevice();
    void RemoveDevice(int d);
    
    uint32_t ParseUniverseText(String unitxt);
    
    void ChangeDeviceUniverses(int d, uint8_t net, uint8_t subnet, const uint8_t *inuni, const uint8_t *outuni);
    
    void SendDMX512(uint16_t universe, const uint8_t (&buf)[512]);
}
