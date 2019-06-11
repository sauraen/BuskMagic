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

inline bool isInt(String str, bool allowNegative = true){
    str = str.trim();
    if(str.isEmpty()) return false;
    CharPointer_UTF32 s = str.toUTF32();
    for(int i=0; i<s.length(); ++s){
        if(s[i] == '-'){
            if(i != 0 || !allowNegative) return false;
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
