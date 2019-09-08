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
#include <cassert>

inline bool isInt(String str, bool allowNegative = true){
    str = str.trim();
    if(str.isEmpty()) return false;
    CharPointer_UTF32 s = str.toUTF32();
    for(int i=0; i<s.length(); ++s){
        if(s[i] == '-'){
            if(i != 0 || !allowNegative) return false;
            continue;
        }else if(s[i] >= '0' && s[i] <= '9'){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

inline bool isHex(String str, bool allow0x = true){
    str = str.trim().toLowerCase();
    if(str.isEmpty()) return false;
    if(str.startsWith("0x") && allow0x) str = str.substring(2);
    CharPointer_UTF32 s = str.toUTF32();
    for(int i=0; i<s.length(); ++s){
        if((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

inline bool isDec(String str, bool allowNegative = true){
    str = str.trim();
    if(str.isEmpty()) return false;
    CharPointer_UTF32 s = str.toUTF32();
    bool decimalpoint = false;
    for(int i=0; i<s.length(); ++s){
        if(s[i] == '-'){
            if(i != 0 || !allowNegative) return false;
            continue;
        }else if(s[i] == '.'){
            if(decimalpoint) return false;
            decimalpoint = true;
            continue;
        }else if(s[i] >= '0' && s[i] <= '9'){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

template<typename INT_TYPE> inline String hex(INT_TYPE i, int bits){
    String ret;
    while(bits > 0){
        uint8_t nybble = i & 0xF;
        if(nybble <= 9) ret = String::charToString('0' + nybble) + ret;
        else ret = String::charToString('A' + nybble - 0xA) + ret;
        i >>= 4;
        bits -= 4;
    }
    return ret;
}

inline String hex(uint8_t i) { return hex(i, 8); }
inline String hex(uint16_t i) { return hex(i, 16); }
inline String hex(uint32_t i) { return hex(i, 32); }

inline String safeASCII(char c){
    if(c >= ' ' && c <= '~') return String::charToString(c);
    return "_";
}

inline bool isMac(){
#ifdef JUCE_MAC
    return true;
#else
    return false;
#endif
}

inline bool isRightClick(const MouseEvent &event){
    return event.mods.isRightButtonDown() || (isMac() && event.mods.isCtrlDown());
}

inline void WarningBox(String text, String title = "BuskMagic"){
    NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, title, text);
}

inline void InfoBox(String text, String title = "BuskMagic"){
    NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, title, text);
}

#define NULLSTATEMENT ((void)0)
#define REQUIRESEMICOLON do{NULLSTATEMENT;} while(false)

#define FROMLOOKANDFEEL(colorType) \
    LookAndFeel::getDefaultLookAndFeel().findColour(colorType)
    
inline Colour LFWindowColor(){
    return FROMLOOKANDFEEL(ResizableWindow::backgroundColourId);
}
inline Colour LFWidgetColor(){
    return FROMLOOKANDFEEL(TextEditor::backgroundColourId);
}

#undef FROMLOOKANDFEEL

#define TEXTCHANGEDHANDLER_PRE \
    bool turnRed = false; \
    String text = editorThatWasChanged.getText(); \
    bool isint = isInt(text); \
    int val = text.getIntValue(); \
    bool ishex = isHex(text); \
    int hexval = text.getHexValue32(); \
    bool isdec = isDec(text); \
    float decval = text.getFloatValue(); \
    REQUIRESEMICOLON

#define TEXTCHANGEDHANDLER_POST \
    TurnRed(&editorThatWasChanged, turnRed); \
    ignoreUnused(isint); \
    ignoreUnused(val); \
    ignoreUnused(ishex); \
    ignoreUnused(hexval); \
    ignoreUnused(isdec); \
    ignoreUnused(decval); \
    REQUIRESEMICOLON
    
inline void TurnRed(TextEditor *ed, bool turnRed = true){
    ed->setColour(TextEditor::backgroundColourId,
        turnRed ? Colours::red : LFWidgetColor());
    ed->repaint();
}
inline void TurnRed(const std::unique_ptr<TextEditor> &ed, bool turnRed = true){
    TurnRed(ed.get(), turnRed);
}

inline void ConfigureTextEditor(std::unique_ptr<TextEditor> &ed, 
        TextEditor::Listener *parent, String text){
    ed->setMultiLine(false);
    ed->setReadOnly(false);
    ed->setScrollbarsShown(false);
    ed->setCaretVisible(true);
    ed->setPopupMenuEnabled(true);
    ed->setReturnKeyStartsNewLine(false);
    ed->setEscapeAndReturnKeysConsumed(false);
    ed->setSelectAllWhenFocused(true);
    ed->addListener(parent);
    ed->setText(text);
}

inline void ConfigureOptionButton(std::unique_ptr<ToggleButton> &opt,
        Button::Listener *parent, int radiogroup, Colour col, String text, bool val){
    opt->addListener(parent);
    opt->setRadioGroupId(radiogroup, dontSendNotification);
    opt->setButtonText(text);
    opt->setToggleState(val, dontSendNotification);
    opt->setColour(ToggleButton::textColourId, col);
    opt->setColour(ToggleButton::tickColourId, col);
    opt->setColour(ToggleButton::tickDisabledColourId, col);
}

inline Font GetNormalFont(float size = 15.0f){
    return Font(size, Font::plain).withTypefaceStyle("Regular");
}

inline Colour GetTextColorFor(Colour background){
    return background.getBrightness() > 0.5f ? Colours::black : Colours::white;
}

inline Colour ShowColorChooserWindow(Colour initcolor, Component *optionalparent = nullptr){
    std::unique_ptr<ColourSelector> colsel(new ColourSelector(
        ColourSelector::showColourAtTop |
        ColourSelector::showSliders |
        ColourSelector::showColourspace
    ));
    colsel->setCurrentColour(initcolor, dontSendNotification);
    colsel->setSize(300, 300);
    DialogWindow::LaunchOptions opts;
    opts.dialogTitle = "BuskMagic - Select a color\n";
    opts.content.set(colsel.get(), false);
    opts.componentToCentreAround = optionalparent;
    opts.runModal();
    return colsel->getCurrentColour();
}

inline void SeedRNG(){
    Random::getSystemRandom().setSeedRandomly();
}
inline int64_t GenerateUUID(){
    return Random::getSystemRandom().nextInt64();
}

inline var VT_GetChildProperty(ValueTree v, Identifier cname, Identifier pname, const var &defval = ""){
    return v.getOrCreateChildWithName(cname, nullptr).getProperty(pname, defval);
}
inline void VT_SetChildProperty(ValueTree v, Identifier cname, Identifier pname, const var &value){
    //std::cout << "Setting " << cname.toString() << " " << pname.toString() << " to " << value.toString() << "\n"; //TODO XXX
    v.getOrCreateChildWithName(cname, nullptr).setProperty(pname, value, nullptr);
}
inline void VT_RemoveChildWithName(ValueTree v, Identifier name){
    ValueTree c = v.getChildWithName(name);
    if(c.isValid()){
        v.removeChild(c, nullptr);
    }
}

inline ValueTree VT_Load(File f, Identifier topleveltype){
    if(!f.existsAsFile()){
        std::cout << "File " << f.getFullPathName() << " does not exist\n";
        return ValueTree();
    }
    std::unique_ptr<XmlElement> fix_xml = parseXML(f);
    if(fix_xml == nullptr){
        std::cout << "File " << f.getFullPathName() << " is not valid XML\n";
        return ValueTree();
    }
    ValueTree v = ValueTree::fromXml(*fix_xml);
    if(!v.isValid()){
        std::cout << "File " << f.getFullPathName() << " is not a valid Juce ValueTree\n";
        return ValueTree();
    }
    if(!v.hasType(topleveltype)){
        std::cout << "File " << f.getFullPathName() << " is not the correct type of ValueTree (" << topleveltype.toString() << ")\n";
        return ValueTree();
    }
    return v;
}

inline bool VT_Save(ValueTree vt, File f, String extension, String commentinsides){
    std::unique_ptr<XmlElement> xml(vt.createXml());
    return xml->writeToFile(f.withFileExtension(extension), 
        "<!-- " + commentinsides + " -->", "UTF-8", 60);
}

//Identifiers
extern Identifier idBuskMagicShow;
extern Identifier idArtNetSystem;
extern Identifier idMIDISystem;
extern Identifier idTimingSystem;
extern Identifier idChannelSystem;
extern Identifier idFixtureSystem;
extern Identifier idControllerSystem;
extern Identifier idLightingSystem;
//Common attributes
extern Identifier idUUID;
extern Identifier idName;
extern Identifier idLetters;
extern Identifier idType;
extern Identifier idMode;
extern Identifier idAction;
extern Identifier idParam;
//I/O attributes
extern Identifier idNet;
extern Identifier idMapNet;
extern Identifier idSubnet;
extern Identifier idMapSubnet;
extern Identifier idUniverse;
extern Identifier idChannel;
extern Identifier idPort;
extern Identifier idNote;
extern Identifier idVel;
//Objects
extern Identifier idPhasor;
extern Identifier idController;
extern Identifier idFixDefs;
extern Identifier idFixtures;
extern Identifier idFixture;
extern Identifier idStates;
extern Identifier idState;
extern Identifier idMIDIUser;
extern Identifier idMIDISetting;
//ArtNetSystem
extern Identifier idPollMode;
extern Identifier idArtNetDevice;
extern Identifier idStyle;
extern Identifier idMap;
extern Identifier idInUni;
extern Identifier idOutUni;
extern Identifier idMapInUni;
extern Identifier idMapOutUni;
extern Identifier idBindIndex;
extern Identifier idIP;
extern Identifier idShortName;
extern Identifier idLongName;
//MIDISystem
extern Identifier idInPorts;
extern Identifier idInPort;
extern Identifier idOutPorts;
extern Identifier idOutPort;
extern Identifier idDevName;
extern Identifier idOut;
extern Identifier idContinuous;
//TimingSystem
extern Identifier idTempoMS;
extern Identifier idMeasureLen;
extern Identifier idOnlyInt;
//ChannelSystem
extern Identifier idMag;
extern Identifier idAngle;
extern Identifier idDefaultValue;
extern Identifier idOp;
//FixtureSystem
extern Identifier idInUse;
extern Identifier idManufacturer;
extern Identifier idProfile;
extern Identifier idFootprint;
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
extern Identifier idFixDir;
extern Identifier idFixDef;
extern Identifier idFixID;
//ControllerSystem
extern Identifier idMagicValue;
extern Identifier idMuggleValue;
extern Identifier idPosX;
extern Identifier idPosY;
extern Identifier idNoState;
extern Identifier idGroup;
extern Identifier idColor;
extern Identifier idGroupColor;
extern Identifier idEnabled;
extern Identifier idKnob;
extern Identifier idShape;
extern Identifier idTimeBase;
extern Identifier idNStates;
extern Identifier idDState;
extern Identifier idSState;
extern Identifier idProtected;
