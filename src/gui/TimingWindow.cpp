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
//[/Headers]

#include "TimingWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TimingWindow::TimingWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
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

    lblTapDouble.reset (new Label ("lblTapBeat",
                                   TRANS("x2")));
    addAndMakeVisible (lblTapDouble.get());
    lblTapDouble->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTapDouble->setJustificationType (Justification::centred);
    lblTapDouble->setEditable (false, false, false);
    lblTapDouble->setColour (TextEditor::textColourId, Colours::black);
    lblTapDouble->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTapDouble->setBounds (8, 136, 64, 24);

    lblTapHalf.reset (new Label ("lblTapHalf",
                                 TRANS("/2")));
    addAndMakeVisible (lblTapHalf.get());
    lblTapHalf->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTapHalf->setJustificationType (Justification::centred);
    lblTapHalf->setEditable (false, false, false);
    lblTapHalf->setColour (TextEditor::textColourId, Colours::black);
    lblTapHalf->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTapHalf->setBounds (88, 136, 64, 24);

    lblTempo.reset (new Label ("lblTempo",
                               TRANS("Tempo:")));
    addAndMakeVisible (lblTempo.get());
    lblTempo->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTempo->setJustificationType (Justification::centredLeft);
    lblTempo->setEditable (false, false, false);
    lblTempo->setColour (TextEditor::textColourId, Colours::black);
    lblTempo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblTempo->setBounds (168, 16, 56, 24);

    textEditor.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (textEditor.get());
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (TRANS("123.456"));

    textEditor->setBounds (224, 16, 56, 24);

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

    textEditor2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (textEditor2.get());
    textEditor2->setMultiLine (false);
    textEditor2->setReturnKeyStartsNewLine (false);
    textEditor2->setReadOnly (false);
    textEditor2->setScrollbarsShown (true);
    textEditor2->setCaretVisible (true);
    textEditor2->setPopupMenuEnabled (true);
    textEditor2->setText (TRANS("16"));

    textEditor2->setBounds (240, 40, 24, 24);

    label.reset (new Label ("new label",
                            TRANS("beats")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (264, 40, 56, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (328, 160);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TimingWindow::~TimingWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblTapBeat = nullptr;
    lblTapMeasure = nullptr;
    lblTapDouble = nullptr;
    lblTapHalf = nullptr;
    lblTempo = nullptr;
    textEditor = nullptr;
    lblMeasure = nullptr;
    lblBPM = nullptr;
    textEditor2 = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TimingWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 16, y = 16, width = 48, height = 32;
        Colour fillColour = Colour (0xffa5792a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 96, y = 16, width = 48, height = 32;
        Colour fillColour = Colour (0xffa5792a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 16, y = 96, width = 48, height = 32;
        Colour fillColour = Colour (0xffa5792a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 96, y = 96, width = 48, height = 32;
        Colour fillColour = Colour (0xffa5792a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimingWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="328" initialHeight="160">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="16 16 48 32" fill="solid: ffa5792a" hasStroke="0"/>
    <RECT pos="96 16 48 32" fill="solid: ffa5792a" hasStroke="0"/>
    <RECT pos="16 96 48 32" fill="solid: ffa5792a" hasStroke="0"/>
    <RECT pos="96 96 48 32" fill="solid: ffa5792a" hasStroke="0"/>
  </BACKGROUND>
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
  <LABEL name="lblTapBeat" id="36f9e9bd24dc7f2e" memberName="lblTapDouble"
         virtualName="" explicitFocusOrder="0" pos="8 136 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblTapHalf" id="a655a61b87d5cf52" memberName="lblTapHalf"
         virtualName="" explicitFocusOrder="0" pos="88 136 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="lblTempo" id="6606c2230e91c01f" memberName="lblTempo" virtualName=""
         explicitFocusOrder="0" pos="168 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="37e3bc569d4b8cc" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="224 16 56 24" initialText="123.456"
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
  <TEXTEDITOR name="new text editor" id="a58c3c5dac9fca7e" memberName="textEditor2"
              virtualName="" explicitFocusOrder="0" pos="240 40 24 24" initialText="16"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="4e4054d3038cc2b1" memberName="label" virtualName=""
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

