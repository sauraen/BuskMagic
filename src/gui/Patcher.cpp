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

#include "FixtureSystem.h"
#include "FixtureEditor.h"
#include "Popup/CtrlrEditor.h"
//[/Headers]

#include "Patcher.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Patcher::Patcher ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    grpEdit.reset (new GroupComponent ("grpEdit",
                                       TRANS("Fixture Properties")));
    addAndMakeVisible (grpEdit.get());

    grpEdit->setBounds (648, 400, 312, 144);

    grpAdd.reset (new GroupComponent ("grpAdd",
                                      TRANS("Add Fixture")));
    addAndMakeVisible (grpAdd.get());

    grpAdd->setBounds (312, 448, 312, 96);

    lblDisk.reset (new Label ("lblDisk",
                              TRANS("Fixture definitions on disk:")));
    addAndMakeVisible (lblDisk.get());
    lblDisk->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDisk->setJustificationType (Justification::centredLeft);
    lblDisk->setEditable (false, false, false);
    lblDisk->setColour (TextEditor::textColourId, Colours::black);
    lblDisk->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDisk->setBounds (0, 0, 168, 24);

    btnDirectory.reset (new TextButton ("btnDirectory"));
    addAndMakeVisible (btnDirectory.get());
    btnDirectory->setButtonText (TRANS("Directory..."));
    btnDirectory->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnDirectory->addListener (this);

    btnDirectory->setBounds (208, 0, 80, 24);

    lblShowfile.reset (new Label ("lblShowfile",
                                  TRANS("Fixture definitions in showfile:")));
    addAndMakeVisible (lblShowfile.get());
    lblShowfile->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblShowfile->setJustificationType (Justification::centredLeft);
    lblShowfile->setEditable (false, false, false);
    lblShowfile->setColour (TextEditor::textColourId, Colours::black);
    lblShowfile->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblShowfile->setBounds (312, 0, 264, 24);

    btnLoad.reset (new TextButton ("btnLoad"));
    addAndMakeVisible (btnLoad.get());
    btnLoad->setButtonText (CharPointer_UTF8 ("\xe2\x86\x92"));
    btnLoad->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnLoad->addListener (this);

    btnLoad->setBounds (288, 208, 24, 24);

    btnSave.reset (new TextButton ("btnSave"));
    addAndMakeVisible (btnSave.get());
    btnSave->setButtonText (CharPointer_UTF8 ("\xe2\x86\x90"));
    btnSave->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop);
    btnSave->addListener (this);

    btnSave->setBounds (288, 232, 24, 24);

    btnNewDef.reset (new TextButton ("btnNewDef"));
    addAndMakeVisible (btnNewDef.get());
    btnNewDef->setButtonText (TRANS("+"));
    btnNewDef->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnNewDef->addListener (this);

    btnNewDef->setBounds (576, 0, 24, 24);

    btnDeleteDef.reset (new TextButton ("btnDeleteDef"));
    addAndMakeVisible (btnDeleteDef.get());
    btnDeleteDef->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnDeleteDef->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnDeleteDef->addListener (this);

    btnDeleteDef->setBounds (600, 0, 24, 24);

    btnDeleteFixture.reset (new TextButton ("btnDeleteFixture"));
    addAndMakeVisible (btnDeleteFixture.get());
    btnDeleteFixture->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnDeleteFixture->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnDeleteFixture->addListener (this);

    btnDeleteFixture->setBounds (936, 0, 24, 24);

    lblFixtures.reset (new Label ("lblFixtures",
                                  TRANS("Fixtures in show:")));
    addAndMakeVisible (lblFixtures.get());
    lblFixtures->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblFixtures->setJustificationType (Justification::centredLeft);
    lblFixtures->setEditable (false, false, false);
    lblFixtures->setColour (TextEditor::textColourId, Colours::black);
    lblFixtures->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblFixtures->setBounds (648, 0, 232, 24);

    lblAddQty.reset (new Label ("lblAddQty",
                                TRANS("Qty:")));
    addAndMakeVisible (lblAddQty.get());
    lblAddQty->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddQty->setJustificationType (Justification::centredLeft);
    lblAddQty->setEditable (false, false, false);
    lblAddQty->setColour (TextEditor::textColourId, Colours::black);
    lblAddQty->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddQty->setBounds (320, 488, 40, 24);

    txtAddQty.reset (new TextEditor ("txtAddQty"));
    addAndMakeVisible (txtAddQty.get());
    txtAddQty->setMultiLine (false);
    txtAddQty->setReturnKeyStartsNewLine (false);
    txtAddQty->setReadOnly (false);
    txtAddQty->setScrollbarsShown (true);
    txtAddQty->setCaretVisible (true);
    txtAddQty->setPopupMenuEnabled (true);
    txtAddQty->setText (TRANS("4"));

    txtAddQty->setBounds (360, 488, 24, 24);

    lblAddFixID.reset (new Label ("lblAddFixID",
                                  TRANS("From FixID:")));
    addAndMakeVisible (lblAddFixID.get());
    lblAddFixID->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddFixID->setJustificationType (Justification::centredLeft);
    lblAddFixID->setEditable (false, false, false);
    lblAddFixID->setColour (TextEditor::textColourId, Colours::black);
    lblAddFixID->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddFixID->setBounds (392, 512, 80, 24);

    txtAddFixID.reset (new TextEditor ("txtAddFixID"));
    addAndMakeVisible (txtAddFixID.get());
    txtAddFixID->setMultiLine (false);
    txtAddFixID->setReturnKeyStartsNewLine (false);
    txtAddFixID->setReadOnly (false);
    txtAddFixID->setScrollbarsShown (true);
    txtAddFixID->setCaretVisible (true);
    txtAddFixID->setPopupMenuEnabled (true);
    txtAddFixID->setText (TRANS("0"));

    txtAddFixID->setBounds (472, 512, 40, 24);

    lblAddUni.reset (new Label ("lblAddUni",
                                TRANS("From Uni: 0x")));
    addAndMakeVisible (lblAddUni.get());
    lblAddUni->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddUni->setJustificationType (Justification::centredLeft);
    lblAddUni->setEditable (false, false, false);
    lblAddUni->setColour (TextEditor::textColourId, Colours::black);
    lblAddUni->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddUni->setBounds (392, 488, 88, 24);

    btnAdd.reset (new TextButton ("btnAdd"));
    addAndMakeVisible (btnAdd.get());
    btnAdd->setButtonText (CharPointer_UTF8 ("Add \xe2\x86\x92"));
    btnAdd->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnAdd->addListener (this);

    btnAdd->setBounds (512, 512, 104, 24);

    txtAddUni.reset (new TextEditor ("txtAddUni"));
    addAndMakeVisible (txtAddUni.get());
    txtAddUni->setMultiLine (false);
    txtAddUni->setReturnKeyStartsNewLine (false);
    txtAddUni->setReadOnly (false);
    txtAddUni->setScrollbarsShown (true);
    txtAddUni->setCaretVisible (true);
    txtAddUni->setPopupMenuEnabled (true);
    txtAddUni->setText (TRANS("0000"));

    txtAddUni->setBounds (480, 488, 40, 24);

    lblAddChn.reset (new Label ("lblAddChn",
                                TRANS("Channel:")));
    addAndMakeVisible (lblAddChn.get());
    lblAddChn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddChn->setJustificationType (Justification::centredLeft);
    lblAddChn->setEditable (false, false, false);
    lblAddChn->setColour (TextEditor::textColourId, Colours::black);
    lblAddChn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddChn->setBounds (520, 488, 64, 24);

    txtAddChn.reset (new TextEditor ("txtAddChn"));
    addAndMakeVisible (txtAddChn.get());
    txtAddChn->setMultiLine (false);
    txtAddChn->setReturnKeyStartsNewLine (false);
    txtAddChn->setReadOnly (false);
    txtAddChn->setScrollbarsShown (true);
    txtAddChn->setCaretVisible (true);
    txtAddChn->setPopupMenuEnabled (true);
    txtAddChn->setText (TRANS("1"));

    txtAddChn->setBounds (584, 488, 32, 24);

    lblAddName.reset (new Label ("lblAddName",
                                 TRANS("Fix. Names:")));
    addAndMakeVisible (lblAddName.get());
    lblAddName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddName->setJustificationType (Justification::centredLeft);
    lblAddName->setEditable (false, false, false);
    lblAddName->setColour (TextEditor::textColourId, Colours::black);
    lblAddName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddName->setBounds (320, 464, 80, 24);

    txtAddName.reset (new TextEditor ("txtAddName"));
    addAndMakeVisible (txtAddName.get());
    txtAddName->setMultiLine (false);
    txtAddName->setReturnKeyStartsNewLine (false);
    txtAddName->setReadOnly (false);
    txtAddName->setScrollbarsShown (true);
    txtAddName->setCaretVisible (true);
    txtAddName->setPopupMenuEnabled (true);
    txtAddName->setText (TRANS("(e.g. Downstage Wash)"));

    txtAddName->setBounds (400, 464, 216, 24);

    lblName.reset (new Label ("lblName",
                              TRANS("Name:")));
    addAndMakeVisible (lblName.get());
    lblName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblName->setJustificationType (Justification::centredLeft);
    lblName->setEditable (false, false, false);
    lblName->setColour (TextEditor::textColourId, Colours::black);
    lblName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblName->setBounds (656, 464, 56, 24);

    txtName.reset (new TextEditor ("txtName"));
    addAndMakeVisible (txtName.get());
    txtName->setMultiLine (false);
    txtName->setReturnKeyStartsNewLine (false);
    txtName->setReadOnly (false);
    txtName->setScrollbarsShown (true);
    txtName->setCaretVisible (true);
    txtName->setPopupMenuEnabled (true);
    txtName->setText (TRANS("Downstage Wash"));

    txtName->setBounds (712, 464, 208, 24);

    lblUni.reset (new Label ("lblUni",
                             TRANS("Uni: 0x")));
    addAndMakeVisible (lblUni.get());
    lblUni->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUni->setJustificationType (Justification::centredLeft);
    lblUni->setEditable (false, false, false);
    lblUni->setColour (TextEditor::textColourId, Colours::black);
    lblUni->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUni->setBounds (656, 488, 56, 24);

    txtUni.reset (new TextEditor ("txtUni"));
    addAndMakeVisible (txtUni.get());
    txtUni->setMultiLine (false);
    txtUni->setReturnKeyStartsNewLine (false);
    txtUni->setReadOnly (false);
    txtUni->setScrollbarsShown (true);
    txtUni->setCaretVisible (true);
    txtUni->setPopupMenuEnabled (true);
    txtUni->setText (TRANS("0000"));

    txtUni->setBounds (712, 488, 40, 24);

    lblChn.reset (new Label ("lblChn",
                             TRANS("Channel:")));
    addAndMakeVisible (lblChn.get());
    lblChn->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblChn->setJustificationType (Justification::centredLeft);
    lblChn->setEditable (false, false, false);
    lblChn->setColour (TextEditor::textColourId, Colours::black);
    lblChn->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblChn->setBounds (784, 488, 64, 24);

    txtChn.reset (new TextEditor ("txtChn"));
    addAndMakeVisible (txtChn.get());
    txtChn->setMultiLine (false);
    txtChn->setReturnKeyStartsNewLine (false);
    txtChn->setReadOnly (false);
    txtChn->setScrollbarsShown (true);
    txtChn->setCaretVisible (true);
    txtChn->setPopupMenuEnabled (true);
    txtChn->setText (TRANS("512"));

    txtChn->setBounds (848, 488, 32, 24);

    lblFixID.reset (new Label ("lblFixID",
                               TRANS("Fixture ID:")));
    addAndMakeVisible (lblFixID.get());
    lblFixID->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblFixID->setJustificationType (Justification::centredLeft);
    lblFixID->setEditable (false, false, false);
    lblFixID->setColour (TextEditor::textColourId, Colours::black);
    lblFixID->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblFixID->setBounds (656, 512, 72, 24);

    txtFixID.reset (new TextEditor ("txtFixID"));
    addAndMakeVisible (txtFixID.get());
    txtFixID->setMultiLine (false);
    txtFixID->setReturnKeyStartsNewLine (false);
    txtFixID->setReadOnly (false);
    txtFixID->setScrollbarsShown (true);
    txtFixID->setCaretVisible (true);
    txtFixID->setPopupMenuEnabled (true);
    txtFixID->setText (TRANS("0"));

    txtFixID->setBounds (728, 512, 40, 24);

    btnSetName.reset (new TextButton ("btnSetName"));
    addAndMakeVisible (btnSetName.get());
    btnSetName->setButtonText (TRANS("Set"));
    btnSetName->setConnectedEdges (Button::ConnectedOnLeft);
    btnSetName->addListener (this);

    btnSetName->setBounds (920, 464, 32, 24);

    lblFixInfo.reset (new Label ("lblFixInfo",
                                 TRANS("Manufacturer: XXX\n"
                                 "Fixture: XXX\n"
                                 "Profile: XXX (XX)")));
    addAndMakeVisible (lblFixInfo.get());
    lblFixInfo->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblFixInfo->setJustificationType (Justification::centredLeft);
    lblFixInfo->setEditable (false, false, false);
    lblFixInfo->setColour (TextEditor::textColourId, Colours::black);
    lblFixInfo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblFixInfo->setBounds (656, 416, 296, 48);

    btnSetUni.reset (new TextButton ("btnSetUni"));
    addAndMakeVisible (btnSetUni.get());
    btnSetUni->setButtonText (TRANS("Set"));
    btnSetUni->setConnectedEdges (Button::ConnectedOnLeft);
    btnSetUni->addListener (this);

    btnSetUni->setBounds (752, 488, 32, 24);

    btnSetChn.reset (new TextButton ("btnSetChn"));
    addAndMakeVisible (btnSetChn.get());
    btnSetChn->setButtonText (TRANS("Set From"));
    btnSetChn->setConnectedEdges (Button::ConnectedOnLeft);
    btnSetChn->addListener (this);

    btnSetChn->setBounds (880, 488, 72, 24);

    btnSetFixID.reset (new TextButton ("btnSetFixID"));
    addAndMakeVisible (btnSetFixID.get());
    btnSetFixID->setButtonText (TRANS("Set From"));
    btnSetFixID->setConnectedEdges (Button::ConnectedOnLeft);
    btnSetFixID->addListener (this);

    btnSetFixID->setBounds (768, 512, 72, 24);

    btnRefresh.reset (new TextButton ("btnRefresh"));
    addAndMakeVisible (btnRefresh.get());
    btnRefresh->setButtonText (TRANS("Rfrsh"));
    btnRefresh->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnRefresh->addListener (this);

    btnRefresh->setBounds (168, 0, 40, 24);

    btnSort.reset (new TextButton ("btnSort"));
    addAndMakeVisible (btnSort.get());
    btnSort->setButtonText (TRANS("Sort"));
    btnSort->setConnectedEdges (Button::ConnectedOnRight);
    btnSort->addListener (this);

    btnSort->setBounds (880, 0, 56, 24);


    //[UserPreSize]

    lstDir.reset(new TextListBox(this));
    lstDefs.reset(new TextListBox(this));
    lstFixtures.reset(new TextListBox(this));
    addAndMakeVisible(lstDir.get());
    addAndMakeVisible(lstDefs.get());
    addAndMakeVisible(lstFixtures.get());
    lstDir->setSelectAddedItems(false);
    lstFixtures->setMultipleSelectionEnabled(true);
    lstFixtures->setSelectAddedItems(false);

    lstDir->setBounds(0, 24, 288, 520);
    lstDefs->setBounds(312, 24, 312, 416);
    lstFixtures->setBounds(648, 24, 312, 368);
    
    setOpaque(true);
    
    //[/UserPreSize]

    setSize (960, 544);


    //[Constructor] You can add your own custom stuff here..

    fillDirBox();
    fillDefsBox();
    fillFixturesBox();
    refreshFixtureEditControls();

    //[/Constructor]
}

