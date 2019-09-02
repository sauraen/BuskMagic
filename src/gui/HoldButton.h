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

class HoldButton : public SynthButton, private Timer
{
public:
    HoldButton(Button::Listener *l);
    ~HoldButton() {}
    
    void mouseDown(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;
    
    void HandleMIDI(int port, MidiMessage msg);
    String GetMIDISettingStr(MIDISetting::Type type);
    bool SetMIDISettingFromStr(MIDISetting::Type type, String str);
    void LearnMIDI(int port, MidiMessage msg);

private:
    Button::Listener *parent;
    
    PopupWindow popup;
    OwnedArray<MIDISetting> midisettings;
    
    void timerCallback() override;
    void TriggeredInternal();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoldButton)
};
