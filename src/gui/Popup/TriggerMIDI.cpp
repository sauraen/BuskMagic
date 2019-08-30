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

//[/Headers]

#include "TriggerMIDI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TriggerMIDI::TriggerMIDI (void *data)
    : triggerbtn((TriggerButton*)data)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblOn.reset (new Label ("lblOn",
                            TRANS("Trigger:")));
    addAndMakeVisible (lblOn.get());
    lblOn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOn->setJustificationType (Justification::centredLeft);
    lblOn->setEditable (false, false, false);
    lblOn->setColour (TextEditor::textColourId, Colours::black);
    lblOn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOn->setBounds (0, 0, 56, 24);

    lblOutOn.reset (new Label ("lblOutOn",
                               TRANS("Out on:")));
    addAndMakeVisible (lblOutOn.get());
    lblOutOn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOutOn->setJustificationType (Justification::centredLeft);
    lblOutOn->setEditable (false, false, false);
    lblOutOn->setColour (TextEditor::textColourId, Colours::black);
    lblOutOn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOutOn->setBounds (0, 24, 56, 24);

    txtTrig.reset (new TextEditor ("txtTrig"));
    addAndMakeVisible (txtTrig.get());
    txtTrig->setMultiLine (false);
    txtTrig->setReturnKeyStartsNewLine (false);
    txtTrig->setReadOnly (false);
    txtTrig->setScrollbarsShown (true);
    txtTrig->setCaretVisible (true);
    txtTrig->setPopupMenuEnabled (true);
    txtTrig->setText (TRANS("16.16.NoteOff.100"));

    txtTrig->setBounds (56, 0, 120, 24);

    btnLearnTrig.reset (new TextButton ("btnLearnTrig"));
    addAndMakeVisible (btnLearnTrig.get());
    btnLearnTrig->setButtonText (TRANS("Learn"));
    btnLearnTrig->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnTrig->addListener (this);

    btnLearnTrig->setBounds (176, 0, 48, 24);

    txtOutOn.reset (new TextEditor ("txtOutOn"));
    addAndMakeVisible (txtOutOn.get());
    txtOutOn->setMultiLine (false);
    txtOutOn->setReturnKeyStartsNewLine (false);
    txtOutOn->setReadOnly (false);
    txtOutOn->setScrollbarsShown (true);
    txtOutOn->setCaretVisible (true);
    txtOutOn->setPopupMenuEnabled (true);
    txtOutOn->setText (TRANS("1.1.CC.80"));

    txtOutOn->setBounds (56, 24, 144, 24);

    lblOutOff.reset (new Label ("lblOutOff",
                                TRANS("Out off:")));
    addAndMakeVisible (lblOutOff.get());
    lblOutOff->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOutOff->setJustificationType (Justification::centredLeft);
    lblOutOff->setEditable (false, false, false);
    lblOutOff->setColour (TextEditor::textColourId, Colours::black);
    lblOutOff->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOutOff->setBounds (0, 48, 56, 24);

    txtOutOff.reset (new TextEditor ("txtOutOff"));
    addAndMakeVisible (txtOutOff.get());
    txtOutOff->setMultiLine (false);
    txtOutOff->setReturnKeyStartsNewLine (false);
    txtOutOff->setReadOnly (false);
    txtOutOff->setScrollbarsShown (true);
    txtOutOff->setCaretVisible (true);
    txtOutOff->setPopupMenuEnabled (true);
    txtOutOff->setText (TRANS("1.1.CC.80"));

    txtOutOff->setBounds (56, 48, 144, 24);

    btnHelp.reset (new TextButton ("btnHelp"));
    addAndMakeVisible (btnHelp.get());
    btnHelp->setButtonText (TRANS("?"));
    btnHelp->addListener (this);

    btnHelp->setBounds (200, 48, 24, 24);


    //[UserPreSize]

    ConfigureTextEditor(txtTrig, this, triggerbtn->GetMIDISettingStr(MIDISetting::tr_trig));
    ConfigureTextEditor(txtOutOn, this, triggerbtn->GetMIDISettingStr(MIDISetting::tr_out_on));
    ConfigureTextEditor(txtOutOff, this, triggerbtn->GetMIDISettingStr(MIDISetting::tr_out_off));

    setOpaque(true);

    //[/UserPreSize]

    setSize (224, 72);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TriggerMIDI::~TriggerMIDI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblOn = nullptr;
    lblOutOn = nullptr;
    txtTrig = nullptr;
    btnLearnTrig = nullptr;
    txtOutOn = nullptr;
    lblOutOff = nullptr;
    txtOutOff = nullptr;
    btnHelp = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TriggerMIDI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TriggerMIDI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TriggerMIDI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnLearnTrig.get())
    {
        //[UserButtonCode_btnLearnTrig] -- add your button handler code here..
        //[/UserButtonCode_btnLearnTrig]
    }
    else if (buttonThatWasClicked == btnHelp.get())
    {
        //[UserButtonCode_btnHelp] -- add your button handler code here..
        InfoBox(MIDISetting::GetHelpText());
        //[/UserButtonCode_btnHelp]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TriggerMIDI::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtTrig.get()){
        turnRed = !triggerbtn->SetMIDISettingFromStr(MIDISetting::tr_trig, text);
    }else if(&editorThatWasChanged == txtOutOn.get()){
        turnRed = !triggerbtn->SetMIDISettingFromStr(MIDISetting::tr_out_on, text);
    }else if(&editorThatWasChanged == txtOutOff.get()){
        turnRed = !triggerbtn->SetMIDISettingFromStr(MIDISetting::tr_out_off, text);
    }
    TEXTCHANGEDHANDLER_POST;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TriggerMIDI" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="void *data" variableInitialisers="triggerbtn((TriggerButton*)data)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="224" initialHeight="72">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblOn" id="d0ac42dffdb426eb" memberName="lblOn" virtualName=""
         explicitFocusOrder="0" pos="0 0 56 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Trigger:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblOutOn" id="860b25a77b187284" memberName="lblOutOn" virtualName=""
         explicitFocusOrder="0" pos="0 24 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Out on:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtTrig" id="4b232f1f6458c142" memberName="txtTrig" virtualName=""
              explicitFocusOrder="0" pos="56 0 120 24" initialText="16.16.NoteOff.100"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnTrig" id="7f49b557b931e3e2" memberName="btnLearnTrig"
              virtualName="" explicitFocusOrder="0" pos="176 0 48 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtOutOn" id="8a08e2fd71f05f09" memberName="txtOutOn" virtualName=""
              explicitFocusOrder="0" pos="56 24 144 24" initialText="1.1.CC.80"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblOutOff" id="c22eecbe137c2ec" memberName="lblOutOff"
         virtualName="" explicitFocusOrder="0" pos="0 48 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Out off:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtOutOff" id="9f9f13c1778023df" memberName="txtOutOff"
              virtualName="" explicitFocusOrder="0" pos="56 48 144 24" initialText="1.1.CC.80"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnHelp" id="56d59fa52e86890d" memberName="btnHelp" virtualName=""
              explicitFocusOrder="0" pos="200 48 24 24" buttonText="?" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
