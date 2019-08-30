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
#include "gui/SynthButton.h"
#include "ControllerSystem.h"
#include "gui/Popup/PopupWindow.h"
#include "gui/Popup/ButtonMIDI.h"

class EnableButton : public SynthButton
{
public:
    EnableButton(Controller *c) : controller(c) {
        SetColor(controller->GetColor());
        setToggleState(controller->IsEnabled(), dontSendNotification);
        setTriggeredOnMouseDown(false);
    }

    ~EnableButton(){
        
    }
    
    void paint(Graphics &g) override {
        SetColor(controller->GetColor());
        setToggleState(controller->IsEnabled(), dontSendNotification);
        SynthButton::paint(g);
    }
    
    void mouseDown(const MouseEvent &event) override {
        if(isRightClick(event)){
            Point<int> mouse = getMouseXYRelative();
            popup.show<ButtonMIDI>(mouse.x + getScreenX(), mouse.y + getScreenY(), controller);
        }else{
            SynthButton::mouseDown(event);
        }
    }

    void mouseUp(const MouseEvent &event) override {
        if(!isRightClick(event) && event.mods.isLeftButtonDown()){
            setToggleState(!getToggleState(), dontSendNotification);
            controller->SetEnabled(getToggleState());
        }else{
            SynthButton::mouseUp(event);
        }
    }

private:
    Controller *controller;
    
    PopupWindow popup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnableButton)
};
