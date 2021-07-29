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
#include "TimingSystem.h"

#include "gui/MatrixEditor.h"
#include "gui/Controller/ControllerCmps.h"
#include "gui/Controller/ControllerCanvas.h"

static void RefreshMatrixEditor(bool invalidate){
    MatrixEditor::mtxed_static->RefreshControllerFilters();
    if(invalidate) MatrixEditor::mtxed_static->RefreshVisibleControllerSet();
}

MagicValue::MagicValue(Controller *parent, float litvalue)
    : controller(parent), mugglevalue(litvalue), chan(nullptr) {}
MagicValue::MagicValue(const MagicValue &other, Controller *newparent)
    : controller(newparent), mugglevalue(other.mugglevalue), chan(other.chan) {}

MagicValue::MagicValue(ValueTree mv_node, Controller *parent) : controller(parent) {
    int64_t uuid = (int64)mv_node.getProperty(idChannel, 0);
    if(uuid == 0){
        chan = nullptr;
    }else{
        chan = ChannelSystem::FindChannelByUUID(uuid);
        if(chan == nullptr){
            WarningBox("Internally inconsistent channel UUIDs in showfile!\n"
                    "Show is now corrupted!");
        }
    }
    mugglevalue = mv_node.getProperty(idMuggleValue, 0.0f);
}
ValueTree MagicValue::Save(){
    ValueTree ret(idMagicValue);
    ret.setProperty(idChannel, (int64)(chan == nullptr ? 0 : chan->UUID()), nullptr);
    ret.setProperty(idMuggleValue, mugglevalue, nullptr);
    return ret;
}

void MagicValue::SetLiteral(float v) {
    mugglevalue = v;
    RefreshComponent();
}
void MagicValue::SetChannel(Channel *ch) {
    chan = ch;
    RefreshComponent();
}
String MagicValue::GetText(){
    return chan != nullptr ? chan->GetLetters() : LightingSystem::ValueToString(mugglevalue);
}
float MagicValue::Evaluate(float angle) const {
    return chan != nullptr ? chan->Evaluate(angle) : mugglevalue;
}
void MagicValue::RefreshComponent(){
    controller->RefreshComponent();
}

////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
    : pos(0,0), nostate(false),
      name("New Controller Blah blah"), uuid(GenerateUUID()), group(0),
      color(Colours::red), groupColor(Colours::lightgrey),
      component(nullptr)
{
    for(int i=0; i<=ControllerSystem::NumStates(); ++i){
        states_enabled.add(true);
    }
    AddMIDIAction(MIDIUser::in_on);
    AddMIDIAction(MIDIUser::in_off);
    AddMIDIAction(MIDIUser::in_toggle);
    AddMIDIAction(MIDIUser::out_on);
    AddMIDIAction(MIDIUser::out_off);
}

Controller::~Controller() {}
Controller::Controller(const Controller &other) : MIDIUser(other),
      pos(other.pos + Point<int>(32,16)), nostate(other.nostate),
      name(""), uuid(GenerateUUID()), group(other.group),
      color(other.color), groupColor(other.groupColor),
      states_enabled(other.states_enabled), component(nullptr)
{
    String othername_prefix; int othername_int;
    if(endsWithInt(other.name, othername_prefix, othername_int)){
        name = othername_prefix + String(othername_int + 1);
    }else{
        name = other.name + " 2";
    }
    if(pos.x + 50 > ControllerCanvas::size) pos.x = other.pos.x - 16;
    if(pos.y + 50 > ControllerCanvas::size) pos.y = other.pos.y - 32;
    if(group > 0){
        for(int i=0; i<=ControllerSystem::NumStates(); ++i){
            states_enabled.set(i, false);
        }
    }
}

