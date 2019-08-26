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

#include "gui/FixParamEd/Generic.h"
#include "gui/FixParamEd/Color.h"

#include "FixtureSystem.h"
//[/Headers]

#include "FixtureEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FixtureEditor::FixtureEditor (ValueTree fxt)
    : fixture(fxt)
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
                             TRANS("DMX Footprint:")));
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

    lblAddParam->setBounds (0, 384, 39, 24);

    cbxAddParam.reset (new ComboBox ("cbxAddParam"));
    addAndMakeVisible (cbxAddParam.get());
    cbxAddParam->setEditableText (false);
    cbxAddParam->setJustificationType (Justification::centredLeft);
    cbxAddParam->setTextWhenNothingSelected (TRANS("Generic"));
    cbxAddParam->setTextWhenNoChoicesAvailable (TRANS("Error"));
    cbxAddParam->addItem (TRANS("Generic"), 1);
    cbxAddParam->addItem (TRANS("Color"), 2);
    cbxAddParam->addListener (this);

    cbxAddParam->setBounds (40, 384, 120, 24);

    btnAddParam.reset (new TextButton ("btnAddParam"));
    addAndMakeVisible (btnAddParam.get());
    btnAddParam->setButtonText (TRANS("+"));
    btnAddParam->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnAddParam->addListener (this);

    btnAddParam->setBounds (160, 384, 24, 24);

    btnRemoveParam.reset (new TextButton ("btnRemoveParam"));
    addAndMakeVisible (btnRemoveParam.get());
    btnRemoveParam->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveParam->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnRemoveParam->addListener (this);

    btnRemoveParam->setBounds (112, 96, 24, 24);

    btnParamUp.reset (new TextButton ("btnParamUp"));
    addAndMakeVisible (btnParamUp.get());
    btnParamUp->setButtonText (CharPointer_UTF8 ("\xe2\x86\x91"));
    btnParamUp->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnParamUp->addListener (this);

    btnParamUp->setBounds (136, 96, 24, 24);

    btnParamDown.reset (new TextButton ("btnParamDown"));
    addAndMakeVisible (btnParamDown.get());
    btnParamDown->setButtonText (CharPointer_UTF8 ("\xe2\x86\x93"));
    btnParamDown->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnParamDown->addListener (this);

    btnParamDown->setBounds (160, 96, 24, 24);

    lblPName.reset (new Label ("lblPName",
                               TRANS("Name:")));
    addAndMakeVisible (lblPName.get());
    lblPName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblPName->setJustificationType (Justification::centredLeft);
    lblPName->setEditable (false, false, false);
    lblPName->setColour (TextEditor::textColourId, Colours::black);
    lblPName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblPName->setBounds (184, 96, 56, 24);

    txtPName.reset (new TextEditor ("txtPName"));
    addAndMakeVisible (txtPName.get());
    txtPName->setMultiLine (false);
    txtPName->setReturnKeyStartsNewLine (false);
    txtPName->setReadOnly (false);
    txtPName->setScrollbarsShown (true);
    txtPName->setCaretVisible (true);
    txtPName->setPopupMenuEnabled (true);
    txtPName->setText (String());

    txtPName->setBounds (240, 96, 104, 24);

    lblPLetters.reset (new Label ("lblPLetters",
                                  TRANS("Short name (1-2 ltrs):")));
    addAndMakeVisible (lblPLetters.get());
    lblPLetters->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblPLetters->setJustificationType (Justification::centredLeft);
    lblPLetters->setEditable (false, false, false);
    lblPLetters->setColour (TextEditor::textColourId, Colours::black);
    lblPLetters->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblPLetters->setBounds (184, 120, 136, 24);

    txtPLetters.reset (new TextEditor ("txtPLetters"));
    addAndMakeVisible (txtPLetters.get());
    txtPLetters->setMultiLine (false);
    txtPLetters->setReturnKeyStartsNewLine (false);
    txtPLetters->setReadOnly (false);
    txtPLetters->setScrollbarsShown (true);
    txtPLetters->setCaretVisible (true);
    txtPLetters->setPopupMenuEnabled (true);
    txtPLetters->setText (String());

    txtPLetters->setBounds (320, 120, 24, 24);


    //[UserPreSize]

    lstParams.reset(new TextListBox(this));
    addAndMakeVisible(lstParams.get());
    lstParams->setBounds(0, 120, 184, 264);

    txtManufacturer->addListener(this);
    txtFixtureName->addListener(this);
    txtProfileName->addListener(this);
    txtDMX->addListener(this);
    txtPName->addListener(this);
    txtPLetters->addListener(this);
    
    setOpaque(true);
    
    //[/UserPreSize]

    setSize (344, 408);


    //[Constructor] You can add your own custom stuff here..

    cbxAddParam->setSelectedItemIndex(0, dontSendNotification);

    txtManufacturer->setText(fixture.getProperty(idManufacturer, "[not specified]"));
    txtFixtureName->setText(fixture.getProperty(idName, "[no name]"));
    txtProfileName->setText(fixture.getProperty(idProfile, "[not specified]"));
    txtDMX->setText(fixture.getProperty(idFootprint, 0));
    txtPName->setText("");
    txtPLetters->setText("");
    fillParamsBox();

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
    txtPName = nullptr;
    lblPLetters = nullptr;
    txtPLetters = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    lstParams = nullptr;
    //[/Destructor]
}

