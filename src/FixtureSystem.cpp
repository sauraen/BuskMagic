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

#include "LightingSystem.h"
#include "ChannelSystem.h"

#include "gui/MatrixEditor.h"

static void RefreshMatrixEditor(bool invalidate){
    MatrixEditor::mtxed_static->RefreshChannelFilters();
    if(invalidate) MatrixEditor::mtxed_static->RefreshVisibleChannelSet();
}

Fixture::Fixture(ValueTree def_, String name_, int fixid_, uint16_t uni_, uint16_t chn_)
    : def(def_), name(name_), fixid(fixid_), uni(uni_), chn(chn_) {
    def.setProperty(idInUse, true, nullptr);
    for(int p=0; p<def.getNumChildren(); ++p){
        ValueTree param = def.getChild(p);
        String ptype = param.getProperty(idType, "");
        if(ptype == "Generic"){
            Channel *gchan = new Channel(this);
            gchan->SetName(param.getProperty(idName, "Error"));
            gchan->SetLetters(param.getProperty(idLetters, "X"));
            gchan->SetDefaultValue(0.0f);
            gchan->SetOp(Channel::OpAdd);
            channels.add(gchan);
        }else if(ptype == "Color"){
            Channel *hchan = new Channel(this);
            hchan->SetName("Hue - " + param.getProperty(idName, "Error").toString());
            hchan->SetLetters("H");
            hchan->SetDefaultValue(0.0f);
            hchan->SetOp(Channel::OpAdd);
            channels.add(hchan);
            Channel *lchan = new Channel(this);
            lchan->SetName("Lightness - " + param.getProperty(idName, "Error").toString());
            lchan->SetLetters("L");
            lchan->SetDefaultValue(0.0f);
            lchan->SetOp(Channel::OpAdd);
            channels.add(lchan);
        }
    }
}
Fixture::~Fixture() {

}

Fixture::Fixture(ValueTree fx_node){
    int64 defuuid = fx_node.getProperty(idFixDef);
    def = ValueTree();
    for(int i=0; i<FixtureSystem::GetFixtureDefs().getNumChildren(); ++i){
        ValueTree temp = FixtureSystem::GetFixtureDefs().getChild(i);
        if(defuuid == (int64)temp.getProperty(idUUID, 0)){
            def = temp;
            break;
        }
    }
    if(!def.isValid()){
        WarningBox("Internally inconsistent fixture definition UUIDs in showfile!\n"
            "Show state is most likely corrupted!");
        return;
    }
    name = fx_node.getProperty(idName, "name").toString();
    fixid = fx_node.getProperty(idFixID, 0);
    uni = (int)fx_node.getProperty(idUniverse, 0);
    chn = (int)fx_node.getProperty(idChannel, 1);
    for(int i=0; i<fx_node.getNumChildren(); ++i){
        channels.add(new Channel(fx_node.getChild(i), this));
    }
}
ValueTree Fixture::Save(){
    ValueTree ret(idFixture);
    ret.setProperty(idFixDef, def.getProperty(idUUID, 0), nullptr);
    ret.setProperty(idName, name, nullptr);
    ret.setProperty(idFixID, fixid, nullptr);
    ret.setProperty(idUniverse, (int)uni, nullptr);
    ret.setProperty(idChannel, (int)chn, nullptr);
    for(int i=0; i<channels.size(); ++i){
        ret.addChild(channels[i]->Save(), -1, nullptr);
    }
    return ret;
}

String Fixture::GetDescription() const {
    return String(fixid) + ": "
        + hex(uni) + "." + String(chn) + "-"
        + String(chn + (int)def.getProperty(idFootprint, 1) - 1) + ": "
        + name + " (" + def.getProperty(idManufacturer, "(Manu)").toString() + " "
        + def.getProperty(idName, "(Name)").toString() + ")";
}

String Fixture::GetName() const {
    LS_LOCK_READ();
    return name;
}
void Fixture::SetName(String newname){
    LS_LOCK_WRITE();
    name = newname;
    RefreshMatrixEditor(false);
}
void Fixture::SetFixID(int newfixid){
    LS_LOCK_WRITE();
    fixid = newfixid;
    RefreshMatrixEditor(false);
}
void Fixture::SetPatch(uint16_t newuni, uint16_t newchn){
    LS_LOCK_WRITE();
    uni = newuni;
    chn = newchn;
}
Channel *Fixture::GetChannel(int i) const {
    LS_LOCK_READ();
    if(i < 0 || i >= channels.size()){
        jassertfalse;
        return nullptr;
    }
    return channels[i];
}