Controller::Controller(ValueTree ct_node) : MIDIUser(ct_node.getChildWithName(idMIDIUser)) {
    pos.x = ct_node.getProperty(idPosX, 0);
    pos.y = ct_node.getProperty(idPosY, 0);
    nostate = ct_node.getProperty(idNoState, false);
    name = ct_node.getProperty(idName, "New Controller Blah blah");
    uuid = (int64)ct_node.getProperty(idUUID, 0);
    group = ct_node.getProperty(idGroup, 0);
    color = Colour((uint32)(int)ct_node.getProperty(idColor, (int)0xFFFF0000));
    groupColor = Colour((uint32)(int)ct_node.getProperty(idGroupColor, (int)0xFFFF0000));
    ValueTree states_node = ct_node.getChildWithName(idStates);
    if(!states_node.isValid()) { jassertfalse; return; }
    for(int i=0; i<states_node.getNumChildren(); ++i){
        states_enabled.add(states_node.getChild(i).getProperty(idEnabled));
    }
    component = nullptr;
}
ValueTree Controller::Save(){
    ValueTree ret(idController);
    ret.addChild(MIDIUser::Save(), -1, nullptr);
    ret.setProperty(idType, GetClassType(), nullptr);
    ret.setProperty(idPosX, pos.x, nullptr);
    ret.setProperty(idPosY, pos.y, nullptr);
    ret.setProperty(idNoState, nostate, nullptr);
    ret.setProperty(idName, name, nullptr);
    ret.setProperty(idUUID, (int64)uuid, nullptr);
    ret.setProperty(idGroup, group, nullptr);
    ret.setProperty(idColor, (int)color.getARGB(), nullptr);
    ret.setProperty(idGroupColor, (int)groupColor.getARGB(), nullptr);
    ValueTree states_node(idStates);
    for(int i=0; i<states_enabled.size(); ++i){
        ValueTree state_node(idState);
        state_node.setProperty(idEnabled, states_enabled[i], nullptr);
        states_node.addChild(state_node, -1, nullptr);
    }
    ret.addChild(states_node, -1, nullptr);
    return ret;
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
    if(group == g) return;
    group = g;
    if(group > 0){
        //Turn off if it was just added to a group
        for(int i=0; i<=ControllerSystem::NumStates(); ++i){
            states_enabled.set(i, false);
        }
        SendMIDIAction(MIDIUser::out_off);
        //Copy color from another controller in the group
        for(int i=0; i<ControllerSystem::NumControllers(); ++i){
            Controller *ctrlr = ControllerSystem::GetController(i);
            if(ctrlr == this) continue;
            if(ctrlr->group != group) continue;
            groupColor = ctrlr->groupColor;
            break;
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
            Controller *ctrlr = ControllerSystem::GetController(i);
            if(ctrlr == this) continue;
            if(ctrlr->group != group) continue;
            ctrlr->groupColor = groupColor;
            ctrlr->RefreshComponent();
        }
        //This is only called on the message thread
        ControllerCanvas::canvas_static->repaint();
    }else{
        RefreshComponent();
    }
}

bool Controller::IsEnabledStage() const{
    LS_LOCK_READ();
    return states_enabled[GetEffectiveStageState()];
}
bool Controller::IsEnabledDisplay() const{
    LS_LOCK_READ();
    return states_enabled[GetEffectiveDisplayState()];
}

void Controller::SetEnabledDisplay(bool en){
    LS_LOCK_READ();
    int ds = GetEffectiveDisplayState();
    if(states_enabled[ds] == en) return;
    states_enabled.set(ds, en);
    if(en){
        SendMIDIAction(MIDIUser::out_on);
        if(group > 0){
            for(int i=0; i<ControllerSystem::NumControllers(); ++i){
                Controller *ctrlr = ControllerSystem::GetController(i);
                if(ctrlr == this) continue;
                if(ctrlr->group != group) continue;
                if(!ctrlr->IsEnabledDisplay()) continue;
                ctrlr->SetEnabledDisplay(false);
                ctrlr->RefreshComponent();
            }
        }
    }else{
        SendMIDIAction(MIDIUser::out_off);
    }
    RefreshComponent();
}

