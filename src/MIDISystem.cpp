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

#include "MIDISystem.h"

#include "ControllerSystem.h"

#include <vector>

MIDISetting::MIDISetting(bool out_, bool continuous_)
    : out(out_), continuous(continuous_), 
      port(-1), channel(-1), type(-1), note(60), vel(-1) {}

MIDISetting::~MIDISetting() {}
MIDISetting::MIDISetting(const MIDISetting &other)
    : out(other.out), continuous(other.continuous),
      port(other.port), channel(other.channel), type(other.type),
      note(other.note), vel(other.vel) {}

String MIDISetting::GetHelpText(){
    return "MIDI setting text: P.C.CmdType.N.V\n"
           "-- P: port\n"
           "-- C: channel (1-16)\n"
           "-- CmdType: NoteOff, NoteOn, PolyAft, CC, Prog,\n"
           "            ChnAft, or PitchB\n"
           "-- N: note or CC number\n"
           "-- V: velocity or value\n"
           "X in a field means \"any\"\n"
           "\n"
           "Examples:\n"
           "1.X.NoteOff.60.X -- for a button input\n"
           "2.5.NoteOn.72.H -- for a button input (H = high = 64-127,\n"
           "                   L = low = 0-63)\n"
           "X.X.CC.70 -- for a continuous input (note: no V, V will\n"
           "             be the continuous value)\n"
           "2.16.PolyAft.80.113 -- for a strange-but-legal button output\n"
           "                       (X/H/L not allowed in outputs)\n"
           "X.1.Prog.5 -- for a button input or output (Prog has no V)\n"
           "X.1.ChnAft -- for a continuous input or output (ChnAft has no N)\n"
           "X.1.PitchB -- for a continuous input or output (PitchB has no N)";
}

String MIDISetting::GetStr() {
    if(type < 0) return ""; //No message
    String ret = (port < 0 ? "X" : String(port+1)) + ".";
    ret += (channel < 0 ? "X" : String(channel)) + ".";
    switch(type){
        case 0x8: ret += "NoteOff"; break;
        case 0x9: ret += "NoteOn";  break;
        case 0xA: ret += "PolyAft"; break;
        case 0xB: ret += "CC";      break;
        case 0xC: ret += "Prog";    break;
        case 0xD: ret += "ChnAft";  break;
        case 0xE: ret += "PitchB";  break;
        default:  ret += "Error";
    }
    if(type < 0xD) ret += "." + (note < 0 ? "X" : String(note));
    if(type != 0xC && !continuous){
             if(vel == -1) ret += ".X";
        else if(vel == -2) ret += ".H";
        else if(vel == -3) ret += ".L";
        else ret += "." + String(vel);
    }
    return ret;
}

bool MIDISetting::FromStr(String str) {
    type = -1; //Set to "no message" before beginning
    if(str.isEmpty()) return true; //Empty is valid--no message
    int port_, channel_, type_, note_, vel_;
    StringArray tk = StringArray::fromTokens(str.trim().toLowerCase(), ".", "");
    if(tk.size() < 3) return false;
    if(tk[0] == "x" && !out){
        port_ = -1;
    }else{
        if(!isInt(tk[0], false)) return false;
        port_ = tk[0].getIntValue();
        if(port_ == 0) return false;
        --port_;
    }
    if(tk[1] == "x" && !out){
        channel_ = -1;
    }else{
        if(!isInt(tk[1], false)) return false;
        channel_ = tk[1].getIntValue();
        if(channel_ == 0) return false;
        if(channel_ > 16) return false;
    }
         if(tk[2] == "noteoff") type_ = 0x8;
    else if(tk[2] == "noteon" ) type_ = 0x9;
    else if(tk[2] == "polyaft") type_ = 0xA;
    else if(tk[2] == "cc"     ) type_ = 0xB;
    else if(tk[2] == "prog"   ) type_ = 0xC;
    else if(tk[2] == "chnaft" ) type_ = 0xD;
    else if(tk[2] == "pitchb" ) type_ = 0xE;
    else return false;
    if(type_ == 0xC && continuous) return false;
    int t = 3;
    if(type_ < 0xD){
        if(tk.size() <= t) return false;
        if(tk[t] == "x" && !out){
            note_ = -1;
        }else{
            if(!isInt(tk[t], false)) return false;
            note_ = tk[t].getIntValue();
            if(note_ > 127) return false;
        }
        t = 4;
    }else{
        note_ = -1;
    }
    if(type_ != 0xC && !continuous){
        if(tk.size() <= t) return false;
        if(tk[t] == "x" && !out){
            vel_ = -1;
        }else if(tk[t] == "h" && !out){
            vel_ = -2;
        }else if(tk[t] == "l" && !out){
            vel_ = -3;
        }else{
            if(!isInt(tk[t], false)) return false;
            vel_ = tk[t].getIntValue();
            if(vel_ > 127) return false;
        }
        ++t;
    }else{
        vel_ = -1;
    }
    if(t != tk.size()) return false;
    port = port_;
    channel = channel_;
    type = type_;
    note = note_;
    vel = vel_;
    return true;
}

