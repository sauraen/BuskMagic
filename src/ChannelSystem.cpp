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

#include "ChannelSystem.h"

#include "LightingSystem.h"
#include "FixtureSystem.h"
#include "ControllerSystem.h"

#include "gui/MatrixEditor.h"

static_assert(sizeof(void*) == sizeof(int64_t), "BuskMagic only supports 64-bit platforms!");

Phasor::Phasor(ValueTree ph_node){
    src = (Controller*)(int64)ph_node.getProperty(idController, 0);
    mag = ph_node.getProperty(idMag, 0.0f);
    angle = ph_node.getProperty(idAngle, 0.0f);
}
ValueTree Phasor::Save(){
    ValueTree ret(idPhasor);
    ret.setProperty(idController, (int64)(src == nullptr ? 0 : src->UUID()), nullptr);
    ret.setProperty(idMag, mag, nullptr);
    ret.setProperty(idAngle, angle, nullptr);
    return ret;
}

static void RefreshMatrixEditor(bool invalidate){
    MatrixEditor::mtxed_static->RefreshChannelFilters();
    if(invalidate) MatrixEditor::mtxed_static->RefreshVisibleChannelSet();
}

String Channel::OpGetLetters(ChannelOp o){
    switch(o){
    case OpPrioTop: return CharPointer_UTF8 ("\xe2\x86\x91");
    case OpPrioBottom: return CharPointer_UTF8 ("\xe2\x86\x93");
    case OpPrioMax: return "M";
    case OpPrioMin: return "m";
    case OpPrioMaxWDefault: return "MD";
    case OpPrioMinWDefault: return "md";
    case OpAdd: return "+";
    case OpAddWDefault: return "+D";
    case OpMultiply: return CharPointer_UTF8 ("\xc3\x97");
    case OpMultiplyWDefault: return CharPointer_UTF8 ("\xc3\x97\x44");
    default: jassertfalse; return "E";
    }
}

String Channel::OpGetDescription(ChannelOp o){
    switch(o){
    case OpPrioTop: return CharPointer_UTF8 ("Top Priority");
    case OpPrioBottom: return CharPointer_UTF8 ("Bottom Priority");
    case OpPrioMax: return "Maximum Value (HTP)";
    case OpPrioMin: return "minimum value";
    case OpPrioMaxWDefault: return "Maximum Value (Incl. Default)";
    case OpPrioMinWDefault: return "minimum value (incl. default)";
    case OpAdd: return "Add";
    case OpAddWDefault: return "Add (Incl. Default)";
    case OpMultiply: return "Multiply";
    case OpMultiplyWDefault: return "Multiply (Incl. Default)";
    default: jassertfalse; return "Error";
    }
}

Channel::Channel(Fixture *parentornullptr) : uuid(GenerateUUID()), parent(parentornullptr),
    name("New channel"), letters("N"), defaultvalue(0.0f), 
    op(OpAdd), beingevaluated(false) {
    
}
Channel::~Channel(){
    
}

Channel::Channel(ValueTree ch_node, Fixture *parentornullptr) 
    : parent(parentornullptr), beingevaluated(false) {
    uuid = (int64)ch_node.getProperty(idUUID, 0);
    name = ch_node.getProperty(idName, "New channel");
    letters = ch_node.getProperty(idLetters, "N");
    defaultvalue = ch_node.getProperty(idDefaultValue, 0.0f);
    op = (ChannelOp)(int)ch_node.getProperty(idOp, 0);
    for(int i=0; i<ch_node.getNumChildren(); ++i){
        phasors.add(new Phasor(ch_node.getChild(i)));
    }
}

ValueTree Channel::Save(){
    ValueTree ret(idChannel);
    ret.setProperty(idUUID, (int64)uuid, nullptr);
    ret.setProperty(idName, name, nullptr);
    ret.setProperty(idLetters, letters, nullptr);
    ret.setProperty(idDefaultValue, defaultvalue, nullptr);
    ret.setProperty(idOp, (int)op, nullptr);
    for(int i=0; i<phasors.size(); ++i){
        ret.addChild(phasors[i]->Save(), -1, nullptr);
    }
    return ret;
}

String Channel::GetName() const{
    LS_LOCK_READ();
    return name;
}
void Channel::SetName(String newname){
    LS_LOCK_WRITE();
    name = newname;
    RefreshMatrixEditor(false);
}
String Channel::GetLetters() const{
    LS_LOCK_READ();
    return letters;
}
void Channel::SetLetters(String newletters){
    LS_LOCK_WRITE();
    letters = newletters;
}

