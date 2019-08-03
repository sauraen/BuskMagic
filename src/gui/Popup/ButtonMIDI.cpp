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

#include "ButtonMIDI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ButtonMIDI::ButtonMIDI (void *data)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblOn.reset (new Label ("lblOn",
                            TRANS("On:")));
    addAndMakeVisible (lblOn.get());
    lblOn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOn->setJustificationType (Justification::centredLeft);
    lblOn->setEditable (false, false, false);
    lblOn->setColour (TextEditor::textColourId, Colours::black);
    lblOn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOn->setBounds (0, 0, 32, 24);

    lblOff.reset (new Label ("lblOff",
                             TRANS("Off:")));
    addAndMakeVisible (lblOff.get());
    lblOff->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOff->setJustificationType (Justification::centredLeft);
    lblOff->setEditable (false, false, false);
    lblOff->setColour (TextEditor::textColourId, Colours::black);
    lblOff->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOff->setBounds (0, 24, 32, 24);

    lblToggle.reset (new Label ("lblToggle",
                                TRANS("Tgl:")));
    addAndMakeVisible (lblToggle.get());
    lblToggle->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblToggle->setJustificationType (Justification::centredLeft);
    lblToggle->setEditable (false, false, false);
    lblToggle->setColour (TextEditor::textColourId, Colours::black);
    lblToggle->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblToggle->setBounds (0, 48, 32, 24);

    lblOut.reset (new Label ("lblOut",
                             TRANS("Out:")));
    addAndMakeVisible (lblOut.get());
    lblOut->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblOut->setJustificationType (Justification::centredLeft);
    lblOut->setEditable (false, false, false);
    lblOut->setColour (TextEditor::textColourId, Colours::black);
    lblOut->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblOut->setBounds (0, 72, 32, 24);

    txtOn.reset (new TextEditor ("txtOn"));
    addAndMakeVisible (txtOn.get());
    txtOn->setMultiLine (false);
    txtOn->setReturnKeyStartsNewLine (false);
    txtOn->setReadOnly (false);
    txtOn->setScrollbarsShown (true);
    txtOn->setCaretVisible (true);
    txtOn->setPopupMenuEnabled (true);
    txtOn->setText (TRANS("16.16.NoteOff.100"));

    txtOn->setBounds (32, 0, 120, 24);

    btnLearnOn.reset (new TextButton ("btnLearnOn"));
    addAndMakeVisible (btnLearnOn.get());
    btnLearnOn->setButtonText (TRANS("Learn"));
    btnLearnOn->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnOn->addListener (this);

    btnLearnOn->setBounds (152, 0, 39, 24);

    txtOff.reset (new TextEditor ("txtOff"));
    addAndMakeVisible (txtOff.get());
    txtOff->setMultiLine (false);
    txtOff->setReturnKeyStartsNewLine (false);
    txtOff->setReadOnly (false);
    txtOff->setScrollbarsShown (true);
    txtOff->setCaretVisible (true);
    txtOff->setPopupMenuEnabled (true);
    txtOff->setText (TRANS("0.0.PolyAft.21"));

    txtOff->setBounds (32, 24, 120, 24);

    btnLearnOff.reset (new TextButton ("btnLearnOff"));
    addAndMakeVisible (btnLearnOff.get());
    btnLearnOff->setButtonText (TRANS("Learn"));
    btnLearnOff->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnOff->addListener (this);

    btnLearnOff->setBounds (152, 24, 39, 24);

    txtToggle.reset (new TextEditor ("txtToggle"));
    addAndMakeVisible (txtToggle.get());
    txtToggle->setMultiLine (false);
    txtToggle->setReturnKeyStartsNewLine (false);
    txtToggle->setReadOnly (false);
    txtToggle->setScrollbarsShown (true);
    txtToggle->setCaretVisible (true);
    txtToggle->setPopupMenuEnabled (true);
    txtToggle->setText (TRANS("1.2.ChnAft.90"));

    txtToggle->setBounds (32, 48, 120, 24);

    btnLearnToggle.reset (new TextButton ("btnLearnToggle"));
    addAndMakeVisible (btnLearnToggle.get());
    btnLearnToggle->setButtonText (TRANS("Learn"));
    btnLearnToggle->setConnectedEdges (Button::ConnectedOnLeft);
    btnLearnToggle->addListener (this);

    btnLearnToggle->setBounds (152, 48, 39, 24);

    txtOut.reset (new TextEditor ("txtOut"));
    addAndMakeVisible (txtOut.get());
    txtOut->setMultiLine (false);
    txtOut->setReturnKeyStartsNewLine (false);
    txtOut->setReadOnly (false);
    txtOut->setScrollbarsShown (true);
    txtOut->setCaretVisible (true);
    txtOut->setPopupMenuEnabled (true);
    txtOut->setText (TRANS("1.1.CC.80"));

    txtOut->setBounds (32, 72, 120, 24);


    //[UserPreSize]
    
    txtOn->setEscapeAndReturnKeysConsumed(false);
    txtOff->setEscapeAndReturnKeysConsumed(false);
    txtToggle->setEscapeAndReturnKeysConsumed(false);
    txtOut->setEscapeAndReturnKeysConsumed(false);
    
    //[/UserPreSize]

    setSize (192, 96);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ButtonMIDI::~ButtonMIDI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblOn = nullptr;
    lblOff = nullptr;
    lblToggle = nullptr;
    lblOut = nullptr;
    txtOn = nullptr;
    btnLearnOn = nullptr;
    txtOff = nullptr;
    btnLearnOff = nullptr;
    txtToggle = nullptr;
    btnLearnToggle = nullptr;
    txtOut = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ButtonMIDI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ButtonMIDI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ButtonMIDI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnLearnOn.get())
    {
        //[UserButtonCode_btnLearnOn] -- add your button handler code here..
        //[/UserButtonCode_btnLearnOn]
    }
    else if (buttonThatWasClicked == btnLearnOff.get())
    {
        //[UserButtonCode_btnLearnOff] -- add your button handler code here..
        //[/UserButtonCode_btnLearnOff]
    }
    else if (buttonThatWasClicked == btnLearnToggle.get())
    {
        //[UserButtonCode_btnLearnToggle] -- add your button handler code here..
        //[/UserButtonCode_btnLearnToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ButtonMIDI" componentName=""
                 parentClasses="public Component" constructorParams="void *data"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="192" initialHeight="96">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblOn" id="d0ac42dffdb426eb" memberName="lblOn" virtualName=""
         explicitFocusOrder="0" pos="0 0 32 24" edTextCol="ff000000" edBkgCol="0"
         labelText="On:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblOff" id="674bb573411a1a2f" memberName="lblOff" virtualName=""
         explicitFocusOrder="0" pos="0 24 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Off:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblToggle" id="15655674e83d7296" memberName="lblToggle"
         virtualName="" explicitFocusOrder="0" pos="0 48 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tgl:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblOut" id="860b25a77b187284" memberName="lblOut" virtualName=""
         explicitFocusOrder="0" pos="0 72 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Out:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtOn" id="4b232f1f6458c142" memberName="txtOn" virtualName=""
              explicitFocusOrder="0" pos="32 0 120 24" initialText="16.16.NoteOff.100"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnOn" id="7f49b557b931e3e2" memberName="btnLearnOn"
              virtualName="" explicitFocusOrder="0" pos="152 0 39 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtOff" id="963340a608852fc0" memberName="txtOff" virtualName=""
              explicitFocusOrder="0" pos="32 24 120 24" initialText="0.0.PolyAft.21"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnOff" id="8c9af5e4425ee1ea" memberName="btnLearnOff"
              virtualName="" explicitFocusOrder="0" pos="152 24 39 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtToggle" id="5acc4f32461b1f88" memberName="txtToggle"
              virtualName="" explicitFocusOrder="0" pos="32 48 120 24" initialText="1.2.ChnAft.90"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnLearnToggle" id="3fec8c798ffb8bed" memberName="btnLearnToggle"
              virtualName="" explicitFocusOrder="0" pos="152 48 39 24" buttonText="Learn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtOut" id="8a08e2fd71f05f09" memberName="txtOut" virtualName=""
              explicitFocusOrder="0" pos="32 72 120 24" initialText="1.1.CC.80"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

