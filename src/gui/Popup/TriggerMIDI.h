/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

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

#include "JuceHeader.h"
#include "Common.h"

#include "MIDISystem.h"
#include "gui/TriggerButton.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TriggerMIDI  : public Component,
                     public TextEditor::Listener,
                     public Button::Listener
{
public:
    //==============================================================================
    TriggerMIDI (void *data);
    ~TriggerMIDI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TriggerButton *triggerbtn;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblOn;
    std::unique_ptr<Label> lblOutOn;
    std::unique_ptr<TextEditor> txtTrig;
    std::unique_ptr<TextButton> btnLearnTrig;
    std::unique_ptr<TextEditor> txtOutOn;
    std::unique_ptr<Label> lblOutOff;
    std::unique_ptr<TextEditor> txtOutOff;
    std::unique_ptr<TextButton> btnHelp;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TriggerMIDI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

