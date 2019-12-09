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

#include "USBDMXSystem.h"
#include "LightingSystem.h"
//[/Headers]

#include "USBDMXSetup.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
USBDMXSetup::USBDMXSetup ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblDevices.reset (new Label ("lblDevices",
                                 TRANS("USB devices (readable by BuskMagic):")));
    addAndMakeVisible (lblDevices.get());
    lblDevices->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDevices->setJustificationType (Justification::centredLeft);
    lblDevices->setEditable (false, false, false);
    lblDevices->setColour (TextEditor::textColourId, Colours::black);
    lblDevices->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDevices->setBounds (72, 0, 424, 24);

    btnMap.reset (new TextButton ("btnMap"));
    addAndMakeVisible (btnMap.get());
    btnMap->setButtonText (CharPointer_UTF8 ("Map \xe2\x86\x93"));
    btnMap->setConnectedEdges (Button::ConnectedOnTop);
    btnMap->addListener (this);

    btnMap->setBounds (0, 152, 72, 24);

    lblDeviceInfo.reset (new Label ("lblDeviceInfo",
                                    TRANS("Manufacturer: \n"
                                    "Product: \n"
                                    "Serial Number: \n"
                                    "BuskMagic recognizes this as: ")));
    addAndMakeVisible (lblDeviceInfo.get());
    lblDeviceInfo->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDeviceInfo->setJustificationType (Justification::centredLeft);
    lblDeviceInfo->setEditable (false, false, false);
    lblDeviceInfo->setColour (TextEditor::textColourId, Colours::black);
    lblDeviceInfo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDeviceInfo->setBounds (72, 152, 336, 64);

    lblName.reset (new Label ("lblName",
                              TRANS("Name:")));
    addAndMakeVisible (lblName.get());
    lblName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblName->setJustificationType (Justification::centredLeft);
    lblName->setEditable (false, false, false);
    lblName->setColour (TextEditor::textColourId, Colours::black);
    lblName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblName->setBounds (280, 248, 56, 24);

    txtName.reset (new TextEditor ("txtName"));
    addAndMakeVisible (txtName.get());
    txtName->setMultiLine (false);
    txtName->setReturnKeyStartsNewLine (false);
    txtName->setReadOnly (false);
    txtName->setScrollbarsShown (true);
    txtName->setCaretVisible (true);
    txtName->setPopupMenuEnabled (true);
    txtName->setText (String());

    txtName->setBounds (336, 248, 136, 24);

    lblUniverse.reset (new Label ("lblUniverse",
                                  TRANS("Uni:")));
    addAndMakeVisible (lblUniverse.get());
    lblUniverse->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUniverse->setJustificationType (Justification::centredLeft);
    lblUniverse->setEditable (false, false, false);
    lblUniverse->setColour (TextEditor::textColourId, Colours::black);
    lblUniverse->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniverse->setBounds (280, 272, 40, 24);

    txtUniverse.reset (new TextEditor ("txtUniverse"));
    addAndMakeVisible (txtUniverse.get());
    txtUniverse->setMultiLine (false);
    txtUniverse->setReturnKeyStartsNewLine (false);
    txtUniverse->setReadOnly (false);
    txtUniverse->setScrollbarsShown (true);
    txtUniverse->setCaretVisible (true);
    txtUniverse->setPopupMenuEnabled (true);
    txtUniverse->setText (TRANS("0000"));

    txtUniverse->setBounds (320, 272, 40, 24);

    btnUnmap.reset (new TextButton ("btnUnmap"));
    addAndMakeVisible (btnUnmap.get());
    btnUnmap->setButtonText (CharPointer_UTF8 ("Unmap \xe2\x86\x91"));
    btnUnmap->addListener (this);

    btnUnmap->setBounds (0, 192, 72, 24);

    btnAddSlot.reset (new TextButton ("btnAddSlot"));
    addAndMakeVisible (btnAddSlot.get());
    btnAddSlot->setButtonText (TRANS("+"));
    btnAddSlot->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnAddSlot->addListener (this);

    btnAddSlot->setBounds (248, 248, 24, 24);

    btnRemoveSlot.reset (new TextButton ("btnRemoveSlot"));
    addAndMakeVisible (btnRemoveSlot.get());
    btnRemoveSlot->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveSlot->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnRemoveSlot->addListener (this);

    btnRemoveSlot->setBounds (248, 272, 24, 24);

    lblMapBy.reset (new Label ("lblMapBy",
                               TRANS("Map by:")));
    addAndMakeVisible (lblMapBy.get());
    lblMapBy->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMapBy->setJustificationType (Justification::centredLeft);
    lblMapBy->setEditable (false, false, false);
    lblMapBy->setColour (TextEditor::textColourId, Colours::black);
    lblMapBy->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMapBy->setBounds (408, 152, 72, 24);

    optMapPort.reset (new ToggleButton ("optMapPort"));
    addAndMakeVisible (optMapPort.get());
    optMapPort->setButtonText (TRANS("Port"));
    optMapPort->setRadioGroupId (1);
    optMapPort->addListener (this);
    optMapPort->setToggleState (true, dontSendNotification);

    optMapPort->setBounds (408, 176, 72, 24);

    optMapType.reset (new ToggleButton ("optMapType"));
    addAndMakeVisible (optMapType.get());
    optMapType->setButtonText (TRANS("Type"));
    optMapType->setRadioGroupId (1);
    optMapType->addListener (this);

    optMapType->setBounds (408, 200, 72, 24);

    btnMapHelp.reset (new TextButton ("btnMapHelp"));
    addAndMakeVisible (btnMapHelp.get());
    btnMapHelp->setButtonText (TRANS("?"));
    btnMapHelp->addListener (this);

    btnMapHelp->setBounds (472, 152, 24, 24);

    lblStatus.reset (new Label ("lblStatus",
                                TRANS("Status:")));
    addAndMakeVisible (lblStatus.get());
    lblStatus->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblStatus->setJustificationType (Justification::centredLeft);
    lblStatus->setEditable (false, false, false);
    lblStatus->setColour (TextEditor::textColourId, Colours::black);
    lblStatus->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblStatus->setBounds (248, 224, 192, 24);

    btnRefresh.reset (new TextButton ("btnRefresh"));
    addAndMakeVisible (btnRefresh.get());
    btnRefresh->setButtonText (TRANS("Refresh"));
    btnRefresh->setConnectedEdges (Button::ConnectedOnBottom);
    btnRefresh->addListener (this);

    btnRefresh->setBounds (0, 0, 72, 24);

    lblChans.reset (new Label ("lblChans",
                               TRANS("Chans:")));
    addAndMakeVisible (lblChans.get());
    lblChans->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblChans->setJustificationType (Justification::centredLeft);
    lblChans->setEditable (false, false, false);
    lblChans->setColour (TextEditor::textColourId, Colours::black);
    lblChans->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblChans->setBounds (360, 272, 56, 24);

    txtChans.reset (new TextEditor ("txtChans"));
    addAndMakeVisible (txtChans.get());
    txtChans->setMultiLine (false);
    txtChans->setReturnKeyStartsNewLine (false);
    txtChans->setReadOnly (false);
    txtChans->setScrollbarsShown (true);
    txtChans->setCaretVisible (true);
    txtChans->setPopupMenuEnabled (true);
    txtChans->setText (TRANS("512"));

    txtChans->setBounds (416, 272, 32, 24);

    btnChansHelp.reset (new TextButton ("btnChansHelp"));
    addAndMakeVisible (btnChansHelp.get());
    btnChansHelp->setButtonText (TRANS("?"));
    btnChansHelp->setConnectedEdges (Button::ConnectedOnLeft);
    btnChansHelp->addListener (this);

    btnChansHelp->setBounds (448, 272, 24, 24);


    //[UserPreSize]

    lstDevices.reset(new TextListBox(this));
    addAndMakeVisible(lstDevices.get());
    lstDevices->setBounds(0, 24, 496, 128);

    lstSlots.reset(new TextListBox(this));
    addAndMakeVisible(lstSlots.get());
    lstSlots->setBounds(0, 224, 248, 72);

    txtName->addListener(this);
    txtUniverse->addListener(this);
    txtChans->addListener(this);

    btnMap->setEnabled(false);

    //[/UserPreSize]

    setSize (496, 296);


    //[Constructor] You can add your own custom stuff here..

    bool t = USBDMXSystem::IsLoadMapModeType();
    optMapPort->setToggleState(!t, dontSendNotification);
    optMapType->setToggleState(t, dontSendNotification);

    fillSlotsBox();

    startTimer(200);
    //[/Constructor]
}

