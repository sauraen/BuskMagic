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

#include "FixtureSystem.h"

#include "ChannelSystem.h"

Fixture::Fixture(ValueTree def_, String name_, int fixid_, uint16_t uni_, uint16_t chn_)
    : def(def_), name(name_), fixid(fixid_), uni(uni_), chn(chn_) {
    def.setProperty(Identifier("inuse"), true, nullptr);
    for(int p=0; p<def.getNumChildren(); ++p){
        ValueTree param = def.getChild(p);
        String ptype = param.getProperty(Identifier("type"), "");
        if(ptype == "Generic"){
            Channel *gchan = new Channel();
            gchan->SetName(param.getProperty(Identifier("name"), "Error"));
            gchan->SetLetters(param.getProperty(Identifier("letters"), "X"));
            gchan->SetDefaultValue(0.0f);
            gchan->SetOp(Channel::OpAdd);
            channels.add(gchan);
        }else if(ptype == "Color"){
            Channel *hchan = new Channel();
            hchan->SetName("Hue - " + param.getProperty(Identifier("name"), "Error"));
            hchan->SetLetters("H");
            hchan->SetDefaultValue(0.0f);
            hchan->SetOp(Channel::OpAdd);
            channels.add(hchan);
            Channel *lchan = new Channel();
            lchan->SetName("Lightness - " + param.getProperty(Identifier("name"), "Error"));
            lchan->SetLetters("L");
            lchan->SetDefaultValue(1.0f);
            lchan->SetOp(Channel::OpAdd);
            channels.add(lchan);
        }
    }
}
Fixture::~Fixture() {}

String Fixture::GetDescription() const {
    return String(fixid) + ": " + hex(uni) + "." + String(chn) + ": " + name + " (" 
        + def.getProperty(Identifier("manufacturer"), "(Manu)").toString() + " "
        + def.getProperty(Identifier("name"), "(Name)").toString() + ")";
}

String Fixture::GetName(){
    LS_LOCK_READ();
    return name;
}
void Fixture::SetName(String newname){
    LS_LOCK_WRITE();
    name = newname;
}
void Fixture::SetPatch(uint16_t newuni, uint16_t newchn){
    LS_LOCK_WRITE();
    uni = newuni;
    chn = newchn;
}
Channel *Fixture::GetChannel(int i){
    LS_LOCK_READ();
    if(i < 0 || i >= channels.size()){
        jassertfalse;
        return nullptr;
    }
    return channels[i];
}


namespace FixtureSystem {
    
    bool ParseDMXText(String text, int footprint, int &normal, int &fine, int &ultra){
        normal = 1; fine = -1; ultra = -1;
        StringArray dmx = StringArray::fromTokens(text, ",", "");
        if(dmx.size() < 1 || dmx.size() > 3) return false;
        for(int i=0; i<dmx.size(); ++i){
            String str = dmx[i].trim();
            if(!isInt(str, false)) return false;
            int tmp = str.getIntValue();
            if(tmp < 1 || tmp > footprint) return false;
            if(i == 0){
                normal = tmp;
            }else if(i == 1){
                fine = tmp;
            }else{
                ultra = tmp;
            }
        }
        return true;
    }
    
    String GetDMXText(ValueTree parent){
        String dmxstr = VT_GetChildProperty(parent, "normal", "channel", 1).toString();
        if(parent.getChildWithName(Identifier("fine")).isValid()){
            dmxstr += "," + VT_GetChildProperty(parent, "fine", "channel", 1).toString();
            if(parent.getChildWithName(Identifier("ultra")).isValid()){
                dmxstr += "," + VT_GetChildProperty(parent, "ultra", "channel", 1).toString();
            }
        }
        return dmxstr;
    }
    
    void SetDMXChannels(ValueTree parent, int dmx_normal, int dmx_fine, int dmx_ultra){
        VT_SetChildProperty(parent, "normal", "channel", dmx_normal);
        if(dmx_fine > 0){
            VT_SetChildProperty(parent, "fine", "channel", dmx_fine);
            if(dmx_ultra > 0){
                VT_SetChildProperty(parent, "ultra", "channel", dmx_ultra);
            }else{
                VT_RemoveChildWithName(parent, "ultra");
            }
        }else{
            VT_RemoveChildWithName(parent, "fine");
            VT_RemoveChildWithName(parent, "ultra");
        }
    }
    
    File fixdir;
    File GetFixtureDirectory() { return fixdir; }
    void SetFixtureDirectory(File d) { fixdir = d; }
    
    ValueTree fixdefs(Identifier("fixdefs"));
    ValueTree GetFixtureDefs() { return fixdefs; }
    String GetFixDefName(ValueTree def){
        String ret = "(";
        if((bool)def.getProperty(Identifier("inuse"), false)){
            ret += "*) (";
        }
        ret += def.getProperty(Identifier("footprint"), "XX").toString() + ") ";
        ret += def.getProperty(Identifier("manufacturer"), "(Manu)").toString() + " ";
        ret += def.getProperty(Identifier("name"), "(Name)").toString() + ": ";
        ret += def.getProperty(Identifier("profile"), "(Profile)").toString();
        return ret;
    }
    
    OwnedArray<Fixture> fixtures;
    void AddFixture(ValueTree def, String name, int fixid, uint16_t uni, uint16_t chn){
        LS_LOCK_WRITE();
        fixtures.add(new Fixture(def, name, fixid, uni, chn));
    }
    void RemoveFixture(int i){
        LS_LOCK_WRITE();
        if(i >= fixtures.size()) return;
        ValueTree def = fixtures[i]->GetDef();
        fixtures.remove(i);
        bool useddef = false;
        for(int j=0; j<fixtures.size(); ++j){
            if(fixtures[j]->GetDef() == def){
                useddef = true;
                break;
            }
        }
        if(!useddef){
            def.setProperty(Identifier("inuse"), false, nullptr);
        }
    }
    int NumFixtures() { return fixtures.size(); }
    Fixture *Fix(int i) {
        LS_LOCK_READ();
        if(i < 0 || i >= fixtures.size()){
            jassertfalse;
            return nullptr;
        }
        return fixtures[i];
    }
    
    class FixtureComparator {
    public:
        static int compareElements(Fixture *first, Fixture *second);
    };
    int FixtureComparator::compareElements(Fixture *first, Fixture *second){
        if(first->GetFixID() == second->GetFixID()){
            uint32_t first_unichn = (uint32_t)first->GetUniverse() << 16 | first->GetChannel();
            uint32_t second_unichn = (uint32_t)second->GetUniverse() << 16 | second->GetChannel();
            return first_unichn < second_unichn ? -1 : first_unichn == second_unichn ? 0 : 1;
        }
        return first->GetFixID() < second->GetFixID() ? -1 : 1;
    }
    void SortFixtures(){
        LS_LOCK_WRITE();
        FixtureComparator fc;
        fixtures.sort(fc, false);
    }
    
}
