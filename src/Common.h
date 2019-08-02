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

inline void WarningBox(String text){
    NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "BuskMagic", text);
}

#define NULLSTATEMENT ((void)0)
#define REQUIRESEMICOLON do{NULLSTATEMENT;} while(false)

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
    REQUIRESEMICOLON
    
inline void TurnRed(TextEditor *ed, bool turnRed = true){
    ed->setColour(TextEditor::backgroundColourId,
        turnRed ? Colours::red : LookAndFeel_V4::getDarkColourScheme()
        .getUIColour(LookAndFeel_V4::ColourScheme::widgetBackground));
    ed->repaint();
}
inline void TurnRed(const std::unique_ptr<TextEditor> &ed, bool turnRed = true){
    TurnRed(ed.get(), turnRed);
}

inline var VT_GetChildProperty(ValueTree v, String cname, String pname, const var &defval = ""){
    return v.getOrCreateChildWithName(Identifier(cname), nullptr).getProperty(Identifier(pname), defval);
}
inline void VT_SetChildProperty(ValueTree v, String cname, String pname, const var &value){
    v.getOrCreateChildWithName(Identifier(cname), nullptr).setProperty(Identifier(pname), value, nullptr);
}
inline void VT_RemoveChildWithName(ValueTree v, String name){
    ValueTree c = v.getChildWithName(Identifier(name));
    if(c.isValid()){
        v.removeChild(c, nullptr);
    }
}

inline ValueTree VT_Load(File f, String topleveltype){
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
    if(!v.hasType(Identifier(topleveltype))){
        std::cout << "File " << f.getFullPathName() << " is not the correct type of ValueTree (" << topleveltype << ")\n";
        return ValueTree();
    }
    return v;
}
    
    
