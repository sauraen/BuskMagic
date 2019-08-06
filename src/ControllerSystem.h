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

#include "MIDISystem.h"

class MagicValue {
public:
    MagicValue() : mugglevalue(0.0f), chan(nullptr) {}
    ~MagicValue() {}
    
    inline bool IsMagic() const { return chan != nullptr; }
    inline float GetPlainValue() const { return mugglevalue; }
    inline void SetPlainValue(float v) { mugglevalue = v; }
    inline void *GetChannel() const { return chan; }
    inline void SetChannel(void *ch) { chan = ch; }
    
    inline float Evaluate(float angle) const {
        return chan != nullptr ? /*TODO chan->Evaluate(angle)*/0.0f : mugglevalue;
    }
private:
    float mugglevalue;
    void *chan;
};

class Controller {
public:
    Controller();
    virtual ~Controller();
    
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
    
    virtual void HandleMIDI(int port, MidiMessage msg);
    enum MIDISettingType {
        en_on = 0,
        en_off = 1,
        en_toggle = 2,
        en_out_on = 3,
        en_out_off = 4,
        ct_in = 5,
        ct_goto_lo = 6,
        ct_goto_hi = 7,
        ct_out = 8
    };
    virtual String GetMIDISettingStr(MIDISettingType type);
    virtual bool SetMIDISettingFromStr(MIDISettingType type, String str);
    
    virtual float Evaluate(float angle) const = 0;

protected:
    OwnedArray<MIDISetting> midisettings;
    
private:
    String name;
    int group;
    Colour groupColor;
    
    bool enabled;
};

class SimpleController : public Controller {
public:
    SimpleController();
    virtual ~SimpleController();
    
    inline MagicValue *GetValue() { return &value; }
    
    virtual float Evaluate(float angle) const override;
    
private:
    MagicValue value;
};

class ContinuousController : public Controller {
public:
    ContinuousController();
    virtual ~ContinuousController();
    
    inline float GetKnob() { return knob; }
    void SetKnob(float k);
    
    inline MagicValue *GetLoValue() { return &lovalue; } 
    inline MagicValue *GetHiValue() { return &hivalue; }
    
    virtual void HandleMIDI(int port, MidiMessage msg) override;
    virtual String GetMIDISettingStr(MIDISettingType type) override;
    virtual bool SetMIDISettingFromStr(MIDISettingType, String str) override;
    
    virtual float Evaluate(float angle) const override;
    
private:
    MagicValue lovalue, hivalue;
    float knob;
};

namespace ControllerSystem {
    
    
}
