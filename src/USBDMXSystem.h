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
    
    int NumSlots();
    void AddSlot();
    void RemoveSlot(int s);
    String SlotType(int s);
    String SlotName(int s);
    void SetSlotName(int s, String n);
    uint16_t SlotUni(int s);
    void SetSlotUni(int s, uint16_t uni);
    String SlotDescription(int s);
    
    bool IsLoadMapModeType();
    void SetLoadMapMode(bool mapType);
    String GetLoadMapModeHelpText();
    
    void Init(ValueTree us_node = ValueTree());
    void Finalize();
    ValueTree Save();
    
}
