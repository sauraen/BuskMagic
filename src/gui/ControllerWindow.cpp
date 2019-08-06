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

#include "ControllerWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ControllerWindow::ControllerWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    vptControllers.reset (new Viewport ("vptControllers"));
    addAndMakeVisible (vptControllers.get());

    vptControllers->setBounds (0, 24, 800, 576);

    lblControllers.reset (new Label ("lblControllers",
                                     TRANS("Controllers:")));
    addAndMakeVisible (lblControllers.get());
    lblControllers->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblControllers->setJustificationType (Justification::centredLeft);
    lblControllers->setEditable (false, false, false);
    lblControllers->setColour (TextEditor::textColourId, Colours::black);
    lblControllers->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblControllers->setBounds (0, 0, 80, 24);

    btnNewSimple.reset (new TextButton ("btnNewSimple"));
    addAndMakeVisible (btnNewSimple.get());
    btnNewSimple->setButtonText (TRANS("New Simple"));
    btnNewSimple->setConnectedEdges (Button::ConnectedOnRight);
    btnNewSimple->addListener (this);

    btnNewSimple->setBounds (80, 0, 88, 24);

    btnNewContinuous.reset (new TextButton ("btnNewContinuous"));
    addAndMakeVisible (btnNewContinuous.get());
    btnNewContinuous->setButtonText (TRANS("New Continuous"));
    btnNewContinuous->setConnectedEdges (Button::ConnectedOnLeft);
    btnNewContinuous->addListener (this);

    btnNewContinuous->setBounds (168, 0, 120, 24);

    lblInstructions.reset (new Label ("lblInstructions",
                                      TRANS("Right-click to edit name, properties, MIDI mapping, magic values...")));
    addAndMakeVisible (lblInstructions.get());
    lblInstructions->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblInstructions->setJustificationType (Justification::centredLeft);
    lblInstructions->setEditable (false, false, false);
    lblInstructions->setColour (TextEditor::textColourId, Colours::black);
    lblInstructions->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblInstructions->setBounds (288, 0, 512, 24);


    //[UserPreSize]

    canvas.reset(new ControllerCanvas());
    vptControllers->setViewedComponent(canvas.get());

    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ControllerWindow::~ControllerWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    canvas = nullptr;

    //[/Destructor_pre]

    vptControllers = nullptr;
    lblControllers = nullptr;
    btnNewSimple = nullptr;
    btnNewContinuous = nullptr;
    lblInstructions = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControllerWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControllerWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ControllerWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnNewSimple.get())
    {
        //[UserButtonCode_btnNewSimple] -- add your button handler code here..
        //[/UserButtonCode_btnNewSimple]
    }
    else if (buttonThatWasClicked == btnNewContinuous.get())
    {
        //[UserButtonCode_btnNewContinuous] -- add your button handler code here..
        //[/UserButtonCode_btnNewContinuous]
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

<JUCER_COMPONENT documentType="Component" className="ControllerWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="800" initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44"/>
  <VIEWPORT name="vptControllers" id="7b12c3fe2e485508" memberName="vptControllers"
            virtualName="" explicitFocusOrder="0" pos="0 24 800 576" vscroll="1"
            hscroll="1" scrollbarThickness="8" contentType="0" jucerFile=""
            contentClass="" constructorParams=""/>
  <LABEL name="lblControllers" id="b56006e77548471b" memberName="lblControllers"
         virtualName="" explicitFocusOrder="0" pos="0 0 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Controllers:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnNewSimple" id="405e0cfed0c3c8dc" memberName="btnNewSimple"
              virtualName="" explicitFocusOrder="0" pos="80 0 88 24" buttonText="New Simple"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnNewContinuous" id="868866992ff3ca38" memberName="btnNewContinuous"
              virtualName="" explicitFocusOrder="0" pos="168 0 120 24" buttonText="New Continuous"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblInstructions" id="d0b9b888b227b508" memberName="lblInstructions"
         virtualName="" explicitFocusOrder="0" pos="288 0 512 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Right-click to edit name, properties, MIDI mapping, magic values..."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

