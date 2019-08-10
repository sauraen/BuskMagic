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

#include "MagicValueEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MagicValueEditor::MagicValueEditor (void *data)
    : magic((MagicValue*)data)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    txtLiteral.reset (new TextEditor ("txtLiteral"));
    addAndMakeVisible (txtLiteral.get());
    txtLiteral->setMultiLine (false);
    txtLiteral->setReturnKeyStartsNewLine (false);
    txtLiteral->setReadOnly (false);
    txtLiteral->setScrollbarsShown (true);
    txtLiteral->setCaretVisible (true);
    txtLiteral->setPopupMenuEnabled (true);
    txtLiteral->setText (TRANS("0.5"));

    txtLiteral->setBounds (0, 0, 48, 24);

    cbxChannel.reset (new ComboBox ("cbxChannel"));
    addAndMakeVisible (cbxChannel.get());
    cbxChannel->setEditableText (false);
    cbxChannel->setJustificationType (Justification::centredLeft);
    cbxChannel->setTextWhenNothingSelected (String());
    cbxChannel->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxChannel->addItem (TRANS("^ Non-magic"), 1);
    cbxChannel->addListener (this);

    cbxChannel->setBounds (0, 24, 120, 24);


    //[UserPreSize]

    txtLiteral->setEscapeAndReturnKeysConsumed(false);
    txtLiteral->addListener(this);

    //TODO
    cbxChannel->setText("^ Non-magic");
    txtLiteral->setText(String(magic->GetLiteral(), 2));

    //[/UserPreSize]

    setSize (120, 48);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MagicValueEditor::~MagicValueEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    txtLiteral = nullptr;
    cbxChannel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MagicValueEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MagicValueEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MagicValueEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxChannel.get())
    {
        //[UserComboBoxCode_cbxChannel] -- add your combo box handling code here..
        if(cbxChannel->getText() == "^ Non-magic"){
            txtLiteral->setEnabled(true);
            magic->SetChannel(nullptr);
        }else{
            txtLiteral->setEnabled(false);
            //TODO
        }
        //[/UserComboBoxCode_cbxChannel]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MagicValueEditor::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtLiteral.get()){
        if(!isdec) turnRed = true;
        else magic->SetLiteral(decval);
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

<JUCER_COMPONENT documentType="Component" className="MagicValueEditor" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="void *data" variableInitialisers="magic((MagicValue*)data)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="120" initialHeight="48">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTEDITOR name="txtLiteral" id="f13649dee98ad067" memberName="txtLiteral"
              virtualName="" explicitFocusOrder="0" pos="0 0 48 24" initialText="0.5"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="cbxChannel" id="efc1c9a9e33c3875" memberName="cbxChannel"
            virtualName="" explicitFocusOrder="0" pos="0 24 120 24" editable="0"
            layout="33" items="&#94; Non-magic" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