void Controller::DisplayStateChanged(){
    //LS_LOCK_READ(); Should already be locked
    if(nostate) return; //don't care
    SendMIDIAction(states_enabled[GetEffectiveDisplayState()] ?
        MIDIUser::out_on : MIDIUser::out_off);
    RefreshComponent();
}
void Controller::NumStatesChanged(){
    //LS_LOCK_READ(); Should already be locked
    int ns = ControllerSystem::NumStates()+1;
    while(states_enabled.size() > ns) states_enabled.remove(states_enabled.size()-1);
    while(states_enabled.size() < ns) states_enabled.add(group <= 0);
}
void Controller::CopyState(int dst, int src){
    //LS_LOCK_READ(); Should already be locked
    if(nostate && dst == 0) return;
    states_enabled.set(dst, states_enabled[src]);
}
int Controller::GetEffectiveStageState() const{
    return nostate ? 0 : ControllerSystem::GetEffectiveStageState();
}
int Controller::GetEffectiveDisplayState() const{
    return nostate ? 0 : ControllerSystem::GetEffectiveDisplayState();
}

void Controller::ReceivedMIDIAction(ActionType t, int val){
    ignoreUnused(val);
    LS_LOCK_READ();
    if(t == MIDIUser::in_on){
        SetEnabledDisplay(true);
    }else if(t == MIDIUser::in_off){
        SetEnabledDisplay(false);
    }else if(t == MIDIUser::in_toggle){
        SetEnabledDisplay(!states_enabled[GetEffectiveDisplayState()]);
    }
}

void Controller::RegisterComponent(ControllerCmp *cmp){
    LS_LOCK_WRITE();
    component = cmp;
}
void Controller::RefreshComponent(){
    component->notifyRepaint();
}

////////////////////////////////////////////////////////////////////////////////

SimpleController::SimpleController()
    : Controller(), value(this) {
    name = "Simple Controller";
}
SimpleController::~SimpleController() {}
SimpleController::SimpleController(const SimpleController &other)
    : Controller(other), value(other.value, this) {}
Controller *SimpleController::clone() const{
    return new SimpleController(*this);
}

#define LOAD_CHILD_MAGICVALUE(mvalue) { \
    ValueTree v = ct_node.getChildWithProperty(idType, #mvalue); \
    if(!v.isValid()) { jassertfalse; return; } \
    mvalue = MagicValue(v, this); \
} REQUIRESEMICOLON

#define SAVE_CHILD_MAGICVALUE(mvalue) { \
    ValueTree v = mvalue.Save(); \
    v.setProperty(idType, #mvalue, nullptr); \
    ret.addChild(v, -1, nullptr); \
} REQUIRESEMICOLON

SimpleController::SimpleController(ValueTree ct_node)
    : Controller(ct_node), value(this) {
    LOAD_CHILD_MAGICVALUE(value);
}
ValueTree SimpleController::Save(){
    ValueTree ret = Controller::Save();
    SAVE_CHILD_MAGICVALUE(value);
    return ret;
}

float SimpleController::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Not locking because channel evaluation will lock
    return value.Evaluate(angle);
}

void SimpleController::RemoveAllMagicValuesForChannel(const Channel *chn){
    if(value.GetChannel() == chn) value.SetChannel(nullptr);
}

////////////////////////////////////////////////////////////////////////////////

ContinuousController::ContinuousController()
    : Controller(),
    lovalue(this), hivalue(this, 1.0f) {
    for(int i=0; i<=ControllerSystem::NumStates(); ++i){
        states_knob.add(0.0f);
    }
    name = "Continuous Controller";
    AddMIDIAction(MIDIUser::in_val);
    AddMIDIAction(MIDIUser::in_goto_lo);
    AddMIDIAction(MIDIUser::in_goto_hi);
    AddMIDIAction(MIDIUser::out_val);
}

ContinuousController::~ContinuousController() {}
ContinuousController::ContinuousController(const ContinuousController &other)
    : Controller(other), lovalue(other.lovalue, this),
      hivalue(other.hivalue, this), states_knob(other.states_knob) {}
Controller *ContinuousController::clone() const{
    return new ContinuousController(*this);
}

