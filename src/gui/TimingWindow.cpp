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

#include "TimingSystem.h"

//[/Headers]

#include "TimingWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
TimingWindow *TimingWindow::tw_static = nullptr;
//[/MiscUserDefs]

//==============================================================================
TimingWindow::TimingWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    jassert(tw_static == nullptr);
    tw_static = this;
    //[/Constructor_pre]

    lblTapBeat.reset (new Label ("lblTapBeat",
                                 TRANS("Tap Beat")));
    addAndMakeVisible (lblTapBeat.get());
    lblTapBeat->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTapBeat->setJustificationType (Justification::centred);
    lblTapBeat->setEditable (false, false, false);
    lblTapBeat->setColour (TextEditor::textColourId, Colours::black);
    lblTapBeat->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTapBeat->setBounds (8, 56, 64, 24);

    lblTapMeasure.reset (new Label ("lblTapMeasure",
                                    TRANS("Tap Measure")));
    addAndMakeVisible (lblTapMeasure.get());
    lblTapMeasure->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTapMeasure->setJustificationType (Justification::centred);
    lblTapMeasure->setEditable (false, false, false);
    lblTapMeasure->setColour (TextEditor::textColourId, Colours::black);
    lblTapMeasure->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTapMeasure->setBounds (72, 56, 96, 24);

    lblDouble.reset (new Label ("lblDouble",
                                TRANS("x2")));
    addAndMakeVisible (lblDouble.get());
    lblDouble->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDouble->setJustificationType (Justification::centred);
    lblDouble->setEditable (false, false, false);
    lblDouble->setColour (TextEditor::textColourId, Colours::black);
    lblDouble->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDouble->setBounds (8, 136, 64, 24);

    lblHalf.reset (new Label ("lblHalf",
                              TRANS("/2")));
    addAndMakeVisible (lblHalf.get());
    lblHalf->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblHalf->setJustificationType (Justification::centred);
    lblHalf->setEditable (false, false, false);
    lblHalf->setColour (TextEditor::textColourId, Colours::black);
    lblHalf->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblHalf->setBounds (88, 136, 64, 24);

    lblTempo.reset (new Label ("lblTempo",
                               TRANS("Tempo:")));
    addAndMakeVisible (lblTempo.get());
    lblTempo->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTempo->setJustificationType (Justification::centredLeft);
    lblTempo->setEditable (false, false, false);
    lblTempo->setColour (TextEditor::textColourId, Colours::black);
    lblTempo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTempo->setBounds (168, 16, 56, 24);

    txtBPM.reset (new TextEditor ("txtBPM"));
    addAndMakeVisible (txtBPM.get());
    txtBPM->setMultiLine (false);
    txtBPM->setReturnKeyStartsNewLine (false);
    txtBPM->setReadOnly (false);
    txtBPM->setScrollbarsShown (true);
    txtBPM->setCaretVisible (true);
    txtBPM->setPopupMenuEnabled (true);
    txtBPM->setText (TRANS("123.456"));

    txtBPM->setBounds (224, 16, 56, 24);

    lblMeasure.reset (new Label ("lblMeasure",
                                 TRANS("Measure:")));
    addAndMakeVisible (lblMeasure.get());
    lblMeasure->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMeasure->setJustificationType (Justification::centredLeft);
    lblMeasure->setEditable (false, false, false);
    lblMeasure->setColour (TextEditor::textColourId, Colours::black);
    lblMeasure->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMeasure->setBounds (168, 40, 72, 24);

    lblBPM.reset (new Label ("lblBPM",
                             TRANS("BPM")));
    addAndMakeVisible (lblBPM.get());
    lblBPM->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBPM->setJustificationType (Justification::centredLeft);
    lblBPM->setEditable (false, false, false);
    lblBPM->setColour (TextEditor::textColourId, Colours::black);
    lblBPM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBPM->setBounds (280, 16, 40, 24);

    txtMeasureLen.reset (new TextEditor ("txtMeasureLen"));
    addAndMakeVisible (txtMeasureLen.get());
    txtMeasureLen->setMultiLine (false);
    txtMeasureLen->setReturnKeyStartsNewLine (false);
    txtMeasureLen->setReadOnly (false);
    txtMeasureLen->setScrollbarsShown (true);
    txtMeasureLen->setCaretVisible (true);
    txtMeasureLen->setPopupMenuEnabled (true);
    txtMeasureLen->setText (TRANS("16"));

    txtMeasureLen->setBounds (240, 40, 24, 24);

    lblBeats.reset (new Label ("lblBeats",
                               TRANS("beats")));
    addAndMakeVisible (lblBeats.get());
    lblBeats->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBeats->setJustificationType (Justification::centredLeft);
    lblBeats->setEditable (false, false, false);
    lblBeats->setColour (TextEditor::textColourId, Colours::black);
    lblBeats->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBeats->setBounds (264, 40, 56, 24);


    //[UserPreSize]

    trgTapBeat.reset(new TriggerButton(this));
    addAndMakeVisible(trgTapBeat.get());
    trgTapBeat->setTopLeftPosition(16, 16);

    trgTapMeasure.reset(new TriggerButton(this));
    addAndMakeVisible(trgTapMeasure.get());
    trgTapMeasure->setTopLeftPosition(96, 16);

    trgDouble.reset(new TriggerButton(this));
    addAndMakeVisible(trgDouble.get());
    trgDouble->setTopLeftPosition(16, 96);

    trgHalf.reset(new TriggerButton(this));
    addAndMakeVisible(trgHalf.get());
    trgHalf->setTopLeftPosition(96, 96);
    
    txtBPM->addListener(this);
    txtMeasureLen->addListener(this);

    //[/UserPreSize]

    setSize (328, 160);


    //[Constructor] You can add your own custom stuff here..

    txtBPM->setText(String(TimingSystem::GetTempo(), 3), dontSendNotification);
    txtMeasureLen->setText(String(TimingSystem::GetBeatsPerMeasure()), dontSendNotification);

    //[/Constructor]
}

