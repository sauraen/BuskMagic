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

#include "FixtureSystem.h"
#include "LightingSystem.h"
//[/Headers]

#include "CMY.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

namespace FixParamEd { namespace ColorMode {
//[/MiscUserDefs]

//==============================================================================
CMY::CMY (ValueTree prm)
    : param(prm)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblM.reset (new Label ("lblM",
                           TRANS("M:")));
    addAndMakeVisible (lblM.get());
    lblM->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblM->setJustificationType (Justification::centredLeft);
    lblM->setEditable (false, false, false);
    lblM->setColour (TextEditor::textColourId, Colours::black);
    lblM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblM->setBounds (0, 144, 23, 24);

    txtDMXM.reset (new TextEditor ("txtDMXM"));
    addAndMakeVisible (txtDMXM.get());
    txtDMXM->setMultiLine (false);
    txtDMXM->setReturnKeyStartsNewLine (false);
    txtDMXM->setReadOnly (false);
    txtDMXM->setScrollbarsShown (true);
    txtDMXM->setCaretVisible (true);
    txtDMXM->setPopupMenuEnabled (true);
    txtDMXM->setText (String());

    txtDMXM->setBounds (24, 144, 72, 24);

    txtHueMY.reset (new TextEditor ("txtHueMY"));
    addAndMakeVisible (txtHueMY.get());
    txtHueMY->setMultiLine (false);
    txtHueMY->setReturnKeyStartsNewLine (false);
    txtHueMY->setReadOnly (false);
    txtHueMY->setScrollbarsShown (true);
    txtHueMY->setCaretVisible (true);
    txtHueMY->setPopupMenuEnabled (true);
    txtHueMY->setText (String());

    txtHueMY->setBounds (104, 24, 56, 24);

    lblMY.reset (new Label ("lblMY",
                            TRANS("M+Y (Red):")));
    addAndMakeVisible (lblMY.get());
    lblMY->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMY->setJustificationType (Justification::centredLeft);
    lblMY->setEditable (false, false, false);
    lblMY->setColour (TextEditor::textColourId, Colours::black);
    lblMY->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMY->setBounds (0, 24, 104, 24);

    txtHueY.reset (new TextEditor ("txtHueY"));
    addAndMakeVisible (txtHueY.get());
    txtHueY->setMultiLine (false);
    txtHueY->setReturnKeyStartsNewLine (false);
    txtHueY->setReadOnly (false);
    txtHueY->setScrollbarsShown (true);
    txtHueY->setCaretVisible (true);
    txtHueY->setPopupMenuEnabled (true);
    txtHueY->setText (String());

    txtHueY->setBounds (104, 48, 56, 24);

    lblY.reset (new Label ("lblY",
                           TRANS("Y:")));
    addAndMakeVisible (lblY.get());
    lblY->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblY->setJustificationType (Justification::centredLeft);
    lblY->setEditable (false, false, false);
    lblY->setColour (TextEditor::textColourId, Colours::black);
    lblY->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblY->setBounds (0, 48, 23, 24);

    txtDMXY.reset (new TextEditor ("txtDMXY"));
    addAndMakeVisible (txtDMXY.get());
    txtDMXY->setMultiLine (false);
    txtDMXY->setReturnKeyStartsNewLine (false);
    txtDMXY->setReadOnly (false);
    txtDMXY->setScrollbarsShown (true);
    txtDMXY->setCaretVisible (true);
    txtDMXY->setPopupMenuEnabled (true);
    txtDMXY->setText (String());

    txtDMXY->setBounds (24, 48, 72, 24);

    txtHueYC.reset (new TextEditor ("txtHueYC"));
    addAndMakeVisible (txtHueYC.get());
    txtHueYC->setMultiLine (false);
    txtHueYC->setReturnKeyStartsNewLine (false);
    txtHueYC->setReadOnly (false);
    txtHueYC->setScrollbarsShown (true);
    txtHueYC->setCaretVisible (true);
    txtHueYC->setPopupMenuEnabled (true);
    txtHueYC->setText (String());

    txtHueYC->setBounds (104, 72, 56, 24);

    lblYC.reset (new Label ("lblYC",
                            TRANS("Y+C (Green):")));
    addAndMakeVisible (lblYC.get());
    lblYC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblYC->setJustificationType (Justification::centredLeft);
    lblYC->setEditable (false, false, false);
    lblYC->setColour (TextEditor::textColourId, Colours::black);
    lblYC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblYC->setBounds (0, 72, 104, 24);

