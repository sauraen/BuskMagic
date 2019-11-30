/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

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
#include "gui/TextListBox.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class USBDMXSetup  : public Component,
                     public TextListBox::Listener,
                     public TextEditor::Listener,
                     public Timer,
                     public Button::Listener
{
public:
    //==============================================================================
    USBDMXSetup ();
    ~USBDMXSetup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    void rowSelected(TextListBox *parent, int row) override;
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblDevices;
    std::unique_ptr<TextButton> btnMap;
    std::unique_ptr<Label> lblDeviceInfo;
    std::unique_ptr<Label> lblName;
    std::unique_ptr<TextEditor> txtName;
    std::unique_ptr<Label> lblUniverse;
    std::unique_ptr<TextEditor> txtUniverse;
    std::unique_ptr<TextButton> btnUnmap;
    std::unique_ptr<TextButton> btnAddSlot;
    std::unique_ptr<TextButton> btnRemoveSlot;
    std::unique_ptr<Label> lblMapBy;
    std::unique_ptr<ToggleButton> optMapPort;
    std::unique_ptr<ToggleButton> optMapType;
    std::unique_ptr<TextButton> btnMapHelp;
    std::unique_ptr<Label> lblType;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (USBDMXSetup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

