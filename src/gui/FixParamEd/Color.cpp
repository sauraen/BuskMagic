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
#include "gui/FixParamEd/ColorMode/CMY.h"
#include "gui/FixParamEd/ColorMode/RGB.h"
#include "gui/FixParamEd/ColorMode/RGBA.h"
//[/Headers]

#include "Color.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

namespace FixParamEd {
//[/MiscUserDefs]

//==============================================================================
Color::Color (ValueTree prm)
    : param(prm)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblMode.reset (new Label ("lblMode",
                              TRANS("Mode:")));
    addAndMakeVisible (lblMode.get());
    lblMode->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMode->setJustificationType (Justification::centredLeft);
    lblMode->setEditable (false, false, false);
    lblMode->setColour (TextEditor::textColourId, Colours::black);
    lblMode->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMode->setBounds (0, 0, 55, 24);

    cbxMode.reset (new ComboBox ("cbxMode"));
    addAndMakeVisible (cbxMode.get());
    cbxMode->setEditableText (false);
    cbxMode->setJustificationType (Justification::centredLeft);
    cbxMode->setTextWhenNothingSelected (String());
    cbxMode->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMode->addItem (TRANS("RGB"), 1);
    cbxMode->addItem (TRANS("RGBW"), 2);
    cbxMode->addItem (TRANS("RGBA"), 3);
    cbxMode->addItem (TRANS("RGBAW"), 4);
    cbxMode->addItem (TRANS("CMY"), 5);
    cbxMode->addListener (this);

    cbxMode->setBounds (56, 0, 104, 24);

    lblW.reset (new Label ("lblW",
                           TRANS("W:")));
    addAndMakeVisible (lblW.get());
    lblW->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblW->setJustificationType (Justification::centredLeft);
    lblW->setEditable (false, false, false);
    lblW->setColour (TextEditor::textColourId, Colours::black);
    lblW->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblW->setBounds (0, 240, 24, 24);

    txtDMXW.reset (new TextEditor ("txtDMXW"));
    addAndMakeVisible (txtDMXW.get());
    txtDMXW->setMultiLine (false);
    txtDMXW->setReturnKeyStartsNewLine (false);
    txtDMXW->setReadOnly (false);
    txtDMXW->setScrollbarsShown (true);
    txtDMXW->setCaretVisible (true);
    txtDMXW->setPopupMenuEnabled (true);
    txtDMXW->setText (String());

    txtDMXW->setBounds (24, 240, 72, 24);


    //[UserPreSize]
    txtDMXW->addListener(this);
    
    setOpaque(true);
    
    //[/UserPreSize]

    setSize (160, 264);


    //[Constructor] You can add your own custom stuff here..

    cbxMode->setText(param.getProperty(idColorMode, "RGB").toString());
    fillModeControls();

    //[/Constructor]
}

Color::~Color()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblMode = nullptr;
    cbxMode = nullptr;
    lblW = nullptr;
    txtDMXW = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Color::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 24, width = 160, height = 216;
        Colour fillColour = Colour (0xff2e2aa5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Color::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Color::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxMode.get())
    {
        //[UserComboBoxCode_cbxMode] -- add your combo box handling code here..
        String colormode = cbxMode->getText();
        param.setProperty(idColorMode, colormode, nullptr);
        if(colormode == "CMY"){
            VT_RemoveChildWithName(param, idRed);
            VT_RemoveChildWithName(param, idGreen);
            VT_RemoveChildWithName(param, idBlue);
            VT_RemoveChildWithName(param, idAmber);
            VT_RemoveChildWithName(param, idWhite);
        }else{
            VT_RemoveChildWithName(param, idCyan);
            VT_RemoveChildWithName(param, idMagenta);
            VT_RemoveChildWithName(param, idYellow);
            if(colormode == "RGB" || colormode == "RGBW"){
                VT_RemoveChildWithName(param, idAmber);
            }else{
                //Red huemix changes between amber and non-amber, so re-init it
                VT_RemoveChildWithName(param, idRed);
            }
            if(colormode == "RGB" || colormode == "RGBA"){
                VT_RemoveChildWithName(param, idWhite);
            }
        }
        fillModeControls();
        //[/UserComboBoxCode_cbxMode]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Color::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    DMXTEXTCHANGEDHANDLER;
    if(&editorThatWasChanged == txtDMXW.get()){
        if(!dmx_ok) turnRed = true; else FixtureSystem::SetDMXChannels(
            param.getOrCreateChildWithName(idWhite, nullptr),
            dmx_normal, dmx_fine, dmx_ultra);
    }
    TEXTCHANGEDHANDLER_POST;
}

void Color::fillModeControls()
{
    String mode = param.getProperty(idColorMode, "RGB").toString();
    bool white = (mode == "RGBW" || mode == "RGBAW");
    lblW->setVisible(white);
    txtDMXW->setVisible(white);
    if(white){
        txtDMXW->setText(FixtureSystem::GetDMXText(param.getOrCreateChildWithName(idWhite, nullptr)));
    }
    if(mode == "RGB" || mode == "RGBW"){
        coloreditor.reset(new FixParamEd::ColorMode::RGB(param));
    }else if(mode == "RGBA" || mode == "RGBAW"){
        coloreditor.reset(new FixParamEd::ColorMode::RGBA(param));
    }else if(mode == "CMY"){
        coloreditor.reset(new FixParamEd::ColorMode::CMY(param));
    }else{
        coloreditor = nullptr;
    }
    if(coloreditor != nullptr){
        addAndMakeVisible(coloreditor.get());
        coloreditor->setBounds(0, 24, 160, 216);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Color" componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="ValueTree prm" variableInitialisers="param(prm)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="160" initialHeight="264">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 24 160 216" fill="solid: ff2e2aa5" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="lblMode" id="c3363828fa04e577" memberName="lblMode" virtualName=""
         explicitFocusOrder="0" pos="0 0 55 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Mode:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cbxMode" id="e44a530ad0c42c83" memberName="cbxMode" virtualName=""
            explicitFocusOrder="0" pos="56 0 104 24" editable="0" layout="33"
            items="RGB&#10;RGBW&#10;RGBA&#10;RGBAW&#10;CMY" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="lblW" id="25cff9e153e75d21" memberName="lblW" virtualName=""
         explicitFocusOrder="0" pos="0 240 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="W:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtDMXW" id="9f7ee9c7e89d53ab" memberName="txtDMXW" virtualName=""
              explicitFocusOrder="0" pos="24 240 72 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
}

//[/EndFile]
