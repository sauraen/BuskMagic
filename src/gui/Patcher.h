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
class Patcher  : public Component,
                 public TextListModel::Listener,
                 public Button::Listener
{
public:
    //==============================================================================
    Patcher ();
    ~Patcher();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel *parent, int row) override;
    void rowDoubleClicked(TextListModel* parent, int row) override;

    void fillDirBox();
    void fillDefsBox();
    void fillFixturesBox();
    void refreshFixtureEditControls();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<TextListModel> lsmDir;
    std::unique_ptr<ListBox> lstDir;
    std::unique_ptr<TextListModel> lsmDefs;
    std::unique_ptr<ListBox> lstDefs;
    std::unique_ptr<TextListModel> lsmFixtures;
    std::unique_ptr<ListBox> lstFixtures;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> grpEdit;
    std::unique_ptr<GroupComponent> grpAdd;
    std::unique_ptr<Label> lblDisk;
    std::unique_ptr<TextButton> btnDirectory;
    std::unique_ptr<Label> lblShowfile;
    std::unique_ptr<TextButton> btnLoad;
    std::unique_ptr<TextButton> btnSave;
    std::unique_ptr<TextButton> btnNewDef;
    std::unique_ptr<TextButton> btnDeleteDef;
    std::unique_ptr<TextButton> btnDeleteFixture;
    std::unique_ptr<Label> lblFixtures;
    std::unique_ptr<Label> lblAddQty;
    std::unique_ptr<TextEditor> txtAddQty;
    std::unique_ptr<Label> lblAddFixID;
    std::unique_ptr<TextEditor> txtAddFixID;
    std::unique_ptr<Label> lblAddUni;
    std::unique_ptr<TextButton> btnAdd;
    std::unique_ptr<TextEditor> txtAddUni;
    std::unique_ptr<Label> lblAddChn;
    std::unique_ptr<TextEditor> txtAddChn;
    std::unique_ptr<Label> lblAddName;
    std::unique_ptr<TextEditor> txtAddName;
    std::unique_ptr<Label> lblName;
    std::unique_ptr<TextEditor> txtName;
    std::unique_ptr<Label> lblUni;
    std::unique_ptr<TextEditor> txtUni;
    std::unique_ptr<Label> lblChn;
    std::unique_ptr<TextEditor> txtChn;
    std::unique_ptr<Label> lblFixID;
    std::unique_ptr<TextEditor> txtFixID;
    std::unique_ptr<TextButton> btnSetName;
    std::unique_ptr<Label> lblFixInfo;
    std::unique_ptr<TextButton> btnSetUni;
    std::unique_ptr<TextButton> btnSetChn;
    std::unique_ptr<TextButton> btnSetFixID;
    std::unique_ptr<TextButton> btnRefresh;
    std::unique_ptr<TextButton> btnSort;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Patcher)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