USBDMXSetup::~USBDMXSetup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblDevices = nullptr;
    btnMap = nullptr;
    lblDeviceInfo = nullptr;
    lblName = nullptr;
    txtName = nullptr;
    lblUniverse = nullptr;
    txtUniverse = nullptr;
    btnUnmap = nullptr;
    btnAddSlot = nullptr;
    btnRemoveSlot = nullptr;
    lblMapBy = nullptr;
    optMapPort = nullptr;
    optMapType = nullptr;
    btnMapHelp = nullptr;
    lblStatus = nullptr;
    btnRefresh = nullptr;
    lblChans = nullptr;
    txtChans = nullptr;
    btnChansHelp = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void USBDMXSetup::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void USBDMXSetup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void USBDMXSetup::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnMap.get())
    {
        //[UserButtonCode_btnMap] -- add your button handler code here..
        int d = lstDevices->getLastRowSelected();
        if(d < 0){
            WarningBox("Select a device first!");
            return;
        }
        int s = lstSlots->getLastRowSelected();
        if(s < 0){
            WarningBox("Select a slot first!");
            return;
        }
        USBDMXSystem::MapDevice(d, s);
        fillSlotsBox();
        //[/UserButtonCode_btnMap]
    }
    else if (buttonThatWasClicked == btnUnmap.get())
    {
        //[UserButtonCode_btnUnmap] -- add your button handler code here..
        int row = lstSlots->getLastRowSelected();
        if(row < 0) return;
        USBDMXSystem::UnmapDevice(row);
        fillSlotsBox();
        //[/UserButtonCode_btnUnmap]
    }
    else if (buttonThatWasClicked == btnAddSlot.get())
    {
        //[UserButtonCode_btnAddSlot] -- add your button handler code here..
        USBDMXSystem::AddSlot();
        fillSlotsBox();
        //[/UserButtonCode_btnAddSlot]
    }
    else if (buttonThatWasClicked == btnRemoveSlot.get())
    {
        //[UserButtonCode_btnRemoveSlot] -- add your button handler code here..
        int row = lstSlots->getLastRowSelected();
        if(row < 0) return;
        USBDMXSystem::RemoveSlot(row);
        fillSlotsBox();
        //[/UserButtonCode_btnRemoveSlot]
    }
    else if (buttonThatWasClicked == optMapPort.get())
    {
        //[UserButtonCode_optMapPort] -- add your button handler code here..
        USBDMXSystem::SetLoadMapMode(false);
        //[/UserButtonCode_optMapPort]
    }
    else if (buttonThatWasClicked == optMapType.get())
    {
        //[UserButtonCode_optMapType] -- add your button handler code here..
        USBDMXSystem::SetLoadMapMode(true);
        //[/UserButtonCode_optMapType]
    }
    else if (buttonThatWasClicked == btnMapHelp.get())
    {
        //[UserButtonCode_btnMapHelp] -- add your button handler code here..
        InfoBox(USBDMXSystem::GetLoadMapModeHelpText());
        //[/UserButtonCode_btnMapHelp]
    }
    else if (buttonThatWasClicked == btnRefresh.get())
    {
        //[UserButtonCode_btnRefresh] -- add your button handler code here..
        USBDMXSystem::RefreshDeviceList();
        //[/UserButtonCode_btnRefresh]
    }
    else if (buttonThatWasClicked == btnChansHelp.get())
    {
        //[UserButtonCode_btnChansHelp] -- add your button handler code here..
        InfoBox(USBDMXSystem::GetChansHelpText());
        //[/UserButtonCode_btnChansHelp]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void USBDMXSetup::rowSelected(TextListBox *parent, int row){
    row = parent->getLastRowSelected();
    if(row < 0) return;
    if(parent == lstDevices.get()){
        lblDeviceInfo->setText(USBDMXSystem::DeviceFullInfo(row), dontSendNotification);
        btnMap->setEnabled(USBDMXSystem::DeviceIsSupported(row));
    }else if(parent == lstSlots.get()){
        lblStatus->setText("Status: " + USBDMXSystem::SlotStatus(row), dontSendNotification);
        txtName->setText(USBDMXSystem::SlotName(row), dontSendNotification);
        txtUniverse->setText(hex(USBDMXSystem::SlotUni(row)), dontSendNotification);
        txtChans->setText(String(USBDMXSystem::SlotChans(row)), dontSendNotification);
    }
}