//==============================================================================
void FixtureEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

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
        if((bool)fixture.getProperty(idInUse, false)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic",
                "Cannot add parameters to fixtures which are in use.");
            return;
        }
        param = ValueTree(idParam);
        String t = cbxAddParam->getText();
        int typecount = 1;
        for(int i=0; i<fixture.getNumChildren(); ++i){
            if(fixture.getChild(i).getProperty(idType, "error").toString() == t) ++typecount;
        }
        String typecountstr = (typecount >= 2 ? String(typecount) : "");
        param.setProperty(idType, t, nullptr);
        param.setProperty(idName, t + typecountstr, nullptr);
        param.setProperty(idLetters, t.substring(0, 1) + typecountstr, nullptr);
        fixture.addChild(param, -1, nullptr);
        lstParams->add(getParamDesc(param));
        //[/UserButtonCode_btnAddParam]
    }
    else if (buttonThatWasClicked == btnRemoveParam.get())
    {
        //[UserButtonCode_btnRemoveParam] -- add your button handler code here..
        if(!param.isValid()) return;
        if((bool)fixture.getProperty(idInUse, false)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic",
                "Cannot remove parameters from fixtures which are in use.");
            return;
        }
        int i = fixture.indexOf(param);
        fixture.removeChild(param, nullptr);
        param = ValueTree();
        lstParams->remove(i);
        refreshParamControls();
        //[/UserButtonCode_btnRemoveParam]
    }
    else if (buttonThatWasClicked == btnParamUp.get())
    {
        //[UserButtonCode_btnParamUp] -- add your button handler code here..
        if(!param.isValid()) return;
        if((bool)fixture.getProperty(idInUse, false)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic",
                "Cannot reorder parameters in fixtures which are in use.");
            return;
        }
        int i = fixture.indexOf(param);
        if(i == 0) return;
        fixture.moveChild(i, i-1, nullptr);
        lstParams->set(i-1, getParamDesc(param));
        lstParams->set(i, getParamDesc(fixture.getChild(i)));
        lstParams->selectRow(fixture.indexOf(param));
        //[/UserButtonCode_btnParamUp]
    }
    else if (buttonThatWasClicked == btnParamDown.get())
    {
        //[UserButtonCode_btnParamDown] -- add your button handler code here..
        if(!param.isValid()) return;
        if((bool)fixture.getProperty(idInUse, false)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "BuskMagic",
                "Cannot reorder parameters from fixtures which are in use.");
            return;
        }
        int i = fixture.indexOf(param);
        if(i == fixture.getNumChildren() - 1) return;
        fixture.moveChild(i, i+1, nullptr);
        lstParams->set(i+1, getParamDesc(param));
        lstParams->set(i, getParamDesc(fixture.getChild(i)));
        lstParams->selectRow(fixture.indexOf(param));
        //[/UserButtonCode_btnParamDown]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void FixtureEditor::rowSelected(TextListBox *parent, int row)
{
    if(parent == lstParams.get()){
        param = fixture.getChild(row);
        refreshParamControls();
    }
}
void FixtureEditor::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtManufacturer.get()){
        fixture.setProperty(idManufacturer, text, nullptr);
    }else if(&editorThatWasChanged == txtFixtureName.get()){
        fixture.setProperty(idName, text, nullptr);
    }else if(&editorThatWasChanged == txtProfileName.get()){
        fixture.setProperty(idProfile, text, nullptr);
    }else if(&editorThatWasChanged == txtDMX.get()){
        if(!isint || val < 0){
            turnRed = true;
        }else{
            fixture.setProperty(idFootprint, val, nullptr);
        }
    }else if(&editorThatWasChanged == txtPName.get()){
        if(!param.isValid()) return;
        if(text.length() == 0) turnRed = true;
        param.setProperty(idName, text, nullptr);
        int i = fixture.indexOf(param);
        lstParams->set(i, getParamDesc(param));
    }else if(&editorThatWasChanged == txtPLetters.get()){
        if(!param.isValid()) return;
        if(text.length() == 0 || text.length() > 2) turnRed = true;
        param.setProperty(idLetters, text, nullptr);
        int i = fixture.indexOf(param);
        lstParams->set(i, getParamDesc(param));
    }
    TEXTCHANGEDHANDLER_POST;
}

