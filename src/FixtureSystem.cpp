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
}
