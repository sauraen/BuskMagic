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

#include <atomic>

class MIDIEditor : public Component, public TextEditor::Listener, 
    public Button::Listener, public MIDIUser::Refreshable, private Timer {
public:
    struct Startup{
        MIDIUser *user;
        int mode; //0: normal / 1: only button-related / 2: only knob-related
        Startup(MIDIUser *u, int m) : user(u), mode(m) {}
    };
    
    MIDIEditor(void *data);
    virtual ~MIDIEditor();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    void buttonClicked(Button* buttonThatWasClicked) override;
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    
    void RefreshAfterMIDILearn() override;
private:
    MIDIUser *user;
    Array<TextEditor*> txtsSetting;
    Array<TextButton*> btnsLearn;
    std::unique_ptr<TextButton> btnHelp;
    std::atomic_flag notNeedsMIDIRefresh;
    void timerCallback() override;
};