ContinuousController::ContinuousController(ValueTree ct_node)
    : Controller(ct_node), lovalue(this), hivalue(this) {
    LOAD_CHILD_MAGICVALUE(lovalue);
    LOAD_CHILD_MAGICVALUE(hivalue);
    ValueTree states_node = ct_node.getChildWithName(idStates);
    if(!states_node.isValid()) { jassertfalse; return; }
    for(int i=0; i<states_node.getNumChildren(); ++i){
        states_knob.add(states_node.getChild(i).getProperty(idKnob));
    }
}
ValueTree ContinuousController::Save(){
    ValueTree ret = Controller::Save();
    SAVE_CHILD_MAGICVALUE(lovalue);
    SAVE_CHILD_MAGICVALUE(hivalue);
    ValueTree states_node = ret.getChildWithName(idStates);
    if(!states_node.isValid()) { jassertfalse; return ValueTree(); }
    jassert(states_knob.size() == states_node.getNumChildren());
    for(int i=0; i<states_knob.size(); ++i){
        states_node.getChild(i).setProperty(idKnob, states_knob[i], nullptr);
    }
    return ret;
}

float ContinuousController::GetKnobDisplay(){
    LS_LOCK_READ();
    return states_knob[GetEffectiveDisplayState()];
}
void ContinuousController::SetKnobDisplay(float k){
    LS_LOCK_READ();
    jassert(k >= 0.0f && k <= 1.0f);
    states_knob.set(GetEffectiveDisplayState(), k);
    SendMIDIAction(MIDIUser::out_val, (int)(k * 127.0f));
}

void ContinuousController::DisplayStateChanged(){
    //LS_LOCK_READ(); Should already be locked
    if(nostate) return; //don't care
    SendMIDIAction(MIDIUser::out_val, (int)(states_knob[GetEffectiveDisplayState()] * 127.0f));
    Controller::DisplayStateChanged(); //Calls RefreshComponent()
}
void ContinuousController::NumStatesChanged(){
    //LS_LOCK_READ(); Should already be locked
    Controller::NumStatesChanged();
    int ns = ControllerSystem::NumStates()+1;
    while(states_knob.size() > ns) states_knob.remove(states_knob.size()-1);
    while(states_knob.size() < ns) states_knob.add(0.0f);
}
void ContinuousController::CopyState(int dst, int src){
    //LS_LOCK_READ(); Should already be locked
    if(nostate && dst == 0) return;
    Controller::CopyState(dst, src);
    states_knob.set(dst, states_knob[src]);
}

void ContinuousController::ReceivedMIDIAction(ActionType t, int val) {
    LS_LOCK_READ();
    Controller::ReceivedMIDIAction(t, val);
    if(t == MIDIUser::in_val){
        SetKnobDisplay((float)val / 127.0f);
        RefreshComponent();
    }else if(t == MIDIUser::in_goto_lo){
        SetKnobDisplay(0.0f);
        RefreshComponent();
    }else if(t == MIDIUser::in_goto_hi){
        SetKnobDisplay(1.0f);
        RefreshComponent();
    }
}

float ContinuousController::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Not locking because channel evaluation will lock
    float l = lovalue.Evaluate(angle);
    float h = hivalue.Evaluate(angle);
    float k = states_knob[GetEffectiveStageState()];
    return (l * (1.0f - k)) + (h * k);
}

void ContinuousController::RemoveAllMagicValuesForChannel(const Channel *chn){
    if(lovalue.GetChannel() == chn) lovalue.SetChannel(nullptr);
    if(hivalue.GetChannel() == chn) hivalue.SetChannel(nullptr);
}

////////////////////////////////////////////////////////////////////////////////

ModulatorController::ModulatorController()
    : Controller(),
    lovalue(this), hivalue(this, 1.0f), pwvalue(this, 0.2f), tvalue(this, 1.0f),
    shape(ModulatorShape::pulse), timebase(TimeBase::beat),
    freet_origin(TimingSystem::GetTimeMS()) {
    name = "Modulator Controller";
}

ModulatorController::~ModulatorController() {}
ModulatorController::ModulatorController(const ModulatorController &other)
    : Controller(other),
    lovalue(other.lovalue, this), hivalue(other.hivalue, this),
    pwvalue(other.pwvalue, this), tvalue(other.tvalue, this),
    shape(other.shape), timebase(other.timebase),
    freet_origin(TimingSystem::GetTimeMS()) {}
Controller *ModulatorController::clone() const {
    return new ModulatorController(*this);
}

