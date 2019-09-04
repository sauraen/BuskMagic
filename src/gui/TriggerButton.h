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

#include "MIDISystem.h"
#include "gui/SynthButton.h"
#include "gui/Popup/PopupWindow.h"

class TriggerButton : public SynthButton, public MIDIUser, private Timer
{
public:
    TriggerButton(Button::Listener *l, bool manuallight);
    ~TriggerButton() {}
    
    void mouseDown(const MouseEvent &event) override;
    
    void ReceivedMIDIAction(ActionType t, int val) override;
    
    void SetLight(bool l);

private:
    Button::Listener *parent;
    bool manual;
    
    PopupWindow popup;
    
    void timerCallback() override;
    void TriggeredInternal();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TriggerButton)
};