TimingWindow::~TimingWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblTapBeat = nullptr;
    lblTapMeasure = nullptr;
    lblDouble = nullptr;
    lblHalf = nullptr;
    lblTempo = nullptr;
    txtBPM = nullptr;
    lblMeasure = nullptr;
    lblBPM = nullptr;
    txtMeasureLen = nullptr;
    lblBeats = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    tw_static = nullptr;
    //[/Destructor]
}

//==============================================================================
void TimingWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TimingWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TimingWindow::buttonClicked(Button *buttonThatWasClicked){
    std::cout << "button press\n";
    if(buttonThatWasClicked == trgTapBeat.get()){
        TimingSystem::TapBeat();
    }else if(buttonThatWasClicked == trgTapMeasure.get()){
        TimingSystem::TapMeasure();
    }else if(buttonThatWasClicked == trgDouble.get()){
        txtMeasureLen->setText(String(TimingSystem::GetBeatsPerMeasure()), dontSendNotification);
        TimingSystem::SetTempo(2.0f * TimingSystem::GetTempo());
    }else if(buttonThatWasClicked == trgHalf.get()){
        TimingSystem::SetTempo(0.5f * TimingSystem::GetTempo());
    }
    txtBPM->setText(String(TimingSystem::GetTempo(), 3), dontSendNotification);
}

void TimingWindow::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtBPM.get()){
        if(!isdec || decval < 0.1f || decval > 500.0f) turnRed = true;
        else TimingSystem::SetTempo(decval);
    }else if(&editorThatWasChanged == txtMeasureLen.get()){
        if(!isint || val <= 0) turnRed = true;
        else TimingSystem::SetBeatsPerMeasure(val);
    }
    TEXTCHANGEDHANDLER_POST;
}

void TimingWindow::HandleMIDI(int port, MidiMessage msg){
    trgTapBeat->HandleMIDI(port, msg);
    trgTapMeasure->HandleMIDI(port, msg);
    trgDouble->HandleMIDI(port, msg);
    trgHalf->HandleMIDI(port, msg);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimingWindow" componentName=""
                 parentClasses="public Component, public Button::Listener, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="328"
                 initialHeight="160">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblTapBeat" id="b060ed39fd586d60" memberName="lblTapBeat"
         virtualName="" explicitFocusOrder="0" pos="8 56 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tap Beat" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblTapMeasure" id="4006277d7561730" memberName="lblTapMeasure"
         virtualName="" explicitFocusOrder="0" pos="72 56 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tap Measure" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblDouble" id="36f9e9bd24dc7f2e" memberName="lblDouble"
         virtualName="" explicitFocusOrder="0" pos="8 136 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblHalf" id="a655a61b87d5cf52" memberName="lblHalf" virtualName=""
         explicitFocusOrder="0" pos="88 136 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblTempo" id="6606c2230e91c01f" memberName="lblTempo" virtualName=""
         explicitFocusOrder="0" pos="168 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtBPM" id="37e3bc569d4b8cc" memberName="txtBPM" virtualName=""
              explicitFocusOrder="0" pos="224 16 56 24" initialText="123.456"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblMeasure" id="67af052245673552" memberName="lblMeasure"
         virtualName="" explicitFocusOrder="0" pos="168 40 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Measure:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblBPM" id="9f1e2b87be54206e" memberName="lblBPM" virtualName=""
         explicitFocusOrder="0" pos="280 16 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BPM" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMeasureLen" id="a58c3c5dac9fca7e" memberName="txtMeasureLen"
              virtualName="" explicitFocusOrder="0" pos="240 40 24 24" initialText="16"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblBeats" id="4e4054d3038cc2b1" memberName="lblBeats" virtualName=""
         explicitFocusOrder="0" pos="264 40 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="beats" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
