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

#include "ControllerSystem.h"
#include "gui/Popup/PopupWindow.h"
#include "gui/Popup/MagicValueEditor.h"

class MagicValueBox : public Component
{
public:
    MagicValueBox(MagicValue *mval) : magic(mval) {
        setSize(32, 16);
    }
    
    ~MagicValueBox() {}
    
    void paint(Graphics &g) override {
        g.setColour(Colours::white);
        g.fillRect(getLocalBounds());
        g.setColour(Colours::black);
        g.drawRect(getLocalBounds(), 1);
        g.setFont(GetNormalFont(12.0f));
        g.drawText(magic->GetText(), 0, 0, getWidth(), getHeight(), 
            Justification::centred, false);
    }
    
    void mouseDown(const MouseEvent &event) override {
        if(isRightClick(event)){
            Point<int> mouse = getMouseXYRelative();
            popup.show<MagicValueEditor>(mouse.x + getScreenX(), mouse.y + getScreenY(), magic);
        }else{
            Component::mouseDown(event);
        }
    }
    
private:
    MagicValue *magic;
    
    PopupWindow popup;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagicValueBox)
};
