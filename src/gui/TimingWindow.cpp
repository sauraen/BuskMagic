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
TimingWindow::TimingWindow (ValueTree tw_node)
{
    //[Constructor_pre] You can add your own custom stuff here..
    jassert(tw_static == nullptr);
    tw_static = this;
    //[/Constructor_pre]

    txtBPM.reset (new TextEditor ("txtBPM"));
    addAndMakeVisible (txtBPM.get());
    txtBPM->setMultiLine (false);
    txtBPM->setReturnKeyStartsNewLine (false);
    txtBPM->setReadOnly (false);
    txtBPM->setScrollbarsShown (true);
    txtBPM->setCaretVisible (true);
    txtBPM->setPopupMenuEnabled (true);
    txtBPM->setText (TRANS("123.456"));

    txtBPM->setBounds (16, 8, 64, 24);

    txtMeasureLen.reset (new TextEditor ("txtMeasureLen"));
    addAndMakeVisible (txtMeasureLen.get());
    txtMeasureLen->setMultiLine (false);
    txtMeasureLen->setReturnKeyStartsNewLine (false);
    txtMeasureLen->setReadOnly (false);
    txtMeasureLen->setScrollbarsShown (true);
    txtMeasureLen->setCaretVisible (true);
    txtMeasureLen->setPopupMenuEnabled (true);
    txtMeasureLen->setText (TRANS("16"));

    txtMeasureLen->setBounds (16, 72, 24, 24);

    btnBPMSet.reset (new TextButton ("btnBPMSet"));
    addAndMakeVisible (btnBPMSet.get());
    btnBPMSet->setButtonText (TRANS("Set"));
    btnBPMSet->setConnectedEdges (Button::ConnectedOnLeft);
    btnBPMSet->addListener (this);

    btnBPMSet->setBounds (80, 8, 32, 24);

    lblBPM.reset (new Label ("lblBPM",
                             TRANS("120.000")));
    addAndMakeVisible (lblBPM.get());
    lblBPM->setFont (Font (30.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBPM->setJustificationType (Justification::centred);
    lblBPM->setEditable (false, false, false);
    lblBPM->setColour (TextEditor::textColourId, Colours::black);
    lblBPM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBPM->setBounds (8, 32, 112, 40);

    chkInt.reset (new ToggleButton ("chkInt"));
    addAndMakeVisible (chkInt.get());
    chkInt->setButtonText (TRANS("Int"));
    chkInt->addListener (this);

    chkInt->setBounds (72, 72, 56, 24);


    //[UserPreSize]

    trgUp.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgUp")));
    addAndMakeVisible(trgUp.get());
    trgUp->setTopLeftPosition(120, 8);

    trgDown.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgDown")));
    addAndMakeVisible(trgDown.get());
    trgDown->setTopLeftPosition(120, 64);

    trgDouble.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgDouble")));
    addAndMakeVisible(trgDouble.get());
    trgDouble->setTopLeftPosition(184, 8);

    trgHalf.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgHalf")));
    addAndMakeVisible(trgHalf.get());
    trgHalf->setTopLeftPosition(184, 64);

    trgTapBeat.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgTapBeat")));
    addAndMakeVisible(trgTapBeat.get());
    trgTapBeat->setTopLeftPosition(8, 120);

    trgTapMeasure.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgTapMeasure")));
    addAndMakeVisible(trgTapMeasure.get());
    trgTapMeasure->setTopLeftPosition(104, 120);

    trgFreeze.reset(new TriggerButton(this, this, false, 
        VT_GetChildWithProperty(tw_node, idType, "trgFreeze")));
    addAndMakeVisible(trgFreeze.get());
    trgFreeze->setTopLeftPosition(184, 120);

    txtBPM->addListener(this);
    txtMeasureLen->addListener(this);

    //[/UserPreSize]

    setSize (240, 176);


    //[Constructor] You can add your own custom stuff here..

    txtBPM->setText(String(TimingSystem::GetTempo(), 3), dontSendNotification);
    txtMeasureLen->setText(String(TimingSystem::GetBeatsPerMeasure()), dontSendNotification);
    chkInt->setToggleState(TimingSystem::IsTempoOnlyInt(), dontSendNotification);

    notNeedsMeasureLenRefresh.test_and_set();
    startTimer(33);

    //[/Constructor]
}

TimingWindow::~TimingWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    txtBPM = nullptr;
    txtMeasureLen = nullptr;
    btnBPMSet = nullptr;
    lblBPM = nullptr;
    chkInt = nullptr;


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

    {
        int x = 64, y = 128, width = 32, height = 16;
        String text (TRANS("Tap"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 8, y = 152, width = 48, height = 24;
        String text (TRANS("Beat"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 96, y = 152, width = 64, height = 24;
        String text (TRANS("Measure"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 184, y = 40, width = 48, height = 24;
        String text (CharPointer_UTF8 ("\xc3\x97""2 / \xc3\xb7""2"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 120, y = 40, width = 48, height = 24;
        String text (CharPointer_UTF8 ("\xe2\x86\x95"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (17.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 176, y = 152, width = 64, height = 24;
        String text (TRANS("Freeze"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 43, y = 73, width = 32, height = 22;
        String text (TRANS("bts"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

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

void TimingWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnBPMSet.get())
    {
        //[UserButtonCode_btnBPMSet] -- add your button handler code here..
        String text = txtBPM->getText();
        if(!isDec(text)) return;
        float d = text.getFloatValue();
        if(d < 0.1f || d > 500.0f) return;
        TimingSystem::SetTempo(d);
        //[/UserButtonCode_btnBPMSet]
    }
    else if (buttonThatWasClicked == chkInt.get())
    {
        //[UserButtonCode_chkInt] -- add your button handler code here..
        TimingSystem::SetTempoOnlyInt(chkInt->getToggleState());
        //[/UserButtonCode_chkInt]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

ValueTree TimingWindow::Save(){
    ValueTree ret(idTimingWindow);
    VT_AddChildSetProperty(ret, idType, "trgUp", trgUp->Save());
    VT_AddChildSetProperty(ret, idType, "trgDown", trgDown->Save());
    VT_AddChildSetProperty(ret, idType, "trgDouble", trgDouble->Save());
    VT_AddChildSetProperty(ret, idType, "trgHalf", trgHalf->Save());
    VT_AddChildSetProperty(ret, idType, "trgTapBeat", trgTapBeat->Save());
    VT_AddChildSetProperty(ret, idType, "trgTapMeasure", trgTapMeasure->Save());
    VT_AddChildSetProperty(ret, idType, "trgFreeze", trgFreeze->Save());
    return ret;
}

void TimingWindow::timerCallback(){
    if(!notNeedsMeasureLenRefresh.test_and_set()){
        txtMeasureLen->setText(String(TimingSystem::GetBeatsPerMeasure()), dontSendNotification);
    }
    String s = "";
    if(TimingSystem::IsFrozen()) s += "FRZ ";
    s += String(TimingSystem::GetTempo(), TimingSystem::IsFrozen() || TimingSystem::IsTempoOnlyInt() ? 0 : 3);
    lblBPM->setText(s, dontSendNotification);
}

void TimingWindow::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtBPM.get()){
        if(!isdec || decval < 0.1f || decval > 500.0f) turnRed = true;
    }else if(&editorThatWasChanged == txtMeasureLen.get()){
        if(!isint || val <= 0) turnRed = true;
        else TimingSystem::SetBeatsPerMeasure(val);
    }
    TEXTCHANGEDHANDLER_POST;
}
void TimingWindow::triggeredHiSpeed(TriggerButton *btn){
    float t = TimingSystem::GetTempo();
    if(btn == trgUp.get()){
        TimingSystem::SetTempo(t == std::floor(t) ? t + 1.0f : std::ceil(t));
    }else if(btn == trgDown.get()){
        TimingSystem::SetTempo(t == std::floor(t) ? t - 1.0f : std::floor(t));
    }else if(btn == trgDouble.get()){
        TimingSystem::SetTempo(2.0f * t);
    }else if(btn == trgHalf.get()){
        TimingSystem::SetTempo(0.5f * t);
    }else if(btn == trgTapBeat.get()){
        TimingSystem::TapBeat();
    }else if(btn == trgTapMeasure.get()){
        TimingSystem::TapMeasure();
        notNeedsMeasureLenRefresh.clear();
    }else if(btn == trgFreeze.get()){
        TimingSystem::ToggleFreeze();
    }
}

void TimingWindow::HandleMIDI(int port, MidiMessage msg){
    trgUp->HandleMIDI(port, msg);
    trgDown->HandleMIDI(port, msg);
    trgDouble->HandleMIDI(port, msg);
    trgHalf->HandleMIDI(port, msg);
    trgTapBeat->HandleMIDI(port, msg);
    trgTapMeasure->HandleMIDI(port, msg);
    trgFreeze->HandleMIDI(port, msg);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimingWindow" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TriggerButton::HiSpeedListener, private Timer"
                 constructorParams="ValueTree tw_node" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.660"
                 fixedSize="1" initialWidth="240" initialHeight="176">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="64 128 32 16" fill="solid: ffffffff" hasStroke="0" text="Tap"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="8 152 48 24" fill="solid: ffffffff" hasStroke="0" text="Beat"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="96 152 64 24" fill="solid: ffffffff" hasStroke="0" text="Measure"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="184 40 48 24" fill="solid: ffffffff" hasStroke="0" text="&#215;2 / &#247;2"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="120 40 48 24" fill="solid: ffffffff" hasStroke="0" text="&#8597;"
          fontname="Default font" fontsize="17.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="176 152 64 24" fill="solid: ffffffff" hasStroke="0" text="Freeze"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="43 73 32 22" fill="solid: ffffffff" hasStroke="0" text="bts"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
  </BACKGROUND>
  <TEXTEDITOR name="txtBPM" id="37e3bc569d4b8cc" memberName="txtBPM" virtualName=""
              explicitFocusOrder="0" pos="16 8 64 24" initialText="123.456"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtMeasureLen" id="a58c3c5dac9fca7e" memberName="txtMeasureLen"
              virtualName="" explicitFocusOrder="0" pos="16 72 24 24" initialText="16"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnBPMSet" id="fb881a8402a7ef15" memberName="btnBPMSet"
              virtualName="" explicitFocusOrder="0" pos="80 8 32 24" buttonText="Set"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblBPM" id="23b1d7913a26df55" memberName="lblBPM" virtualName=""
         explicitFocusOrder="0" pos="8 32 112 40" edTextCol="ff000000"
         edBkgCol="0" labelText="120.000" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="30.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="chkInt" id="75c7b174ffa3061" memberName="chkInt" virtualName=""
                explicitFocusOrder="0" pos="72 72 56 24" buttonText="Int" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
