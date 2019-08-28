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

#include "KnobMIDI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KnobMIDI::KnobMIDI (void *data)
    : ccontroller((ContinuousController*)data)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblIn.reset (new Label ("lblIn",
                            TRANS("In:")));
    addAndMakeVisible (lblIn.get());
    lblIn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblIn->setJustificationType (Justification::centredLeft);
    lblIn->setEditable (false, false, false);
    lblIn->setColour (TextEditor::textColourId, Colours::black);
    lblIn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblIn->setBounds (0, 0, 64, 24);

    lblGotoLo.reset (new Label ("lblGotoLo",
                                TRANS("Goto Lo:")));
    addAndMakeVisible (lblGotoLo.get());
    lblGotoLo->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblGotoLo->setJustificationType (Justification::centredLeft);
    lblGotoLo->setEditable (false, false, false);
    lblGotoLo->setColour (TextEditor::textColourId, Colours::black);
    lblGotoLo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblGotoLo->setBounds (0, 24, 64, 24);

    lblGotoHi.reset (new Label ("lblGotoHi",
                                TRANS("Goto Hi:")));
    addAndMakeVisible (lblGotoHi.get());
    lblGotoHi->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblGotoHi->setJustificationType (Justification::centredLeft);
    lblGotoHi->setEditable (false, false, false);
    lblGotoHi->setColour (TextEditor::textColourId, Colours::black);
    lblGotoHi->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblGotoHi->setBounds (0, 48, 64, 24);

    lblOut.reset (new Label ("lblOut",
                             TRANS("Out:")));
    addAndMakeVisible (lblOut.get());
    lblOut->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOut->setJustificationType (Justification::centredLeft);
    lblOut->setEditable (false, false, false);
    lblOut->setColour (TextEditor::textColourId, Colours::black);
    lblOut->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOut->setBounds (0, 72, 64, 24);

    txtIn.reset (new TextEditor ("txtIn"));
    addAndMakeVisible (txtIn.get());
    txtIn->setMultiLine (false);
    txtIn->setReturnKeyStartsNewLine (false);
    txtIn->setReadOnly (false);
    txtIn->setScrollbarsShown (true);
    txtIn->setCaretVisible (true);
    txtIn->setPopupMenuEnabled (true);
    txtIn->setText (TRANS("16.16.NoteOff.100"));

    txtIn->setBounds (64, 0, 144, 24);

    btnLearnIn.reset (new TextButton ("btnLearnIn"));
    addAndMakeVisible (btnLearnIn.get());
    btnLearnIn->setButtonText (TRANS("Learn"));
    btnLearnIn->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnIn->addListener (this);

    btnLearnIn->setBounds (208, 0, 48, 24);

    txtGotoLo.reset (new TextEditor ("txtGotoLo"));
    addAndMakeVisible (txtGotoLo.get());
    txtGotoLo->setMultiLine (false);
    txtGotoLo->setReturnKeyStartsNewLine (false);
    txtGotoLo->setReadOnly (false);
    txtGotoLo->setScrollbarsShown (true);
    txtGotoLo->setCaretVisible (true);
    txtGotoLo->setPopupMenuEnabled (true);
    txtGotoLo->setText (TRANS("0.0.PolyAft.21"));

    txtGotoLo->setBounds (64, 24, 144, 24);

    btnLearnGotoLo.reset (new TextButton ("btnLearnGotoLo"));
    addAndMakeVisible (btnLearnGotoLo.get());
    btnLearnGotoLo->setButtonText (TRANS("Learn"));
    btnLearnGotoLo->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnGotoLo->addListener (this);

    btnLearnGotoLo->setBounds (208, 24, 48, 24);

    txtGotoHi.reset (new TextEditor ("txtGotoHi"));
    addAndMakeVisible (txtGotoHi.get());
    txtGotoHi->setMultiLine (false);
    txtGotoHi->setReturnKeyStartsNewLine (false);
    txtGotoHi->setReadOnly (false);
    txtGotoHi->setScrollbarsShown (true);
    txtGotoHi->setCaretVisible (true);
    txtGotoHi->setPopupMenuEnabled (true);
    txtGotoHi->setText (TRANS("1.2.ChnAft.90"));

    txtGotoHi->setBounds (64, 48, 144, 24);

    btnLearnGotoHi.reset (new TextButton ("btnLearnGotoHi"));
    addAndMakeVisible (btnLearnGotoHi.get());
    btnLearnGotoHi->setButtonText (TRANS("Learn"));
    btnLearnGotoHi->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnGotoHi->addListener (this);

    btnLearnGotoHi->setBounds (208, 48, 48, 24);

    txtOut.reset (new TextEditor ("txtOut"));
    addAndMakeVisible (txtOut.get());
    txtOut->setMultiLine (false);
    txtOut->setReturnKeyStartsNewLine (false);
    txtOut->setReadOnly (false);
    txtOut->setScrollbarsShown (true);
    txtOut->setCaretVisible (true);
    txtOut->setPopupMenuEnabled (true);
    txtOut->setText (TRANS("1.1.CC.80"));

    txtOut->setBounds (64, 72, 144, 24);

    btnHelp.reset (new TextButton ("btnHelp"));
    addAndMakeVisible (btnHelp.get());
    btnHelp->setButtonText (TRANS("?"));
    btnHelp->addListener (this);

    btnHelp->setBounds (232, 72, 24, 24);


    //[UserPreSize]

    ConfigureTextEditor(txtIn, this, ccontroller->GetMIDISettingStr(Controller::ct_in));
    ConfigureTextEditor(txtGotoLo, this, ccontroller->GetMIDISettingStr(Controller::ct_goto_lo));
    ConfigureTextEditor(txtGotoHi, this, ccontroller->GetMIDISettingStr(Controller::ct_goto_hi));
    ConfigureTextEditor(txtOut, this, ccontroller->GetMIDISettingStr(Controller::ct_out));
    
    setOpaque(true);
    
    //[/UserPreSize]

    setSize (256, 96);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