ModulatorController::ModulatorController(ValueTree ct_node)
    : Controller(ct_node), lovalue(this), hivalue(this), pwvalue(this), tvalue(this),
    freet_origin(TimingSystem::GetTimeMS()) {
    LOAD_CHILD_MAGICVALUE(lovalue);
    LOAD_CHILD_MAGICVALUE(hivalue);
    LOAD_CHILD_MAGICVALUE(pwvalue);
    LOAD_CHILD_MAGICVALUE(tvalue);
    shape = (ModulatorShape)(int)ct_node.getProperty(idShape, 3);
    timebase = (TimeBase)(int)ct_node.getProperty(idTimeBase, 1);
}
ValueTree ModulatorController::Save(){
    ValueTree ret = Controller::Save();
    SAVE_CHILD_MAGICVALUE(lovalue);
    SAVE_CHILD_MAGICVALUE(hivalue);
    SAVE_CHILD_MAGICVALUE(pwvalue);
    SAVE_CHILD_MAGICVALUE(tvalue);
    ret.setProperty(idShape, (int)shape, nullptr);
    ret.setProperty(idTimeBase, (int)timebase, nullptr);
    return ret;
}

float ModulatorController::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Not locking because channel evaluation will lock
    float l = lovalue.Evaluate(0.0f);
    float h = hivalue.Evaluate(0.0f);
    float pw = pwvalue.Evaluate(0.0f);
    float period = tvalue.Evaluate(0.0f);
    float t_frac = 0.0f;
    if(period > 0.001f){
        if(timebase == TimeBase::measure || timebase == TimeBase::beat){
            if(timebase == TimeBase::measure){
                t_frac = TimingSystem::GetPositionInMeasure();
            }else{
                t_frac = TimingSystem::GetPositionInBeat();
            }
            t_frac /= period;
        }else if(timebase == TimeBase::second){
            float periodms = period * 1000.0f;
            t_frac = (float)((TimingSystem::GetTimeMS() - freet_origin)
                    % (uint64_t)periodms) / periodms;
        }else{
            jassertfalse;
        }
    }
    t_frac += angle;
    t_frac = t_frac - std::floor(t_frac);
    if(shape == ModulatorShape::sawr){
        pw = 1.0f - pw; //SawR has pulse width measured from the end
    }
    float fallshape = (pw-t_frac)/pw;
    float riseshape = (t_frac-pw)/(1.0f-pw);
    float ret;
    switch(shape){
    case ModulatorShape::cosine:
        ret = (1.0f+std::cos(MathConstants<float>::twoPi * t_frac)) * 0.5f;
        break;
    case ModulatorShape::triangle:
        ret = t_frac < pw ? fallshape : riseshape;
        break;
    case ModulatorShape::noise:
        if(period <= 0.001f){
            ret = l;
        }else{
            int64_t objectid = UUID() ^ (int64_t)this;
            if(timebase == TimeBase::measure){
                ret = TimingSystem::GetRandomAtMeasure(objectid, period);
            }else if(timebase == TimeBase::beat){
                ret = TimingSystem::GetRandomAtBeat(objectid, period);
            }else if(timebase == TimeBase::second){
                ret = TimingSystem::GetRandomAtSecond(objectid, period);
            }else{
                jassertfalse;
                ret = 0.0f;
            }
        }
        break;
    case ModulatorShape::pulse:
        ret = t_frac < pw ? 1.0f : 0.0f;
        break;
    case ModulatorShape::sawf:
        ret = t_frac < pw ? fallshape : 0.0f;
        break;
    case ModulatorShape::sawr:
        ret = t_frac < pw ? 0.0f : riseshape;
        break;
    default:
        jassertfalse;
        ret = 0.0f;
    }
    ret = (h-l)*ret + l;
    return ret;
}

void ModulatorController::RemoveAllMagicValuesForChannel(const Channel *chn){
    if(lovalue.GetChannel() == chn) lovalue.SetChannel(nullptr);
    if(hivalue.GetChannel() == chn) hivalue.SetChannel(nullptr);
    if(pwvalue.GetChannel() == chn) pwvalue.SetChannel(nullptr);
    if(tvalue .GetChannel() == chn) tvalue .SetChannel(nullptr);
}

