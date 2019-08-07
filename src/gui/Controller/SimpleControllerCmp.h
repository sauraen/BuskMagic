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
#include "gui/Controller/EnableButton.h"
#include "gui/Popup/PopupWindow.h"
#include "gui/Popup/CtrlrEditor.h"

class ControllerCanvas;

class SimpleControllerCmp : public Component
{
public:
    SimpleControllerCmp(SimpleController *c) : controller(c){
        btnEnable.reset(new EnableButton(controller));
        addAndMakeVisible(btnEnable.get());
        btnEnable->setTopLeftPosition(8, 24);
        
        setSize(64, 88);
    }

    ~SimpleControllerCmp() {
        btnEnable = nullptr;
    }

    void paint (Graphics& g) override {
        g.fillAll(controller->GetGroupColor());
        g.setColour(controller->GetGroupColor().getBrightness() > 0.5f ? Colours::black : Colours::white);
        g.setFont (10.0f);
        g.drawMultiLineText(controller->GetName(), 0, 70, 64, Justification::centred);
    }

    void resized() override {}
    
    void mouseDown(const MouseEvent &event) override {
        if(event.mods.isLeftButtonDown()){
            dragbegin_local = event.getMouseDownPosition();
            beginDragAutoRepeat(20);
        }else if(isRightClick(event)){
            popup.show<CtrlrEditor>(event.getScreenX(), event.getScreenY(), controller);
        }
    }
    
    void mouseDrag(const MouseEvent &event) override;

private:
    SimpleController *controller;
    
    Point<int> dragbegin_local;
    
    std::unique_ptr<EnableButton> btnEnable;
    
    PopupWindow popup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleControllerCmp)
};
