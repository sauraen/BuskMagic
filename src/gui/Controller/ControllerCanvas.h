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
#include "gui/Controller/SimpleControllerCmp.h"

class ControllerCanvas : public Component, public Timer
{
public:
    ControllerCanvas() {
        ctrlr.reset(new SimpleController());
        ctrlrcmp.reset(new SimpleControllerCmp(ctrlr.get()));
        addAndMakeVisible(ctrlrcmp.get());
        
        setSize(2000, 2000);
        
        startTimerHz(30);
    }

    ~ControllerCanvas() {
        
    }
    
    void timerCallback() override {
        repaint();
    }

    /*
    void paint (Graphics& g) override {
        g.fillAll(LookAndFeel_V4::getDarkColourScheme()
            .getUIColour(LookAndFeel_V4::ColourScheme::windowBackground));
    }
    */
    
    void mouseDown(const MouseEvent &event) override {
        dragbegin_vp = findParentComponentOfClass<Viewport>()->getViewPosition();
    }
    
    void mouseDrag(const MouseEvent &event) override {
        findParentComponentOfClass<Viewport>()->setViewPosition(dragbegin_vp - event.getOffsetFromDragStart());
    }

private:
    std::unique_ptr<SimpleController> ctrlr;
    std::unique_ptr<SimpleControllerCmp> ctrlrcmp;
    
    Point<int> dragbegin_vp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControllerCanvas)
};
