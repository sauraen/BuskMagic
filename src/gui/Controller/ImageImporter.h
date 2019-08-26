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
#include "../../../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ImageImporter  : public Component
{
public:
    //==============================================================================
    ImageImporter ();
    ~ImageImporter();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;

    // Binary resources:
    static const char* modulator_cosine_png;
    static const int modulator_cosine_pngSize;
    static const char* modulator_triangle_png;
    static const int modulator_triangle_pngSize;
    static const char* modulator_noise_png;
    static const int modulator_noise_pngSize;
    static const char* modulator_pulse_png;
    static const int modulator_pulse_pngSize;
    static const char* modulator_sawf_png;
    static const int modulator_sawf_pngSize;
    static const char* modulator_sawr_png;
    static const int modulator_sawr_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Image cachedImage_modulator_cosine_png_1;
    Image cachedImage_modulator_triangle_png_2;
    Image cachedImage_modulator_noise_png_3;
    Image cachedImage_modulator_pulse_png_4;
    Image cachedImage_modulator_sawf_png_5;
    Image cachedImage_modulator_sawr_png_6;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageImporter)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

