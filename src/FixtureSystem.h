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

#pragma once
#include "JuceHeader.h"
#include "Common.h"

extern Identifier idFixDefs;
extern Identifier idFixture;
extern Identifier idInUse;
extern Identifier idType;
extern Identifier idName;
extern Identifier idLetters;
extern Identifier idManufacturer;
extern Identifier idProfile;
extern Identifier idFootprint;

extern Identifier idParam;
extern Identifier idChannel;
extern Identifier idNormal;
extern Identifier idFine;
extern Identifier idUltra;
extern Identifier idHue;
extern Identifier idHueMix;
extern Identifier idColorMode;

extern Identifier idRed;
extern Identifier idGreen;
extern Identifier idBlue;
extern Identifier idAmber;
extern Identifier idWhite;
extern Identifier idUV;
extern Identifier idCyan;
extern Identifier idMagenta;
extern Identifier idYellow;

class Channel;

#define DMXTEXTCHANGEDHANDLER \
    int dmx_normal, dmx_fine, dmx_ultra; \
    bool dmx_ok = FixtureSystem::ParseDMXText(text, \
            (int)param.getParent().getProperty(idFootprint, 1), \
            dmx_normal, dmx_fine, dmx_ultra); \
    REQUIRESEMICOLON

class Fixture {
public:
    Fixture(ValueTree def_, String name_, int fixid_, uint16_t uni_, uint16_t chn_);
    ~Fixture();
    
    String GetDescription() const;
    
    inline ValueTree GetDef() const { return def; }
    
    String GetName() const;
    void SetName(String newname);
    
    inline int GetFixID() const { return fixid; }
    void SetFixID(int newfixid);
    
    inline uint16_t GetUniverse() const { return uni; }
    inline uint16_t GetDMXChannel() const { return chn; }
    void SetPatch(uint16_t newuni, uint16_t newchn);
    
    inline int GetNumChannels() const { return channels.size(); }
    Channel *GetChannel(int i) const;
    
    void Evaluate(uint8_t *uniarray);
private:
    ValueTree def;
    String name;
    int fixid;
    uint16_t uni, chn;
    OwnedArray<Channel> channels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Fixture)
};

namespace FixtureSystem {
    bool ParseDMXText(String text, int footprint, int &normal, int &fine, int &ultra);
    String GetDMXText(ValueTree parent);
    void SetDMXChannels(ValueTree parent, int dmx_normal, int dmx_fine, int dmx_ultra);
    
    File GetFixtureDirectory();
    void SetFixtureDirectory(File d);
    
    ValueTree GetFixtureDefs();
    String GetFixDefName(ValueTree def);
    
    void AddFixture(ValueTree def, String name, int fixid, uint16_t uni, uint16_t chn);
    void RemoveFixture(int i);
    int NumFixtures();
    Fixture *Fix(int i);
    void SortFixtures();
}
