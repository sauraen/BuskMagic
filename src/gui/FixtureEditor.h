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
#include "gui/TextListModel.h"
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
    FixtureEditor (ValueTree fxt);
    ~FixtureEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel *parent, int row) override;
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;

    void fillParamsBox();
    void refreshParamControls();
    static String getParamDesc(ValueTree prm);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ValueTree fixture, param;

    std::unique_ptr<TextListModel> lsmParams;
    std::unique_ptr<ListBox> lstParams;

    std::unique_ptr<Component> parameditor;
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
    std::unique_ptr<TextEditor> txtPName;
    std::unique_ptr<Label> lblPLetters;
    std::unique_ptr<TextEditor> txtPLetters;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FixtureEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

