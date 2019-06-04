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

#include <vector>

namespace MIDISystem {
    
    void HandleMIDIInput(int port, const MidiMessage &message){
        std::cout << "MIDI message received port " << port << ": " << message.getDescription() << "\n"; //TODO
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
        //nothing for now
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
    
    int NumInPorts() { return inports.size(); }
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
    
    int NumOutPorts() { return outports.size(); }
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
        SendInternal(p, MidiMessage::noteOff(c+1, n, (uint8_t)v));
    }
    void SendNoteOn(int p, int c, int n, int v){
        SendInternal(p, MidiMessage::noteOn(c+1, n, (uint8_t)v));
    }
    void SendPolyAftertouch(int p, int c, int n, int a){
        SendInternal(p, MidiMessage::aftertouchChange(c+1, n, a));
    }
    void SendCC(int p, int c, int cc, int v){
        SendInternal(p, MidiMessage::controllerEvent(c+1, cc, v));
    }
    void SendProgChange(int p, int c, int prog){
        SendInternal(p, MidiMessage::programChange(c+1, prog));
    }
    void SendChanAftertouch(int p, int c, int a){
        SendInternal(p, MidiMessage::channelPressureChange(c+1, a));
    }
    void SendPitchBend(int p, int c, int pb){
        SendInternal(p, MidiMessage::pitchWheel(c+1, pb));
    }
}
