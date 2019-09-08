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

#include "gui/Controller/ControllerCanvas.h"
#include "gui/Popup/PopupWindow.h"
//[/Headers]

#include "CtrlrEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrEditor::CtrlrEditor (void *data)
    : controller((Controller*)data)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    txtName.reset (new TextEditor ("txtName"));
    addAndMakeVisible (txtName.get());
    txtName->setMultiLine (false);
    txtName->setReturnKeyStartsNewLine (false);
    txtName->setReadOnly (false);
    txtName->setScrollbarsShown (true);
    txtName->setCaretVisible (true);
    txtName->setPopupMenuEnabled (true);
    txtName->setText (TRANS("NameNameName"));

    txtName->setBounds (0, 0, 120, 24);

    btnMainColor.reset (new TextButton ("btnMainColor"));
    addAndMakeVisible (btnMainColor.get());
    btnMainColor->setButtonText (String());
    btnMainColor->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnMainColor->addListener (this);
    btnMainColor->setColour (TextButton::buttonColourId, Colours::red);

    btnMainColor->setBounds (120, 0, 24, 24);

    lblGroup.reset (new Label ("lblGroup",
                               TRANS("Group:")));
    addAndMakeVisible (lblGroup.get());
    lblGroup->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblGroup->setJustificationType (Justification::centredLeft);
    lblGroup->setEditable (false, false, false);
    lblGroup->setColour (TextEditor::textColourId, Colours::black);
    lblGroup->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblGroup->setBounds (0, 24, 56, 24);

    txtGroup.reset (new TextEditor ("txtGroup"));
    addAndMakeVisible (txtGroup.get());
    txtGroup->setMultiLine (false);
    txtGroup->setReturnKeyStartsNewLine (false);
    txtGroup->setReadOnly (false);
    txtGroup->setScrollbarsShown (true);
    txtGroup->setCaretVisible (true);
    txtGroup->setPopupMenuEnabled (true);
    txtGroup->setText (String());

    txtGroup->setBounds (56, 24, 32, 24);

    btnGroupColor.reset (new TextButton ("btnGroupColor"));
    addAndMakeVisible (btnGroupColor.get());
    btnGroupColor->setButtonText (String());
    btnGroupColor->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnGroupColor->addListener (this);
    btnGroupColor->setColour (TextButton::buttonColourId, Colour (0xffffee9e));

    btnGroupColor->setBounds (88, 24, 24, 24);

    chkNoState.reset (new ToggleButton ("chkNoState"));
    addAndMakeVisible (chkNoState.get());
    chkNoState->setButtonText (TRANS("Immune to State"));
    chkNoState->addListener (this);

    chkNoState->setBounds (0, 48, 150, 24);

    btnDuplicate.reset (new TextButton ("btnDuplicate"));
    addAndMakeVisible (btnDuplicate.get());
    btnDuplicate->setButtonText (TRANS("Duplicate"));
    btnDuplicate->setConnectedEdges (Button::ConnectedOnRight);
    btnDuplicate->addListener (this);

    btnDuplicate->setBounds (0, 72, 72, 24);

    btnDelete.reset (new TextButton ("btnDelete"));
    addAndMakeVisible (btnDelete.get());
    btnDelete->setButtonText (TRANS("Delete"));
    btnDelete->setConnectedEdges (Button::ConnectedOnLeft);
    btnDelete->addListener (this);

    btnDelete->setBounds (72, 72, 72, 24);


    //[UserPreSize]

    ConfigureTextEditor(txtName, this, controller->GetName());
    ConfigureTextEditor(txtGroup, this, controller->GetGroup() <= 0 ? "" : String(controller->GetGroup()));
    
    chkNoState->setToggleState(controller->nostate, dontSendNotification);
    btnMainColor->setColour(TextButton::buttonColourId, controller->GetColor());
    btnGroupColor->setColour(TextButton::buttonColourId, controller->GetGroupColor());

    setOpaque(true);

    //[/UserPreSize]

    setSize (144, 96);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrEditor::~CtrlrEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    txtName = nullptr;
    btnMainColor = nullptr;
    lblGroup = nullptr;
    txtGroup = nullptr;
    btnGroupColor = nullptr;
    chkNoState = nullptr;
    btnDuplicate = nullptr;
    btnDelete = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnMainColor.get())
    {
        //[UserButtonCode_btnMainColor] -- add your button handler code here..
        controller->SetColor(ShowColorChooserWindow(controller->GetColor(), btnMainColor.get()));
        //[/UserButtonCode_btnMainColor]
    }
    else if (buttonThatWasClicked == btnGroupColor.get())
    {
        //[UserButtonCode_btnGroupColor] -- add your button handler code here..
        controller->SetGroupColor(ShowColorChooserWindow(controller->GetGroupColor(), btnGroupColor.get()));
        //[/UserButtonCode_btnGroupColor]
    }
    else if (buttonThatWasClicked == chkNoState.get())
    {
        //[UserButtonCode_chkNoState] -- add your button handler code here..
        controller->nostate = chkNoState->getToggleState();
        //[/UserButtonCode_chkNoState]
    }
    else if (buttonThatWasClicked == btnDuplicate.get())
    {
        //[UserButtonCode_btnDuplicate] -- add your button handler code here..
        ControllerCanvas *canvas = controller->GetCanvas();
        if(canvas == nullptr) return;
        canvas->addComp(ControllerSystem::DuplicateController(controller));
        canvas->grabKeyboardFocus(); //This will take focus away from the popup, which will lead to it closing
        //[/UserButtonCode_btnDuplicate]
    }
    else if (buttonThatWasClicked == btnDelete.get())
    {
        //[UserButtonCode_btnDelete] -- add your button handler code here..
        ControllerCanvas *canvas = controller->GetCanvas();
        if(canvas == nullptr) return;
        canvas->deleteComp(controller);
        canvas->grabKeyboardFocus(); //This will take focus away from the popup, which will lead to it closing
        //[/UserButtonCode_btnDelete]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void CtrlrEditor::textEditorTextChanged(TextEditor &editorThatWasChanged)
{
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtName.get()){
        controller->SetName(text);
    }else if(&editorThatWasChanged == txtGroup.get()){
        if(text == ""){
            controller->SetGroup(0);
        }else if(isint && val >= 1){
            controller->SetGroup(val);
        }else{
            turnRed = true;
        }
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

<JUCER_COMPONENT documentType="Component" className="CtrlrEditor" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="void *data" variableInitialisers="controller((Controller*)data)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="144" initialHeight="96">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTEDITOR name="txtName" id="8a5bd4b32539dcce" memberName="txtName" virtualName=""
              explicitFocusOrder="0" pos="0 0 120 24" initialText="NameNameName"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnMainColor" id="a4224dab004c89fb" memberName="btnMainColor"
              virtualName="" explicitFocusOrder="0" pos="120 0 24 24" bgColOff="ffff0000"
              buttonText="" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblGroup" id="cc8f156c46c39a92" memberName="lblGroup" virtualName=""
         explicitFocusOrder="0" pos="0 24 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Group:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtGroup" id="a2b4b0d2ab96463d" memberName="txtGroup" virtualName=""
              explicitFocusOrder="0" pos="56 24 32 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnGroupColor" id="23f334cb99e0b40d" memberName="btnGroupColor"
              virtualName="" explicitFocusOrder="0" pos="88 24 24 24" bgColOff="ffffee9e"
              buttonText="" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="chkNoState" id="1060fc4bda4aa0be" memberName="chkNoState"
                virtualName="" explicitFocusOrder="0" pos="0 48 150 24" buttonText="Immune to State"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="btnDuplicate" id="605899fa6a170dd7" memberName="btnDuplicate"
              virtualName="" explicitFocusOrder="0" pos="0 72 72 24" buttonText="Duplicate"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnDelete" id="b80024947b061f58" memberName="btnDelete"
              virtualName="" explicitFocusOrder="0" pos="72 72 72 24" buttonText="Delete"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