bool MIDISetting::Matches(int port_, MidiMessage msg){
    if(out){
        std::cout << "Improper use of MIDISetting::Matches on output!\n";
        return false;
    }
    if(type < 0) return false; //No message
    if(port != -1 && port != port_) return false;
    if(channel != -1 && !msg.isForChannel(channel)) return false;
    switch(type){
    case 0x8: if(!msg.isNoteOff(true)) return false; break;
    case 0x9: if(!msg.isNoteOn(false)) return false; break;
    case 0xA: if(!msg.isAftertouch())  return false; break;
    case 0xB: if(!msg.isController())  return false; break;
    case 0xC: if(!msg.isProgramChange()) return false; break;
    case 0xD: if(!msg.isChannelPressure()) return false; break;
    case 0xE: if(!msg.isPitchWheel()) return false; break;
    default: return false;
    }
    if(type < 0xD && note != -1 && note != msg.getRawData()[1]) return false;
    if(type != 0xC && !continuous){
        int byte = type == 0xD ? 1 : 2; //PitchB, byte 2 is MSB
        if(vel == -2 && msg.getRawData()[byte] < 64) return false;
        if(vel == -3 && msg.getRawData()[byte] >= 64) return false;
        if(vel >= 0 && msg.getRawData()[byte] != vel) return false;
    }
    return true;
}

int MIDISetting::GetValueFrom(MidiMessage msg){
    if(out){
        std::cout << "Improper use of MIDISetting::Matches on output!\n";
        return -1;
    }
    if(type < 0 || type == 0xC) return -1;
    return msg.getRawData()[type == 0xD ? 1 : 2];
}

void MIDISetting::SendMsg(int valforcontinuous){
    if(!out){
        std::cout << "Improper use of MIDISetting::SendMsgForValue on input!\n";
        return;
    }
    if(type < 0) return; //No message
    if(continuous && (valforcontinuous < 0 || valforcontinuous > 127)){
        std::cout << "Invalid continuous value in MIDISetting::SendMsgForValue!\n";
        return;
    }
    int v = continuous ? valforcontinuous : vel;
    switch(type){
    case 0x8: MIDISystem::SendNoteOff(port, channel, note, v); return;
    case 0x9: MIDISystem::SendNoteOn(port, channel, note, v); return;
    case 0xA: MIDISystem::SendPolyAftertouch(port, channel, note, v); return;
    case 0xB: MIDISystem::SendCC(port, channel, note, v); return;
    case 0xC: MIDISystem::SendProgChange(port, channel, note); return;
    case 0xD: MIDISystem::SendChanAftertouch(port, channel, v); return;
    case 0xE: MIDISystem::SendPitchBend(port, channel, v << 7); return;
    }
}

namespace MIDISystem {
    
    void HandleMIDIInput(int port, const MidiMessage &message){
        //std::cout << "MIDI message received port " << port 
        //    << ": " << message.getDescription() << "\n";
        ControllerSystem::HandleMIDI(port, message);
        //TODO handle by other systems
    }
    
    struct MIDIInPort {
        MidiInput *device = nullptr;
        int devnum = -1;
    };
    struct MIDIOutPort {
        MidiOutput *device = nullptr;
        int devnum = -1;
    };
    static std::vector<MIDIInPort> inports;
    static std::vector<MIDIOutPort> outports;
    
