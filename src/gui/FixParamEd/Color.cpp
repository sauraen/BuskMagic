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

#include "Color.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Color::Color ()
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


    //[UserPreSize]
    //[/UserPreSize]

    setSize (160, 240);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Color::~Color()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblMode = nullptr;
    cbxMode = nullptr;


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
        //[/UserComboBoxCode_cbxMode]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Color" componentName="" parentClasses="public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="160"
                 initialHeight="240">
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