////////////////////////////////////////////////////////////////////////////////

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
    static inline int FixPosition(int p){
        p -= 64;
        p += Random::getSystemRandom().nextInt(72);
        p >>= 3;
        p <<= 3;
        return p;
    }
    void AddInternal(Controller *c, bool totallynew){
        LS_LOCK_WRITE();
        if(totallynew){
            c->pos = ControllerCanvas::canvas_static->GetCenterPoint();
            c->pos.x = FixPosition(c->pos.x);
            c->pos.y = FixPosition(c->pos.y);
        }
        ctrlrs.add(c);
        RefreshMatrixEditor(true);
    }
    template<class CTRLR> CTRLR *AddController(){
        static_assert(std::is_base_of<Controller, CTRLR>::value,
            "Invalid use of AddController()!");
        CTRLR *c = new CTRLR();
        AddInternal(c, true);
        return c;
    }
    template SimpleController *AddController<SimpleController>();
    template ContinuousController *AddController<ContinuousController>();
    template ModulatorController *AddController<ModulatorController>();
    Controller *DuplicateController(Controller *orig){
        Controller *n = orig->clone();
        AddInternal(n, false);
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

    void RemoveAllMagicValuesForChannel(const Channel *chn){
        LS_LOCK_WRITE();
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->RemoveAllMagicValuesForChannel(chn);
        }
    }

    void RefreshAllComponents(){
        LS_LOCK_READ();
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->RefreshComponent();
        }
    }

    void HandleMIDI(int port, MidiMessage msg){
        LS_LOCK_READ();
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->HandleMIDI(port, msg);
        }
    }

    int nstates;
    int dstate, sstate, fadedeststate;
    float fade;
    bool eval_fadedeststate;
    Array<bool> states_protected;
    Array<float> states_fadeintime;

