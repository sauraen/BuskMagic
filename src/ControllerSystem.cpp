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

#include "ControllerSystem.h"

namespace ControllerSystem {
     
     namespace {
         ReadWriteLock mutex;
     }
     
}

#define CTRLRSYS_LOCK_READ() const ScopedReadLock rlock(ControllerSystem::mutex)
#define CTRLRSYS_LOCK_WRITE() const ScopedWriteLock wlock(ControllerSystem::mutex)

Controller::Controller() 
    : x(0), y(0), color(Colours::red), nostate(false),
      name("New Controller"), group(0), groupColor(Colours::lightgrey),
      enabled(false)
{
    midisettings.add(new MIDISetting(false, false)); //en_on
    midisettings.add(new MIDISetting(false, false)); //en_off
    midisettings.add(new MIDISetting(false, false)); //en_toggle
    midisettings.add(new MIDISetting(true,  false)); //en_out_on
    midisettings.add(new MIDISetting(true,  false)); //en_out_off
}

Controller::~Controller() {}

String Controller::GetName(){
    CTRLRSYS_LOCK_READ();
    return String(name); //This is because String is not thread-safe
}
void Controller::SetName(String n){
    CTRLRSYS_LOCK_WRITE();
    name = n;
}

void Controller::SetGroup(int g){
    CTRLRSYS_LOCK_WRITE();
    group = g;
    //TODO copy group color from other members
}
void Controller::SetGroupColor(Colour col){
    CTRLRSYS_LOCK_WRITE();
    groupColor = col;
    //TODO copy group color to other members
}

void Controller::HandleMIDI(int port, MidiMessage msg){
    CTRLRSYS_LOCK_READ();
    if(midisettings[en_on]->Matches(port, msg)){
        if(enabled) return;
        CTRLRSYS_LOCK_WRITE();
        enabled = true;
        midisettings[en_out_on]->SendMsg();
    }else if(midisettings[en_off]->Matches(port, msg)){
        if(!enabled) return;
        CTRLRSYS_LOCK_WRITE();
        enabled = false;
        midisettings[en_out_off]->SendMsg();
    }else if(midisettings[en_off]->Matches(port, msg)){
        CTRLRSYS_LOCK_WRITE();
        if(enabled){
            enabled = false;
            midisettings[en_out_off]->SendMsg();
        }else{
            enabled = true;
            midisettings[en_out_on]->SendMsg();
        }
    }
}

String Controller::GetMIDISettingStr(MIDISettingType type){
    CTRLRSYS_LOCK_READ();
    if(type > en_out_off || type < 0){
        std::cout << "Invalid usage of Controller::GetMIDISettingStr()!\n";
        return "Error";
    }
    return midisettings[type]->GetStr();
}

bool Controller::SetMIDISettingFromStr(MIDISettingType, String str){
    CTRLRSYS_LOCK_WRITE();
    if(type > en_out_off || type < 0){
        std::cout << "Invalid usage of Controller::SetMIDISettingFromStr()!\n";
        return false;
    }
    return midisettings[type]->FromStr(str);
}

SimpleController::SimpleController() : Controller() {}
SimpleController::~SimpleController() {}

void SimpleController::Evaluate(float angle) {
    CTRLRSYS_LOCK_READ();
    return value->Evaluate(angle);
}

ContinuousController::ContinuousController() : Controller(), knob(0.0f) {
    midisettings.add(new MIDISetting(false, true )); //ct_in
    midisettings.add(new MIDISetting(false, false)); //ct_goto_lo
    midisettings.add(new MIDISetting(false, false)); //ct_goto_hi
    midisettings.add(new MIDISetting(true,  true )); //ct_out
}

ContinuousController::~ContinuousController() {}

void ContinuousController::HandleMIDI(int port, MidiMessage msg) {
    CTRLRSYS_LOCK_READ();
    Controller::HandleMIDI(port, msg);
    if(midisettings[ct_in]->Matches(port, msg)){
        CTRLRSYS_LOCK_WRITE();
        knob = (float)midisettings[ct_in]->GetValueFrom(msg) / 127.0f;
        jassert(knob >= 0.0f && knob <= 1.0f);
        midisettings[ct_out]->SendMsg((int)(knob * 127.0f));
    }else if(midisettings[ct_goto_lo]->Matches(port, msg)){
        CTRLRSYS_LOCK_WRITE();
        knob = 0.0f;
        midisettings[ct_out]->SendMsg(0);
    }else if(midisettings[ct_goto_hi]->Matches(port, msg)){
        CTRLRSYS_LOCK_WRITE();
        knob = 1.0f;
        midisettings[ct_out]->SendMsg(127);
    }
}
String ContinuousController::GetMIDISettingStr(MIDISettingType type) {
    CTRLRSYS_LOCK_READ();
    if(type <= en_out_off) return Controller::GetMIDISettingStr(type);
    if(type > ct_out){
        std::cout << "Invalid usage of ContinuousController::GetMIDISettingStr()!\n";
        return "Error";
    }
    return midisettings[type]->GetStr();
}
bool ContinuousController::SetMIDISettingFromStr(MIDISettingType, String str) {
    CTRLRSYS_LOCK_WRITE();
    if(type <= en_out_off) return Controller::SetMIDISettingFromStr(type, str);
    if(type > ct_out){
        std::cout << "Invalid usage of ContinuousController::SetMIDISettingFromStr()!\n";
        return false;
    }
    return midisettings[type]->FromStr(str);
}

//TODO evaluate

namespace ControllerSystem {
    
    
    
}
