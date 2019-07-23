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
class FixtureEditor  : public Component,
                       public TextListModel::Listener,
                       public TextEditor::Listener,
                       public ComboBox::Listener,
                       public Button::Listener
{
public:
    //==============================================================================
    FixtureEditor ();
    ~FixtureEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> lblManufacturer;
    std::unique_ptr<TextEditor> txtManufacturer;
    std::unique_ptr<Label> lblFixtureName;
    std::unique_ptr<TextEditor> txtFixtureName;
    std::unique_ptr<Label> lblProfileName;
    std::unique_ptr<TextEditor> txtProfileName;
    std::unique_ptr<Label> lblDMX;
    std::unique_ptr<TextEditor> txtDMX;
    std::unique_ptr<Label> lblParameters;
    std::unique_ptr<Label> lblAddParam;
    std::unique_ptr<ComboBox> cbxAddParam;
    std::unique_ptr<TextButton> btnAddParam;
    std::unique_ptr<TextButton> btnRemoveParam;
    std::unique_ptr<TextButton> btnParamUp;
    std::unique_ptr<TextButton> btnParamDown;
    std::unique_ptr<Label> lblPName;
    std::unique_ptr<TextEditor> textEditor;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextEditor> textEditor2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FixtureEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

