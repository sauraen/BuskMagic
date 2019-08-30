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
#include "../../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TimingWindow  : public Component
{
public:
    //==============================================================================
    TimingWindow ();
    ~TimingWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblTapBeat;
    std::unique_ptr<Label> lblTapMeasure;
    std::unique_ptr<Label> lblTapDouble;
    std::unique_ptr<Label> lblTapHalf;
    std::unique_ptr<Label> lblTempo;
    std::unique_ptr<TextEditor> textEditor;
    std::unique_ptr<Label> lblMeasure;
    std::unique_ptr<Label> lblBPM;
    std::unique_ptr<TextEditor> textEditor2;
    std::unique_ptr<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimingWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