void USBDMXSetup::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    int row = lstSlots->getLastRowSelected();
    if(row < 0) return;
    if(&editorThatWasChanged == txtName.get()){
        if(text.isEmpty()){
            turnRed = true;
        }else{
            USBDMXSystem::SetSlotName(row, text);
        }
    }else if(&editorThatWasChanged == txtUniverse.get()){
        if(!ishex || hexval >= 0x8000){
            turnRed = true;
        }else{
            USBDMXSystem::SetSlotUni(row, hexval);
        }
    }else if(&editorThatWasChanged == txtChans.get()){
        if(!isint || intval > 512){
            turnRed = true;
        }else{
            USBDMXSystem::SetSlotChans(row, intval);
        }
    }
    lstSlots->set(row, USBDMXSystem::SlotDescription(row));
    TEXTCHANGEDHANDLER_POST;
}

void USBDMXSetup::timerCallback(){
    int d;
    TEXTLIST_SYNC_1SELECT(lstDevices, USBDMXSystem::NumDevices(), USBDMXSystem::DeviceDescription(i), d);
    if(d >= 0 && d < USBDMXSystem::NumDevices()){
        lblDeviceInfo->setText(USBDMXSystem::DeviceFullInfo(d), dontSendNotification);
    }
    int row = lstSlots->getLastRowSelected();
    if(row >= 0){
        lblStatus->setText("Status: " + USBDMXSystem::SlotStatus(row), dontSendNotification);
    }
}

