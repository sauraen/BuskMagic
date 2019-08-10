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

class PopupWindow : public Component
{
public:
    PopupWindow() {}

    ~PopupWindow() {
        contents = nullptr;
    }
    
    void paint(Graphics &g) override {
        //Should never be called
        g.fillAll(Colours::orange);
    }
    
    template<class ContentComponent> void show(int x, int y, void *contentdata){
        if(contents != nullptr) reset();
        contents.reset(new ContentComponent(contentdata));
        addAndMakeVisible(contents.get());
        setSize(contents->getWidth(), contents->getHeight());
        setOpaque(true);
        addToDesktop(ComponentPeer::windowIsTemporary | ComponentPeer::windowHasDropShadow);
        setVisible(true);
        setTopLeftPosition(x, y);
        contents->grabKeyboardFocus();
    }
    
    void reset(){
        if(contents == nullptr) return;
        contents = nullptr;
        setVisible(false);
        removeFromDesktop();
    }

    void focusOfChildComponentChanged(FocusChangeType cause) override {
        if(hasKeyboardFocus(true)) return;
        reset();
    }
    
    bool keyPressed(const KeyPress &key) override {
        if(key.getKeyCode() == KeyPress::escapeKey){
            reset();
            return true;
        }
        return false;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PopupWindow)
    
    std::unique_ptr<Component> contents;
};