void FixtureEditor::fillParamsBox()
{
    lstParams->clear();
    lstParams->setSelectAddedItems(false);
    for(int i=0; i<fixture.getNumChildren(); ++i){
        lstParams->add(getParamDesc(fixture.getChild(i)));
    }
    lstParams->setSelectAddedItems(true);
}

void FixtureEditor::refreshParamControls()
{
    txtPName->setText(param.isValid() ? param.getProperty(idName, "") : "");
    txtPName->setEnabled(param.isValid());
    txtPLetters->setText(param.isValid() ? param.getProperty(idLetters, "") : "");
    txtPLetters->setEnabled(param.isValid());
    String type = param.isValid() ? param.getProperty(idType, "") : "";
    if(type == "Generic"){
        parameditor.reset(new FixParamEd::Generic(param));
    }else if(type == "Color"){
        parameditor.reset(new FixParamEd::Color(param));
    }else{
        parameditor = nullptr;
    }
    if(parameditor != nullptr){
        addAndMakeVisible(parameditor.get());
        parameditor->setBounds(184, 144, 160, 264);
    }
}

String FixtureEditor::getParamDesc(ValueTree prm)
{
    String ret = prm.getProperty(idLetters, "XX");
    ret += ": " + prm.getProperty(idName, "(Error)").toString();
    ret += " (" + prm.getProperty(idType, "<Error>").toString() + ")";
    return ret;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FixtureEditor" componentName=""
                 parentClasses="public Component, public TextListBox::Listener, public TextEditor::Listener"
                 constructorParams="ValueTree fxt" variableInitialisers="fixture(fxt)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="344" initialHeight="408">
  <BACKGROUND backgroundColour="ff323e44"/>
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
         edBkgCol="0" labelText="DMX Footprint:" editableSingleClick="0"
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
         virtualName="" explicitFocusOrder="0" pos="0 384 39 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Add:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cbxAddParam" id="e40645e8dd385269" memberName="cbxAddParam"
            virtualName="" explicitFocusOrder="0" pos="40 384 120 24" editable="0"
            layout="33" items="Generic&#10;Color" textWhenNonSelected="Generic"
            textWhenNoItems="Error"/>
  <TEXTBUTTON name="btnAddParam" id="7ceb28d89a1747a0" memberName="btnAddParam"
              virtualName="" explicitFocusOrder="0" pos="160 384 24 24" buttonText="+"
              connectedEdges="5" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveParam" id="506bcac0d99da01e" memberName="btnRemoveParam"
              virtualName="" explicitFocusOrder="0" pos="112 96 24 24" buttonText="&#8722;"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnParamUp" id="c0e4ec84cb12c95b" memberName="btnParamUp"
              virtualName="" explicitFocusOrder="0" pos="136 96 24 24" buttonText="&#8593;"
              connectedEdges="11" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnParamDown" id="83e3f14852852c5b" memberName="btnParamDown"
              virtualName="" explicitFocusOrder="0" pos="160 96 24 24" buttonText="&#8595;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblPName" id="2c6c6437b4fb9d3f" memberName="lblPName" virtualName=""
         explicitFocusOrder="0" pos="184 96 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtPName" id="1f724a66d24c5ca3" memberName="txtPName" virtualName=""
              explicitFocusOrder="0" pos="240 96 104 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblPLetters" id="70d37e528f64ad4d" memberName="lblPLetters"
         virtualName="" explicitFocusOrder="0" pos="184 120 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Short name (1-2 ltrs):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtPLetters" id="3345abdfa53cef46" memberName="txtPLetters"
              virtualName="" explicitFocusOrder="0" pos="320 120 24 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
