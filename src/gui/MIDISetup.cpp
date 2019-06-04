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

//[Headers] You can add your own extra header files here...

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

#include "MIDISystem.h"
//[/Headers]

#include "MIDISetup.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MIDISetup::MIDISetup ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblInputDevices.reset (new Label ("lblInputDevices",
                                      TRANS("Input devices:")));
    addAndMakeVisible (lblInputDevices.get());
    lblInputDevices->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblInputDevices->setJustificationType (Justification::centredLeft);
    lblInputDevices->setEditable (false, false, false);
    lblInputDevices->setColour (TextEditor::textColourId, Colours::black);
    lblInputDevices->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblInputDevices->setBounds (0, 0, 176, 24);

    lblInputPorts.reset (new Label ("lblInputPorts",
                                    TRANS("Input ports:")));
    addAndMakeVisible (lblInputPorts.get());
    lblInputPorts->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblInputPorts->setJustificationType (Justification::centredLeft);
    lblInputPorts->setEditable (false, false, false);
    lblInputPorts->setColour (TextEditor::textColourId, Colours::black);
    lblInputPorts->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblInputPorts->setBounds (224, 0, 128, 24);

    btnAddInPort.reset (new TextButton ("btnAddInPort"));
    addAndMakeVisible (btnAddInPort.get());
    btnAddInPort->setButtonText (TRANS("+"));
    btnAddInPort->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnAddInPort->addListener (this);

    btnAddInPort->setBounds (352, 0, 23, 24);

    btnRemoveInPort.reset (new TextButton ("btnRemoveInPort"));
    addAndMakeVisible (btnRemoveInPort.get());
    btnRemoveInPort->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveInPort->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnRemoveInPort->addListener (this);

    btnRemoveInPort->setBounds (376, 0, 23, 24);

    btnAssignInPort.reset (new TextButton ("btnAssignInPort"));
    addAndMakeVisible (btnAssignInPort.get());
    btnAssignInPort->setButtonText (CharPointer_UTF8 ("\xe2\x86\x92"));
    btnAssignInPort->setConnectedEdges (Button::ConnectedOnBottom);
    btnAssignInPort->addListener (this);

    btnAssignInPort->setBounds (184, 72, 32, 24);

    btnUnassignInPort.reset (new TextButton ("btnUnassignInPort"));
    addAndMakeVisible (btnUnassignInPort.get());
    btnUnassignInPort->setButtonText (TRANS("X"));
    btnUnassignInPort->setConnectedEdges (Button::ConnectedOnTop);
    btnUnassignInPort->addListener (this);

    btnUnassignInPort->setBounds (184, 96, 32, 24);

    lblOutputDevices.reset (new Label ("lblOutputDevices",
                                       TRANS("Output devices:")));
    addAndMakeVisible (lblOutputDevices.get());
    lblOutputDevices->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOutputDevices->setJustificationType (Justification::centredLeft);
    lblOutputDevices->setEditable (false, false, false);
    lblOutputDevices->setColour (TextEditor::textColourId, Colours::black);
    lblOutputDevices->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOutputDevices->setBounds (0, 184, 175, 24);

    lblOutputPorts.reset (new Label ("lblOutputPorts",
                                     TRANS("Output ports:")));
    addAndMakeVisible (lblOutputPorts.get());
    lblOutputPorts->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOutputPorts->setJustificationType (Justification::centredLeft);
    lblOutputPorts->setEditable (false, false, false);
    lblOutputPorts->setColour (TextEditor::textColourId, Colours::black);
    lblOutputPorts->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOutputPorts->setBounds (224, 184, 127, 24);

    btnAddOutPort.reset (new TextButton ("btnAddOutPort"));
    addAndMakeVisible (btnAddOutPort.get());
    btnAddOutPort->setButtonText (TRANS("+"));
    btnAddOutPort->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnAddOutPort->addListener (this);

    btnAddOutPort->setBounds (352, 184, 23, 24);

    btnRemoveOutPort.reset (new TextButton ("btnRemoveOutPort"));
    addAndMakeVisible (btnRemoveOutPort.get());
    btnRemoveOutPort->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveOutPort->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnRemoveOutPort->addListener (this);

    btnRemoveOutPort->setBounds (376, 184, 23, 24);

    btnAssignOutPort.reset (new TextButton ("btnAssignOutPort"));
    addAndMakeVisible (btnAssignOutPort.get());
    btnAssignOutPort->setButtonText (CharPointer_UTF8 ("\xe2\x86\x92"));
    btnAssignOutPort->setConnectedEdges (Button::ConnectedOnBottom);
    btnAssignOutPort->addListener (this);

    btnAssignOutPort->setBounds (184, 256, 32, 24);

    btnUnassignOutPort.reset (new TextButton ("btnUnassignOutPort"));
    addAndMakeVisible (btnUnassignOutPort.get());
    btnUnassignOutPort->setButtonText (TRANS("X"));
    btnUnassignOutPort->setConnectedEdges (Button::ConnectedOnTop);
    btnUnassignOutPort->addListener (this);

    btnUnassignOutPort->setBounds (184, 280, 32, 24);


    //[UserPreSize]

    lsmInDevices.reset(new TextListModel());
    lsmInDevices->setListener(this);
    lstInDevices.reset(new ListBox("InDevices", lsmInDevices.get()));
    addAndMakeVisible(lstInDevices.get());
    lstInDevices->setMultipleSelectionEnabled(false);
    lstInDevices->setRowHeight(16);
    lstInDevices->setOutlineThickness(1);
    lstInDevices->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmInPorts.reset(new TextListModel());
    lsmInPorts->setListener(this);
    lstInPorts.reset(new ListBox("InPorts", lsmInPorts.get()));
    addAndMakeVisible(lstInPorts.get());
    lstInPorts->setMultipleSelectionEnabled(false);
    lstInPorts->setRowHeight(16);
    lstInPorts->setOutlineThickness(1);
    lstInPorts->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmOutDevices.reset(new TextListModel());
    lsmOutDevices->setListener(this);
    lstOutDevices.reset(new ListBox("OutDevices", lsmOutDevices.get()));
    addAndMakeVisible(lstOutDevices.get());
    lstOutDevices->setMultipleSelectionEnabled(false);
    lstOutDevices->setRowHeight(16);
    lstOutDevices->setOutlineThickness(1);
    lstOutDevices->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmOutPorts.reset(new TextListModel());
    lsmOutPorts->setListener(this);
    lstOutPorts.reset(new ListBox("InPorts", lsmOutPorts.get()));
    addAndMakeVisible(lstOutPorts.get());
    lstOutPorts->setMultipleSelectionEnabled(false);
    lstOutPorts->setRowHeight(16);
    lstOutPorts->setOutlineThickness(1);
    lstOutPorts->setColour(ListBox::outlineColourId, Colours::lightgrey);

    //[/UserPreSize]

    setSize (400, 360);


    //[Constructor] You can add your own custom stuff here..
    refreshLists();
    //[/Constructor]
}

