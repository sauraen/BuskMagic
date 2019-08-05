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


class Controller {
public:
    Controller();
    ~Controller();
    
    int x, y;
    Colour color;
    bool nostate;
    
    String GetName() const;
    void SetName(String n);
    inline int GetGroup() const { return group; }
    void SetGroup(int g);
    inline Colour GetGroupColor() const { return groupColor; }
    void SetGroupColor(Colour col);
    
    inline bool IsEnabled() const { return enabled; }
    void SetEnabled(bool en);
    
    virtual void HandleMIDI(MidiMessage msg);
    enum MIDISettingType {
        en_on = 0,
        en_off = 1,
        en_toggle = 2,
        en_out_on = 3,
        en_out_off = 4,
        ct_in = 5,
        ct_lo = 6,
        ct_hi = 7,
        ct_out = 8
    };
    virtual String GetMIDISettingStr(MIDISettingType type);
    virtual bool SetMIDISettingFromStr(MIDISettingType, String str);
    
    virtual void Evaluate() = 0;

protected:
    ReadWriteLock mutex;
    OwnedArray<MIDISetting> en_msets;
    
private:
    String name;
    int group;
    Colour groupColor;
    
    bool enabled;
    
};

namespace ControllerSystem {
    
    
}