Patcher::~Patcher()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    grpEdit = nullptr;
    grpAdd = nullptr;
    lblDisk = nullptr;
    btnDirectory = nullptr;
    lblShowfile = nullptr;
    btnLoad = nullptr;
    btnSave = nullptr;
    btnNewDef = nullptr;
    btnDeleteDef = nullptr;
    btnDeleteFixture = nullptr;
    lblFixtures = nullptr;
    lblAddQty = nullptr;
    txtAddQty = nullptr;
    lblAddFixID = nullptr;
    txtAddFixID = nullptr;
    lblAddUni = nullptr;
    btnAdd = nullptr;
    txtAddUni = nullptr;
    lblAddChn = nullptr;
    txtAddChn = nullptr;
    lblAddName = nullptr;
    txtAddName = nullptr;
    lblName = nullptr;
    txtName = nullptr;
    lblUni = nullptr;
    txtUni = nullptr;
    lblChn = nullptr;
    txtChn = nullptr;
    lblFixID = nullptr;
    txtFixID = nullptr;
    btnSetName = nullptr;
    lblFixInfo = nullptr;
    btnSetUni = nullptr;
    btnSetChn = nullptr;
    btnSetFixID = nullptr;
    btnRefresh = nullptr;
    btnSort = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    lstDir = nullptr;
    lstDefs = nullptr;
    lstFixtures = nullptr;

    //[/Destructor]
}