MIDISetup::~MIDISetup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblInputDevices = nullptr;
    lblInputPorts = nullptr;
    btnAddInPort = nullptr;
    btnRemoveInPort = nullptr;
    btnAssignInPort = nullptr;
    btnUnassignInPort = nullptr;
    lblOutputDevices = nullptr;
    lblOutputPorts = nullptr;
    btnAddOutPort = nullptr;
    btnRemoveOutPort = nullptr;
    btnAssignOutPort = nullptr;
    btnUnassignOutPort = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MIDISetup::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MIDISetup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    lstInDevices->setBounds(0, 24, 176, 152);
    lstInPorts->setBounds(224, 24, 176, 152);
    lstOutDevices->setBounds(0, 208, 176, 152);
    lstOutPorts->setBounds(224, 208, 176, 152);
    //[/UserResized]
}

void MIDISetup::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnAddInPort.get())
    {
        //[UserButtonCode_btnAddInPort] -- add your button handler code here..
        MIDISystem::AddInPort();
        refreshLists();
        //[/UserButtonCode_btnAddInPort]
    }
    else if (buttonThatWasClicked == btnRemoveInPort.get())
    {
        //[UserButtonCode_btnRemoveInPort] -- add your button handler code here..
        int r = lstInPorts->getLastRowSelected();
        if(r < 0 || r >= MIDISystem::NumInPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid input port to remove.");
            return;
        }
        MIDISystem::RemoveInPort(r);
        refreshLists();
        //[/UserButtonCode_btnRemoveInPort]
    }
    else if (buttonThatWasClicked == btnAssignInPort.get())
    {
        //[UserButtonCode_btnAssignInPort] -- add your button handler code here..
        int p = lstInPorts->getLastRowSelected();
        if(p < 0 || p >= MIDISystem::NumInPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid input port to assign to.");
            return;
        }
        int d = lstInDevices->getLastRowSelected();
        if(d < 0 || d >= lsmInDevices->getNumRows()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid input device to assign.");
            return;
        }
        if(MIDISystem::InPortDeviceNumber(p) >= 0){
            MIDISystem::UnassignInPort(p);
        }
        for(int i=0; i<MIDISystem::NumInPorts(); ++i){
            if(d == MIDISystem::InPortDeviceNumber(i)){
                MIDISystem::UnassignInPort(i);
            }
        }
        MIDISystem::AssignInDevice(d, p);
        refreshLists();
        //[/UserButtonCode_btnAssignInPort]
    }
    else if (buttonThatWasClicked == btnUnassignInPort.get())
    {
        //[UserButtonCode_btnUnassignInPort] -- add your button handler code here..
        int p = lstInPorts->getLastRowSelected();
        if(p < 0 || p >= MIDISystem::NumInPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid input port to unassign a device from.");
            return;
        }
        if(MIDISystem::InPortDeviceNumber(p) < 0){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "There's already no device assigned to this port.");
            return;
        }
        MIDISystem::UnassignInPort(p);
        refreshLists();
        //[/UserButtonCode_btnUnassignInPort]
    }
    else if (buttonThatWasClicked == btnAddOutPort.get())
    {
        //[UserButtonCode_btnAddOutPort] -- add your button handler code here..
        MIDISystem::AddOutPort();
        refreshLists();
        //[/UserButtonCode_btnAddOutPort]
    }
    else if (buttonThatWasClicked == btnRemoveOutPort.get())
    {
        //[UserButtonCode_btnRemoveOutPort] -- add your button handler code here..
        int r = lstOutPorts->getLastRowSelected();
        if(r < 0 || r >= MIDISystem::NumOutPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid output port to remove.");
            return;
        }
        MIDISystem::RemoveOutPort(r);
        refreshLists();
        //[/UserButtonCode_btnRemoveOutPort]
    }
    else if (buttonThatWasClicked == btnAssignOutPort.get())
    {
        //[UserButtonCode_btnAssignOutPort] -- add your button handler code here..
        int p = lstOutPorts->getLastRowSelected();
        if(p < 0 || p >= MIDISystem::NumOutPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid output port to assign to.");
            return;
        }
        int d = lstOutDevices->getLastRowSelected();
        if(d < 0 || d >= lsmOutDevices->getNumRows()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid output device to assign.");
            return;
        }
        if(MIDISystem::OutPortDeviceNumber(p) >= 0){
            MIDISystem::UnassignOutPort(p);
        }
        for(int i=0; i<MIDISystem::NumOutPorts(); ++i){
            if(d == MIDISystem::OutPortDeviceNumber(i)){
                MIDISystem::UnassignOutPort(i);
            }
        }
        MIDISystem::AssignOutDevice(d, p);
        refreshLists();
        //[/UserButtonCode_btnAssignOutPort]
    }
    else if (buttonThatWasClicked == btnUnassignOutPort.get())
    {
        //[UserButtonCode_btnUnassignOutPort] -- add your button handler code here..
        int p = lstOutPorts->getLastRowSelected();
        if(p < 0 || p >= MIDISystem::NumOutPorts()){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "Please select a valid output port to unassign a device from.");
            return;
        }
        if(MIDISystem::OutPortDeviceNumber(p) < 0){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic", "There's already no device assigned to this port.");
            return;
        }
        MIDISystem::UnassignOutPort(p);
        refreshLists();
        //[/UserButtonCode_btnUnassignOutPort]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MIDISetup::refreshLists(){
    StringArray indevices = MidiInput::getDevices();
    lsmInDevices->clear();
    lstInDevices->updateContent();
    for(int i=0; i<indevices.size(); ++i){
        lsmInDevices->add(indevices[i]);
    }
    lstInDevices->updateContent();
    //
    lsmInPorts->clear();
    lstInPorts->updateContent();
    for(int i=0; i<MIDISystem::NumInPorts(); ++i){
        lsmInPorts->add(String(i) + ": " + MIDISystem::InPortDeviceName(i));
    }
    lstInPorts->updateContent();
    //
    StringArray outdevices = MidiOutput::getDevices();
    lsmOutDevices->clear();
    lstOutDevices->updateContent();
    for(int i=0; i<outdevices.size(); ++i){
        lsmOutDevices->add(outdevices[i]);
    }
    lstOutDevices->updateContent();
    //
    lsmOutPorts->clear();
    lstOutPorts->updateContent();
    for(int i=0; i<MIDISystem::NumOutPorts(); ++i){
        lsmOutPorts->add(String(i) + ": " + MIDISystem::OutPortDeviceName(i));
    }
    lstOutPorts->updateContent();
}

