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
#include "gui/TimingWindow.h"
#include "LightingSystem.h"

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

void MIDISetting::Learn(int port_, MidiMessage msg, bool invert){
    if(continuous && msg.isProgramChange()) return;
    uint8_t intype = msg.getRawData()[0] >> 4;
    if(intype == 0xF || intype < 0x8) return;
    port = port_;
    channel = msg.getChannel();
    if(invert && ((intype & 0xE) == 0x8)){
        intype ^= 1; //Swap note on and note off
    }
    type = intype;
    if(type < 0xD){
        note = msg.getRawData()[1];
    }else{
        note = -1;
    }
    if(continuous || !out || type == 0xC){
        vel = -1;
    }else if(type == 0xD){
        vel = msg.getRawData()[1];
    }else{
        vel = msg.getRawData()[2];
    }
    if(out && type == 0x8 && vel >= 0) vel = 0;
}

MIDIUser::MIDIUser(){
    for(int i=0; i<ActionType_SIZE; ++i){
        settings.add(nullptr);
    }
}
MIDIUser::~MIDIUser(){
    MIDISystem::LearnMIDIStop();
    for(int i=0; i<ActionType_SIZE; ++i){
        if(settings[i] != nullptr) delete settings[i];
    }
}
MIDIUser::MIDIUser(const MIDIUser &other){
    for(int i=0; i<ActionType_SIZE; ++i){
        if(other.settings[i] == nullptr){
            settings.add(nullptr);
        }else{
            settings.add(new MIDISetting(*other.settings[i]));
        }
    }
}

String MIDIUser::GetActionName(ActionType t){
    switch(t){
        case in_val: return "In:";
        case in_on: return "On:";
        case in_off: return "Off:";
        case in_toggle: return "Toggle:";
        case in_trigger: return "Trigger:";
        case in_goto_lo: return "Goto Lo:";
        case in_goto_hi: return "Goto Hi:";
        case out_val: return "Out:";
        case out_on: return "Out on:";
        case out_off: return "Out off:";
        default: return "ERROR";
    }
}

void MIDIUser::AddMIDIAction(ActionType t){
    if(t < 0 || t >= ActionType_SIZE) return;
    if(settings[t] != nullptr) return;
    settings.set(t, new MIDISetting(IsOutput(t), IsContinuous(t)));
}
bool MIDIUser::HasMIDIAction(ActionType t){
    if(t < 0 || t >= ActionType_SIZE) return false;
    return settings[t] != nullptr;
}
String MIDIUser::GetMIDISettingStr(ActionType t){
    if(t < 0 || t >= ActionType_SIZE) return "ERROR";
    if(settings[t] == nullptr) return "ERROR";
    return settings[t]->GetStr();
}
bool MIDIUser::SetMIDISettingFromStr(ActionType t, String str){
    if(t < 0 || t >= ActionType_SIZE) return "ERROR";
    if(settings[t] == nullptr) return "ERROR";
    return settings[t]->FromStr(str);
}

void MIDIUser::SendMIDIAction(ActionType t, int val){
    if(t < 0 || t >= ActionType_SIZE) return;
    if(settings[t] == nullptr) return;
    settings[t]->SendMsg(val);
}

void MIDIUser::HandleMIDI(int port, MidiMessage msg){
    for(int i=0; i<ActionType_SIZE; ++i){
        ActionType action = static_cast<ActionType>(i);
        if(settings[i] == nullptr) continue;
        if(IsOutput(action)) continue;
        if(settings[i]->Matches(port, msg)){
            int val = settings[i]->GetValueFrom(msg);
            ReceivedMIDIAction(action, val);
        }
    }
}
void MIDIUser::LearnMIDIStart(ActionType t, Refreshable *r){
    learn_target = t;
    refreshable = r;
    MIDISystem::LearnMIDIStart(this);
}
void MIDIUser::LearnMIDI(int port, MidiMessage msg){
    if(learn_target < 0 || learn_target >= ActionType_SIZE || settings[learn_target] == nullptr){
        jassertfalse;
        return;
    }
    switch(learn_target){
    case out_val:
    case in_val:
        settings[out_val]->Learn(port, msg, false); 
        settings[in_val]->Learn(port, msg, false); 
        break;
    case out_on:
    case in_on:
        settings[out_on]->Learn(port, msg, false);
        settings[in_on]->Learn(port, msg, false);
        settings[out_off]->Learn(port, msg, true);
        settings[in_off]->Learn(port, msg, true);
        break;
    case out_off:
    case in_off:
        settings[out_off]->Learn(port, msg, false);
        settings[in_off]->Learn(port, msg, false);
        settings[out_on]->Learn(port, msg, true);
        settings[in_on]->Learn(port, msg, true);
        break;
    case in_toggle:
    case in_trigger:
        settings[learn_target]->Learn(port, msg, false);
        settings[out_on]->Learn(port, msg, false);
        settings[out_off]->Learn(port, msg, true);
        break;
    default:
        settings[learn_target]->Learn(port, msg, false);
    }
    if(refreshable != nullptr) refreshable->RefreshAfterMIDILearn();
}

namespace MIDISystem {
    
    MIDIUser *learner;
    
    void HandleMIDIInput(int port, const MidiMessage &message){
        if(message.isSysEx() || message.isMetaEvent()) return;
        {
            LS_LOCK_READ();
            if(learner){
                learner->LearnMIDI(port, message);
                learner = nullptr;
                return;
            }
        }
        //std::cout << "MIDI message received port " << port 
        //    << ": " << message.getDescription() << "\n";
        ControllerSystem::HandleMIDI(port, message);
        if(TimingWindow::tw_static != nullptr) TimingWindow::tw_static->HandleMIDI(port, message);
        //TODO handle by other systems
    }
    
    void LearnMIDIStart(MIDIUser *u){
        LS_LOCK_WRITE();
        learner = u;
    }
    void LearnMIDIStop(){
        LS_LOCK_WRITE();
        learner = nullptr;
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
        learner = nullptr;
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
