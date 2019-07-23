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

#include "FixtureEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FixtureEditor::FixtureEditor ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblManufacturer.reset (new Label ("lblManufacturer",
                                      TRANS("Manufacturer:")));
    addAndMakeVisible (lblManufacturer.get());
    lblManufacturer->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblManufacturer->setJustificationType (Justification::centredLeft);
    lblManufacturer->setEditable (false, false, false);
    lblManufacturer->setColour (TextEditor::textColourId, Colours::black);
    lblManufacturer->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblManufacturer->setBounds (0, 0, 96, 24);

    txtManufacturer.reset (new TextEditor ("txtManufacturer"));
    addAndMakeVisible (txtManufacturer.get());
    txtManufacturer->setMultiLine (false);
    txtManufacturer->setReturnKeyStartsNewLine (false);
    txtManufacturer->setReadOnly (false);
    txtManufacturer->setScrollbarsShown (true);
    txtManufacturer->setCaretVisible (true);
    txtManufacturer->setPopupMenuEnabled (true);
    txtManufacturer->setText (String());

    txtManufacturer->setBounds (96, 0, 248, 24);

    lblFixtureName.reset (new Label ("lblFixtureName",
                                     TRANS("Fixture Name:")));
    addAndMakeVisible (lblFixtureName.get());
    lblFixtureName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblFixtureName->setJustificationType (Justification::centredLeft);
    lblFixtureName->setEditable (false, false, false);
    lblFixtureName->setColour (TextEditor::textColourId, Colours::black);
    lblFixtureName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblFixtureName->setBounds (0, 24, 96, 24);

    txtFixtureName.reset (new TextEditor ("txtFixtureName"));
    addAndMakeVisible (txtFixtureName.get());
    txtFixtureName->setMultiLine (false);
    txtFixtureName->setReturnKeyStartsNewLine (false);
    txtFixtureName->setReadOnly (false);
    txtFixtureName->setScrollbarsShown (true);
    txtFixtureName->setCaretVisible (true);
    txtFixtureName->setPopupMenuEnabled (true);
    txtFixtureName->setText (String());

    txtFixtureName->setBounds (96, 24, 248, 24);

    lblProfileName.reset (new Label ("lblProfileName",
                                     TRANS("Profile Name:")));
    addAndMakeVisible (lblProfileName.get());
    lblProfileName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblProfileName->setJustificationType (Justification::centredLeft);
    lblProfileName->setEditable (false, false, false);
    lblProfileName->setColour (TextEditor::textColourId, Colours::black);
    lblProfileName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblProfileName->setBounds (0, 48, 96, 24);

    txtProfileName.reset (new TextEditor ("txtProfileName"));
    addAndMakeVisible (txtProfileName.get());
    txtProfileName->setMultiLine (false);
    txtProfileName->setReturnKeyStartsNewLine (false);
    txtProfileName->setReadOnly (false);
    txtProfileName->setScrollbarsShown (true);
    txtProfileName->setCaretVisible (true);
    txtProfileName->setPopupMenuEnabled (true);
    txtProfileName->setText (String());

    txtProfileName->setBounds (96, 48, 248, 24);

    lblDMX.reset (new Label ("lblDMX",
                             TRANS("DMX Channels:")));
    addAndMakeVisible (lblDMX.get());
    lblDMX->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDMX->setJustificationType (Justification::centredLeft);
    lblDMX->setEditable (false, false, false);
    lblDMX->setColour (TextEditor::textColourId, Colours::black);
    lblDMX->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDMX->setBounds (0, 72, 104, 24);

    txtDMX.reset (new TextEditor ("txtDMX"));
    addAndMakeVisible (txtDMX.get());
    txtDMX->setMultiLine (false);
    txtDMX->setReturnKeyStartsNewLine (false);
    txtDMX->setReadOnly (false);
    txtDMX->setScrollbarsShown (true);
    txtDMX->setCaretVisible (true);
    txtDMX->setPopupMenuEnabled (true);
    txtDMX->setText (TRANS("0"));

    txtDMX->setBounds (104, 72, 32, 24);

    lblParameters.reset (new Label ("lblParameters",
                                    TRANS("Parameters:")));
    addAndMakeVisible (lblParameters.get());
    lblParameters->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblParameters->setJustificationType (Justification::centredLeft);
    lblParameters->setEditable (false, false, false);
    lblParameters->setColour (TextEditor::textColourId, Colours::black);
    lblParameters->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblParameters->setBounds (0, 96, 88, 24);

    lblAddParam.reset (new Label ("lblAddParam",
                                  TRANS("Add:")));
    addAndMakeVisible (lblAddParam.get());
    lblAddParam->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddParam->setJustificationType (Justification::centredLeft);
    lblAddParam->setEditable (false, false, false);
    lblAddParam->setColour (TextEditor::textColourId, Colours::black);
    lblAddParam->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddParam->setBounds (0, 360, 39, 24);

    cbxAddParam.reset (new ComboBox ("cbxAddParam"));
    addAndMakeVisible (cbxAddParam.get());
    cbxAddParam->setEditableText (false);
    cbxAddParam->setJustificationType (Justification::centredLeft);
    cbxAddParam->setTextWhenNothingSelected (TRANS("Dimmer"));
    cbxAddParam->setTextWhenNoChoicesAvailable (TRANS("Error"));
    cbxAddParam->addItem (TRANS("Dimmer"), 1);
    cbxAddParam->addItem (TRANS("Color"), 2);
    cbxAddParam->addItem (TRANS("Colorwheel"), 3);
    cbxAddParam->addItem (TRANS("Pan"), 4);
    cbxAddParam->addItem (TRANS("Tilt"), 5);
    cbxAddParam->addItem (TRANS("Zoom"), 6);
    cbxAddParam->addItem (TRANS("Focus"), 7);
    cbxAddParam->addItem (TRANS("Frost"), 8);
    cbxAddParam->addItem (TRANS("Iris"), 9);
    cbxAddParam->addItem (TRANS("Shutter"), 10);
    cbxAddParam->addItem (TRANS("Prism"), 11);
    cbxAddParam->addItem (TRANS("Gobo"), 12);
    cbxAddParam->addItem (TRANS("Effect"), 13);
    cbxAddParam->addItem (TRANS("Control"), 14);
    cbxAddParam->addItem (TRANS("Misc"), 15);
    cbxAddParam->addListener (this);

    cbxAddParam->setBounds (40, 360, 120, 24);

    btnAddParam.reset (new TextButton ("btnAddParam"));
    addAndMakeVisible (btnAddParam.get());
    btnAddParam->setButtonText (TRANS("+"));
    btnAddParam->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnAddParam->addListener (this);

    btnAddParam->setBounds (160, 360, 23, 24);

    btnRemoveParam.reset (new TextButton ("btnRemoveParam"));
    addAndMakeVisible (btnRemoveParam.get());
    btnRemoveParam->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveParam->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnRemoveParam->addListener (this);

    btnRemoveParam->setBounds (112, 96, 23, 24);

    btnParamUp.reset (new TextButton ("btnParamUp"));
    addAndMakeVisible (btnParamUp.get());
    btnParamUp->setButtonText (CharPointer_UTF8 ("\xe2\x86\x91"));
    btnParamUp->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnParamUp->addListener (this);

    btnParamUp->setBounds (136, 96, 23, 24);

    btnParamDown.reset (new TextButton ("btnParamDown"));
    addAndMakeVisible (btnParamDown.get());
    btnParamDown->setButtonText (CharPointer_UTF8 ("\xe2\x86\x93"));
    btnParamDown->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnParamDown->addListener (this);

    btnParamDown->setBounds (160, 96, 23, 24);

    lblPName.reset (new Label ("lblPName",
                               TRANS("Name:")));
    addAndMakeVisible (lblPName.get());
    lblPName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblPName->setJustificationType (Justification::centredLeft);
    lblPName->setEditable (false, false, false);
    lblPName->setColour (TextEditor::textColourId, Colours::black);
    lblPName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblPName->setBounds (184, 96, 56, 24);

    textEditor.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (textEditor.get());
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String());

    textEditor->setBounds (240, 96, 104, 24);

    label.reset (new Label ("new label",
                            TRANS("Short name (1-2 ltrs):")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (184, 120, 136, 24);

    textEditor2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (textEditor2.get());
    textEditor2->setMultiLine (false);
    textEditor2->setReturnKeyStartsNewLine (false);
    textEditor2->setReadOnly (false);
    textEditor2->setScrollbarsShown (true);
    textEditor2->setCaretVisible (true);
    textEditor2->setPopupMenuEnabled (true);
    textEditor2->setText (String());

    textEditor2->setBounds (320, 120, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (344, 384);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FixtureEditor::~FixtureEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblManufacturer = nullptr;
    txtManufacturer = nullptr;
    lblFixtureName = nullptr;
    txtFixtureName = nullptr;
    lblProfileName = nullptr;
    txtProfileName = nullptr;
    lblDMX = nullptr;
    txtDMX = nullptr;
    lblParameters = nullptr;
    lblAddParam = nullptr;
    cbxAddParam = nullptr;
    btnAddParam = nullptr;
    btnRemoveParam = nullptr;
    btnParamUp = nullptr;
    btnParamDown = nullptr;
    lblPName = nullptr;
    textEditor = nullptr;
    label = nullptr;
    textEditor2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FixtureEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 120, width = 184, height = 240;
        Colour fillColour = Colour (0xffa5412a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 184, y = 144, width = 160, height = 240;
        Colour fillColour = Colour (0xffa52a4d);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FixtureEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FixtureEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxAddParam.get())
    {
        //[UserComboBoxCode_cbxAddParam] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxAddParam]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void FixtureEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnAddParam.get())
    {
        //[UserButtonCode_btnAddParam] -- add your button handler code here..
        //[/UserButtonCode_btnAddParam]
    }
    else if (buttonThatWasClicked == btnRemoveParam.get())
    {
        //[UserButtonCode_btnRemoveParam] -- add your button handler code here..
        //[/UserButtonCode_btnRemoveParam]
    }
    else if (buttonThatWasClicked == btnParamUp.get())
    {
        //[UserButtonCode_btnParamUp] -- add your button handler code here..
        //[/UserButtonCode_btnParamUp]
    }
    else if (buttonThatWasClicked == btnParamDown.get())
    {
        //[UserButtonCode_btnParamDown] -- add your button handler code here..
        //[/UserButtonCode_btnParamDown]
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

<JUCER_COMPONENT documentType="Component" className="FixtureEditor" componentName=""
                 parentClasses="public Component, public TextListModel::Listener, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="344"
                 initialHeight="384">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 120 184 240" fill="solid: ffa5412a" hasStroke="0"/>
    <RECT pos="184 144 160 240" fill="solid: ffa52a4d" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="lblManufacturer" id="4f03172ce75ed418" memberName="lblManufacturer"
         virtualName="" explicitFocusOrder="0" pos="0 0 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Manufacturer:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtManufacturer" id="dc10fb62cbb3c7bb" memberName="txtManufacturer"
              virtualName="" explicitFocusOrder="0" pos="96 0 248 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblFixtureName" id="624e45f2c29b9975" memberName="lblFixtureName"
         virtualName="" explicitFocusOrder="0" pos="0 24 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fixture Name:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtFixtureName" id="1a937ffc570067ed" memberName="txtFixtureName"
              virtualName="" explicitFocusOrder="0" pos="96 24 248 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblProfileName" id="7cfd0e70f06c240b" memberName="lblProfileName"
         virtualName="" explicitFocusOrder="0" pos="0 48 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Profile Name:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtProfileName" id="b6138ceadd0ae96f" memberName="txtProfileName"
              virtualName="" explicitFocusOrder="0" pos="96 48 248 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblDMX" id="f72cd4a6867a395a" memberName="lblDMX" virtualName=""
         explicitFocusOrder="0" pos="0 72 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="DMX Channels:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMX" id="860e67035d42db35" memberName="txtDMX" virtualName=""
              explicitFocusOrder="0" pos="104 72 32 24" initialText="0" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblParameters" id="ef5a52390094e6dc" memberName="lblParameters"
         virtualName="" explicitFocusOrder="0" pos="0 96 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Parameters:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblAddParam" id="be324afea060f313" memberName="lblAddParam"
         virtualName="" explicitFocusOrder="0" pos="0 360 39 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Add:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cbxAddParam" id="e40645e8dd385269" memberName="cbxAddParam"
            virtualName="" explicitFocusOrder="0" pos="40 360 120 24" editable="0"
            layout="33" items="Dimmer&#10;Color&#10;Colorwheel&#10;Pan&#10;Tilt&#10;Zoom&#10;Focus&#10;Frost&#10;Iris&#10;Shutter&#10;Prism&#10;Gobo&#10;Effect&#10;Control&#10;Misc"
            textWhenNonSelected="Dimmer" textWhenNoItems="Error"/>
  <TEXTBUTTON name="btnAddParam" id="7ceb28d89a1747a0" memberName="btnAddParam"
              virtualName="" explicitFocusOrder="0" pos="160 360 23 24" buttonText="+"
              connectedEdges="5" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveParam" id="506bcac0d99da01e" memberName="btnRemoveParam"
              virtualName="" explicitFocusOrder="0" pos="112 96 23 24" buttonText="&#8722;"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnParamUp" id="c0e4ec84cb12c95b" memberName="btnParamUp"
              virtualName="" explicitFocusOrder="0" pos="136 96 23 24" buttonText="&#8593;"
              connectedEdges="11" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnParamDown" id="83e3f14852852c5b" memberName="btnParamDown"
              virtualName="" explicitFocusOrder="0" pos="160 96 23 24" buttonText="&#8595;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblPName" id="2c6c6437b4fb9d3f" memberName="lblPName" virtualName=""
         explicitFocusOrder="0" pos="184 96 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1f724a66d24c5ca3" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="240 96 104 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="70d37e528f64ad4d" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="184 120 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Short name (1-2 ltrs):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="3345abdfa53cef46" memberName="textEditor2"
              virtualName="" explicitFocusOrder="0" pos="320 120 24 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

