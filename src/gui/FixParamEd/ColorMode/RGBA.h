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

#include "JuceHeader.h"
#include "Common.h"

namespace FixParamEd { namespace ColorMode {
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RGBA  : public Component,
              public TextEditor::Listener
{
public:
    //==============================================================================
    RGBA (ValueTree prm);
    ~RGBA();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ValueTree param;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblR;
    std::unique_ptr<TextEditor> txtDMXR;
    std::unique_ptr<TextEditor> txtHueR;
    std::unique_ptr<Label> lblRA;
    std::unique_ptr<TextEditor> txtHueRA;
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
    std::unique_ptr<Label> lblA;
    std::unique_ptr<TextEditor> txtDMXA;
    std::unique_ptr<TextEditor> txtHueA;
    std::unique_ptr<Label> lblAG;
    std::unique_ptr<TextEditor> txtHueAG;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RGBA)
};

//[EndFile] You can add extra defines here...
}}

//[/EndFile]