inline void WriteValueDMXChannel(float &value, ValueTree param, uint16_t dmxchannel,
    uint16_t footprint, uint8_t *out, Identifier precision){
    value *= 256.0f;
    float fv = std::floor(value);
    if(fv > 255.0f) fv = 255.0f;
    uint8_t d = (uint8_t)fv;
    value -= fv;
    ValueTree subnode = param.getChildWithName(precision);
    if(!subnode.isValid()) return;
    uint16_t c = (int)subnode.getProperty(idChannel, 1);
    if(c > footprint) return;
    c += dmxchannel - 2; //Both DMX channel and channel number are 1-indexed
    if(c >= 512) return;
    out[c] = d;
}

inline void WriteAllValueDMXChannels(float value, ValueTree param, uint16_t dmxchannel,
    uint16_t footprint, uint8_t *out){
    if(value > 1.0f) value = 1.0f;
    if(value < 0.0f) value = 0.0f;
    WriteValueDMXChannel(value, param, dmxchannel, footprint, out, idNormal);
    WriteValueDMXChannel(value, param, dmxchannel, footprint, out, idFine);
    WriteValueDMXChannel(value, param, dmxchannel, footprint, out, idUltra);
}

inline void GetHueAndHueMix(ValueTree param, Identifier basecolor, float &hue, float &huemix){
    ValueTree subnode = param.getChildWithName(basecolor);
    if(!subnode.isValid()){
        hue = 0.0f;
        huemix = 0.0f;
    }
    hue = (float)subnode.getProperty(idHue, 0.0f);
    huemix = (float)subnode.getProperty(idHueMix, 0.0f);
}

///Add a multiple of 1.0f to hue until it is between lovalue and 1.0f+lovalue.
inline float WrapHueToRange(float hue, float lovalue){
    float ret = hue + std::ceil(lovalue) - lovalue;
    ret -= std::floor(ret);
    return ret + lovalue;
}

inline void WhiteFadeRGBW(float lightness, float &colorchan){
    if(lightness < 0.5f){
        return;
    }else if(lightness < 1.0f){
        colorchan += ((lightness - 0.5f) * 2.0f) * (1.0f - colorchan);
    }else if(lightness < 1.5f){
        colorchan = (1.5f - lightness) * 2.0f;
    }else{
        colorchan = 0.0f;
    }
}
inline void WhiteFadeRGBNoW(float lightness, float &colorchan){
    if(lightness < 1.0f){
        colorchan += lightness * (1.0f - colorchan);
    }else{
        colorchan = 1.0f;
    }
}
inline void WhiteFadeCMY(float lightness, float &colorchan){
    if(lightness < 1.0f){
        colorchan -= lightness * colorchan;
    }else{
        colorchan = 0.0f;
    }
}

float Fixture::EvaluateChannel(Channel *c, bool isHue){
    if(ControllerSystem::GetFadeDestState() >= 1){
        ControllerSystem::SetEvalSourceState();
        float s = c->Evaluate(0.0f);
        ControllerSystem::SetEvalDestState();
        float d = c->Evaluate(0.0f);
        ControllerSystem::SetEvalSourceState();
        float f = ControllerSystem::GetTransitionFactor();
        if(isHue){
            s -= std::floor(s);
            d -= std::floor(d);
            if(d - s > 0.5f){
                s += 1.0f;
            }else if(d - s < -0.5f){
                d += 1.0f;
            }
            f = (d - s) * f + s;
            return f - std::floor(f);
        }else{
            return (d - s) * f + s;
        }
    }else{
        return c->Evaluate(0.0f);
    }
}

