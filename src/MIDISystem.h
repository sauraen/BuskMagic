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
private:
    bool out, continuous;
    int port, channel, type, note, vel;
};

namespace MIDISystem {
    
    void Init();
    void Finalize();
    
    void Load(ValueTree v);
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
}