//==============================================================================
void Patcher::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Patcher::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Patcher::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnDirectory.get())
    {
        //[UserButtonCode_btnDirectory] -- add your button handler code here..
        File dir = FixtureSystem::GetFixtureDirectory();
        FileChooser fc("Select a directory containing fixture files...",
                dir.isDirectory() ? dir : File::getSpecialLocation(File::userHomeDirectory), "*");
        if(!fc.browseForDirectory()) return;
        FixtureSystem::SetFixtureDirectory(fc.getResult());
        fillDirBox();
        //[/UserButtonCode_btnDirectory]
    }
    else if (buttonThatWasClicked == btnLoad.get())
    {
        //[UserButtonCode_btnLoad] -- add your button handler code here..
        int r = lstDir->getLastRowSelected();
        if(r < 0) return;
        File fxf = FixtureSystem::GetFixtureDirectory().getChildFile(lstDir->get(r) + ".xml");
        if(!fxf.existsAsFile()){
            WarningBox("This file no longer exists.");
            fillDirBox();
            return;
        }
        ValueTree v = VT_Load(fxf, "fixturedef");
        if(!v.isValid()){
            WarningBox("This is not a valid fixture file.");
            fillDirBox();
            return;
        }
        v.setProperty("inuse", false, nullptr); //Fixtures may be saved with this set!
        FixtureSystem::GetFixtureDefs().addChild(v, -1, nullptr);
        lstDefs->add(FixtureSystem::GetFixDefName(v));
        //[/UserButtonCode_btnLoad]
    }
    else if (buttonThatWasClicked == btnSave.get())
    {
        //[UserButtonCode_btnSave] -- add your button handler code here..
        int r = lstDefs->getLastRowSelected();
        if(r < 0) return;
        ValueTree v = FixtureSystem::GetFixtureDefs().getChild(r);
        if(!v.isValid()) return;
        File dir = FixtureSystem::GetFixtureDirectory();
        FileChooser fc("Save fixture as...",
                dir.isDirectory() ? dir : File::getSpecialLocation(File::userHomeDirectory), "*.xml");
        if(!fc.browseForFileToSave(true)) return;
        std::unique_ptr<XmlElement> xml(v.createXml());
        if(!xml->writeToFile(fc.getResult().withFileExtension("xml"), "<!-- BuskMagic Fixture File -->", "UTF-8", 80)){
            WarningBox("Could not save fixture file.");
        }else{
            fillDirBox();
        }
        //[/UserButtonCode_btnSave]
    }
    else if (buttonThatWasClicked == btnNewDef.get())
    {
        //[UserButtonCode_btnNewDef] -- add your button handler code here..
        ValueTree v("fixturedef");
        v.setProperty(idManufacturer, "(Manufacturer)", nullptr);
        v.setProperty(idName, "(New fixture)", nullptr);
        v.setProperty(idProfile, "1-channel mode", nullptr);
        v.setProperty(idFootprint, 1, nullptr);
        FixtureSystem::GetFixtureDefs().addChild(v, -1, nullptr);
        lstDefs->add(FixtureSystem::GetFixDefName(v));
        //[/UserButtonCode_btnNewDef]
    }
    else if (buttonThatWasClicked == btnDeleteDef.get())
    {
        //[UserButtonCode_btnDeleteDef] -- add your button handler code here..
        int r = lstDefs->getLastRowSelected();
        if(r < 0) return;
        ValueTree v = FixtureSystem::GetFixtureDefs().getChild(r);
        if(!v.isValid()) return;
        if((bool)v.getProperty("inuse", false)){
            WarningBox("Cannot delete a fixture definition which is in use.");
            return;
        }
        FixtureSystem::GetFixtureDefs().removeChild(v, nullptr);
        lstDefs->remove(r);
        //[/UserButtonCode_btnDeleteDef]
    }
    else if (buttonThatWasClicked == btnDeleteFixture.get())
    {
        //[UserButtonCode_btnDeleteFixture] -- add your button handler code here..
        for(int i=lstFixtures->getNumSelectedRows() - 1; i>=0; --i){
            int r = lstFixtures->getSelectedRow(i);
            FixtureSystem::RemoveFixture(r);
        }
        fillFixturesBox();
        //[/UserButtonCode_btnDeleteFixture]
    }
    else if (buttonThatWasClicked == btnAdd.get())
    {
        //[UserButtonCode_btnAdd] -- add your button handler code here..
        int r = lstDefs->getLastRowSelected();
        if(r < 0) return;
        ValueTree def = FixtureSystem::GetFixtureDefs().getChild(r);
        bool error = false;
        //
        String name = txtAddName->getText().trim();
        if(name.isEmpty()){
            error = true;
            TurnRed(txtAddName);
        }else TurnRed(txtAddName, false);
        //
        String text = txtAddQty->getText();
        int qty = text.getIntValue();
        if(!isInt(text, false) || qty <= 0){
            error = true;
            TurnRed(txtAddQty);
        }else TurnRed(txtAddQty, false);
        //
        text = txtAddUni->getText();
        int uni = text.getHexValue32();
        if(!isHex(text) || uni < 0 || uni >= 0x8000){
            error = true;
            TurnRed(txtAddUni);
        }else TurnRed(txtAddUni, false);
        //
        text = txtAddChn->getText();
        int chn = text.getIntValue();
        if(!isInt(text, false) || chn < 1 || chn > 512){
            error = true;
            TurnRed(txtAddChn);
        }else TurnRed(txtAddChn, false);
        //
        text = txtAddFixID->getText();
        int fixid = text.getIntValue();
        if(!isInt(text, true)){
            error = true;
            TurnRed(txtAddFixID);
        }else TurnRed(txtAddFixID, false);
        //
        if(error) return;
        //
        int footprint = def.getProperty(idFootprint, 1);
        if(qty * footprint + chn > 513){
            WarningBox("Cannot fit " + String(qty) + "x fixtures with footprint " + String(footprint)
                + " at channel " + String(chn) + ".");
            return;
        }
        for(int i=0; i<qty; ++i){
            FixtureSystem::AddFixture(def, name, fixid, uni, chn);
            chn += footprint;
            fixid += 1;
        }
        lstDefs->set(r, FixtureSystem::GetFixDefName(def)); //In case first use, put (*)
        fillFixturesBox();
        //[/UserButtonCode_btnAdd]
    }
    else if (buttonThatWasClicked == btnSetName.get())
    {
        //[UserButtonCode_btnSetName] -- add your button handler code here..
        String name = txtName->getText().trim();
        if(name.isEmpty()){
            TurnRed(txtName);
            return;
        }
        TurnRed(txtName, false);
        for(int i=0; i<lstFixtures->getNumSelectedRows(); ++i){
            int r = lstFixtures->getSelectedRow(i);
            Fixture *fix = FixtureSystem::Fix(r);
            fix->SetName(name);
            lstFixtures->set(r, fix->GetDescription());
        }
        //[/UserButtonCode_btnSetName]
    }
    else if (buttonThatWasClicked == btnSetUni.get())
    {
        //[UserButtonCode_btnSetUni] -- add your button handler code here..
        String text = txtUni->getText();
        int uni = text.getHexValue32();
        if(!isHex(text) || uni < 0 || uni >= 0x8000){
            TurnRed(txtUni);
            return;
        }
        TurnRed(txtUni, false);
        for(int i=0; i<lstFixtures->getNumSelectedRows(); ++i){
            int r = lstFixtures->getSelectedRow(i);
            Fixture *fix = FixtureSystem::Fix(r);
            fix->SetPatch(uni, fix->GetDMXChannel());
            lstFixtures->set(r, fix->GetDescription());
        }
        //[/UserButtonCode_btnSetUni]
    }
    else if (buttonThatWasClicked == btnSetChn.get())
    {
        //[UserButtonCode_btnSetChn] -- add your button handler code here..
        String text = txtChn->getText();
        int chn = text.getIntValue();
        if(!isInt(text, false) || chn < 1 || chn > 512){
            TurnRed(txtChn);
            return;
        }
        TurnRed(txtChn, false);
        for(int i=0; i<lstFixtures->getNumSelectedRows(); ++i){
            int r = lstFixtures->getSelectedRow(i);
            Fixture *fix = FixtureSystem::Fix(r);
            int footprint = (int)fix->GetDef().getProperty(idFootprint, 1);
            if(chn + footprint > 513){
                WarningBox("Could not fit one or more fixtures in universe, aborted.");
                return;
            }
            fix->SetPatch(fix->GetUniverse(), chn);
            chn += footprint;
            lstFixtures->set(r, fix->GetDescription());
        }
        //[/UserButtonCode_btnSetChn]
    }
    else if (buttonThatWasClicked == btnSetFixID.get())
    {
        //[UserButtonCode_btnSetFixID] -- add your button handler code here..
        String text = txtFixID->getText();
        int fixid = text.getIntValue();
        if(!isInt(text, true)){
            TurnRed(txtFixID);
            return;
        }
        TurnRed(txtFixID, false);
        for(int i=0; i<lstFixtures->getNumSelectedRows(); ++i){
            int r = lstFixtures->getSelectedRow(i);
            Fixture *fix = FixtureSystem::Fix(r);
            fix->SetFixID(fixid++);
            lstFixtures->set(r, fix->GetDescription());
        }
        //[/UserButtonCode_btnSetFixID]
    }
    else if (buttonThatWasClicked == btnRefresh.get())
    {
        //[UserButtonCode_btnRefresh] -- add your button handler code here..
        fillDirBox();
        //[/UserButtonCode_btnRefresh]
    }
    else if (buttonThatWasClicked == btnSort.get())
    {
        //[UserButtonCode_btnSort] -- add your button handler code here..
        FixtureSystem::SortFixtures();
        fillFixturesBox();
        //[/UserButtonCode_btnSort]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Patcher::rowSelected(TextListBox *parent, int row)
{
    if(parent == lstDir.get()){
        //
    }else if(parent == lstDefs.get()){
        //
    }else if(parent == lstFixtures.get()){
        refreshFixtureEditControls();
    }
}

void Patcher::rowDoubleClicked(TextListBox* parent, int row)
{
    if(parent == lstDir.get()){
        //
    }else if(parent == lstDefs.get()){
        if(row < 0) return;
        ValueTree v = FixtureSystem::GetFixtureDefs().getChild(row);
        if(!v.isValid()) return;
        DialogWindow::LaunchOptions opts;
        opts.dialogTitle = "BuskMagic - Fixture Editor";
        opts.content.set(new FixtureEditor(v), true);
        opts.componentToCentreAround = lstDefs.get();
        opts.resizable = false;
        opts.runModal();
        lstDefs->set(row, FixtureSystem::GetFixDefName(v));
    }else if(parent == lstFixtures.get()){
        //
    }
}

void Patcher::fillDirBox()
{
    lstDir->clear();
    File dir = FixtureSystem::GetFixtureDirectory();
    if(!dir.isDirectory()) return;
    Array<File> fixs = dir.findChildFiles(File::findFiles, false, "*.xml");
    if(fixs.size() == 0) return;
    for(int i=0; i<fixs.size(); ++i){
        ValueTree v = VT_Load(fixs[i], "fixturedef");
        if(!v.isValid()) continue;
        lstDir->add(fixs[i].getFileNameWithoutExtension());
    }
}

void Patcher::fillDefsBox()
{
    lstDefs->clear();
    lstDefs->setSelectAddedItems(false);
    ValueTree defs = FixtureSystem::GetFixtureDefs();
    for(int i=0; i<defs.getNumChildren(); ++i){
        lstDefs->add(FixtureSystem::GetFixDefName(defs.getChild(i)));
    }
    lstDefs->setSelectAddedItems(true);
}

void Patcher::fillFixturesBox()
{
    lstFixtures->clear();
    for(int i=0; i<FixtureSystem::NumFixtures(); ++i){
        lstFixtures->add(FixtureSystem::Fix(i)->GetDescription());
    }
}

void Patcher::refreshFixtureEditControls()
{
    int r = lstFixtures->getLastRowSelected();
    if(r < 0){
        lblFixInfo->setText("(Select some fixtures above)", dontSendNotification);
        txtName->setText("");
        txtUni->setText("");
        txtChn->setText("");
        txtFixID->setText("");
        return;
    }
    Fixture *fix = FixtureSystem::Fix(r);
    ValueTree def = fix->GetDef();
    lblFixInfo->setText("Manufacturer: " + def.getProperty(idManufacturer, "(Manu)").toString() + "\n"
        + "Name: " + def.getProperty(idName, "(Name)").toString() + "\n"
        + "Profile: " + def.getProperty(idProfile, "(Profile)").toString() + " ("
        + def.getProperty(idFootprint, "XX").toString() + ")", dontSendNotification);
    txtName->setText(fix->GetName());
    txtUni->setText(hex(fix->GetUniverse()));
    txtChn->setText(String(fix->GetDMXChannel()));
    txtFixID->setText(String(fix->GetFixID()));
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Patcher" componentName=""
                 parentClasses="public Component, public TextListBox::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="960"
                 initialHeight="544">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="grpEdit" id="ac74fa1d06f306ee" memberName="grpEdit" virtualName=""
                  explicitFocusOrder="0" pos="648 400 312 144" title="Fixture Properties"/>
  <GROUPCOMPONENT name="grpAdd" id="656fe626e2a1c50d" memberName="grpAdd" virtualName=""
                  explicitFocusOrder="0" pos="312 448 312 96" title="Add Fixture"/>
  <LABEL name="lblDisk" id="8608433261170576" memberName="lblDisk" virtualName=""
         explicitFocusOrder="0" pos="0 0 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fixture definitions on disk:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnDirectory" id="2d8c73536d69bea" memberName="btnDirectory"
              virtualName="" explicitFocusOrder="0" pos="208 0 80 24" buttonText="Directory..."
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblShowfile" id="643b6c08c0eb71d4" memberName="lblShowfile"
         virtualName="" explicitFocusOrder="0" pos="312 0 264 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fixture definitions in showfile:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnLoad" id="8c8b9eb262b05176" memberName="btnLoad" virtualName=""
              explicitFocusOrder="0" pos="288 208 24 24" buttonText="&#8594;"
              connectedEdges="11" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnSave" id="5e180f9927cda3f0" memberName="btnSave" virtualName=""
              explicitFocusOrder="0" pos="288 232 24 24" buttonText="&#8592;"
              connectedEdges="7" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnNewDef" id="7ceb28d89a1747a0" memberName="btnNewDef"
              virtualName="" explicitFocusOrder="0" pos="576 0 24 24" buttonText="+"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnDeleteDef" id="506bcac0d99da01e" memberName="btnDeleteDef"
              virtualName="" explicitFocusOrder="0" pos="600 0 24 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnDeleteFixture" id="a20ed334392c9c49" memberName="btnDeleteFixture"
              virtualName="" explicitFocusOrder="0" pos="936 0 24 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblFixtures" id="244c2d7cad8d2638" memberName="lblFixtures"
         virtualName="" explicitFocusOrder="0" pos="648 0 232 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fixtures in show:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblAddQty" id="fd17579f84d8bd06" memberName="lblAddQty"
         virtualName="" explicitFocusOrder="0" pos="320 488 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Qty:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtAddQty" id="e2d209a05f07ec0b" memberName="txtAddQty"
              virtualName="" explicitFocusOrder="0" pos="360 488 24 24" initialText="4"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblAddFixID" id="21a25c99119344c8" memberName="lblAddFixID"
         virtualName="" explicitFocusOrder="0" pos="392 512 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="From FixID:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtAddFixID" id="79fc8529f709c9b3" memberName="txtAddFixID"
              virtualName="" explicitFocusOrder="0" pos="472 512 40 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblAddUni" id="a6878538164fee45" memberName="lblAddUni"
         virtualName="" explicitFocusOrder="0" pos="392 488 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="From Uni: 0x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btnAdd" id="dba1c93ba1dd0819" memberName="btnAdd" virtualName=""
              explicitFocusOrder="0" pos="512 512 104 24" buttonText="Add &#8594;"
              connectedEdges="5" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="txtAddUni" id="9cc577cb7f74ce1d" memberName="txtAddUni"
              virtualName="" explicitFocusOrder="0" pos="480 488 40 24" initialText="0000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblAddChn" id="f4ac89258935f135" memberName="lblAddChn"
         virtualName="" explicitFocusOrder="0" pos="520 488 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channel:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtAddChn" id="83dfdec8b81e43ff" memberName="txtAddChn"
              virtualName="" explicitFocusOrder="0" pos="584 488 32 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblAddName" id="99107f268414c8cd" memberName="lblAddName"
         virtualName="" explicitFocusOrder="0" pos="320 464 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fix. Names:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtAddName" id="3a7ceb72d77a547f" memberName="txtAddName"
              virtualName="" explicitFocusOrder="0" pos="400 464 216 24" initialText="(e.g. Downstage Wash)"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblName" id="e94edd1681fb7f17" memberName="lblName" virtualName=""
         explicitFocusOrder="0" pos="656 464 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtName" id="53604091056169ab" memberName="txtName" virtualName=""
              explicitFocusOrder="0" pos="712 464 208 24" initialText="Downstage Wash"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUni" id="644224b31f3c03eb" memberName="lblUni" virtualName=""
         explicitFocusOrder="0" pos="656 488 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Uni: 0x" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUni" id="c282a7df7cc3eafc" memberName="txtUni" virtualName=""
              explicitFocusOrder="0" pos="712 488 40 24" initialText="0000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblChn" id="415308cf92be49f6" memberName="lblChn" virtualName=""
         explicitFocusOrder="0" pos="784 488 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channel:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtChn" id="5b08460b7d853707" memberName="txtChn" virtualName=""
              explicitFocusOrder="0" pos="848 488 32 24" initialText="512"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblFixID" id="3f2dc52e7ee5fc2c" memberName="lblFixID" virtualName=""
         explicitFocusOrder="0" pos="656 512 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fixture ID:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtFixID" id="c04a79ebaf0219e" memberName="txtFixID" virtualName=""
              explicitFocusOrder="0" pos="728 512 40 24" initialText="0" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnSetName" id="f07fef1e429ead06" memberName="btnSetName"
              virtualName="" explicitFocusOrder="0" pos="920 464 32 24" buttonText="Set"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblFixInfo" id="949056db2a25e42e" memberName="lblFixInfo"
         virtualName="" explicitFocusOrder="0" pos="656 416 296 48" edTextCol="ff000000"
         edBkgCol="0" labelText="Manufacturer: XXX&#10;Fixture: XXX&#10;Profile: XXX (XX)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <TEXTBUTTON name="btnSetUni" id="94ba90b6fffbcdd5" memberName="btnSetUni"
              virtualName="" explicitFocusOrder="0" pos="752 488 32 24" buttonText="Set"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnSetChn" id="b36fbcb79ad2fbb5" memberName="btnSetChn"
              virtualName="" explicitFocusOrder="0" pos="880 488 72 24" buttonText="Set From"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnSetFixID" id="c9f7169ff229925a" memberName="btnSetFixID"
              virtualName="" explicitFocusOrder="0" pos="768 512 72 24" buttonText="Set From"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRefresh" id="d6d09ddfd9cd75fa" memberName="btnRefresh"
              virtualName="" explicitFocusOrder="0" pos="168 0 40 24" buttonText="Rfrsh"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnSort" id="ace6165fca3188c7" memberName="btnSort" virtualName=""
              explicitFocusOrder="0" pos="880 0 56 24" buttonText="Sort" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