KnobMIDI::~KnobMIDI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblIn = nullptr;
    lblGotoLo = nullptr;
    lblGotoHi = nullptr;
    lblOut = nullptr;
    txtIn = nullptr;
    btnLearnIn = nullptr;
    txtGotoLo = nullptr;
    btnLearnGotoLo = nullptr;
    txtGotoHi = nullptr;
    btnLearnGotoHi = nullptr;
    txtOut = nullptr;
    btnHelp = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KnobMIDI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KnobMIDI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void KnobMIDI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnLearnIn.get())
    {
        //[UserButtonCode_btnLearnIn] -- add your button handler code here..
        //[/UserButtonCode_btnLearnIn]
    }
    else if (buttonThatWasClicked == btnLearnGotoLo.get())
    {
        //[UserButtonCode_btnLearnGotoLo] -- add your button handler code here..
        //[/UserButtonCode_btnLearnGotoLo]
    }
    else if (buttonThatWasClicked == btnLearnGotoHi.get())
    {
        //[UserButtonCode_btnLearnGotoHi] -- add your button handler code here..
        //[/UserButtonCode_btnLearnGotoHi]
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

void KnobMIDI::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtIn.get()){
        turnRed = !ccontroller->SetMIDISettingFromStr(Controller::ct_in, text);
    }else if(&editorThatWasChanged == txtGotoLo.get()){
        turnRed = !ccontroller->SetMIDISettingFromStr(Controller::ct_goto_lo, text);
    }else if(&editorThatWasChanged == txtGotoHi.get()){
        turnRed = !ccontroller->SetMIDISettingFromStr(Controller::ct_goto_hi, text);
    }else if(&editorThatWasChanged == txtOut.get()){
        turnRed = !ccontroller->SetMIDISettingFromStr(Controller::ct_out, text);
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

<JUCER_COMPONENT documentType="Component" className="KnobMIDI" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="void *data" variableInitialisers="ccontroller((ContinuousController*)data)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="256" initialHeight="96">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblIn" id="d0ac42dffdb426eb" memberName="lblIn" virtualName=""
         explicitFocusOrder="0" pos="0 0 64 24" edTextCol="ff000000" edBkgCol="0"
         labelText="In:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblGotoLo" id="674bb573411a1a2f" memberName="lblGotoLo"
         virtualName="" explicitFocusOrder="0" pos="0 24 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Goto Lo:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblGotoHi" id="15655674e83d7296" memberName="lblGotoHi"
         virtualName="" explicitFocusOrder="0" pos="0 48 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Goto Hi:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblOut" id="860b25a77b187284" memberName="lblOut" virtualName=""
         explicitFocusOrder="0" pos="0 72 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Out:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtIn" id="4b232f1f6458c142" memberName="txtIn" virtualName=""
              explicitFocusOrder="0" pos="64 0 144 24" initialText="16.16.NoteOff.100"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnIn" id="7f49b557b931e3e2" memberName="btnLearnIn"
              virtualName="" explicitFocusOrder="0" pos="208 0 48 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtGotoLo" id="963340a608852fc0" memberName="txtGotoLo"
              virtualName="" explicitFocusOrder="0" pos="64 24 144 24" initialText="0.0.PolyAft.21"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnGotoLo" id="8c9af5e4425ee1ea" memberName="btnLearnGotoLo"
              virtualName="" explicitFocusOrder="0" pos="208 24 48 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtGotoHi" id="5acc4f32461b1f88" memberName="txtGotoHi"
              virtualName="" explicitFocusOrder="0" pos="64 48 144 24" initialText="1.2.ChnAft.90"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnGotoHi" id="3fec8c798ffb8bed" memberName="btnLearnGotoHi"
              virtualName="" explicitFocusOrder="0" pos="208 48 48 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtOut" id="8a08e2fd71f05f09" memberName="txtOut" virtualName=""
              explicitFocusOrder="0" pos="64 72 144 24" initialText="1.1.CC.80"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnHelp" id="56d59fa52e86890d" memberName="btnHelp" virtualName=""
              explicitFocusOrder="0" pos="232 72 24 24" buttonText="?" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