    txtHueC.reset (new TextEditor ("txtHueC"));
    addAndMakeVisible (txtHueC.get());
    txtHueC->setMultiLine (false);
    txtHueC->setReturnKeyStartsNewLine (false);
    txtHueC->setReadOnly (false);
    txtHueC->setScrollbarsShown (true);
    txtHueC->setCaretVisible (true);
    txtHueC->setPopupMenuEnabled (true);
    txtHueC->setText (String());

    txtHueC->setBounds (104, 96, 56, 24);

    lblC.reset (new Label ("lblC",
                           TRANS("C:")));
    addAndMakeVisible (lblC.get());
    lblC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblC->setJustificationType (Justification::centredLeft);
    lblC->setEditable (false, false, false);
    lblC->setColour (TextEditor::textColourId, Colours::black);
    lblC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblC->setBounds (0, 96, 23, 24);

    txtDMXC.reset (new TextEditor ("txtDMXC"));
    addAndMakeVisible (txtDMXC.get());
    txtDMXC->setMultiLine (false);
    txtDMXC->setReturnKeyStartsNewLine (false);
    txtDMXC->setReadOnly (false);
    txtDMXC->setScrollbarsShown (true);
    txtDMXC->setCaretVisible (true);
    txtDMXC->setPopupMenuEnabled (true);
    txtDMXC->setText (String());

    txtDMXC->setBounds (24, 96, 72, 24);

    txtHueCM.reset (new TextEditor ("txtHueCM"));
    addAndMakeVisible (txtHueCM.get());
    txtHueCM->setMultiLine (false);
    txtHueCM->setReturnKeyStartsNewLine (false);
    txtHueCM->setReadOnly (false);
    txtHueCM->setScrollbarsShown (true);
    txtHueCM->setCaretVisible (true);
    txtHueCM->setPopupMenuEnabled (true);
    txtHueCM->setText (String());

    txtHueCM->setBounds (104, 120, 56, 24);

    lblCM.reset (new Label ("lblCM",
                            TRANS("C+M (Blue):")));
    addAndMakeVisible (lblCM.get());
    lblCM->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblCM->setJustificationType (Justification::centredLeft);
    lblCM->setEditable (false, false, false);
    lblCM->setColour (TextEditor::textColourId, Colours::black);
    lblCM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblCM->setBounds (0, 120, 104, 24);

    txtHueM.reset (new TextEditor ("txtHueM"));
    addAndMakeVisible (txtHueM.get());
    txtHueM->setMultiLine (false);
    txtHueM->setReturnKeyStartsNewLine (false);
    txtHueM->setReadOnly (false);
    txtHueM->setScrollbarsShown (true);
    txtHueM->setCaretVisible (true);
    txtHueM->setPopupMenuEnabled (true);
    txtHueM->setText (String());

    txtHueM->setBounds (104, 144, 56, 24);

    lblDescription.reset (new Label ("lblDescription",
                                     TRANS("DMX             Hue")));
    addAndMakeVisible (lblDescription.get());
    lblDescription->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDescription->setJustificationType (Justification::centredLeft);
    lblDescription->setEditable (false, false, false);
    lblDescription->setColour (TextEditor::textColourId, Colours::black);
    lblDescription->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDescription->setBounds (24, 0, 128, 24);


    //[UserPreSize]

    txtDMXC->addListener(this);
    txtDMXM->addListener(this);
    txtDMXY->addListener(this);
    txtHueC->addListener(this);
    txtHueCM->addListener(this);
    txtHueM->addListener(this);
    txtHueMY->addListener(this);
    txtHueY->addListener(this);
    txtHueYC->addListener(this);

    setOpaque(true);

    //[/UserPreSize]

    setSize (160, 216);


    //[Constructor] You can add your own custom stuff here..

    txtDMXC->setText(FixtureSystem::GetDMXText(param.getOrCreateChildWithName(idCyan, nullptr)));
    txtDMXM->setText(FixtureSystem::GetDMXText(param.getOrCreateChildWithName(idMagenta, nullptr)));
    txtDMXY->setText(FixtureSystem::GetDMXText(param.getOrCreateChildWithName(idYellow, nullptr)));
    txtHueC->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idCyan, idHue, 0.625f)));
    txtHueCM->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idCyan, idHueMix, 0.75f)));
    txtHueM->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idMagenta, idHue, 0.875f)));
    txtHueMY->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idMagenta, idHueMix, 0.0f)));
    txtHueY->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idYellow, idHue, 0.25f)));
    txtHueYC->setText(LightingSystem::ValueToString((float)VT_GetChildProperty(param, idYellow, idHueMix, 0.5f)));

    //[/Constructor]
}

