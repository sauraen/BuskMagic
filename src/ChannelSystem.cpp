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

String Channel::OpGetLetters(ChannelOp o){
    switch(o){
    case OpPrioTop: return CharPointer_UTF8 ("\xe2\x86\x91");
    case OpPrioBottom: return CharPointer_UTF8 ("\xe2\x86\x93");
    case OpPrioMax: return "M";
    case OpPrioMin: return "m";
    case OpPrioMaxWDefault: return "MD";
    case OpPrioMinWDefault: return "md";
    case OpAdd: return "+";
    case OpMultiply: return CharPointer_UTF8 ("\xc3\x97");
    default: jassertfalse; return "E";
    }
}

String Channel::OpGetDescription(ChannelOp o){
    switch(o){
    case OpPrioTop: return CharPointer_UTF8 ("\xe2\x86\x91 Top Priority");
    case OpPrioBottom: return CharPointer_UTF8 ("\xe2\x86\x93 Bottom Priority");
    case OpPrioMax: return "Maximum Value (HTP)";
    case OpPrioMin: return "minimum value";
    case OpPrioMaxWDefault: return "Maximum Value (Including Default)";
    case OpPrioMinWDefault: return "minimum value (including default)";
    case OpAdd: return "Add";
    case OpMultiply: return "Multiply";
    default: jassertfalse; return "Error";
    }
}

Channel::Channel() : name("New channel"), letters("N"), defaultvalue(0.0f), 
    op(OpAdd) {
    
}
Channel::~Channel(){
    
}

String Channel::GetName() const{
    LS_LOCK_READ();
    return name;
}
void Channel::SetName(String newname){
    LS_LOCK_WRITE();
    name = newname;
}
String Channel::GetLetters() const{
    LS_LOCK_READ();
    return letters;
}
void Channel::SetLetters(String newletters){
    LS_LOCK_WRITE();
    letters = newletters;
}

Phasor *Channel::GetPhasor(int i) const {
    LS_LOCK_READ();
    if(i < 0 || i >= phasors.size()) return nullptr;
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

void Channel::RemovePhasorForController(Controller *c){
    LS_LOCK_WRITE();
    for(int i=phasors.size()-1; i>=0; --i){
        if(phasors[i]->src == c) phasors.remove(i);
    }
}

void Channel::SortPhasors(){
    //LS_LOCK_WRITE(); //Already locked from ChannelSystem::SortAllChannelPhasors
    //TODO
}

#define EVALCHN() phasors[i]->mag * c->Evaluate(angle + phasors[i]->angle)

float Channel::Evaluate(float angle) const {
    //LS_LOCK_READ(); //Already locked from evaluate system
    float val; bool flag;
    switch(op){
    case OpPrioTop:
    case OpPrioBottom:
        for(int i=(op == OpPrioTop ? 0 : phasors.size()-1); 
                  (op == OpPrioTop ? (i<phasors.size()) : (i>=0)); 
                  (op == OpPrioTop ? ++i : --i)){
            Controller *c = phasors[i]->src;
            if(c->IsEnabled()){
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
            if(c->IsEnabled()){
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
            if(c->IsEnabled()){
                float v = EVALCHN();
                if(op == OpPrioMax ? (v > val) : (v < val)){
                    val = v;
                }
            }
        }
        return val;
    case OpAdd:
        //TODO
        break;
    case OpMultiply:
        //
        break;
    default:
        jassertfalse;
        return 0.0f;
    }
}