void MIDISetup::rowSelected(TextListModel* parent, int row){
    if(parent == lsmInDevices.get()){

    }else if(parent == lsmInPorts.get()){

    }else if(parent == lsmOutDevices.get()){

    }else if(parent == lsmOutPorts.get()){

    }
}

void MIDISetup::rowDoubleClicked(TextListModel* parent, int row){
    if(parent == lsmInDevices.get()){

    }else if(parent == lsmInPorts.get()){

    }else if(parent == lsmOutDevices.get()){

    }else if(parent == lsmOutPorts.get()){

    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MIDISetup" componentName=""
                 parentClasses="public Component, public TextListModel::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="400"
                 initialHeight="360">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblInputDevices" id="31092e7bf531baaf" memberName="lblInputDevices"
         virtualName="" explicitFocusOrder="0" pos="0 0 176 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input devices:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblInputPorts" id="b34dfb0294faa11d" memberName="lblInputPorts"
         virtualName="" explicitFocusOrder="0" pos="224 0 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input ports:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnAddInPort" id="7ceb28d89a1747a0" memberName="btnAddInPort"
              virtualName="" explicitFocusOrder="0" pos="352 0 23 24" buttonText="+"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveInPort" id="506bcac0d99da01e" memberName="btnRemoveInPort"
              virtualName="" explicitFocusOrder="0" pos="376 0 23 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnAssignInPort" id="8c8b9eb262b05176" memberName="btnAssignInPort"
              virtualName="" explicitFocusOrder="0" pos="184 72 32 24" buttonText="&#8594;"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnUnassignInPort" id="a9516e6ac1d73b6e" memberName="btnUnassignInPort"
              virtualName="" explicitFocusOrder="0" pos="184 96 32 24" buttonText="X"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblOutputDevices" id="503b77530e3a269b" memberName="lblOutputDevices"
         virtualName="" explicitFocusOrder="0" pos="0 184 175 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output devices:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblOutputPorts" id="dd397ece32417cdb" memberName="lblOutputPorts"
         virtualName="" explicitFocusOrder="0" pos="224 184 127 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output ports:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnAddOutPort" id="32be3ccac2a3d38" memberName="btnAddOutPort"
              virtualName="" explicitFocusOrder="0" pos="352 184 23 24" buttonText="+"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveOutPort" id="d26a010a439d0900" memberName="btnRemoveOutPort"
              virtualName="" explicitFocusOrder="0" pos="376 184 23 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnAssignOutPort" id="61e8989500b683d3" memberName="btnAssignOutPort"
              virtualName="" explicitFocusOrder="0" pos="184 256 32 24" buttonText="&#8594;"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnUnassignOutPort" id="ddb085d7e4d50770" memberName="btnUnassignOutPort"
              virtualName="" explicitFocusOrder="0" pos="184 280 32 24" buttonText="X"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
