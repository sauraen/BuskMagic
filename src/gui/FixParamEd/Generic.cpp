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

#include "Generic.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Generic::Generic ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblValue.reset (new Label ("lblValue",
                               TRANS("Value:")));
    addAndMakeVisible (lblValue.get());
    lblValue->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblValue->setJustificationType (Justification::centredLeft);
    lblValue->setEditable (false, false, false);
    lblValue->setColour (TextEditor::textColourId, Colours::black);
    lblValue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblValue->setBounds (0, 0, 64, 24);

    textEditor.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (textEditor.get());
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String());

    textEditor->setBounds (64, 0, 72, 24);

    lblHelp.reset (new Label ("lblHelp",
                              TRANS("(Enter DMX channel number, 1-indexed. All parameter boxes also accept XX,YY or XX,YY,ZZ for normal,fine,ultra.)")));
    addAndMakeVisible (lblHelp.get());
    lblHelp->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblHelp->setJustificationType (Justification::centredLeft);
    lblHelp->setEditable (false, false, false);
    lblHelp->setColour (Label::textColourId, Colour (0xffcdcdcd));
    lblHelp->setColour (TextEditor::textColourId, Colours::black);
    lblHelp->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblHelp->setBounds (0, 32, 150, 104);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (160, 240);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Generic::~Generic()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblValue = nullptr;
    textEditor = nullptr;
    lblHelp = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Generic::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Generic::resized()
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

<JUCER_COMPONENT documentType="Component" className="Generic" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="160"
                 initialHeight="240">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="lblValue" id="fb7fb6fce39bf2d2" memberName="lblValue" virtualName=""
         explicitFocusOrder="0" pos="0 0 64 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Value:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7193b68ebf01b042" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="64 0 72 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblHelp" id="cc2c30a1dc5fb8ad" memberName="lblHelp" virtualName=""
         explicitFocusOrder="0" pos="0 32 150 104" textCol="ffcdcdcd"
         edTextCol="ff000000" edBkgCol="0" labelText="(Enter DMX channel number, 1-indexed. All parameter boxes also accept XX,YY or XX,YY,ZZ for normal,fine,ultra.)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

