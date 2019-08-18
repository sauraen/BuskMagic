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

#include "LightingSystem.h"
#include "ChannelSystem.h"

#include "gui/MatrixEditor.h"
#include "gui/Controller/ControllerCmps.h"
#include "gui/Controller/ControllerCanvas.h"


static void RefreshMatrixEditor(bool invalidate){
    MatrixEditor::mtxed_static->RefreshControllerFilters();
    if(invalidate) MatrixEditor::mtxed_static->RefreshVisibleControllerSet();
}

MagicValue::MagicValue(Controller *parent) 
    : controller(parent), mugglevalue(0.0f), chan(nullptr) {}
MagicValue::MagicValue(const MagicValue &other, Controller *newparent) 
    : controller(newparent), mugglevalue(other.mugglevalue), chan(other.chan) {}
void MagicValue::SetLiteral(float v) { 
    mugglevalue = v;
    RefreshComponent();
}
void MagicValue::SetChannel(Channel *ch) {
    chan = ch; 
    RefreshComponent();
}
String MagicValue::GetText(){
    return chan != nullptr ? chan->GetLetters() : String(mugglevalue, 2);
}
float MagicValue::Evaluate(float angle) const {
    return chan != nullptr ? chan->Evaluate(angle) : mugglevalue;
}
void MagicValue::RefreshComponent(){
    controller->RefreshComponent();
}

Controller::Controller() 
    : pos(0,0), color(Colours::red), nostate(false),
      name("New Controller Blah blah"), group(0), groupColor(Colours::lightgrey),
      enabled(false)
{
    midisettings.add(new MIDISetting(false, false)); //en_on
    midisettings.add(new MIDISetting(false, false)); //en_off
    midisettings.add(new MIDISetting(false, false)); //en_toggle
    midisettings.add(new MIDISetting(true,  false)); //en_out_on
    midisettings.add(new MIDISetting(true,  false)); //en_out_off
}

Controller::~Controller() {}
Controller::Controller(const Controller &other)
    : pos(other.pos + Point<int>(100,100)), color(other.color), nostate(other.nostate), 
      name(other.name + " 2"), group(other.group), groupColor(other.groupColor),
      enabled(false), component(nullptr)
{
    for(int i=0; i<other.midisettings.size(); ++i){
        midisettings.add(new MIDISetting(*other.midisettings[i]));
    }
}

String Controller::GetName() const{
    LS_LOCK_READ();
    return name;
}
void Controller::SetName(String n){
    LS_LOCK_WRITE();
    name = n;
    RefreshComponent();
    RefreshMatrixEditor(false);
}
void Controller::SetColor(Colour col){
    color = col;
    RefreshComponent();
}

void Controller::SetGroup(int g){
    LS_LOCK_WRITE();
    group = g;
    if(group > 0){
        for(int i=0; i<ControllerSystem::NumControllers(); ++i){
            if(ControllerSystem::GetController(i)->group == group){
                groupColor = ControllerSystem::GetController(i)->groupColor;
                break;
            }
        }
    }
    RefreshComponent();
    RefreshMatrixEditor(false);
}
void Controller::SetGroupColor(Colour col){
    LS_LOCK_WRITE();
    groupColor = col;
    if(group > 0){
        for(int i=0; i<ControllerSystem::NumControllers(); ++i){
            if(ControllerSystem::GetController(i)->group == group){
                ControllerSystem::GetController(i)->groupColor = groupColor;
            }
        }
        ControllerCanvas *canvas = GetCanvas();
        if(canvas != nullptr) canvas->repaint();
    }else{
        RefreshComponent();
    }
}

void Controller::SetEnabled(bool en){
    LS_LOCK_READ();
    if(enabled == en) return;
    enabled = en;
    if(enabled){
        midisettings[en_out_on]->SendMsg();
    }else{
        midisettings[en_out_off]->SendMsg();
    }
    RefreshComponent();
}

