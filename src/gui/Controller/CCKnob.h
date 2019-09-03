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
#include "gui/Popup/MIDIEditor.h"

class CCKnob : public Slider
{
public:
    CCKnob(ContinuousController *cc) : Slider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox), ccontroller(cc) {
        setRotaryParameters((-150.0f + 360.0f) * 3.14159f / 180.0f,  
            (150.0f + 360.0f) * 3.14159f / 180.0f, true);
        setMouseDragSensitivity(200);
        setVelocityBasedMode(false);
        setRange(0.0, 1.0, 0.0);
        setSize(64, 64);
        setValue(ccontroller->GetKnobDisplay(), dontSendNotification);
    }

    ~CCKnob(){
        
    }
    
    void paint(Graphics &g) override {
        setValue(ccontroller->GetKnobDisplay(), dontSendNotification);
        Slider::paint(g);
    }
    
    void mouseDown(const MouseEvent &event) override {
        if(isRightClick(event)){
            Point<int> mouse = getMouseXYRelative();
            MIDIEditor::Startup startup(ccontroller, 2);
            popup.show<MIDIEditor>(mouse.x + getScreenX(), mouse.y + getScreenY(), &startup);
        }else{
            Slider::mouseDown(event);
        }
    }

private:
    ContinuousController *ccontroller;
    
    PopupWindow popup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CCKnob)
};