void USBDMXSetup::fillSlotsBox(){
    int s;
    TEXTLIST_SYNC_1SELECT(lstSlots, USBDMXSystem::NumSlots(), USBDMXSystem::SlotDescription(i), s);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="USBDMXSetup" componentName=""
                 parentClasses="public Component, public TextListBox::Listener, public TextEditor::Listener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="496"
                 initialHeight="296">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblDevices" id="af3c963fa34df561" memberName="lblDevices"
         virtualName="" explicitFocusOrder="0" pos="72 0 424 24" edTextCol="ff000000"
         edBkgCol="0" labelText="USB devices (readable by BuskMagic):"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <TEXTBUTTON name="btnMap" id="9ef5ee916134b79a" memberName="btnMap" virtualName=""
              explicitFocusOrder="0" pos="0 152 72 24" buttonText="Map &#8595;"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblDeviceInfo" id="4ef899223be9062a" memberName="lblDeviceInfo"
         virtualName="" explicitFocusOrder="0" pos="72 152 336 64" edTextCol="ff000000"
         edBkgCol="0" labelText="Manufacturer: &#10;Product: &#10;Serial Number: &#10;BuskMagic recognizes this as: "
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="lblName" id="7d3f78265abfa0ef" memberName="lblName" virtualName=""
         explicitFocusOrder="0" pos="280 248 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtName" id="bc35ea61aa9e8dbd" memberName="txtName" virtualName=""
              explicitFocusOrder="0" pos="336 248 136 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblUniverse" id="6a983e1b03e7558f" memberName="lblUniverse"
         virtualName="" explicitFocusOrder="0" pos="280 272 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Uni:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniverse" id="80625db9f19e7069" memberName="txtUniverse"
              virtualName="" explicitFocusOrder="0" pos="320 272 40 24" initialText="0000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnUnmap" id="8c5906a80e1c57db" memberName="btnUnmap" virtualName=""
              explicitFocusOrder="0" pos="0 192 72 24" buttonText="Unmap &#8593;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnAddSlot" id="aaf813906edeb025" memberName="btnAddSlot"
              virtualName="" explicitFocusOrder="0" pos="248 248 24 24" buttonText="+"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveSlot" id="8eea23f9295ba0b" memberName="btnRemoveSlot"
              virtualName="" explicitFocusOrder="0" pos="248 272 24 24" buttonText="&#8722;"
              connectedEdges="5" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblMapBy" id="28fff9208714bd4f" memberName="lblMapBy" virtualName=""
         explicitFocusOrder="0" pos="408 152 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Map by:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="optMapPort" id="53d628975640d16f" memberName="optMapPort"
                virtualName="" explicitFocusOrder="0" pos="408 176 72 24" buttonText="Port"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="optMapType" id="4c2c1da230eb3fa7" memberName="optMapType"
                virtualName="" explicitFocusOrder="0" pos="408 200 72 24" buttonText="Type"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TEXTBUTTON name="btnMapHelp" id="f6af057f433dc4a7" memberName="btnMapHelp"
              virtualName="" explicitFocusOrder="0" pos="472 152 24 24" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblStatus" id="cd4cb2768b6e4377" memberName="lblStatus"
         virtualName="" explicitFocusOrder="0" pos="248 224 192 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Status:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnRefresh" id="ecbae560e71793af" memberName="btnRefresh"
              virtualName="" explicitFocusOrder="0" pos="0 0 72 24" buttonText="Refresh"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblChans" id="83784da525645170" memberName="lblChans" virtualName=""
         explicitFocusOrder="0" pos="360 272 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Chans:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtChans" id="68dbcec1d14783a7" memberName="txtChans" virtualName=""
              explicitFocusOrder="0" pos="416 272 32 24" initialText="512"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnChansHelp" id="e90ae583fc87d4d8" memberName="btnChansHelp"
              virtualName="" explicitFocusOrder="0" pos="448 272 24 24" buttonText="?"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

