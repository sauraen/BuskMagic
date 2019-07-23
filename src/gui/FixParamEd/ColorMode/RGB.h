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
class RGB  : public Component,
             public TextEditor::Listener
{
public:
    //==============================================================================
    RGB ();
    ~RGB();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblR;
    std::unique_ptr<TextEditor> txtDMXR;
    std::unique_ptr<TextEditor> txtHueR;
    std::unique_ptr<Label> lblRG;
    std::unique_ptr<TextEditor> txtHueRG;
    std::unique_ptr<Label> lblG;
    std::unique_ptr<TextEditor> txtDMXG;
    std::unique_ptr<TextEditor> txtHueG;
    std::unique_ptr<Label> lblGB;
    std::unique_ptr<TextEditor> txtHueGB;
    std::unique_ptr<Label> lblB;
    std::unique_ptr<TextEditor> txtDMXB;
    std::unique_ptr<TextEditor> txtHueB;
    std::unique_ptr<Label> lblBR;
    std::unique_ptr<TextEditor> txtHueBR;
    std::unique_ptr<Label> lblDescription;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RGB)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