void Controller::HandleMIDI(int port, MidiMessage msg){
    LS_LOCK_READ();
    if(midisettings[en_on]->Matches(port, msg)){
        if(enabled) return;
        enabled = true;
        midisettings[en_out_on]->SendMsg();
        RefreshComponent();
    }else if(midisettings[en_off]->Matches(port, msg)){
        if(!enabled) return;
        enabled = false;
        midisettings[en_out_off]->SendMsg();
        RefreshComponent();
    }else if(midisettings[en_toggle]->Matches(port, msg)){
        if(enabled){
            enabled = false;
            midisettings[en_out_off]->SendMsg();
        }else{
            enabled = true;
            midisettings[en_out_on]->SendMsg();
        }
        RefreshComponent();
    }
}

String Controller::GetMIDISettingStr(MIDISettingType type){
    LS_LOCK_READ();
    if(type > en_out_off || type < 0){
        std::cout << "Invalid usage of Controller::GetMIDISettingStr()!\n";
        return "Error";
    }
    return midisettings[type]->GetStr();
}

bool Controller::SetMIDISettingFromStr(MIDISettingType type, String str){
    LS_LOCK_WRITE();
    if(type > en_out_off || type < 0){
        std::cout << "Invalid usage of Controller::SetMIDISettingFromStr()!\n";
        return false;
    }
    return midisettings[type]->FromStr(str);
}

void Controller::RegisterComponent(ControllerCmp *cmp){
    LS_LOCK_WRITE();
    component = cmp;
}
void Controller::RefreshComponent(){
    LS_LOCK_READ();
    if(component != nullptr) component->repaint();
}
ControllerCanvas *Controller::GetCanvas(){
    LS_LOCK_READ();
    if(component == nullptr) return nullptr;
    ControllerCanvas *canvas = component->findParentComponentOfClass<ControllerCanvas>();
    return canvas;
}

SimpleController::SimpleController() : Controller(), value(this) {}
SimpleController::~SimpleController() {}
SimpleController::SimpleController(const SimpleController &other)
    : Controller(other), value(other.value, this) {}

float SimpleController::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Not locking because channel evaluation will lock
    return value.Evaluate(angle);
}

ContinuousController::ContinuousController() 
    : Controller(), lovalue(this), hivalue(this), knob(0.0f) {
    midisettings.add(new MIDISetting(false, true )); //ct_in
    midisettings.add(new MIDISetting(false, false)); //ct_goto_lo
    midisettings.add(new MIDISetting(false, false)); //ct_goto_hi
    midisettings.add(new MIDISetting(true,  true )); //ct_out
}

ContinuousController::~ContinuousController() {}
ContinuousController::ContinuousController(const ContinuousController &other)
    : Controller(other), lovalue(other.lovalue, this), 
      hivalue(other.hivalue, this), knob(other.knob) {}

void ContinuousController::SetKnob(float k){
    LS_LOCK_WRITE();
    knob = k;
    midisettings[ct_out]->SendMsg((int)(knob * 127.0f));
}

void ContinuousController::HandleMIDI(int port, MidiMessage msg) {
    LS_LOCK_READ();
    Controller::HandleMIDI(port, msg);
    if(midisettings[ct_in]->Matches(port, msg)){
        knob = (float)midisettings[ct_in]->GetValueFrom(msg) / 127.0f;
        jassert(knob >= 0.0f && knob <= 1.0f);
        midisettings[ct_out]->SendMsg((int)(knob * 127.0f));
        RefreshComponent();
    }else if(midisettings[ct_goto_lo]->Matches(port, msg)){
        knob = 0.0f;
        midisettings[ct_out]->SendMsg(0);
        RefreshComponent();
    }else if(midisettings[ct_goto_hi]->Matches(port, msg)){
        knob = 1.0f;
        midisettings[ct_out]->SendMsg(127);
        RefreshComponent();
    }
}
String ContinuousController::GetMIDISettingStr(MIDISettingType type) {
    LS_LOCK_READ();
    if(type <= en_out_off) return Controller::GetMIDISettingStr(type);
    if(type > ct_out){
        std::cout << "Invalid usage of ContinuousController::GetMIDISettingStr()!\n";
        return "Error";
    }
    return midisettings[type]->GetStr();
}
bool ContinuousController::SetMIDISettingFromStr(MIDISettingType type, String str) {
    LS_LOCK_WRITE();
    if(type <= en_out_off) return Controller::SetMIDISettingFromStr(type, str);
    if(type > ct_out){
        std::cout << "Invalid usage of ContinuousController::SetMIDISettingFromStr()!\n";
        return false;
    }
    return midisettings[type]->FromStr(str);
}