String Channel::GetFixName() const{
    LS_LOCK_READ();
    return parent == nullptr ? "Free channels" : parent->GetName();
}
int Channel::GetFixID() const{
    LS_LOCK_READ();
    return parent == nullptr ? -1 : parent->GetFixID();
}

Phasor *Channel::GetPhasor(int i) const {
    LS_LOCK_READ();
    if(i < 0 || i >= phasors.size()){
        jassertfalse;
        return nullptr;
    }
    return phasors[i];
}

Phasor *Channel::GetPhasorForController(Controller *c, bool addIfNotPresent){
    {
        LS_LOCK_READ();
        for(int i=0; i<phasors.size(); ++i){
            if(phasors[i]->src == c) return phasors[i];
        }
        if(!addIfNotPresent) return nullptr;
    } //Must give up read lock before acquiring write lock to avoid deadlock
    LS_LOCK_WRITE();
    Phasor *ret = new Phasor(c);
    phasors.add(ret);
    SortPhasors();
    return ret;
}

void Channel::RemovePhasor(int i){
    LS_LOCK_WRITE();
    phasors.remove(i);
}

void Channel::RemovePhasor(Phasor *ph){
    LS_LOCK_WRITE();
    phasors.removeObject(ph, true);
}

void Channel::RemovePhasorForController(Controller *c){
    LS_LOCK_WRITE();
    for(int i=phasors.size()-1; i>=0; --i){
        if(phasors[i]->src == c){
            phasors.remove(i);
            return;
        }
    }
}

void Channel::SortPhasors(){
    LS_LOCK_WRITE();
    int destpos = 0;
    for(int i=0; i<ControllerSystem::NumControllers(); ++i){
        Controller *c = ControllerSystem::GetController(i);
        for(int j=0; j<phasors.size(); ++j){
            if(phasors[j]->src == c){
                phasors.move(j, destpos++);
                break;
            }
        }
    }
    jassert(destpos == phasors.size());
}

void Channel::ConvertPhasorsUUIDToPointer(){
    for(int j=0; j<phasors.size(); ++j){
        uint64_t uuid = (uint64_t)phasors[j]->src;
        bool flag = false;
        for(int i=0; i<ControllerSystem::NumControllers(); ++i){
            Controller *c = ControllerSystem::GetController(i);
            if(uuid == c->UUID()){
                phasors[j]->src = c;
                flag = true;
                break;
            }
        }
        if(!flag){
            phasors.remove(j);
            --j;
            WarningBox("Internally inconsistent controller UUIDs in showfile!\n"
                "Show state is most likely corrupted!");
        }
    }
}

class EvaluatedTracker {
public:
    inline EvaluatedTracker(const Channel *ch) : channel(ch){ channel->beingevaluated = true; }
    inline ~EvaluatedTracker() { channel->beingevaluated = false; }
private:
    const Channel *channel;
};

#define EVALCHN() (phasors[i]->mag * c->Evaluate(angle + phasors[i]->angle))

float Channel::Evaluate(float angle) const {
    LS_LOCK_READ();
    if(beingevaluated){
        LightingSystem::SignalRecursion();
        return 0.0f;
    }
    EvaluatedTracker trkr(this);
    float val; bool flag;
    switch(op){
    case OpPrioTop:
    case OpPrioBottom:
        for(int i=(op == OpPrioTop ? 0 : phasors.size()-1); 
                  (op == OpPrioTop ? (i<phasors.size()) : (i>=0)); 
                  (op == OpPrioTop ? ++i : --i)){
            Controller *c = phasors[i]->src;
            if(c->IsEnabledStage()){
                return EVALCHN();
            }
        }
        return defaultvalue;
    case OpPrioMax:
    case OpPrioMin:
        flag = false;
        val = 0.0f; //doesn't matter
        for(int i=0; i<phasors.size(); ++i){
            Controller *c = phasors[i]->src;
            if(c->IsEnabledStage()){
                float v = EVALCHN();
                if(!flag || (op == OpPrioMax ? (v > val) : (v < val))){
                    flag = true;
                    val = v;
                }
            }
        }
        if(flag) return val;
        return defaultvalue;
    case OpPrioMaxWDefault:
    case OpPrioMinWDefault:
        val = defaultvalue;
        for(int i=0; i<phasors.size(); ++i){
            Controller *c = phasors[i]->src;
            if(c->IsEnabledStage()){
                float v = EVALCHN();
                if(op == OpPrioMax ? (v > val) : (v < val)){
                    val = v;
                }
            }
        }
        return val;
    case OpAdd:
    case OpAddWDefault:
    case OpMultiply:
    case OpMultiplyWDefault:
        flag = false;
        val = (op == OpAdd) ? 0.0f : (op == OpMultiply) ? 1.0f : defaultvalue;
        for(int i=0; i<phasors.size(); ++i){
            Controller *c = phasors[i]->src;
            if(c->IsEnabledStage()){
                flag = true;
                float v = EVALCHN();
                if(op == OpAdd || op == OpAddWDefault){
                    val += v;
                }else{
                    val *= v;
                }
            }
        }
        if(flag) return val;
        return defaultvalue;
    default:
        jassertfalse;
        return 0.0f;
    }
}

