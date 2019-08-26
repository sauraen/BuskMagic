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

#include "ImageImporter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ImageImporter::ImageImporter ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    cachedImage_modulator_cosine_png_1 = ImageCache::getFromMemory (modulator_cosine_png, modulator_cosine_pngSize);
    cachedImage_modulator_triangle_png_2 = ImageCache::getFromMemory (modulator_triangle_png, modulator_triangle_pngSize);
    cachedImage_modulator_noise_png_3 = ImageCache::getFromMemory (modulator_noise_png, modulator_noise_pngSize);
    cachedImage_modulator_pulse_png_4 = ImageCache::getFromMemory (modulator_pulse_png, modulator_pulse_pngSize);
    cachedImage_modulator_sawf_png_5 = ImageCache::getFromMemory (modulator_sawf_png, modulator_sawf_pngSize);
    cachedImage_modulator_sawr_png_6 = ImageCache::getFromMemory (modulator_sawr_png, modulator_sawr_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ImageImporter::~ImageImporter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ImageImporter::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 60, y = 52, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_cosine_png_1,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    {
        int x = 60, y = 76, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_triangle_png_2,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    {
        int x = 60, y = 100, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_noise_png_3,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    {
        int x = 100, y = 52, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_pulse_png_4,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    {
        int x = 100, y = 76, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_sawf_png_5,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    {
        int x = 100, y = 100, width = 36, height = 24;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_modulator_sawr_png_6,
                           x, y, width, height,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ImageImporter::resized()
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

<JUCER_COMPONENT documentType="Component" className="ImageImporter" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <IMAGE pos="60 52 36 24" resource="modulator_cosine_png" opacity="1.0"
           mode="2"/>
    <IMAGE pos="60 76 36 24" resource="modulator_triangle_png" opacity="1.0"
           mode="2"/>
    <IMAGE pos="60 100 36 24" resource="modulator_noise_png" opacity="1.0"
           mode="2"/>
    <IMAGE pos="100 52 36 24" resource="modulator_pulse_png" opacity="1.0"
           mode="2"/>
    <IMAGE pos="100 76 36 24" resource="modulator_sawf_png" opacity="1.0"
           mode="2"/>
    <IMAGE pos="100 100 36 24" resource="modulator_sawr_png" opacity="1.0"
           mode="2"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: modulator_cosine_png, 215, "../../../data/modulator_cosine.png"
static const unsigned char resource_ImageImporter_modulator_cosine_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,
11,252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,103,73,68,65,84,72,199,237,84,49,18,0,32,8,242,250,255,159,105,105,204,65,82,
179,51,214,46,80,84,68,174,0,0,152,183,146,216,22,108,238,226,185,182,13,101,167,244,70,139,96,65,154,131,245,64,253,231,106,106,218,132,52,161,81,115,123,83,188,250,39,210,48,11,34,7,126,196,239,89,152,
27,151,7,81,200,221,150,11,92,134,56,60,124,44,2,169,73,168,93,202,143,228,118,152,28,218,147,111,74,232,225,155,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_cosine_png = (const char*) resource_ImageImporter_modulator_cosine_png;
const int ImageImporter::modulator_cosine_pngSize = 215;

// JUCER_RESOURCE: modulator_triangle_png, 191, "../../../data/modulator_triangle.png"
static const unsigned char resource_ImageImporter_modulator_triangle_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,
11,252,97,5,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,79,73,68,65,84,72,199,99,96,160,33,248,255,255,255,127,236,28,162,117,
145,36,57,10,6,6,80,28,41,195,192,128,209,104,28,53,108,212,176,81,48,90,14,208,206,46,90,58,140,34,179,169,233,176,65,147,111,105,154,12,72,49,156,174,133,15,62,203,6,180,20,68,182,124,180,56,30,145,
0,0,41,1,119,137,249,117,237,188,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_triangle_png = (const char*) resource_ImageImporter_modulator_triangle_png;
const int ImageImporter::modulator_triangle_pngSize = 191;

// JUCER_RESOURCE: modulator_noise_png, 257, "../../../data/modulator_noise.png"
static const unsigned char resource_ImageImporter_modulator_noise_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,145,73,68,65,84,72,199,237,84,65,14,192,32,8,83,194,255,191,220,93,182,100,91,20,
69,96,110,139,61,25,83,42,85,105,74,65,0,128,235,66,100,189,8,221,61,29,196,174,130,51,137,210,183,80,50,136,29,46,162,234,27,12,255,79,102,123,63,128,219,29,212,68,164,3,72,219,93,206,57,151,120,220,
18,170,21,250,134,69,201,154,182,248,206,167,210,166,201,206,26,145,5,223,212,30,0,121,252,74,41,115,180,6,120,180,153,218,44,2,128,101,78,57,250,105,93,26,178,36,83,15,87,210,231,150,112,84,122,61,22,
191,51,39,116,97,10,54,208,213,175,151,222,180,131,67,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_noise_png = (const char*) resource_ImageImporter_modulator_noise_png;
const int ImageImporter::modulator_noise_pngSize = 257;

// JUCER_RESOURCE: modulator_pulse_png, 196, "../../../data/modulator_pulse.png"
static const unsigned char resource_ImageImporter_modulator_pulse_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,84,73,68,65,84,72,199,99,96,24,16,240,31,10,24,6,17,24,108,238,25,5,212,1,140,212,
136,108,70,70,70,198,225,30,70,232,97,66,182,159,145,13,34,55,87,49,81,203,107,163,6,17,6,44,148,102,145,97,158,61,70,14,192,21,233,244,172,28,153,6,91,160,140,58,104,212,65,195,206,65,163,96,200,1,0,
103,211,40,1,21,164,70,223,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_pulse_png = (const char*) resource_ImageImporter_modulator_pulse_png;
const int ImageImporter::modulator_pulse_pngSize = 196;

// JUCER_RESOURCE: modulator_sawf_png, 217, "../../../data/modulator_sawf.png"
static const unsigned char resource_ImageImporter_modulator_sawf_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,105,73,68,65,84,72,199,237,150,65,14,192,32,8,4,89,211,255,127,121,189,120,104,
154,218,26,193,64,148,185,187,12,162,70,145,216,144,100,250,100,131,10,96,209,42,0,200,230,88,140,190,88,201,172,9,82,183,184,100,143,84,161,207,197,51,97,87,239,200,143,134,157,112,61,142,128,141,112,
143,82,24,169,187,72,8,169,55,9,87,177,94,113,55,169,175,194,46,82,127,69,183,255,101,38,51,84,221,250,99,182,39,26,103,190,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_sawf_png = (const char*) resource_ImageImporter_modulator_sawf_png;
const int ImageImporter::modulator_sawf_pngSize = 217;

// JUCER_RESOURCE: modulator_sawr_png, 219, "../../../data/modulator_sawr.png"
static const unsigned char resource_ImageImporter_modulator_sawr_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,107,73,68,65,84,72,199,237,149,73,10,0,33,12,4,19,153,255,127,185,189,40,12,50,
227,130,75,34,116,157,196,67,186,196,68,69,122,0,0,45,55,100,19,0,16,132,220,69,238,136,48,91,96,137,197,123,253,140,38,104,130,151,106,212,67,246,69,124,29,105,59,58,170,202,241,32,203,230,195,205,140,
100,17,23,66,95,95,153,155,39,204,76,232,47,216,68,168,22,122,92,168,21,120,199,79,68,42,68,107,212,103,175,213,121,75,77,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ImageImporter::modulator_sawr_png = (const char*) resource_ImageImporter_modulator_sawr_png;
const int ImageImporter::modulator_sawr_pngSize = 219;


//[EndFile] You can add extra defines here...
//[/EndFile]

