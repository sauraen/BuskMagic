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
#include "gui/TextListModel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MIDISetup  : public Component,
                   public TextListModel::Listener,
                   public Button::Listener
{
public:
    //==============================================================================
    MIDISetup ();
    ~MIDISetup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row) override;
    void rowDoubleClicked(TextListModel* parent, int row) override;

    void refreshLists();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<TextListModel> lsmInDevices;
    std::unique_ptr<ListBox> lstInDevices;
    std::unique_ptr<TextListModel> lsmInPorts;
    std::unique_ptr<ListBox> lstInPorts;
    std::unique_ptr<TextListModel> lsmOutDevices;
    std::unique_ptr<ListBox> lstOutDevices;
    std::unique_ptr<TextListModel> lsmOutPorts;
    std::unique_ptr<ListBox> lstOutPorts;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblInputDevices;
    std::unique_ptr<Label> lblInputPorts;
    std::unique_ptr<TextButton> btnAddInPort;
    std::unique_ptr<TextButton> btnRemoveInPort;
    std::unique_ptr<TextButton> btnAssignInPort;
    std::unique_ptr<TextButton> btnUnassignInPort;
    std::unique_ptr<Label> lblOutputDevices;
    std::unique_ptr<Label> lblOutputPorts;
    std::unique_ptr<TextButton> btnAddOutPort;
    std::unique_ptr<TextButton> btnRemoveOutPort;
    std::unique_ptr<TextButton> btnAssignOutPort;
    std::unique_ptr<TextButton> btnUnassignOutPort;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDISetup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

