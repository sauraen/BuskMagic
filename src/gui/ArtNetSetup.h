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
class ArtNetSetup  : public Component,
                     public TextListBox::Listener,
                     public TextEditor::Listener,
                     public Timer,
                     public Button::Listener
{
public:
    //==============================================================================
    ArtNetSetup ();
    ~ArtNetSetup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    void rowSelected(TextListBox *parent, int row) override;
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* artnet_logo_png;
    static const int artnet_logo_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<TextListBox> lstDevices;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblHeader;
    std::unique_ptr<Label> lblDeviceType;
    std::unique_ptr<Label> lblDeviceStatus;
    std::unique_ptr<Label> lblIP;
    std::unique_ptr<TextEditor> txtIP;
    std::unique_ptr<TextButton> btnIP;
    std::unique_ptr<Label> lblUniverseHeader;
    std::unique_ptr<Label> lblUni;
    std::unique_ptr<ToggleButton> chkMap;
    std::unique_ptr<TextEditor> txtUniNet;
    std::unique_ptr<Label> lblUniPt1;
    std::unique_ptr<TextEditor> txtUniSub;
    std::unique_ptr<Label> lblUniPt2;
    std::unique_ptr<TextEditor> txtUniInputs;
    std::unique_ptr<Label> lblUniSlash1;
    std::unique_ptr<TextEditor> txtUniOutputs;
    std::unique_ptr<TextEditor> txtMapNet;
    std::unique_ptr<Label> lblUniPt3;
    std::unique_ptr<TextEditor> txtMapSub;
    std::unique_ptr<Label> lblUniPt4;
    std::unique_ptr<TextEditor> txtMapInputs;
    std::unique_ptr<Label> lblUniSlash2;
    std::unique_ptr<TextEditor> txtMapOutputs;
    std::unique_ptr<TextButton> btnChangeUni;
    std::unique_ptr<TextButton> btnAddDevice;
    std::unique_ptr<TextButton> btnRemoveDevice;
    std::unique_ptr<Label> lblMAC;
    std::unique_ptr<ToggleButton> optPollNo;
    std::unique_ptr<ToggleButton> optPollStatic;
    std::unique_ptr<ToggleButton> optPollDHCP;
    std::unique_ptr<TextEditor> txtShortName;
    std::unique_ptr<Label> lblNameSlash;
    std::unique_ptr<TextEditor> txtLongName;
    std::unique_ptr<Label> lblDeviceExtra;
    Image cachedImage_artnet_logo_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArtNetSetup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