CMY::~CMY()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblM = nullptr;
    txtDMXM = nullptr;
    txtHueMY = nullptr;
    lblMY = nullptr;
    txtHueY = nullptr;
    lblY = nullptr;
    txtDMXY = nullptr;
    txtHueYC = nullptr;
    lblYC = nullptr;
    txtHueC = nullptr;
    lblC = nullptr;
    txtDMXC = nullptr;
    txtHueCM = nullptr;
    lblCM = nullptr;
    txtHueM = nullptr;
    lblDescription = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CMY::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CMY::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void CMY::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    DMXTEXTCHANGEDHANDLER;
    if(&editorThatWasChanged == txtDMXC.get()){
        if(!dmx_ok) turnRed = true; else FixtureSystem::SetDMXChannels(
            param.getOrCreateChildWithName(idCyan, nullptr),
            dmx_normal, dmx_fine, dmx_ultra);
    }else if(&editorThatWasChanged == txtDMXM.get()){
        if(!dmx_ok) turnRed = true; else FixtureSystem::SetDMXChannels(
            param.getOrCreateChildWithName(idMagenta, nullptr),
            dmx_normal, dmx_fine, dmx_ultra);
    }else if(&editorThatWasChanged == txtDMXY.get()){
        if(!dmx_ok) turnRed = true; else FixtureSystem::SetDMXChannels(
            param.getOrCreateChildWithName(idYellow, nullptr),
            dmx_normal, dmx_fine, dmx_ultra);
    }else if(&editorThatWasChanged == txtHueC.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idCyan, idHue, viewvalue);
    }else if(&editorThatWasChanged == txtHueCM.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idCyan, idHueMix, viewvalue);
    }else if(&editorThatWasChanged == txtHueM.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idMagenta, idHue, viewvalue);
    }else if(&editorThatWasChanged == txtHueMY.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idMagenta, idHueMix, viewvalue);
    }else if(&editorThatWasChanged == txtHueY.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idYellow, idHue, viewvalue);
    }else if(&editorThatWasChanged == txtHueYC.get()){
        if(!isviewvalue || viewvalue < 0.0f || viewvalue >= 1.0f) turnRed = true;
        else VT_SetChildProperty(param, idYellow, idHueMix, viewvalue);
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

<JUCER_COMPONENT documentType="Component" className="CMY" componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="ValueTree prm" variableInitialisers="param(prm)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="160" initialHeight="216">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblM" id="38f1aaac5d95b0ca" memberName="lblM" virtualName=""
         explicitFocusOrder="0" pos="0 144 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="M:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXM" id="9f7ee9c7e89d53ab" memberName="txtDMXM" virtualName=""
              explicitFocusOrder="0" pos="24 144 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueMY" id="ea26a466b5e37632" memberName="txtHueMY" virtualName=""
              explicitFocusOrder="0" pos="104 24 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblMY" id="d5801027ede5aabd" memberName="lblMY" virtualName=""
         explicitFocusOrder="0" pos="0 24 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="M+Y (Red):" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueY" id="69717f9b2bef903" memberName="txtHueY" virtualName=""
              explicitFocusOrder="0" pos="104 48 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblY" id="181bac7d94b8484e" memberName="lblY" virtualName=""
         explicitFocusOrder="0" pos="0 48 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Y:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXY" id="a300f505f364945e" memberName="txtDMXY" virtualName=""
              explicitFocusOrder="0" pos="24 48 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueYC" id="e303282fc8afe509" memberName="txtHueYC" virtualName=""
              explicitFocusOrder="0" pos="104 72 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblYC" id="4fe7d4a4da0dd757" memberName="lblYC" virtualName=""
         explicitFocusOrder="0" pos="0 72 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Y+C (Green):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueC" id="c241147e133d676e" memberName="txtHueC" virtualName=""
              explicitFocusOrder="0" pos="104 96 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblC" id="d32fe5ac40f01595" memberName="lblC" virtualName=""
         explicitFocusOrder="0" pos="0 96 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="C:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXC" id="249d88025ae5b5a2" memberName="txtDMXC" virtualName=""
              explicitFocusOrder="0" pos="24 96 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtHueCM" id="135f6bd2f86e9a29" memberName="txtHueCM" virtualName=""
              explicitFocusOrder="0" pos="104 120 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblCM" id="a838fb38874abaf9" memberName="lblCM" virtualName=""
         explicitFocusOrder="0" pos="0 120 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="C+M (Blue):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtHueM" id="3fead027864ef25f" memberName="txtHueM" virtualName=""
              explicitFocusOrder="0" pos="104 144 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="lblDescription" id="805bbb1ad803a595" memberName="lblDescription"
         virtualName="" explicitFocusOrder="0" pos="24 0 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="DMX             Hue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
}}

//[/EndFile]
