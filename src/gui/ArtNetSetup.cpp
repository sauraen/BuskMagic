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

#include "ArtNetSystem.h"
//[/Headers]

#include "ArtNetSetup.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ArtNetSetup::ArtNetSetup ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lblHeader.reset (new Label ("lblHeader",
                                TRANS("M S IP Address      BI NT.S.  IN   /  OUT   NAME")));
    addAndMakeVisible (lblHeader.get());
    lblHeader->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblHeader->setJustificationType (Justification::centredLeft);
    lblHeader->setEditable (false, false, false);
    lblHeader->setColour (TextEditor::textColourId, Colours::black);
    lblHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblHeader->setBounds (0, 24, 552, 24);

    lblDeviceType.reset (new Label ("lblDeviceType",
                                    TRANS("Discovered Controller:")));
    addAndMakeVisible (lblDeviceType.get());
    lblDeviceType->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDeviceType->setJustificationType (Justification::centredLeft);
    lblDeviceType->setEditable (false, false, false);
    lblDeviceType->setColour (TextEditor::textColourId, Colours::black);
    lblDeviceType->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDeviceType->setBounds (0, 184, 144, 24);

    lblDeviceStatus.reset (new Label ("lblDeviceStatus",
                                      TRANS("Status: 0x00, 0x00 / <Device status text.........................................................................................>")));
    addAndMakeVisible (lblDeviceStatus.get());
    lblDeviceStatus->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDeviceStatus->setJustificationType (Justification::centredLeft);
    lblDeviceStatus->setEditable (false, false, false);
    lblDeviceStatus->setColour (TextEditor::textColourId, Colours::black);
    lblDeviceStatus->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDeviceStatus->setBounds (0, 208, 600, 24);

    lblIP.reset (new Label ("lblIP",
                            TRANS("IP:")));
    addAndMakeVisible (lblIP.get());
    lblIP->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblIP->setJustificationType (Justification::centredLeft);
    lblIP->setEditable (false, false, false);
    lblIP->setColour (TextEditor::textColourId, Colours::black);
    lblIP->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblIP->setBounds (0, 232, 32, 24);

    txtIP.reset (new TextEditor ("txtIP"));
    addAndMakeVisible (txtIP.get());
    txtIP->setMultiLine (false);
    txtIP->setReturnKeyStartsNewLine (false);
    txtIP->setReadOnly (false);
    txtIP->setScrollbarsShown (true);
    txtIP->setCaretVisible (true);
    txtIP->setPopupMenuEnabled (true);
    txtIP->setText (TRANS("000.000.000.000"));

    txtIP->setBounds (32, 232, 104, 24);

    btnIP.reset (new TextButton ("btnIP"));
    addAndMakeVisible (btnIP.get());
    btnIP->setButtonText (TRANS("Set"));
    btnIP->setConnectedEdges (Button::ConnectedOnLeft);
    btnIP->addListener (this);

    btnIP->setBounds (136, 232, 32, 24);

    lblUniverseHeader.reset (new Label ("lblUniverseHeader",
                                        TRANS("Net   Sub     Inputs        Outputs")));
    addAndMakeVisible (lblUniverseHeader.get());
    lblUniverseHeader->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUniverseHeader->setJustificationType (Justification::centredLeft);
    lblUniverseHeader->setEditable (false, false, false);
    lblUniverseHeader->setColour (TextEditor::textColourId, Colours::black);
    lblUniverseHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniverseHeader->setBounds (120, 256, 200, 24);

    lblUni.reset (new Label ("lblUni",
                             TRANS("Device universes:")));
    addAndMakeVisible (lblUni.get());
    lblUni->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUni->setJustificationType (Justification::centredLeft);
    lblUni->setEditable (false, false, false);
    lblUni->setColour (TextEditor::textColourId, Colours::black);
    lblUni->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUni->setBounds (0, 280, 120, 24);

    chkMap.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkMap.get());
    chkMap->setButtonText (TRANS("Map from uni:"));
    chkMap->addListener (this);

    chkMap->setBounds (0, 304, 120, 24);

    txtUniNet.reset (new TextEditor ("txtUniNet"));
    addAndMakeVisible (txtUniNet.get());
    txtUniNet->setMultiLine (false);
    txtUniNet->setReturnKeyStartsNewLine (false);
    txtUniNet->setReadOnly (false);
    txtUniNet->setScrollbarsShown (false);
    txtUniNet->setCaretVisible (true);
    txtUniNet->setPopupMenuEnabled (true);
    txtUniNet->setText (TRANS("00"));

    txtUniNet->setBounds (120, 280, 24, 24);

    lblUniPt1.reset (new Label ("lblUniPt1",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt1.get());
    lblUniPt1->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt1->setJustificationType (Justification::centredLeft);
    lblUniPt1->setEditable (false, false, false);
    lblUniPt1->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt1->setBounds (144, 280, 16, 24);

    txtUniSub.reset (new TextEditor ("txtUniSub"));
    addAndMakeVisible (txtUniSub.get());
    txtUniSub->setMultiLine (false);
    txtUniSub->setReturnKeyStartsNewLine (false);
    txtUniSub->setReadOnly (false);
    txtUniSub->setScrollbarsShown (false);
    txtUniSub->setCaretVisible (true);
    txtUniSub->setPopupMenuEnabled (true);
    txtUniSub->setText (TRANS("0"));

    txtUniSub->setBounds (160, 280, 16, 24);

    lblUniPt2.reset (new Label ("lblUniPt1",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt2.get());
    lblUniPt2->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt2->setJustificationType (Justification::centredLeft);
    lblUniPt2->setEditable (false, false, false);
    lblUniPt2->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt2->setBounds (176, 280, 16, 24);

    txtUniInputs.reset (new TextEditor ("txtUniInputs"));
    addAndMakeVisible (txtUniInputs.get());
    txtUniInputs->setMultiLine (false);
    txtUniInputs->setReturnKeyStartsNewLine (false);
    txtUniInputs->setReadOnly (false);
    txtUniInputs->setScrollbarsShown (false);
    txtUniInputs->setCaretVisible (true);
    txtUniInputs->setPopupMenuEnabled (true);
    txtUniInputs->setText (TRANS("8,9,A,B"));

    txtUniInputs->setBounds (192, 280, 56, 24);

    lblUniSlash1.reset (new Label ("lblUniSlash1",
                                   TRANS("/")));
    addAndMakeVisible (lblUniSlash1.get());
    lblUniSlash1->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniSlash1->setJustificationType (Justification::centredLeft);
    lblUniSlash1->setEditable (false, false, false);
    lblUniSlash1->setColour (TextEditor::textColourId, Colours::black);
    lblUniSlash1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniSlash1->setBounds (248, 280, 16, 24);

    txtUniOutputs.reset (new TextEditor ("txtUniOutputs"));
    addAndMakeVisible (txtUniOutputs.get());
    txtUniOutputs->setMultiLine (false);
    txtUniOutputs->setReturnKeyStartsNewLine (false);
    txtUniOutputs->setReadOnly (false);
    txtUniOutputs->setScrollbarsShown (false);
    txtUniOutputs->setCaretVisible (true);
    txtUniOutputs->setPopupMenuEnabled (true);
    txtUniOutputs->setText (TRANS("0,1,2,3"));

    txtUniOutputs->setBounds (264, 280, 56, 24);

    txtMapNet.reset (new TextEditor ("txtMapNet"));
    addAndMakeVisible (txtMapNet.get());
    txtMapNet->setMultiLine (false);
    txtMapNet->setReturnKeyStartsNewLine (false);
    txtMapNet->setReadOnly (false);
    txtMapNet->setScrollbarsShown (false);
    txtMapNet->setCaretVisible (true);
    txtMapNet->setPopupMenuEnabled (true);
    txtMapNet->setText (TRANS("00"));

    txtMapNet->setBounds (120, 304, 24, 24);

    lblUniPt3.reset (new Label ("lblUniPt3",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt3.get());
    lblUniPt3->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt3->setJustificationType (Justification::centredLeft);
    lblUniPt3->setEditable (false, false, false);
    lblUniPt3->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt3->setBounds (144, 304, 16, 24);

    txtMapSub.reset (new TextEditor ("txtMapSub"));
    addAndMakeVisible (txtMapSub.get());
    txtMapSub->setMultiLine (false);
    txtMapSub->setReturnKeyStartsNewLine (false);
    txtMapSub->setReadOnly (false);
    txtMapSub->setScrollbarsShown (false);
    txtMapSub->setCaretVisible (true);
    txtMapSub->setPopupMenuEnabled (true);
    txtMapSub->setText (TRANS("0"));

    txtMapSub->setBounds (160, 304, 16, 24);

    lblUniPt4.reset (new Label ("lblUniPt4",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt4.get());
    lblUniPt4->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt4->setJustificationType (Justification::centredLeft);
    lblUniPt4->setEditable (false, false, false);
    lblUniPt4->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt4->setBounds (176, 304, 16, 24);

    txtMapInputs.reset (new TextEditor ("txtMapInputs"));
    addAndMakeVisible (txtMapInputs.get());
    txtMapInputs->setMultiLine (false);
    txtMapInputs->setReturnKeyStartsNewLine (false);
    txtMapInputs->setReadOnly (false);
    txtMapInputs->setScrollbarsShown (false);
    txtMapInputs->setCaretVisible (true);
    txtMapInputs->setPopupMenuEnabled (true);
    txtMapInputs->setText (TRANS("8,9,A,B"));

    txtMapInputs->setBounds (192, 304, 56, 24);

    lblUniSlash2.reset (new Label ("lblUniSlash2",
                                   TRANS("/")));
    addAndMakeVisible (lblUniSlash2.get());
    lblUniSlash2->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniSlash2->setJustificationType (Justification::centredLeft);
    lblUniSlash2->setEditable (false, false, false);
    lblUniSlash2->setColour (TextEditor::textColourId, Colours::black);
    lblUniSlash2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniSlash2->setBounds (248, 304, 16, 24);

    txtMapOutputs.reset (new TextEditor ("txtMapOutputs"));
    addAndMakeVisible (txtMapOutputs.get());
    txtMapOutputs->setMultiLine (false);
    txtMapOutputs->setReturnKeyStartsNewLine (false);
    txtMapOutputs->setReadOnly (false);
    txtMapOutputs->setScrollbarsShown (false);
    txtMapOutputs->setCaretVisible (true);
    txtMapOutputs->setPopupMenuEnabled (true);
    txtMapOutputs->setText (TRANS("0,1,2,3"));

    txtMapOutputs->setBounds (264, 304, 56, 24);

    btnChangeUni.reset (new TextButton ("btnChangeUni"));
    addAndMakeVisible (btnChangeUni.get());
    btnChangeUni->setButtonText (TRANS("Ask to Change"));
    btnChangeUni->setConnectedEdges (Button::ConnectedOnLeft);
    btnChangeUni->addListener (this);

    btnChangeUni->setBounds (320, 280, 104, 24);

    btnAddDevice.reset (new TextButton ("btnAddDevice"));
    addAndMakeVisible (btnAddDevice.get());
    btnAddDevice->setButtonText (TRANS("+"));
    btnAddDevice->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnAddDevice->addListener (this);

    btnAddDevice->setBounds (552, 24, 24, 24);

    btnRemoveDevice.reset (new TextButton ("btnRemoveDevice"));
    addAndMakeVisible (btnRemoveDevice.get());
    btnRemoveDevice->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveDevice->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnRemoveDevice->addListener (this);

    btnRemoveDevice->setBounds (576, 24, 24, 24);

    lblMAC.reset (new Label ("lblMAC",
                             TRANS("MAC: 00:00:00:00:00:00 / OEM: 0x0000 / ESTA: 0x4040 (AA)")));
    addAndMakeVisible (lblMAC.get());
    lblMAC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMAC->setJustificationType (Justification::centredLeft);
    lblMAC->setEditable (false, false, false);
    lblMAC->setColour (TextEditor::textColourId, Colours::black);
    lblMAC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMAC->setBounds (176, 232, 424, 24);

    optPollNo.reset (new ToggleButton ("optPollNo"));
    addAndMakeVisible (optPollNo.get());
    optPollNo->setButtonText (TRANS("Don\'t poll network"));
    optPollNo->setRadioGroupId (1);
    optPollNo->addListener (this);

    optPollNo->setBounds (0, 0, 144, 24);

    optPollStatic.reset (new ToggleButton ("optPollStatic"));
    addAndMakeVisible (optPollStatic.get());
    optPollStatic->setButtonText (TRANS("Poll static (2.255.255.255)"));
    optPollStatic->setRadioGroupId (1);
    optPollStatic->addListener (this);

    optPollStatic->setBounds (144, 0, 192, 24);

    optPollDHCP.reset (new ToggleButton ("optPollDHCP"));
    addAndMakeVisible (optPollDHCP.get());
    optPollDHCP->setButtonText (TRANS("Poll DHCP (e.g. 192.168.0.255)"));
    optPollDHCP->setRadioGroupId (1);
    optPollDHCP->addListener (this);
    optPollDHCP->setToggleState (true, dontSendNotification);

    optPollDHCP->setBounds (344, 0, 224, 24);

    txtShortName.reset (new TextEditor ("txtShortName"));
    addAndMakeVisible (txtShortName.get());
    txtShortName->setMultiLine (false);
    txtShortName->setReturnKeyStartsNewLine (false);
    txtShortName->setReadOnly (false);
    txtShortName->setScrollbarsShown (true);
    txtShortName->setCaretVisible (true);
    txtShortName->setPopupMenuEnabled (true);
    txtShortName->setText (TRANS("<Short name>"));

    txtShortName->setBounds (144, 184, 128, 24);

    lblNameSlash.reset (new Label ("lblNameSlash",
                                   TRANS("/")));
    addAndMakeVisible (lblNameSlash.get());
    lblNameSlash->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblNameSlash->setJustificationType (Justification::centredLeft);
    lblNameSlash->setEditable (false, false, false);
    lblNameSlash->setColour (TextEditor::textColourId, Colours::black);
    lblNameSlash->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblNameSlash->setBounds (272, 184, 16, 24);

    txtLongName.reset (new TextEditor ("txtLongName"));
    addAndMakeVisible (txtLongName.get());
    txtLongName->setMultiLine (false);
    txtLongName->setReturnKeyStartsNewLine (false);
    txtLongName->setReadOnly (false);
    txtLongName->setScrollbarsShown (true);
    txtLongName->setCaretVisible (true);
    txtLongName->setPopupMenuEnabled (true);
    txtLongName->setText (TRANS("<Device long name>"));

    txtLongName->setBounds (288, 184, 312, 24);

    lblDeviceExtra.reset (new Label ("new label",
                                     TRANS("F/W: 0x0000 / DMX Seq: 0x01")));
    addAndMakeVisible (lblDeviceExtra.get());
    lblDeviceExtra->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDeviceExtra->setJustificationType (Justification::centredLeft);
    lblDeviceExtra->setEditable (false, false, false);
    lblDeviceExtra->setColour (TextEditor::textColourId, Colours::black);
    lblDeviceExtra->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblDeviceExtra->setBounds (328, 248, 192, 24);

    cachedImage_artnet_logo_png_1 = ImageCache::getFromMemory (artnet_logo_png, artnet_logo_pngSize);

    //[UserPreSize]

    lstDevices.reset(new TextListBox(this));
    addAndMakeVisible(lstDevices.get());
    lstDevices->setFont(Font(Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lstDevices->setBounds(0, 48, 600, 136);

    txtShortName->addListener(this);
    txtLongName->addListener(this);
    txtIP->addListener(this);
    txtUniNet->addListener(this);
    txtUniSub->addListener(this);
    txtUniInputs->addListener(this);
    txtUniOutputs->addListener(this);
    txtMapNet->addListener(this);
    txtMapSub->addListener(this);
    txtMapInputs->addListener(this);
    txtMapOutputs->addListener(this);

    setOpaque(true);

    //[/UserPreSize]

    setSize (600, 330);


    //[Constructor] You can add your own custom stuff here..

    optPollNo    ->setToggleState(ArtNetSystem::GetPollMode() == 0, dontSendNotification);
    optPollStatic->setToggleState(ArtNetSystem::GetPollMode() == 1, dontSendNotification);
    optPollDHCP  ->setToggleState(ArtNetSystem::GetPollMode() == 2, dontSendNotification);
    optPollDHCP  ->setButtonText("Poll DHCP (" + ArtNetSystem::GetDHCPBroadcastAddress().toString() + ")");

    startTimer(100);
    //[/Constructor]
}

ArtNetSetup::~ArtNetSetup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblHeader = nullptr;
    lblDeviceType = nullptr;
    lblDeviceStatus = nullptr;
    lblIP = nullptr;
    txtIP = nullptr;
    btnIP = nullptr;
    lblUniverseHeader = nullptr;
    lblUni = nullptr;
    chkMap = nullptr;
    txtUniNet = nullptr;
    lblUniPt1 = nullptr;
    txtUniSub = nullptr;
    lblUniPt2 = nullptr;
    txtUniInputs = nullptr;
    lblUniSlash1 = nullptr;
    txtUniOutputs = nullptr;
    txtMapNet = nullptr;
    lblUniPt3 = nullptr;
    txtMapSub = nullptr;
    lblUniPt4 = nullptr;
    txtMapInputs = nullptr;
    lblUniSlash2 = nullptr;
    txtMapOutputs = nullptr;
    btnChangeUni = nullptr;
    btnAddDevice = nullptr;
    btnRemoveDevice = nullptr;
    lblMAC = nullptr;
    optPollNo = nullptr;
    optPollStatic = nullptr;
    optPollDHCP = nullptr;
    txtShortName = nullptr;
    lblNameSlash = nullptr;
    txtLongName = nullptr;
    lblDeviceExtra = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    lstDevices = nullptr;

    //[/Destructor]
}

//==============================================================================
void ArtNetSetup::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 520, y = 256, width = 80, height = 72;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        g.drawImageWithin (cachedImage_artnet_logo_png_1,
                           x, y, width, height,
                           RectanglePlacement::centred,
                           false);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ArtNetSetup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ArtNetSetup::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnIP.get())
    {
        //[UserButtonCode_btnIP] -- add your button handler code here..
        ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(lstDevices->getLastRowSelected());
        if(dev == nullptr) return;
        if(dev->mode != ArtNetSystem::ArtNetDevice::Mode::manual) return;
        dev->ip = IPAddress(txtIP->getText());
        //[/UserButtonCode_btnIP]
    }
    else if (buttonThatWasClicked == chkMap.get())
    {
        //[UserButtonCode_chkMap] -- add your button handler code here..
        ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(lstDevices->getLastRowSelected());
        if(dev == nullptr) return;
        dev->map = chkMap->getToggleState();
        txtMapNet->setEnabled(dev->map);
        txtMapSub->setEnabled(dev->map);
        txtMapInputs->setEnabled(dev->map);
        txtMapOutputs->setEnabled(dev->map);
        //[/UserButtonCode_chkMap]
    }
    else if (buttonThatWasClicked == btnChangeUni.get())
    {
        //[UserButtonCode_btnChangeUni] -- add your button handler code here..
        int d = lstDevices->getLastRowSelected();
        if(d < 0 || d >= ArtNetSystem::NumDevices()) return;
        String str = txtUniNet->getText();
        if(!isHex(str)) return;
        int net = str.getHexValue32();
        if(net < 0 || net >= 0x80) return;
        str = txtUniSub->getText();
        if(!isHex(str)) return;
        int subnet = str.getHexValue32();
        if(subnet < 0 || subnet >= 0x10) return;
        uint32_t inuni = ArtNetSystem::ParseUniverseText(txtUniInputs->getText());
        uint32_t outuni = ArtNetSystem::ParseUniverseText(txtUniOutputs->getText());
        if(inuni == 0xFFFFFFFF || outuni == 0xFFFFFFFF) return;
        ArtNetSystem::ChangeDeviceUniverses(d, net, subnet, (uint8_t*)&inuni, (uint8_t*)&outuni);
        //[/UserButtonCode_btnChangeUni]
    }
    else if (buttonThatWasClicked == btnAddDevice.get())
    {
        //[UserButtonCode_btnAddDevice] -- add your button handler code here..
        ArtNetSystem::AddBlankDevice();
        //[/UserButtonCode_btnAddDevice]
    }
    else if (buttonThatWasClicked == btnRemoveDevice.get())
    {
        //[UserButtonCode_btnRemoveDevice] -- add your button handler code here..
        int d = lstDevices->getLastRowSelected();
        if(d < 0 || d >= ArtNetSystem::NumDevices()) return;
        ArtNetSystem::RemoveDevice(d);
        //[/UserButtonCode_btnRemoveDevice]
    }
    else if (buttonThatWasClicked == optPollNo.get())
    {
        //[UserButtonCode_optPollNo] -- add your button handler code here..
        ArtNetSystem::SetPollMode(0);
        //[/UserButtonCode_optPollNo]
    }
    else if (buttonThatWasClicked == optPollStatic.get())
    {
        //[UserButtonCode_optPollStatic] -- add your button handler code here..
        ArtNetSystem::SetPollMode(1);
        //[/UserButtonCode_optPollStatic]
    }
    else if (buttonThatWasClicked == optPollDHCP.get())
    {
        //[UserButtonCode_optPollDHCP] -- add your button handler code here..
        ArtNetSystem::SetPollMode(2);
        //[/UserButtonCode_optPollDHCP]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ArtNetSetup::rowSelected(TextListBox *parent, int row){
    ignoreUnused(row);
    if(parent == lstDevices.get()){
        int r = lstDevices->getLastRowSelected();
        if(r < 0) return;
        ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(r);
        if(dev == nullptr) return;
        txtIP->setText(dev->ip.toString());
        bool manual = dev->mode == ArtNetSystem::ArtNetDevice::Mode::manual;
        txtIP->setEnabled(manual);
        btnIP->setEnabled(manual);
        txtShortName->setEnabled(manual);
        txtLongName->setEnabled(manual);
        chkMap->setToggleState(dev->map, dontSendNotification);
        txtMapNet->setEnabled(dev->map);
        txtMapSub->setEnabled(dev->map);
        txtMapInputs->setEnabled(dev->map);
        txtMapOutputs->setEnabled(dev->map);
        txtMapNet->setText(hex(dev->map_net));
        txtMapSub->setText(hex(dev->map_subnet, 4));
        txtMapInputs->setText(ArtNetSystem::GetUniverseText(&dev->map_inuni[0]));
        txtMapOutputs->setText(ArtNetSystem::GetUniverseText(&dev->map_outuni[0]));
    }
}

void ArtNetSetup::textEditorTextChanged(TextEditor &editorThatWasChanged){
    ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(lstDevices->getLastRowSelected());
    if(dev == nullptr) return;
    TEXTCHANGEDHANDLER_PRE;
    uint32_t unis = ArtNetSystem::ParseUniverseText(text);
    if(&editorThatWasChanged == txtShortName.get()){
        dev->shortname = text;
    }else if(&editorThatWasChanged == txtLongName.get()){
        dev->longname = text;
    }else if(&editorThatWasChanged == txtIP.get()){
        IPAddress ip = ArtNetSystem::ParseIPAddress(text);
        turnRed = ip.isNull();
    }else if(&editorThatWasChanged == txtMapNet.get()){
        if(!ishex || hexval < 0 || hexval >= 0x80){
            turnRed = true;
        }else{
            dev->map_net = hexval;
        }
    }else if(&editorThatWasChanged == txtMapSub.get()){
        if(!ishex || hexval < 0 || hexval >= 0x10){
            turnRed = true;
        }else{
            dev->map_subnet = hexval;
        }
    }else if(&editorThatWasChanged == txtMapInputs.get()){
        if(unis == 0xFFFFFFFF){
            turnRed = true;
        }else{
            *(uint32_t*)&dev->map_inuni[0] = unis;
        }
    }else if(&editorThatWasChanged == txtMapOutputs.get()){
        if(unis == 0xFFFFFFFF){
            turnRed = true;
        }else{
            *(uint32_t*)&dev->map_outuni[0] = unis;
        }
    }else if(&editorThatWasChanged == txtUniNet.get()){
        if(!ishex || hexval < 0 || hexval >= 0x80){
            turnRed = true;
        }
    }else if(&editorThatWasChanged == txtUniSub.get()){
        if(!ishex || hexval < 0 || hexval >= 0x10){
            turnRed = true;
        }
    }else if(&editorThatWasChanged == txtUniInputs.get()){
        if(unis == 0xFFFFFFFF){
            turnRed = true;
        }
    }else if(&editorThatWasChanged == txtUniOutputs.get()){
        if(unis == 0xFFFFFFFF){
            turnRed = true;
        }
    }
    TEXTCHANGEDHANDLER_POST;
}

void ArtNetSetup::timerCallback(){
    int d = lstDevices->getLastRowSelected();
    String oldselection = lstDevices->get(d);
    int i;
    for(i=0; i<ArtNetSystem::NumDevices(); ++i){
        String str = ArtNetSystem::GetDevice(i)->GetTableRow();
        if(lstDevices->getNumRows() <= i) lstDevices->add(str);
        else lstDevices->set(i, str);
    }
    for(; i<lstDevices->getNumRows();){
        lstDevices->remove(i);
    }
    int newrow = lstDevices->indexOf(oldselection);
    if(newrow >= 0 && newrow != d){
        lstDevices->selectRow(newrow);
        d = newrow;
    }
    if(d < 0 || d >= ArtNetSystem::NumDevices()) return;
    ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(d);
    lblDeviceType->setText(dev->GetDescription() + ":", dontSendNotification);
    if(!txtShortName->hasKeyboardFocus(false)){
        txtShortName->setText(dev->shortname, dontSendNotification);
    }
    if(!txtLongName->hasKeyboardFocus(false)){
        txtLongName->setText(dev->longname, dontSendNotification);
    }
    lblDeviceStatus->setText("Status: 0x" + hex(dev->status[0]) + ", 0x" + hex(dev->status[1])
            + " / " + dev->nodereport, dontSendNotification);
    lblMAC->setText("MAC: " + dev->mac.toString(":") + " / OEM: 0x" + hex(dev->oem)
            + " / ESTA: 0x" + hex(dev->esta) + " (" + safeASCII(dev->esta & 0xFF) + safeASCII(dev->esta >> 8) + ")",
            dontSendNotification);
    lblDeviceExtra->setText("F/W: 0x" + hex(dev->fw) + " / DMX Seq: 0x" + hex(dev->artdmx_sequence), dontSendNotification);
    if(!txtUniNet->hasKeyboardFocus(false) && !txtUniSub->hasKeyboardFocus(false)
            && !txtUniInputs->hasKeyboardFocus(false) && !txtUniOutputs->hasKeyboardFocus(false)
            && !btnChangeUni->hasKeyboardFocus(false)){
        txtUniNet->setText(hex(dev->net));
        txtUniSub->setText(hex(dev->subnet, 4));
        txtUniInputs->setText(ArtNetSystem::GetUniverseText(&dev->inuni[0]));
        txtUniOutputs->setText(ArtNetSystem::GetUniverseText(&dev->outuni[0]));
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ArtNetSetup" componentName=""
                 parentClasses="public Component, public TextListBox::Listener, public TextEditor::Listener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="330">
  <BACKGROUND backgroundColour="ff323e44">
    <IMAGE pos="520 256 80 72" resource="artnet_logo_png" opacity="1.0"
           mode="1"/>
  </BACKGROUND>
  <LABEL name="lblHeader" id="7366d591fbb23722" memberName="lblHeader"
         virtualName="" explicitFocusOrder="0" pos="0 24 552 24" edTextCol="ff000000"
         edBkgCol="0" labelText="M S IP Address      BI NT.S.  IN   /  OUT   NAME"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15.0" kerning="0.0"
         bold="0" italic="0" justification="33"/>
  <LABEL name="lblDeviceType" id="c0173b0f81b41697" memberName="lblDeviceType"
         virtualName="" explicitFocusOrder="0" pos="0 184 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Discovered Controller:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="lblDeviceStatus" id="8d04887dd8380ed4" memberName="lblDeviceStatus"
         virtualName="" explicitFocusOrder="0" pos="0 208 600 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Status: 0x00, 0x00 / &lt;Device status text.........................................................................................&gt;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="lblIP" id="f1f0c1e0d38b0a2c" memberName="lblIP" virtualName=""
         explicitFocusOrder="0" pos="0 232 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IP:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtIP" id="793ba136fbe526f2" memberName="txtIP" virtualName=""
              explicitFocusOrder="0" pos="32 232 104 24" initialText="000.000.000.000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnIP" id="590a68f0509ca9d9" memberName="btnIP" virtualName=""
              explicitFocusOrder="0" pos="136 232 32 24" buttonText="Set" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblUniverseHeader" id="f295d9b0d1b31a34" memberName="lblUniverseHeader"
         virtualName="" explicitFocusOrder="0" pos="120 256 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Net   Sub     Inputs        Outputs"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="lblUni" id="86c1ebc7b4aea96d" memberName="lblUni" virtualName=""
         explicitFocusOrder="0" pos="0 280 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Device universes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="c07831b30c342dbc" memberName="chkMap"
                virtualName="" explicitFocusOrder="0" pos="0 304 120 24" buttonText="Map from uni:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="txtUniNet" id="c7845550147bcdf8" memberName="txtUniNet"
              virtualName="" explicitFocusOrder="0" pos="120 280 24 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt1" id="58d603994d4c6271" memberName="lblUniPt1"
         virtualName="" explicitFocusOrder="0" pos="144 280 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniSub" id="bd208cff56ac9065" memberName="txtUniSub"
              virtualName="" explicitFocusOrder="0" pos="160 280 16 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt1" id="6354456708acfc6a" memberName="lblUniPt2"
         virtualName="" explicitFocusOrder="0" pos="176 280 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniInputs" id="a4dbf1f8ebda57e8" memberName="txtUniInputs"
              virtualName="" explicitFocusOrder="0" pos="192 280 56 24" initialText="8,9,A,B"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniSlash1" id="b559a0b72688537" memberName="lblUniSlash1"
         virtualName="" explicitFocusOrder="0" pos="248 280 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniOutputs" id="c8e7697cf4782629" memberName="txtUniOutputs"
              virtualName="" explicitFocusOrder="0" pos="264 280 56 24" initialText="0,1,2,3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtMapNet" id="9ba3c0ed36d5af56" memberName="txtMapNet"
              virtualName="" explicitFocusOrder="0" pos="120 304 24 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt3" id="f3be54f9b57e22a3" memberName="lblUniPt3"
         virtualName="" explicitFocusOrder="0" pos="144 304 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapSub" id="b6cf960763fda67f" memberName="txtMapSub"
              virtualName="" explicitFocusOrder="0" pos="160 304 16 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt4" id="d043c68ab6557487" memberName="lblUniPt4"
         virtualName="" explicitFocusOrder="0" pos="176 304 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapInputs" id="202c159d9d5303e3" memberName="txtMapInputs"
              virtualName="" explicitFocusOrder="0" pos="192 304 56 24" initialText="8,9,A,B"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniSlash2" id="f4f2d75537f7f359" memberName="lblUniSlash2"
         virtualName="" explicitFocusOrder="0" pos="248 304 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapOutputs" id="cf35c4119449d4d0" memberName="txtMapOutputs"
              virtualName="" explicitFocusOrder="0" pos="264 304 56 24" initialText="0,1,2,3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnChangeUni" id="5ea00af7a01ee815" memberName="btnChangeUni"
              virtualName="" explicitFocusOrder="0" pos="320 280 104 24" buttonText="Ask to Change"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnAddDevice" id="7ceb28d89a1747a0" memberName="btnAddDevice"
              virtualName="" explicitFocusOrder="0" pos="552 24 24 24" buttonText="+"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveDevice" id="506bcac0d99da01e" memberName="btnRemoveDevice"
              virtualName="" explicitFocusOrder="0" pos="576 24 24 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblMAC" id="6a5bac3590aa317b" memberName="lblMAC" virtualName=""
         explicitFocusOrder="0" pos="176 232 424 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MAC: 00:00:00:00:00:00 / OEM: 0x0000 / ESTA: 0x4040 (AA)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <TOGGLEBUTTON name="optPollNo" id="4986d64c796f9a9c" memberName="optPollNo"
                virtualName="" explicitFocusOrder="0" pos="0 0 144 24" buttonText="Don't poll network"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="optPollStatic" id="a13d783268b49e41" memberName="optPollStatic"
                virtualName="" explicitFocusOrder="0" pos="144 0 192 24" buttonText="Poll static (2.255.255.255)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="optPollDHCP" id="c2a3097ed3026cfd" memberName="optPollDHCP"
                virtualName="" explicitFocusOrder="0" pos="344 0 224 24" buttonText="Poll DHCP (e.g. 192.168.0.255)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TEXTEDITOR name="txtShortName" id="e27c307a48a2ff07" memberName="txtShortName"
              virtualName="" explicitFocusOrder="0" pos="144 184 128 24" initialText="&lt;Short name&gt;"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="lblNameSlash" id="e73e84dd3767c47c" memberName="lblNameSlash"
         virtualName="" explicitFocusOrder="0" pos="272 184 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtLongName" id="9a9ab3d2248ee071" memberName="txtLongName"
              virtualName="" explicitFocusOrder="0" pos="288 184 312 24" initialText="&lt;Device long name&gt;"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="18c8ab8509175c58" memberName="lblDeviceExtra"
         virtualName="" explicitFocusOrder="0" pos="328 248 192 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F/W: 0x0000 / DMX Seq: 0x01" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: artnet_logo_png, 1613, "../../data/art-net_logo.png"
static const unsigned char resource_ArtNetSetup_artnet_logo_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,200,0,0,0,178,1,3,0,0,1,74,40,34,236,0,0,0,4,103,65,77,65,0,0,177,143,11,252,97,
5,0,0,0,6,80,76,84,69,15,95,85,0,0,0,18,161,172,144,0,0,0,1,116,82,78,83,0,64,230,216,102,0,0,0,1,98,75,71,68,0,136,5,29,72,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,7,116,73,77,
69,7,227,6,21,6,11,14,180,66,25,255,0,0,5,176,73,68,65,84,88,195,173,152,193,107,29,69,24,192,191,205,134,157,34,143,204,107,245,176,150,144,109,131,127,192,214,83,14,143,110,34,21,123,16,244,40,130,240,
136,23,143,233,45,96,200,110,210,162,30,10,201,193,131,224,193,127,161,127,128,224,36,21,26,161,88,143,10,130,219,122,168,39,157,90,161,91,92,118,252,190,153,217,247,102,146,29,237,193,13,153,239,253,
222,111,118,230,155,217,153,121,47,1,0,85,193,40,193,226,149,133,115,0,23,168,88,77,176,40,206,97,177,177,136,197,250,62,22,0,88,136,119,126,3,168,175,227,171,31,168,248,145,138,251,84,124,75,226,152,
94,221,165,226,232,132,42,159,244,119,124,240,254,14,192,91,239,93,7,120,243,221,143,168,41,236,45,189,70,93,190,129,85,94,163,98,245,26,22,187,116,239,198,219,88,236,93,155,119,121,98,187,188,67,197,
33,21,159,81,113,155,196,39,244,106,159,138,61,93,80,151,213,3,20,242,167,109,180,95,174,99,3,223,77,1,162,58,147,74,9,136,46,141,71,32,0,22,242,113,66,49,73,13,143,70,231,37,197,52,25,79,41,230,241,56,
167,56,141,14,181,151,144,171,6,99,3,185,32,254,221,198,199,54,62,20,38,214,83,83,175,94,179,60,178,145,217,24,221,49,17,164,174,55,187,86,23,54,46,85,58,222,212,145,38,137,242,21,133,201,123,154,175,
81,140,167,121,26,81,254,151,242,17,197,36,247,227,40,205,151,109,92,163,152,142,174,72,138,89,123,69,80,204,147,188,143,83,138,211,56,207,109,212,245,215,99,211,62,93,145,206,243,134,122,174,199,111,
98,3,55,244,253,63,159,138,223,219,120,207,198,187,149,137,71,125,20,38,138,218,180,35,182,108,204,237,251,107,54,46,219,184,100,99,98,35,179,49,126,98,98,100,35,60,49,237,216,216,95,234,214,179,195,143,
145,247,23,111,165,184,6,224,209,228,241,231,91,160,249,2,241,159,139,127,29,110,235,65,74,96,170,197,185,86,74,2,196,13,146,170,44,177,175,129,65,92,83,29,188,248,10,18,78,132,161,21,238,210,132,85,14,
109,199,194,33,25,213,78,43,248,224,25,195,149,175,41,194,110,88,212,130,161,88,169,134,225,12,27,98,21,182,10,19,75,28,123,100,144,89,90,193,55,24,213,208,132,117,216,167,179,30,112,84,241,189,121,239,
253,165,73,225,111,134,157,170,35,105,54,161,75,53,145,180,53,159,75,151,154,214,163,171,30,101,149,75,76,184,20,75,151,240,103,222,95,3,187,30,101,149,166,61,67,92,184,247,197,210,165,168,113,9,118,61,
42,60,226,191,184,20,43,151,34,229,244,14,80,206,200,191,202,242,36,45,179,135,11,217,31,84,107,125,241,92,186,158,94,62,78,129,54,233,206,34,111,118,210,203,171,153,38,237,94,221,187,152,206,41,221,72,
12,245,79,161,95,103,18,184,106,60,234,122,98,56,122,156,7,135,128,31,245,52,65,138,5,221,65,139,130,40,234,87,214,210,178,75,43,43,180,102,250,85,176,188,228,210,132,135,105,155,85,167,41,154,173,228,
88,56,61,104,98,179,117,29,213,28,50,97,215,53,209,124,149,11,168,121,172,230,171,92,242,184,117,9,155,180,107,30,119,0,7,57,223,1,219,124,182,31,184,206,116,199,163,201,124,63,224,126,92,241,168,223,
43,88,135,227,8,43,151,250,157,179,134,157,28,208,124,246,59,135,168,118,105,54,90,111,31,249,132,99,129,98,182,118,59,143,148,79,213,89,234,71,251,76,120,84,187,244,84,186,244,164,113,73,250,228,237,
84,185,235,81,225,81,230,147,187,139,37,247,118,49,62,100,119,79,123,20,121,59,60,178,59,220,238,226,214,163,29,143,174,122,84,120,68,103,193,124,167,250,103,1,243,169,126,225,115,194,167,246,133,207,
144,204,63,81,190,10,159,47,76,253,215,105,179,55,72,224,83,57,163,127,187,84,249,197,88,101,199,11,217,3,189,234,52,253,106,169,26,165,99,49,254,112,127,28,85,51,218,60,54,212,140,50,217,140,55,55,179,
57,101,143,94,207,230,53,95,94,184,232,220,119,126,255,37,183,149,227,196,144,66,82,227,205,36,59,178,167,91,220,233,195,82,169,206,158,114,250,2,189,169,173,81,205,41,195,105,7,104,163,78,153,76,209,
103,121,73,85,106,223,20,7,181,49,80,52,190,41,185,180,134,181,58,35,213,79,85,199,26,107,76,150,51,19,117,116,16,105,19,41,207,196,109,212,89,3,167,76,163,223,40,237,215,88,199,48,9,101,101,77,233,25,
94,67,33,6,91,195,19,51,27,54,69,69,183,153,220,252,172,105,90,228,224,72,149,254,188,176,179,227,26,106,129,134,90,210,116,215,174,209,39,113,71,38,83,122,56,51,163,39,77,145,225,170,5,215,112,61,231,
21,26,51,159,115,147,105,35,208,68,202,55,133,54,181,206,160,242,13,33,14,8,77,81,123,166,180,105,216,1,59,166,179,79,162,236,167,160,55,118,170,90,50,230,117,111,244,147,166,247,202,254,193,245,70,15,
148,134,74,166,20,142,177,189,150,21,153,76,58,38,51,153,22,130,12,119,231,186,16,182,194,153,245,102,199,205,229,192,122,59,115,89,163,236,49,192,58,250,168,212,147,219,155,214,26,213,155,186,55,42,108,
170,160,169,131,70,206,141,159,219,55,109,200,28,116,33,115,211,164,48,96,246,244,158,31,50,85,41,67,102,182,204,207,24,222,133,12,83,33,19,233,20,134,140,121,16,3,70,152,157,54,104,178,46,100,116,10,
131,38,166,20,6,141,254,134,30,159,125,62,116,124,52,33,147,181,33,195,85,200,196,56,220,225,12,40,133,128,193,71,20,48,152,66,192,240,46,100,48,133,128,137,116,170,67,6,83,8,153,162,13,25,222,133,12,
195,165,58,108,34,117,55,96,64,61,13,153,226,239,144,193,51,51,96,152,26,124,62,230,107,115,192,64,216,148,103,204,255,123,149,170,80,15,69,92,149,42,166,63,100,71,88,218,3,103,10,176,21,161,217,130,184,
90,102,98,20,87,96,255,201,224,153,164,14,154,53,199,148,53,26,108,185,172,227,106,146,44,97,63,3,247,168,38,97,183,7,91,187,41,146,232,254,112,63,117,2,59,78,63,157,49,56,158,106,59,129,9,182,217,27,
53,55,43,137,30,169,49,255,0,59,214,58,186,40,212,165,40,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ArtNetSetup::artnet_logo_png = (const char*) resource_ArtNetSetup_artnet_logo_png;
const int ArtNetSetup::artnet_logo_pngSize = 1613;


//[EndFile] You can add extra defines here...
//[/EndFile]
