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

class SynthButton : public Button
{
public:
    SynthButton() : Button("SynthButton"), col(Colours::red) {
        setSize(48, 32);
    }

    ~SynthButton() {}
    
    void SetColor(Colour newcolor) { col = newcolor; repaint(); }

    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
        Colour c;
        if(getToggleState()){
            c = col;
        }else{
            c = col.withMultipliedSaturation(0.2f).withMultipliedBrightness(0.7f);
        }
        if(shouldDrawButtonAsHighlighted){
            c = c.brighter(0.25f);
        }
        if(shouldDrawButtonAsDown){
            c = c.darker(0.4f);
        }
        g.setColour(c);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 5);
        g.setColour(Colours::lightgrey);
        g.drawRoundedRectangle(getLocalBounds().toFloat(), 5, 1);
    }

private:
    Colour col;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthButton)
};