    class MIDISystemCallback : public MidiInputCallback {
        virtual void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
            for(int i=0; i<inports.size(); ++i){
                if(source == inports[i].device){
                    HandleMIDIInput(i, message);
                    return;
                }
            }
            std::cout << "MIDISystem received incoming message from unregistered device!\n";
        }
    };
    static MIDISystemCallback callback;
    
    void Init(){
        AddInPort();
        AddOutPort();
    }
    void Finalize(){
        for(int i=0; i<inports.size(); ++i){
            if(inports[i].device != nullptr){
                inports[i].device->stop();
                delete inports[i].device;
            }
        }
        inports.clear();
        for(int i=0; i<outports.size(); ++i){
            if(outports[i].device != nullptr) delete outports[i].device;
        }
        outports.clear();
    }
    
    void Load(ValueTree v){
        std::cout << "TODO loading not implemented yet\n";
    }
    ValueTree Save(){
        std::cout << "TODO saving not implemented yet\n";
        return ValueTree();
    }
    
    int NumInPorts() { return (int)inports.size(); }
    void AddInPort() { inports.push_back(MIDIInPort()); }
    void RemoveInPort(int p){
        if(p < 0 || p >= inports.size()) return;
        if(inports[p].device != nullptr){
            inports[p].device->stop();
            delete inports[p].device;
        }
        inports.erase(inports.begin() + p);
    }
    int InPortDeviceNumber(int p){
        if(p < 0 || p >= inports.size()) return -1;
        return inports[p].devnum;
    }
    String InPortDeviceName(int p){
        if(p < 0 || p >= inports.size()) return "[error]";
        if(inports[p].device == nullptr) return "[none]";
        return inports[p].device->getName();
    }
    void AssignInDevice(int d, int p){
        if(p < 0 || p >= inports.size()) return;
        if(inports[p].device != nullptr) return;
        MidiInput *device = MidiInput::openDevice(d, &callback);
        if(device == nullptr) return;
        inports[p].device = device;
        inports[p].devnum = d;
        device->start();
    }
    void UnassignInPort(int p){
        if(p < 0 || p >= inports.size()) return;
        if(inports[p].device == nullptr) return;
        inports[p].device->stop();
        delete inports[p].device;
        inports[p].device = nullptr;
        inports[p].devnum = -1;
    }
    
    int NumOutPorts() { return (int)outports.size(); }
    void AddOutPort() { outports.push_back(MIDIOutPort()); }
    void RemoveOutPort(int p){
        if(p < 0 || p >= outports.size()) return;
        if(outports[p].device != nullptr) delete outports[p].device;
        outports.erase(outports.begin() + p);
    }
    int OutPortDeviceNumber(int p){
        if(p < 0 || p >= outports.size()) return -1;
        return outports[p].devnum;
    }
    String OutPortDeviceName(int p){
        if(p < 0 || p >= outports.size()) return "[error]";
        if(outports[p].device == nullptr) return "[none]";
        return outports[p].device->getName();
    }
    void AssignOutDevice(int d, int p){
        if(p < 0 || p >= outports.size()) return;
        if(outports[p].device != nullptr) return;
        MidiOutput *device = MidiOutput::openDevice(d);
        if(device == nullptr) return;
        outports[p].device = device;
        outports[p].devnum = d;
    }
    void UnassignOutPort(int p){
        if(p < 0 || p >= outports.size()) return;
        if(outports[p].device == nullptr) return;
        delete outports[p].device;
        outports[p].device = nullptr;
        outports[p].devnum = -1;
    }
    
    void SendInternal(int p, const MidiMessage &msg){
        if(p < 0 || p >= outports.size()) return;
        if(outports[p].device == nullptr) return;
        outports[p].device->sendMessageNow(msg);
    }
    void SendNoteOff(int p, int c, int n, int v){
        SendInternal(p, MidiMessage::noteOff(c, n, (uint8_t)v));
    }
    void SendNoteOn(int p, int c, int n, int v){
        SendInternal(p, MidiMessage::noteOn(c, n, (uint8_t)v));
    }
    void SendPolyAftertouch(int p, int c, int n, int a){
        SendInternal(p, MidiMessage::aftertouchChange(c, n, a));
    }
    void SendCC(int p, int c, int cc, int v){
        SendInternal(p, MidiMessage::controllerEvent(c, cc, v));
    }
    void SendProgChange(int p, int c, int prog){
        SendInternal(p, MidiMessage::programChange(c, prog));
    }
    void SendChanAftertouch(int p, int c, int a){
        SendInternal(p, MidiMessage::channelPressureChange(c, a));
    }
    void SendPitchBend(int p, int c, int pb){
        SendInternal(p, MidiMessage::pitchWheel(c, pb));
    }
}