float ContinuousController::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Not locking because channel evaluation will lock
    float l = lovalue.Evaluate(angle);
    float h = hivalue.Evaluate(angle);
    return (l * (1.0f - knob)) + (h * knob);
}

namespace ControllerSystem {
    
    OwnedArray<Controller> ctrlrs;
    
    int NumControllers() { return ctrlrs.size(); }
    Controller *GetController(int i){
        LS_LOCK_READ();
        if(i < 0 || i >= ctrlrs.size()){
            jassertfalse;
            return nullptr;
        }
        return ctrlrs[i];
    }
    SimpleController *AddSimpleController(){
        LS_LOCK_WRITE();
        SimpleController *sc = new SimpleController();
        ctrlrs.add(sc);
        RefreshMatrixEditor(true);
        return sc;
    }
    ContinuousController *AddContinuousController(){
        LS_LOCK_WRITE();
        ContinuousController *cc = new ContinuousController();
        ctrlrs.add(cc);
        RefreshMatrixEditor(true);
        return cc;
    }
    Controller *DuplicateController(Controller *orig){
        LS_LOCK_WRITE();
        Controller *n;
        if(SimpleController *sc = dynamic_cast<SimpleController*>(orig)){
            n = new SimpleController(*sc);
        }else if(ContinuousController *cc = dynamic_cast<ContinuousController*>(orig)){
            n = new ContinuousController(*cc);
        }else{
            jassertfalse;
            return nullptr;
        }
        RefreshMatrixEditor(true);
        ctrlrs.add(n);
        return n;
    }
    void RemoveController(Controller *ctrlr){
        LS_LOCK_WRITE();
        ChannelSystem::RemoveAllPhasorsForController(ctrlr);
        ctrlrs.removeObject(ctrlr, true);
        RefreshMatrixEditor(true);
    }
    
    void ChangeControllerOrder(int orig, int newpos){
        LS_LOCK_WRITE();
        ctrlrs.move(orig, newpos);
        ChannelSystem::SortAllChannelPhasors();
        RefreshMatrixEditor(true);
    }
    
    void RemoveAllMagicValuesForChannel(Channel *chn){
        LS_LOCK_WRITE();
        for(int i=0; i<ctrlrs.size(); ++i){
            if(SimpleController *sc = dynamic_cast<SimpleController*>(ctrlrs[i])){
                if(sc->GetValue()->GetChannel() == chn){
                    sc->GetValue()->SetChannel(nullptr);
                }
            }else if(ContinuousController *cc = dynamic_cast<ContinuousController*>(ctrlrs[i])){
                if(cc->GetLoValue()->GetChannel() == chn){
                    cc->GetLoValue()->SetChannel(nullptr);
                }
                if(cc->GetHiValue()->GetChannel() == chn){
                    cc->GetHiValue()->SetChannel(nullptr);
                }
            }else{
                jassertfalse;
            }
        }
    }
    
    void HandleMIDI(int port, MidiMessage msg){
        LS_LOCK_READ();
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->HandleMIDI(port, msg);
        }
    }
    
}