#define DEFAULT_FADETIME 0.0f

    void Init(ValueTree as_node){
        if(as_node.isValid()){
            nstates = as_node.getProperty(idNStates, 10);
            dstate = as_node.getProperty(idDState, 1);
            sstate = fadedeststate = as_node.getProperty(idSState, 1);
            ValueTree states_node = as_node.getChildWithName(idStates);
            if(!states_node.isValid()) { jassertfalse; return; }
            jassert(states_node.getNumChildren() == nstates+1);
            for(int i=0; i<=nstates; ++i){
                states_protected.add(states_node.getChild(i).getProperty(idProtected, false));
                states_fadeintime.add(states_node.getChild(i).getProperty(idFadeInTime, DEFAULT_FADETIME));
            }
            for(int i=0; i<as_node.getNumChildren(); ++i){
                ValueTree v = as_node.getChild(i);
                if(!v.hasType(idController)) continue;
                Controller *c;
                String classtype = v.getProperty(idType, "").toString();
                if(classtype == "Simple"){
                    c = new SimpleController(v);
                }else if(classtype == "Continuous"){
                    c = new ContinuousController(v);
                }else if(classtype == "Modulator"){
                    c = new ModulatorController(v);
                }else{
                    jassertfalse;
                    continue;
                }
                ctrlrs.add(c);
            }
        }else{
            nstates = 10;
            for(int i=0; i<=nstates; ++i){
                states_protected.add(false);
                states_fadeintime.add(DEFAULT_FADETIME);
            }
            dstate = sstate = fadedeststate = 1;
        }
        fade = -1.0f;
        eval_fadedeststate = false;
    }
    void Finalize(){
        ctrlrs.clear();
        states_protected.clear();
        states_fadeintime.clear();
    }
    ValueTree Save(){
        ValueTree ret(idControllerSystem);
        ret.setProperty(idNStates, nstates, nullptr);
        ret.setProperty(idDState, dstate, nullptr);
        ret.setProperty(idSState, sstate, nullptr);
        ValueTree states_node(idStates);
        for(int i=0; i<states_protected.size(); ++i){
            ValueTree state_node(idState);
            state_node.setProperty(idProtected, states_protected[i], nullptr);
            state_node.setProperty(idFadeInTime, states_fadeintime[i], nullptr);
            states_node.addChild(state_node, -1, nullptr);
        }
        ret.addChild(states_node, -1, nullptr);
        for(int i=0; i<ctrlrs.size(); ++i){
            ret.addChild(ctrlrs[i]->Save(), -1, nullptr);
        }
        return ret;
    }

    int NumStates(){
        return nstates;
    }
    void AddState(){
        LS_LOCK_WRITE();
        ++nstates;
        states_protected.add(false);
        states_fadeintime.add(DEFAULT_FADETIME);
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->NumStatesChanged();
        }
    }
    void RemoveState(){
        LS_LOCK_WRITE();
        if(nstates == 1) return;
        --nstates;
        if(dstate > nstates) dstate = nstates;
        if(sstate > nstates) sstate = nstates;
        if(fadedeststate > nstates){
            fadedeststate = nstates;
            fade = -1.0f;
        }
        states_protected.removeLast();
        states_fadeintime.removeLast();
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->NumStatesChanged();
        }
    }
    void AllCtrlrsDisplayStateChanged(){
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->DisplayStateChanged();
        }
    }
    void CopyState(int dst, int src){
        LS_LOCK_READ();
        if(dst < 0 || src < 0 || dst > nstates || src > nstates){
            jassertfalse;
            return;
        }
        if(dst > 0){
            states_protected.set(dst, states_protected[src]);
            states_fadeintime.set(dst, states_fadeintime[src]);
        }
        for(int i=0; i<ctrlrs.size(); ++i){
            ctrlrs[i]->CopyState(dst, src);
        }
        if(dst == dstate || (states_protected[dstate] && dst == 0)){
            AllCtrlrsDisplayStateChanged();
        }
    }
    bool IsStateProtected(int s){
        LS_LOCK_READ();
        jassert(s >= 1 && s <= nstates);
        return states_protected[s];
    }
    void ProtectState(int s, bool protect){
        LS_LOCK_WRITE();
        jassert(s >= 1 && s <= nstates);
        if(states_protected[s] == protect) return;
        if(s == sstate){
            if(protect){
                CopyState(0, s);
            }else{
                CopyState(s, 0);
            }
        }
        states_protected.set(s, protect);
    }

    int GetEffectiveStageState(){
        if(fade >= 0.0f && eval_fadedeststate) return fadedeststate;
        if(states_protected[sstate]) return 0;
        return sstate;
    }
    int GetSelectedStageState(){
        return sstate;
    }
    int GetEffectiveDisplayState(){
        if(sstate == dstate && states_protected[sstate]) return 0;
        return dstate;
    }
    int GetSelectedDisplayState(){
        return dstate;
    }
    int GetFadeDestState(){
        return fade >= 0.0f ? fadedeststate : -1;
    }
    
    
    void ActivateStateInternal(int s){
        if(states_protected[s]){
            CopyState(0, s);
        }
        dstate = sstate = fadedeststate = s;
        AllCtrlrsDisplayStateChanged();
    }
    void ActivateState(int s){
        LS_LOCK_READ();
        jassert(s >= 1 && s <= nstates);
        if(states_fadeintime[s] <= 0.0f){
            ActivateStateInternal(s);
        }else{
            fade = 0.0f;
            fadedeststate = s;
        }
    }
    void BlindState(int s){
        LS_LOCK_READ();
        jassert(s >= 1 && s <= nstates);
        dstate = s;
        AllCtrlrsDisplayStateChanged();
    }
    
    float GetTransitionFactor(){
        return fade;
    }
    void SetEvalSourceState(){
        eval_fadedeststate = false;
    }
    void SetEvalDestState(){
        eval_fadedeststate = true;
    }
    void UpdateFade(float dt){
        LS_LOCK_READ();
        if(fade < 0.0f) return;
        fade += dt / states_fadeintime[fadedeststate];
        if(fade >= 1.0f){
            fade = -1.0f;
            ActivateStateInternal(fadedeststate);
        }
    }
    
    float GetDestFadeTime(){
        return states_fadeintime[fadedeststate];
    }
    void SetDestFadeTime(float f){
        if(!(f > 0.0f)) f = 0.0f;
        states_fadeintime.set(fadedeststate, f);
    }
}