namespace ChannelSystem {
    
    static OwnedArray<Channel> freechannels;
    
    int NumTotalChannels(){
        LS_LOCK_READ();
        int total = freechannels.size();
        for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
            total += FixtureSystem::Fix(i)->GetNumChannels();
        }
        return total;
    }
    int NumFreeChannels() { return freechannels.size(); }
    Channel *GetFreeChannel(int i){
        LS_LOCK_READ();
        if(i < 0 || i >= freechannels.size()){
            jassertfalse;
            return nullptr;
        }
        return freechannels[i];
    }
    Channel *AddFreeChannel(){
        LS_LOCK_WRITE();
        Channel *ret = new Channel(nullptr);
        freechannels.add(ret);
        RefreshMatrixEditor(true);
        return ret;
    }
    void RemoveFreeChannel(int i){
        LS_LOCK_WRITE();
        if(i < 0 || i >= freechannels.size()){
            jassertfalse;
            return;
        }
        ControllerSystem::RemoveAllMagicValuesForChannel(freechannels[i]);
        freechannels.remove(i);
        RefreshMatrixEditor(true);
    }
    
    void RemoveAllPhasorsForController(Controller *c){
        LS_LOCK_WRITE();
        for(int i=0; i<freechannels.size(); ++i){
            freechannels[i]->RemovePhasorForController(c);
        }
        for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
            for(int j=0; j<FixtureSystem::Fix(i)->GetNumChannels(); ++j){
                FixtureSystem::Fix(i)->GetChannel(j)->RemovePhasorForController(c);
            }
        }
    }
    
    void SortAllChannelPhasors(){
        LS_LOCK_WRITE();
        for(int i=0; i<freechannels.size(); ++i){
            freechannels[i]->SortPhasors();
        }
        for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
            for(int j=0; j<FixtureSystem::Fix(i)->GetNumChannels(); ++j){
                FixtureSystem::Fix(i)->GetChannel(j)->SortPhasors();
            }
        }
    }
    
    void ConvertAllPhasorsUUIDToPointer(){
        for(int i=0; i<freechannels.size(); ++i){
            freechannels[i]->ConvertPhasorsUUIDToPointer();
        }
        for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
            for(int j=0; j<FixtureSystem::Fix(i)->GetNumChannels(); ++j){
                FixtureSystem::Fix(i)->GetChannel(j)->ConvertPhasorsUUIDToPointer();
            }
        }
    }
    
    Channel *FindChannelByUUID(int64_t uuid){
        for(int i=0; i<freechannels.size(); ++i){
            if(freechannels[i]->UUID() == uuid){
                return freechannels[i];
            }
        }
        for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
            for(int j=0; j<FixtureSystem::Fix(i)->GetNumChannels(); ++j){
                if(FixtureSystem::Fix(i)->GetChannel(j)->UUID() == uuid){
                    return FixtureSystem::Fix(i)->GetChannel(j);
                }
            }
        }
        return nullptr;
    }
    
    void Init(ValueTree cs_node){
        if(cs_node.isValid()){
            for(int i=0; i<cs_node.getNumChildren(); ++i){
                freechannels.add(new Channel(cs_node.getChild(i), nullptr));
            }
        }
    }
    void Finalize(){
        freechannels.clear();
    }
    ValueTree Save(){
        ValueTree ret(idChannelSystem);
        for(int i=0; i<freechannels.size(); ++i){
            ret.addChild(freechannels[i]->Save(), -1, nullptr);
        }
        return ret;
    }
}
