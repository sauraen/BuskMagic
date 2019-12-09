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
#include "Common.h"

namespace USBDMXSystem {
    
    uint32_t NumDevices();
    String DeviceDescription(uint32_t d);
    String DeviceFullInfo(uint32_t d);
    bool DeviceIsSupported(uint32_t d);
    void RefreshDeviceList();
    void MapDevice(uint32_t d, uint32_t s);
    void UnmapDevice(uint32_t s);
    
    uint32_t NumSlots();
    void AddSlot();
    void RemoveSlot(uint32_t s);
    String SlotType(uint32_t s);
    String SlotStatus(uint32_t s);
    String SlotName(uint32_t s);
    void SetSlotName(uint32_t s, String n);
    uint16_t SlotUni(uint32_t s);
    void SetSlotUni(uint32_t s, uint16_t uni);
    uint16_t SlotChans(uint32_t s);
    void SetSlotChans(uint32_t s, uint16_t chans);
    String GetChansHelpText();
    String SlotDescription(uint32_t s);
    
    void GetNeededUniversesSorted(Array<uint16_t> &list);
    void SendDMX512(uint16_t universe, const uint8_t *buf512);
    
    bool IsLoadMapModeType();
    void SetLoadMapMode(bool mapType);
    String GetLoadMapModeHelpText();
    
    void Init(ValueTree us_node = ValueTree());
    void Finalize();
    ValueTree Save();
    
}
