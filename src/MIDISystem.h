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

class MIDISetting {
public:
    MIDISetting(bool out_, bool continuous_);
    ~MIDISetting();
    MIDISetting(const MIDISetting &other);
    
    static String GetHelpText();
    
    String GetStr();
    bool FromStr(String str);
    
    bool Matches(int port_, MidiMessage msg);
    int GetValueFrom(MidiMessage msg); //Assumes it matches!
    void SendMsg(int valforcontinuous=-1);
    
    void Learn(int port_, MidiMessage msg, bool invert);
    
    /*
    enum Type {
        en_on = 0,
        en_off = 1,
        en_toggle = 2,
        en_out_on = 3,
        en_out_off = 4,
        ct_in = 5,
        ct_goto_lo = 6,
        ct_goto_hi = 7,
        ct_out = 8,
        tr_trig = 9,
        tr_out_on = 10,
        tr_out_off = 11
    };
    */
private:
    bool out, continuous;
    int port, channel, type, note, vel;
};

class MIDIUser {
public:
    MIDIUser();
    virtual ~MIDIUser();
    MIDIUser(const MIDIUser &other);
    
    class Refreshable {
    public:
        virtual ~Refreshable() {}
        virtual void RefreshAfterMIDILearn() = 0;
    };
    
    enum ActionType : uint32_t {
        in_val,
        in_on,
        in_off,
        in_toggle,
        in_trigger,
        in_goto_lo,
        in_goto_hi,
        out_val,
        out_on,
        out_off,
        ActionType_SIZE
    };
    inline static bool IsOutput(ActionType t) { return t >= out_val; }
    inline static bool IsContinuous(ActionType t) { return t == out_val || t == in_val; }
    inline static bool IsKnobRelated(ActionType t) { return IsContinuous(t) || t == in_goto_lo || t == in_goto_hi; }
    static String GetActionName(ActionType t);
    
    void AddMIDIAction(ActionType t);
    bool HasMIDIAction(ActionType t);
    String GetMIDISettingStr(ActionType t);
    bool SetMIDISettingFromStr(ActionType t, String str);
    
    virtual void ReceivedMIDIAction(ActionType t, int val) = 0;
    void SendMIDIAction(ActionType t, int val = 0);
    
    void HandleMIDI(int port, MidiMessage msg);
    void LearnMIDIStart(ActionType t, Refreshable *ref);
    void LearnMIDI(int port, MidiMessage msg);
    
private:
    Array<MIDISetting*> settings;
    ActionType learn_target;
    Refreshable *refreshable;
};

namespace MIDISystem {
    
    void Init(ValueTree ms_node = ValueTree());
    void Finalize();
    ValueTree Save();
    
    int NumInPorts();
    void AddInPort();
    void RemoveInPort(int p);
    int InPortDeviceNumber(int p);
    String InPortDeviceName(int p);
    void AssignInDevice(int d, int p);
    void UnassignInPort(int p);
    
    int NumOutPorts();
    void AddOutPort();
    void RemoveOutPort(int p);
    int OutPortDeviceNumber(int p);
    String OutPortDeviceName(int p);
    void AssignOutDevice(int d, int p);
    void UnassignOutPort(int p);
    
    void SendNoteOff(int p, int c, int n, int v);
    void SendNoteOn(int p, int c, int n, int v);
    void SendPolyAftertouch(int p, int c, int n, int a);
    void SendCC(int p, int c, int cc, int v);
    void SendProgChange(int p, int c, int prog);
    void SendChanAftertouch(int p, int c, int a);
    void SendPitchBend(int p, int c, int pb);
    
    void LearnMIDIStart(MIDIUser *u);
    void LearnMIDIStop();
}
