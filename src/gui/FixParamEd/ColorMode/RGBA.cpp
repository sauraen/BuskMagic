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

#include "RGBA.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RGBA::RGBA ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblR.reset (new Label ("lblR",
                           TRANS("R:")));
    addAndMakeVisible (lblR.get());
    lblR->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblR->setJustificationType (Justification::centredLeft);
    lblR->setEditable (false, false, false);
    lblR->setColour (TextEditor::textColourId, Colours::black);
    lblR->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblR->setBounds (0, 24, 23, 24);

    txtDMXR.reset (new TextEditor ("txtDMXR"));
    addAndMakeVisible (txtDMXR.get());
    txtDMXR->setMultiLine (false);
    txtDMXR->setReturnKeyStartsNewLine (false);
    txtDMXR->setReadOnly (false);
    txtDMXR->setScrollbarsShown (true);
    txtDMXR->setCaretVisible (true);
    txtDMXR->setPopupMenuEnabled (true);
    txtDMXR->setText (String());

    txtDMXR->setBounds (24, 24, 72, 24);

    txtHueR.reset (new TextEditor ("txtHueR"));
    addAndMakeVisible (txtHueR.get());
    txtHueR->setMultiLine (false);
    txtHueR->setReturnKeyStartsNewLine (false);
    txtHueR->setReadOnly (false);
    txtHueR->setScrollbarsShown (true);
    txtHueR->setCaretVisible (true);
    txtHueR->setPopupMenuEnabled (true);
    txtHueR->setText (TRANS("0.00"));

    txtHueR->setBounds (104, 24, 56, 24);

    lblRA.reset (new Label ("lblRA",
                            TRANS("R+A (Orange):")));
    addAndMakeVisible (lblRA.get());
    lblRA->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblRA->setJustificationType (Justification::centredLeft);
    lblRA->setEditable (false, false, false);
    lblRA->setColour (TextEditor::textColourId, Colours::black);
    lblRA->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblRA->setBounds (0, 48, 104, 24);

    txtHueRA.reset (new TextEditor ("txtHueRA"));
    addAndMakeVisible (txtHueRA.get());
    txtHueRA->setMultiLine (false);
    txtHueRA->setReturnKeyStartsNewLine (false);
    txtHueRA->setReadOnly (false);
    txtHueRA->setScrollbarsShown (true);
    txtHueRA->setCaretVisible (true);
    txtHueRA->setPopupMenuEnabled (true);
    txtHueRA->setText (TRANS("0.10"));

    txtHueRA->setBounds (104, 48, 56, 24);

    lblG.reset (new Label ("lblG",
                           TRANS("G:")));
    addAndMakeVisible (lblG.get());
    lblG->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblG->setJustificationType (Justification::centredLeft);
    lblG->setEditable (false, false, false);
    lblG->setColour (TextEditor::textColourId, Colours::black);
    lblG->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblG->setBounds (0, 120, 23, 24);

    txtDMXG.reset (new TextEditor ("txtDMXG"));
    addAndMakeVisible (txtDMXG.get());
    txtDMXG->setMultiLine (false);
    txtDMXG->setReturnKeyStartsNewLine (false);
    txtDMXG->setReadOnly (false);
    txtDMXG->setScrollbarsShown (true);
    txtDMXG->setCaretVisible (true);
    txtDMXG->setPopupMenuEnabled (true);
    txtDMXG->setText (String());

    txtDMXG->setBounds (24, 120, 72, 24);

    txtHueG.reset (new TextEditor ("txtHueG"));
    addAndMakeVisible (txtHueG.get());
    txtHueG->setMultiLine (false);
    txtHueG->setReturnKeyStartsNewLine (false);
    txtHueG->setReadOnly (false);
    txtHueG->setScrollbarsShown (true);
    txtHueG->setCaretVisible (true);
    txtHueG->setPopupMenuEnabled (true);
    txtHueG->setText (TRANS("0.50"));

    txtHueG->setBounds (104, 120, 56, 24);

    lblGB.reset (new Label ("lblGB",
                            TRANS("G+B (Cyan):")));
    addAndMakeVisible (lblGB.get());
    lblGB->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblGB->setJustificationType (Justification::centredLeft);
    lblGB->setEditable (false, false, false);
    lblGB->setColour (TextEditor::textColourId, Colours::black);
    lblGB->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblGB->setBounds (0, 144, 104, 24);

    txtHueGB.reset (new TextEditor ("txtHueGB"));
    addAndMakeVisible (txtHueGB.get());
    txtHueGB->setMultiLine (false);
    txtHueGB->setReturnKeyStartsNewLine (false);
    txtHueGB->setReadOnly (false);
    txtHueGB->setScrollbarsShown (true);
    txtHueGB->setCaretVisible (true);
    txtHueGB->setPopupMenuEnabled (true);
    txtHueGB->setText (TRANS("0.625"));

    txtHueGB->setBounds (104, 144, 56, 24);

    lblB.reset (new Label ("lblB",
                           TRANS("B:")));
    addAndMakeVisible (lblB.get());
    lblB->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblB->setJustificationType (Justification::centredLeft);
    lblB->setEditable (false, false, false);
    lblB->setColour (TextEditor::textColourId, Colours::black);
    lblB->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblB->setBounds (0, 168, 23, 24);

    txtDMXB.reset (new TextEditor ("txtDMXB"));
    addAndMakeVisible (txtDMXB.get());
    txtDMXB->setMultiLine (false);
    txtDMXB->setReturnKeyStartsNewLine (false);
    txtDMXB->setReadOnly (false);
    txtDMXB->setScrollbarsShown (true);
    txtDMXB->setCaretVisible (true);
    txtDMXB->setPopupMenuEnabled (true);
    txtDMXB->setText (String());

    txtDMXB->setBounds (24, 168, 72, 24);

    txtHueB.reset (new TextEditor ("txtHueB"));
    addAndMakeVisible (txtHueB.get());
    txtHueB->setMultiLine (false);
    txtHueB->setReturnKeyStartsNewLine (false);
    txtHueB->setReadOnly (false);
    txtHueB->setScrollbarsShown (true);
    txtHueB->setCaretVisible (true);
    txtHueB->setPopupMenuEnabled (true);
    txtHueB->setText (TRANS("0.75"));

    txtHueB->setBounds (104, 168, 56, 24);

    lblBR.reset (new Label ("lblBR",
                            TRANS("B+R (Magenta):")));
    addAndMakeVisible (lblBR.get());
    lblBR->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBR->setJustificationType (Justification::centredLeft);
    lblBR->setEditable (false, false, false);
    lblBR->setColour (TextEditor::textColourId, Colours::black);
    lblBR->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBR->setBounds (0, 192, 104, 24);

    txtHueBR.reset (new TextEditor ("txtHueBR"));
    addAndMakeVisible (txtHueBR.get());
    txtHueBR->setMultiLine (false);
    txtHueBR->setReturnKeyStartsNewLine (false);
    txtHueBR->setReadOnly (false);
    txtHueBR->setScrollbarsShown (true);
    txtHueBR->setCaretVisible (true);
    txtHueBR->setPopupMenuEnabled (true);
    txtHueBR->setText (TRANS("0.875"));

    txtHueBR->setBounds (104, 192, 56, 24);

    lblDescription.reset (new Label ("lblDescription",
                                     TRANS("DMX             Hue")));
    addAndMakeVisible (lblDescription.get());
    lblDescription->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDescription->setJustificationType (Justification::centredLeft);
    lblDescription->setEditable (false, false, false);
    lblDescription->setColour (TextEditor::textColourId, Colours::black);
    lblDescription->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDescription->setBounds (24, 0, 128, 24);

    lblA.reset (new Label ("lblA",
                           TRANS("A:")));
    addAndMakeVisible (lblA.get());
    lblA->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblA->setJustificationType (Justification::centredLeft);
    lblA->setEditable (false, false, false);
    lblA->setColour (TextEditor::textColourId, Colours::black);
    lblA->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblA->setBounds (0, 72, 23, 24);

    txtDMXA.reset (new TextEditor ("txtDMXA"));
    addAndMakeVisible (txtDMXA.get());
    txtDMXA->setMultiLine (false);
    txtDMXA->setReturnKeyStartsNewLine (false);
    txtDMXA->setReadOnly (false);
    txtDMXA->setScrollbarsShown (true);
    txtDMXA->setCaretVisible (true);
    txtDMXA->setPopupMenuEnabled (true);
    txtDMXA->setText (String());

    txtDMXA->setBounds (24, 72, 72, 24);

    txtHueA.reset (new TextEditor ("txtHueA"));
    addAndMakeVisible (txtHueA.get());
    txtHueA->setMultiLine (false);
    txtHueA->setReturnKeyStartsNewLine (false);
    txtHueA->setReadOnly (false);
    txtHueA->setScrollbarsShown (true);
    txtHueA->setCaretVisible (true);
    txtHueA->setPopupMenuEnabled (true);
    txtHueA->setText (TRANS("0.20"));

    txtHueA->setBounds (104, 72, 56, 24);

    lblAG.reset (new Label ("lblAG",
                            TRANS("A+G (YellowGr):")));
    addAndMakeVisible (lblAG.get());
    lblAG->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAG->setJustificationType (Justification::centredLeft);
    lblAG->setEditable (false, false, false);
    lblAG->setColour (TextEditor::textColourId, Colours::black);
    lblAG->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAG->setBounds (0, 96, 104, 24);

    txtHueAG.reset (new TextEditor ("txtHueAG"));
    addAndMakeVisible (txtHueAG.get());
    txtHueAG->setMultiLine (false);
    txtHueAG->setReturnKeyStartsNewLine (false);
    txtHueAG->setReadOnly (false);
    txtHueAG->setScrollbarsShown (true);
    txtHueAG->setCaretVisible (true);
    txtHueAG->setPopupMenuEnabled (true);
    txtHueAG->setText (TRANS("0.32"));

    txtHueAG->setBounds (104, 96, 56, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (160, 216);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

RGBA::~RGBA()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblR = nullptr;
    txtDMXR = nullptr;
    txtHueR = nullptr;
    lblRA = nullptr;
    txtHueRA = nullptr;
    lblG = nullptr;
    txtDMXG = nullptr;
    txtHueG = nullptr;
    lblGB = nullptr;
    txtHueGB = nullptr;
    lblB = nullptr;
    txtDMXB = nullptr;
    txtHueB = nullptr;
    lblBR = nullptr;
    txtHueBR = nullptr;
    lblDescription = nullptr;
    lblA = nullptr;
    txtDMXA = nullptr;
    txtHueA = nullptr;
    lblAG = nullptr;
    txtHueAG = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RGBA::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RGBA::resized()
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

<JUCER_COMPONENT documentType="Component" className="RGBA" componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="160"
                 initialHeight="216">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblR" id="38f1aaac5d95b0ca" memberName="lblR" virtualName=""
         explicitFocusOrder="0" pos="0 24 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXR" id="9f7ee9c7e89d53ab" memberName="txtDMXR" virtualName=""
              explicitFocusOrder="0" pos="24 24 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueR" id="ea26a466b5e37632" memberName="txtHueR" virtualName=""
              explicitFocusOrder="0" pos="104 24 56 24" initialText="0.00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblRA" id="d5801027ede5aabd" memberName="lblRA" virtualName=""
         explicitFocusOrder="0" pos="0 48 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R+A (Orange):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueRA" id="69717f9b2bef903" memberName="txtHueRA" virtualName=""
              explicitFocusOrder="0" pos="104 48 56 24" initialText="0.10"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblG" id="181bac7d94b8484e" memberName="lblG" virtualName=""
         explicitFocusOrder="0" pos="0 120 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="G:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXG" id="a300f505f364945e" memberName="txtDMXG" virtualName=""
              explicitFocusOrder="0" pos="24 120 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueG" id="e303282fc8afe509" memberName="txtHueG" virtualName=""
              explicitFocusOrder="0" pos="104 120 56 24" initialText="0.50"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblGB" id="4fe7d4a4da0dd757" memberName="lblGB" virtualName=""
         explicitFocusOrder="0" pos="0 144 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="G+B (Cyan):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueGB" id="c241147e133d676e" memberName="txtHueGB" virtualName=""
              explicitFocusOrder="0" pos="104 144 56 24" initialText="0.625"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblB" id="d32fe5ac40f01595" memberName="lblB" virtualName=""
         explicitFocusOrder="0" pos="0 168 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="B:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXB" id="249d88025ae5b5a2" memberName="txtDMXB" virtualName=""
              explicitFocusOrder="0" pos="24 168 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueB" id="135f6bd2f86e9a29" memberName="txtHueB" virtualName=""
              explicitFocusOrder="0" pos="104 168 56 24" initialText="0.75"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblBR" id="a838fb38874abaf9" memberName="lblBR" virtualName=""
         explicitFocusOrder="0" pos="0 192 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="B+R (Magenta):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueBR" id="3fead027864ef25f" memberName="txtHueBR" virtualName=""
              explicitFocusOrder="0" pos="104 192 56 24" initialText="0.875"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblDescription" id="805bbb1ad803a595" memberName="lblDescription"
         virtualName="" explicitFocusOrder="0" pos="24 0 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="DMX             Hue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblA" id="15045b7fb759b1db" memberName="lblA" virtualName=""
         explicitFocusOrder="0" pos="0 72 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="A:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXA" id="8d0fe68520e759fd" memberName="txtDMXA" virtualName=""
              explicitFocusOrder="0" pos="24 72 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueA" id="5495ef2fdaea0c9c" memberName="txtHueA" virtualName=""
              explicitFocusOrder="0" pos="104 72 56 24" initialText="0.20"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblAG" id="396d5ec9acdc2688" memberName="lblAG" virtualName=""
         explicitFocusOrder="0" pos="0 96 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="A+G (YellowGr):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueAG" id="a1cd12ee21b1909" memberName="txtHueAG" virtualName=""
              explicitFocusOrder="0" pos="104 96 56 24" initialText="0.32"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

