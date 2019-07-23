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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../../../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CMY  : public Component,
             public TextEditor::Listener
{
public:
    //==============================================================================
    CMY ();
    ~CMY();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblM;
    std::unique_ptr<TextEditor> txtDMXM;
    std::unique_ptr<TextEditor> txtHueMY;
    std::unique_ptr<Label> lblMY;
    std::unique_ptr<TextEditor> txtHueY;
    std::unique_ptr<Label> lblY;
    std::unique_ptr<TextEditor> txtDMXY;
    std::unique_ptr<TextEditor> txtHueYC;
    std::unique_ptr<Label> lblYC;
    std::unique_ptr<TextEditor> txtHueC;
    std::unique_ptr<Label> lblC;
    std::unique_ptr<TextEditor> txtDMXC;
    std::unique_ptr<TextEditor> txtHueCM;
    std::unique_ptr<Label> lblCM;
    std::unique_ptr<TextEditor> txtHueM;
    std::unique_ptr<Label> lblDescription;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CMY)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

