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
#include "gui/TriggerButton.h"
#include "gui/HoldButton.h"

class StatesWindow 
    : public Component, public Button::Listener, public HoldButton::Listener, 
    public TextEditor::Listener, private Timer
{
public:
    static StatesWindow *sw_static;
    
    StatesWindow(ValueTree sw_node);
    ~StatesWindow();
    ValueTree Save();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    void buttonClicked(Button *buttonThatWasClicked) override;
    void holdButtonStateChanged(HoldButton *buttonWhoseStateChanged) override;
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    
    void HandleMIDI(int port, MidiMessage msg);
    
private:
    OwnedArray<TriggerButton> trgsState;
    std::unique_ptr<ToggleButton> chkProtected;
    std::unique_ptr<TextEditor> txtFade;
    std::unique_ptr<HoldButton> btnCopy;
    std::unique_ptr<HoldButton> btnBlind;
    std::unique_ptr<TextButton> btnAdd;
    std::unique_ptr<TextButton> btnRemove;
    int guistate;
    int copyfrom;
    
    bool blinker;
    void timerCallback() override;
    
    void MakeButton(int i, ValueTree buttons_node);
    void ChangeSize();
    void SetOnlyLight(int i);
};