void Fixture::Evaluate(uint8_t *uniarray){
    int footprint = def.getProperty(idFootprint, 1);
    int c = 0;
    for(int p=0; p<def.getNumChildren(); ++p){
        ValueTree param = def.getChild(p);
        String ptype = param.getProperty(idType, "");
        if(ptype == "Generic"){
            float gvalue = EvaluateChannel(channels[c++], false);
            WriteAllValueDMXChannels(gvalue, param, chn, footprint, uniarray);
        }else if(ptype == "Color"){
            float hue = EvaluateChannel(channels[c++], true);
            float lightness = EvaluateChannel(channels[c++], false);
            if(lightness < 0.0f) lightness = 0.0f;
            if(lightness > 1.5f) lightness = 1.5f;
            String colormode = param.getProperty(idColorMode, "RGB");
            const float eps = 0.000001f;
            if(colormode != "CMY"){
                bool hasamber = colormode == "RGBA" || colormode == "RGBAW";
                bool haswhite = colormode == "RGBW" || colormode == "RGBAW";
                float r = 0.0f, a = 0.0f, g = 0.0f, b = 0.0f;
                float rh, rhm, ah, ahm, gh, ghm, bh, bhm;
                GetHueAndHueMix(param, idRed, rh, rhm);
                if(hasamber) GetHueAndHueMix(param, idAmber, ah, ahm);
                GetHueAndHueMix(param, idGreen, gh, ghm);
                GetHueAndHueMix(param, idBlue, bh, bhm);
                if(rhm < rh) rhm += 1.0f;
                if(!hasamber){
                    if(gh < rhm) gh += 1.0f;
                }else{
                    if(ah < rhm) ah += 1.0f;
                    if(ahm < ah) ahm += 1.0f;
                    if(gh < ahm) gh += 1.0f;
                }
                if(ghm < gh) ghm += 1.0f;
                if(bh < ghm) bh += 1.0f;
                if(bhm < bh) bhm += 1.0f;
                if(rh + 1.0f < bhm){
                    std::cout << "Bad hue/huemix values in " << colormode << "fixture!\n";
                }
                hue = WrapHueToRange(hue, rh);
                if(hue >= rh && hue < rhm){
                    r = 1.0f;
                    (hasamber ? a : g) = (hue - rh) / (eps + rhm - rh);
////////////////////////////////////////////////////////////////////////////////
}else if(!hasamber && hue >= rhm && hue < gh){
    g = 1.0f;
    r = (gh - hue) / (eps + gh - rhm);
////////////////////////////////////////////////////////////////////////////////
                            }else if(hasamber && hue >= rhm && hue < ah){
                                a = 1.0f;
                                r = (ah - hue) / (eps + ah - rhm);
                            }else if(hasamber && hue >= ah && hue < ahm){
                                a = 1.0f;
                                g = (hue - ah) / (eps + ahm - ah);
                            }else if(hasamber && hue >= ahm && hue < gh){
                                g = 1.0f;
                                a = (gh - hue) / (eps + gh - ahm);
////////////////////////////////////////////////////////////////////////////////
                }else if(hue >= gh && hue < ghm){
                    g = 1.0f;
                    b = (hue - gh) / (eps + ghm - gh);
                }else if(hue >= ghm && hue < bh){
                    b = 1.0f;
                    g = (bh - hue) / (eps + bh - ghm);
                }else if(hue >= bh && hue < bhm){
                    b = 1.0f;
                    r = (hue - bh) / (eps + bhm - bh);
                }else if(hue >= bhm && hue < 1.0f + rh){
                    r = 1.0f;
                    b = (rh + 1.0f - hue) / (eps + rh + 1.0f - bhm);
                }else{
                    jassertfalse; //Should not be possible even for invalid values
                }
                if(haswhite){
                    float w = lightness < 0.5f ? lightness * 2.0f : 1.0f;
                    WriteAllValueDMXChannels(w, param.getChildWithName(idWhite), chn, footprint, uniarray);
                    WhiteFadeRGBW(lightness, r);
                    if(hasamber) WhiteFadeRGBW(lightness, a);
                    WhiteFadeRGBW(lightness, g);
                    WhiteFadeRGBW(lightness, b);
                }else{
                    WhiteFadeRGBNoW(lightness, r);
                    if(hasamber) WhiteFadeRGBNoW(lightness, a);
                    WhiteFadeRGBNoW(lightness, g);
                    WhiteFadeRGBNoW(lightness, b);
                }
                WriteAllValueDMXChannels(r, param.getChildWithName(idRed), chn, footprint, uniarray);
                if(hasamber) WriteAllValueDMXChannels(a, param.getChildWithName(idAmber), chn, footprint, uniarray);
                WriteAllValueDMXChannels(g, param.getChildWithName(idGreen), chn, footprint, uniarray);
                WriteAllValueDMXChannels(b, param.getChildWithName(idBlue), chn, footprint, uniarray);
            }else{
                float c = 0.0f, m = 0.0f, y = 0.0f;
                float ch, chm, mh, mhm, yh, yhm;
                GetHueAndHueMix(param, idCyan, ch, chm);
                GetHueAndHueMix(param, idMagenta, mh, mhm);
                GetHueAndHueMix(param, idYellow, yh, yhm);
                if(chm < ch) chm += 1.0f;
                if(mh < chm) mh += 1.0f;
                if(mhm < mh) mhm += 1.0f;
                if(yh < mhm) yh += 1.0f;
                if(yhm < yh) yhm += 1.0f;
                if(ch + 1.0f < yhm){
                    std::cout << "Bad hue/huemix values in CMY fixture!\n";
                }
                hue = WrapHueToRange(hue, ch);
                if(hue >= ch && hue < chm){
                    c = 1.0f;
                    m = (hue - ch) / (eps + chm - ch);
                }else if(hue >= chm && hue < mh){
                    m = 1.0f;
                    c = (mh - hue) / (eps + mh - chm);
                }else if(hue >= mh && hue < mhm){
                    m = 1.0f;
                    y = (hue - mh) / (eps + mhm - mh);
                }else if(hue >= mhm && hue < yh){
                    y = 1.0f;
                    m = (yh - hue) / (eps + yh - mhm);
                }else if(hue >= yh && hue < yhm){
                    y = 1.0f;
                    c = (hue - yh) / (eps + yhm - yh);
                }else if(hue >= yhm && hue < 1.0f + ch){
                    c = 1.0f;
                    y = (ch + 1.0f - hue) / (eps + ch + 1.0f - yhm);
                }else{
                    jassertfalse; //Should not be possible even for invalid values
                }
                WhiteFadeCMY(lightness, c);
                WhiteFadeCMY(lightness, m);
                WhiteFadeCMY(lightness, y);
                WriteAllValueDMXChannels(c, param.getChildWithName(idCyan), chn, footprint, uniarray);
                WriteAllValueDMXChannels(m, param.getChildWithName(idMagenta), chn, footprint, uniarray);
                WriteAllValueDMXChannels(y, param.getChildWithName(idYellow), chn, footprint, uniarray);
            }
        }
    }
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
        if(parent.getChildWithName(idFine).isValid()){
            dmxstr += "," + VT_GetChildProperty(parent, "fine", "channel", 1).toString();
            if(parent.getChildWithName(idUltra).isValid()){
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

    ValueTree fixdefs(idFixDefs);
    ValueTree GetFixtureDefs() { return fixdefs; }
    String GetFixDefName(ValueTree def){
        String ret = "(";
        if((bool)def.getProperty(idInUse, false)){
            ret += "*) (";
        }
        ret += def.getProperty(idFootprint, "XX").toString() + ") ";
        ret += def.getProperty(idManufacturer, "(Manu)").toString() + " ";
        ret += def.getProperty(idName, "(Name)").toString() + ": ";
        ret += def.getProperty(idProfile, "(Profile)").toString();
        return ret;
    }

    static OwnedArray<Fixture> fixtures;
    void AddFixture(ValueTree def, String name, int fixid, uint16_t uni, uint16_t chn){
        LS_LOCK_WRITE();
        fixtures.add(new Fixture(def, name, fixid, uni, chn));
        RefreshMatrixEditor(true);
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
            def.setProperty(idInUse, false, nullptr);
        }
        RefreshMatrixEditor(true);
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
            uint32_t first_unichn = (uint32_t)first->GetUniverse() << 16 | first->GetDMXChannel();
            uint32_t second_unichn = (uint32_t)second->GetUniverse() << 16 | second->GetDMXChannel();
            return first_unichn < second_unichn ? -1 : first_unichn == second_unichn ? 0 : 1;
        }
        return first->GetFixID() < second->GetFixID() ? -1 : 1;
    }
    void SortFixtures(){
        LS_LOCK_WRITE();
        FixtureComparator fc;
        fixtures.sort(fc, false);
    }

    void Init(ValueTree fs_node){
        if(fs_node.isValid()){
            fixdir = fs_node.getProperty(idFixDir, "").toString();
            ValueTree d = fs_node.getChildWithName(idFixDefs);
            if(!d.isValid()) { jassertfalse; return; }
            fixdefs = d;
            ValueTree fixnode = fs_node.getChildWithName(idFixtures);
            if(!fixnode.isValid()) { jassertfalse; return; }
            for(int i=0; i<fixnode.getNumChildren(); ++i){
                fixtures.add(new Fixture(fixnode.getChild(i)));
            }
        }
    }
    void Finalize(){
        fixtures.clear();
        fixdefs = ValueTree(idFixDefs);
    }
    ValueTree Save(){
        ValueTree ret(idFixtureSystem);
        ret.setProperty(idFixDir, fixdir.getFullPathName(), nullptr); //TODO relative to showfile
        for(int i=0; i<fixdefs.getNumChildren(); ++i){
            if(!fixdefs.getChild(i).hasProperty(idUUID)){
                fixdefs.getChild(i).setProperty(idUUID, (int64)GenerateUUID(), nullptr);
            }
        }
        ret.addChild(fixdefs, -1, nullptr);
        ValueTree fixnode(idFixtures);
        for(int i=0; i<fixtures.size(); ++i){
            fixnode.addChild(fixtures[i]->Save(), -1, nullptr);
        }
        ret.addChild(fixnode, -1, nullptr);
        return ret;
    }

}
