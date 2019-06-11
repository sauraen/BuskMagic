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

    chkPoll.reset (new ToggleButton ("chkPoll"));
    addAndMakeVisible (chkPoll.get());
    chkPoll->setButtonText (TRANS("Poll network"));
    chkPoll->addListener (this);
    chkPoll->setToggleState (true, dontSendNotification);

    chkPoll->setBounds (0, 0, 112, 24);

    lblHeader.reset (new Label ("lblHeader",
                                TRANS("M S IP Address     BI NT.S.  IN   /  OUT   NAME")));
    addAndMakeVisible (lblHeader.get());
    lblHeader->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblHeader->setJustificationType (Justification::centredLeft);
    lblHeader->setEditable (false, false, false);
    lblHeader->setColour (TextEditor::textColourId, Colours::black);
    lblHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblHeader->setBounds (0, 24, 360, 24);

    lblInfo1.reset (new Label ("lblInfo1",
                               TRANS("Discovered Node: Long Name\n"
                               "Device status/diagnostic message")));
    addAndMakeVisible (lblInfo1.get());
    lblInfo1->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblInfo1->setJustificationType (Justification::topLeft);
    lblInfo1->setEditable (false, false, false);
    lblInfo1->setColour (TextEditor::textColourId, Colours::black);
    lblInfo1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblInfo1->setBounds (0, 184, 600, 40);

    lblInfo2.reset (new Label ("lblInfo2",
                               TRANS("OEM: 0x0000\n"
                               "ESTA: 0x4040 (AA)\n"
                               "F/W: 0x0000\n"
                               "Status: 0x00, 0x00\n"
                               "DMX Seq: 0x01")));
    addAndMakeVisible (lblInfo2.get());
    lblInfo2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblInfo2->setJustificationType (Justification::centredLeft);
    lblInfo2->setEditable (false, false, false);
    lblInfo2->setColour (TextEditor::textColourId, Colours::black);
    lblInfo2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblInfo2->setBounds (448, 224, 152, 96);

    lblIP.reset (new Label ("lblIP",
                            TRANS("IP:")));
    addAndMakeVisible (lblIP.get());
    lblIP->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblIP->setJustificationType (Justification::centredLeft);
    lblIP->setEditable (false, false, false);
    lblIP->setColour (TextEditor::textColourId, Colours::black);
    lblIP->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblIP->setBounds (0, 224, 32, 24);

    txtIP.reset (new TextEditor ("txtIP"));
    addAndMakeVisible (txtIP.get());
    txtIP->setMultiLine (false);
    txtIP->setReturnKeyStartsNewLine (false);
    txtIP->setReadOnly (false);
    txtIP->setScrollbarsShown (true);
    txtIP->setCaretVisible (true);
    txtIP->setPopupMenuEnabled (true);
    txtIP->setText (TRANS("000.000.000.000"));

    txtIP->setBounds (32, 224, 104, 24);

    btnIP.reset (new TextButton ("btnIP"));
    addAndMakeVisible (btnIP.get());
    btnIP->setButtonText (TRANS("Set"));
    btnIP->setConnectedEdges (Button::ConnectedOnLeft);
    btnIP->addListener (this);

    btnIP->setBounds (136, 224, 32, 24);

    lblUniverseHeader.reset (new Label ("lblUniverseHeader",
                                        TRANS("Net   Sub     Inputs        Outputs")));
    addAndMakeVisible (lblUniverseHeader.get());
    lblUniverseHeader->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUniverseHeader->setJustificationType (Justification::centredLeft);
    lblUniverseHeader->setEditable (false, false, false);
    lblUniverseHeader->setColour (TextEditor::textColourId, Colours::black);
    lblUniverseHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniverseHeader->setBounds (120, 248, 200, 24);

    lblUni.reset (new Label ("lblUni",
                             TRANS("Device universes:")));
    addAndMakeVisible (lblUni.get());
    lblUni->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblUni->setJustificationType (Justification::centredLeft);
    lblUni->setEditable (false, false, false);
    lblUni->setColour (TextEditor::textColourId, Colours::black);
    lblUni->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUni->setBounds (0, 272, 120, 24);

    chkMap.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkMap.get());
    chkMap->setButtonText (TRANS("Map from uni:"));
    chkMap->addListener (this);

    chkMap->setBounds (0, 296, 120, 24);

    txtUniNet.reset (new TextEditor ("txtUniNet"));
    addAndMakeVisible (txtUniNet.get());
    txtUniNet->setMultiLine (false);
    txtUniNet->setReturnKeyStartsNewLine (false);
    txtUniNet->setReadOnly (false);
    txtUniNet->setScrollbarsShown (false);
    txtUniNet->setCaretVisible (true);
    txtUniNet->setPopupMenuEnabled (true);
    txtUniNet->setText (TRANS("00"));

    txtUniNet->setBounds (120, 272, 24, 24);

    lblUniPt1.reset (new Label ("lblUniPt1",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt1.get());
    lblUniPt1->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt1->setJustificationType (Justification::centredLeft);
    lblUniPt1->setEditable (false, false, false);
    lblUniPt1->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt1->setBounds (144, 272, 16, 24);

    txtUniSub.reset (new TextEditor ("txtUniSub"));
    addAndMakeVisible (txtUniSub.get());
    txtUniSub->setMultiLine (false);
    txtUniSub->setReturnKeyStartsNewLine (false);
    txtUniSub->setReadOnly (false);
    txtUniSub->setScrollbarsShown (false);
    txtUniSub->setCaretVisible (true);
    txtUniSub->setPopupMenuEnabled (true);
    txtUniSub->setText (TRANS("0"));

    txtUniSub->setBounds (160, 272, 16, 24);

    lblUniPt2.reset (new Label ("lblUniPt1",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt2.get());
    lblUniPt2->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt2->setJustificationType (Justification::centredLeft);
    lblUniPt2->setEditable (false, false, false);
    lblUniPt2->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt2->setBounds (176, 272, 16, 24);

    txtUniInputs.reset (new TextEditor ("txtUniInputs"));
    addAndMakeVisible (txtUniInputs.get());
    txtUniInputs->setMultiLine (false);
    txtUniInputs->setReturnKeyStartsNewLine (false);
    txtUniInputs->setReadOnly (false);
    txtUniInputs->setScrollbarsShown (false);
    txtUniInputs->setCaretVisible (true);
    txtUniInputs->setPopupMenuEnabled (true);
    txtUniInputs->setText (TRANS("8,9,A,B"));

    txtUniInputs->setBounds (192, 272, 56, 24);

    lblUniSlash1.reset (new Label ("lblUniSlash1",
                                   TRANS("/")));
    addAndMakeVisible (lblUniSlash1.get());
    lblUniSlash1->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniSlash1->setJustificationType (Justification::centredLeft);
    lblUniSlash1->setEditable (false, false, false);
    lblUniSlash1->setColour (TextEditor::textColourId, Colours::black);
    lblUniSlash1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniSlash1->setBounds (248, 272, 16, 24);

    txtUniOutputs.reset (new TextEditor ("txtUniOutputs"));
    addAndMakeVisible (txtUniOutputs.get());
    txtUniOutputs->setMultiLine (false);
    txtUniOutputs->setReturnKeyStartsNewLine (false);
    txtUniOutputs->setReadOnly (false);
    txtUniOutputs->setScrollbarsShown (false);
    txtUniOutputs->setCaretVisible (true);
    txtUniOutputs->setPopupMenuEnabled (true);
    txtUniOutputs->setText (TRANS("0,1,2,3"));

    txtUniOutputs->setBounds (264, 272, 56, 24);

    txtMapNet.reset (new TextEditor ("txtMapNet"));
    addAndMakeVisible (txtMapNet.get());
    txtMapNet->setMultiLine (false);
    txtMapNet->setReturnKeyStartsNewLine (false);
    txtMapNet->setReadOnly (false);
    txtMapNet->setScrollbarsShown (false);
    txtMapNet->setCaretVisible (true);
    txtMapNet->setPopupMenuEnabled (true);
    txtMapNet->setText (TRANS("00"));

    txtMapNet->setBounds (120, 296, 24, 24);

    lblUniPt3.reset (new Label ("lblUniPt3",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt3.get());
    lblUniPt3->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt3->setJustificationType (Justification::centredLeft);
    lblUniPt3->setEditable (false, false, false);
    lblUniPt3->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt3->setBounds (144, 296, 16, 24);

    txtMapSub.reset (new TextEditor ("txtMapSub"));
    addAndMakeVisible (txtMapSub.get());
    txtMapSub->setMultiLine (false);
    txtMapSub->setReturnKeyStartsNewLine (false);
    txtMapSub->setReadOnly (false);
    txtMapSub->setScrollbarsShown (false);
    txtMapSub->setCaretVisible (true);
    txtMapSub->setPopupMenuEnabled (true);
    txtMapSub->setText (TRANS("0"));

    txtMapSub->setBounds (160, 296, 16, 24);

    lblUniPt4.reset (new Label ("lblUniPt4",
                                TRANS(".")));
    addAndMakeVisible (lblUniPt4.get());
    lblUniPt4->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniPt4->setJustificationType (Justification::centredLeft);
    lblUniPt4->setEditable (false, false, false);
    lblUniPt4->setColour (TextEditor::textColourId, Colours::black);
    lblUniPt4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniPt4->setBounds (176, 296, 16, 24);

    txtMapInputs.reset (new TextEditor ("txtMapInputs"));
    addAndMakeVisible (txtMapInputs.get());
    txtMapInputs->setMultiLine (false);
    txtMapInputs->setReturnKeyStartsNewLine (false);
    txtMapInputs->setReadOnly (false);
    txtMapInputs->setScrollbarsShown (false);
    txtMapInputs->setCaretVisible (true);
    txtMapInputs->setPopupMenuEnabled (true);
    txtMapInputs->setText (TRANS("8,9,A,B"));

    txtMapInputs->setBounds (192, 296, 56, 24);

    lblUniSlash2.reset (new Label ("lblUniSlash2",
                                   TRANS("/")));
    addAndMakeVisible (lblUniSlash2.get());
    lblUniSlash2->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    lblUniSlash2->setJustificationType (Justification::centredLeft);
    lblUniSlash2->setEditable (false, false, false);
    lblUniSlash2->setColour (TextEditor::textColourId, Colours::black);
    lblUniSlash2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblUniSlash2->setBounds (248, 296, 16, 24);

    txtMapOutputs.reset (new TextEditor ("txtMapOutputs"));
    addAndMakeVisible (txtMapOutputs.get());
    txtMapOutputs->setMultiLine (false);
    txtMapOutputs->setReturnKeyStartsNewLine (false);
    txtMapOutputs->setReadOnly (false);
    txtMapOutputs->setScrollbarsShown (false);
    txtMapOutputs->setCaretVisible (true);
    txtMapOutputs->setPopupMenuEnabled (true);
    txtMapOutputs->setText (TRANS("0,1,2,3"));

    txtMapOutputs->setBounds (264, 296, 56, 24);

    btnChangeUni.reset (new TextButton ("btnChangeUni"));
    addAndMakeVisible (btnChangeUni.get());
    btnChangeUni->setButtonText (TRANS("Ask to Change"));
    btnChangeUni->setConnectedEdges (Button::ConnectedOnLeft);
    btnChangeUni->addListener (this);

    btnChangeUni->setBounds (320, 272, 104, 24);

    btnAddDevice.reset (new TextButton ("btnAddDevice"));
    addAndMakeVisible (btnAddDevice.get());
    btnAddDevice->setButtonText (TRANS("+"));
    btnAddDevice->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnAddDevice->addListener (this);

    btnAddDevice->setBounds (552, 24, 23, 24);

    btnRemoveDevice.reset (new TextButton ("btnRemoveDevice"));
    addAndMakeVisible (btnRemoveDevice.get());
    btnRemoveDevice->setButtonText (CharPointer_UTF8 ("\xe2\x88\x92"));
    btnRemoveDevice->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnRemoveDevice->addListener (this);

    btnRemoveDevice->setBounds (576, 24, 23, 24);

    lblMAC.reset (new Label ("lblMAC",
                             TRANS("MAC: 00:00:00:00:00:00")));
    addAndMakeVisible (lblMAC.get());
    lblMAC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMAC->setJustificationType (Justification::centredLeft);
    lblMAC->setEditable (false, false, false);
    lblMAC->setColour (TextEditor::textColourId, Colours::black);
    lblMAC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMAC->setBounds (176, 224, 168, 24);


    //[UserPreSize]

    lsmDevices.reset(new TextListModel());
    lsmDevices->setListener(this);
    lsmDevices->setFont(Font(Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));
    lstDevices.reset(new ListBox("Devices", lsmDevices.get()));
    addAndMakeVisible(lstDevices.get());
    lstDevices->setMultipleSelectionEnabled(false);
    lstDevices->setRowHeight(16);
    lstDevices->setOutlineThickness(1);
    lstDevices->setColour(ListBox::outlineColourId, Colours::lightgrey);

    txtUniNet->addListener(this);
    txtUniSub->addListener(this);
    txtUniInputs->addListener(this);
    txtUniOutputs->addListener(this);
    txtMapNet->addListener(this);
    txtMapSub->addListener(this);
    txtMapInputs->addListener(this);
    txtMapOutputs->addListener(this);

    //[/UserPreSize]

    setSize (600, 322);


    //[Constructor] You can add your own custom stuff here..
    ArtNetSystem::Init(); //TODO move this to main
    
    chkPoll->setToggleState(ArtNetSystem::IsPolling(), dontSendNotification);

    startTimer(100);
    //[/Constructor]
}

ArtNetSetup::~ArtNetSetup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chkPoll = nullptr;
    lblHeader = nullptr;
    lblInfo1 = nullptr;
    lblInfo2 = nullptr;
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


    //[Destructor]. You can add your own custom destruction code here..
    lstDevices = nullptr;
    lsmDevices = nullptr;
    
    ArtNetSystem::Finalize();
    //[/Destructor]
}

//==============================================================================
void ArtNetSetup::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ArtNetSetup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    lstDevices->setBounds(0, 48, 600, 136);
    //[/UserResized]
}

void ArtNetSetup::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == chkPoll.get())
    {
        //[UserButtonCode_chkPoll] -- add your button handler code here..
        ArtNetSystem::EnablePolling(chkPoll->getToggleState());
        //[/UserButtonCode_chkPoll]
    }
    else if (buttonThatWasClicked == btnIP.get())
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ArtNetSetup::rowSelected(TextListModel *parent, int row){
    if(parent == lsmDevices.get()){
        ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(lstDevices->getLastRowSelected());
        if(dev == nullptr) return;
        txtIP->setText(dev->ip.toString());
        bool ipChangeEnabled = dev->mode == ArtNetSystem::ArtNetDevice::Mode::manual;
        txtIP->setEnabled(ipChangeEnabled);
        btnIP->setEnabled(ipChangeEnabled);
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
    String text = editorThatWasChanged.getText();
    bool isint = isInt(text);
    int val = text.getIntValue();
    bool ishex = isHex(text);
    int hexval = text.getHexValue32();
    uint32_t unis = ArtNetSystem::ParseUniverseText(text);
    bool turnRed = false;
    if(&editorThatWasChanged == txtMapNet.get()){
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
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::darkgrey);
    }
}

void ArtNetSetup::timerCallback(){
    bool updateList = lsmDevices->getNumRows() != ArtNetSystem::NumDevices();
    int d = lstDevices->getLastRowSelected();
    int i;
    for(i=0; i<ArtNetSystem::NumDevices(); ++i){
        String str = ArtNetSystem::GetDevice(i)->GetTableRow();
        if(lsmDevices->getNumRows() <= i) lsmDevices->add(str);
        else lsmDevices->set(i, str);
        lstDevices->repaintRow(i);
    }
    for(; i<lsmDevices->getNumRows();){
        lsmDevices->remove(i);
    }
    if(updateList){
        lstDevices->updateContent();
        if(d < ArtNetSystem::NumDevices()) lstDevices->selectRow(d);
    }
    if(d < 0 || d >= ArtNetSystem::NumDevices()) return;
    ArtNetSystem::ArtNetDevice *dev = ArtNetSystem::GetDevice(d);
    lblInfo1->setText(dev->GetLongDescription() + "\n" + dev->nodereport, dontSendNotification);
    lblInfo2->setText("OEM: 0x" + hex(dev->oem) + "\n"
                    + "ESTA: 0x" + hex(dev->esta) + " (" + safeASCII(dev->esta & 0xFF) + safeASCII(dev->esta >> 8) + ")\n"
                    + "F/W: 0x" + hex(dev->fw) + "\n"
                    + "Status: 0x" + hex(dev->status[0]) + ", 0x" + hex(dev->status[1]) + "\n"
                    + "DMX Seq: 0x" + hex(dev->artdmx_sequence), dontSendNotification);
    lblMAC->setText(dev->mac.toString(":"), dontSendNotification);
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
                 parentClasses="public Component, public TextListModel::Listener, public TextEditor::Listener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="322">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TOGGLEBUTTON name="chkPoll" id="7da47f7a98100feb" memberName="chkPoll" virtualName=""
                explicitFocusOrder="0" pos="0 0 112 24" buttonText="Poll network"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="lblHeader" id="7366d591fbb23722" memberName="lblHeader"
         virtualName="" explicitFocusOrder="0" pos="0 24 360 24" edTextCol="ff000000"
         edBkgCol="0" labelText="M S IP Address     BI NT.S.  IN   /  OUT   NAME"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15.0" kerning="0.0"
         bold="0" italic="0" justification="33"/>
  <LABEL name="lblInfo1" id="c0173b0f81b41697" memberName="lblInfo1" virtualName=""
         explicitFocusOrder="0" pos="0 184 600 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Discovered Node: Long Name&#10;Device status/diagnostic message"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="9"/>
  <LABEL name="lblInfo2" id="8d04887dd8380ed4" memberName="lblInfo2" virtualName=""
         explicitFocusOrder="0" pos="448 224 152 96" edTextCol="ff000000"
         edBkgCol="0" labelText="OEM: 0x0000&#10;ESTA: 0x4040 (AA)&#10;F/W: 0x0000&#10;Status: 0x00, 0x00&#10;DMX Seq: 0x01"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="lblIP" id="f1f0c1e0d38b0a2c" memberName="lblIP" virtualName=""
         explicitFocusOrder="0" pos="0 224 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IP:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtIP" id="793ba136fbe526f2" memberName="txtIP" virtualName=""
              explicitFocusOrder="0" pos="32 224 104 24" initialText="000.000.000.000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnIP" id="590a68f0509ca9d9" memberName="btnIP" virtualName=""
              explicitFocusOrder="0" pos="136 224 32 24" buttonText="Set" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblUniverseHeader" id="f295d9b0d1b31a34" memberName="lblUniverseHeader"
         virtualName="" explicitFocusOrder="0" pos="120 248 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Net   Sub     Inputs        Outputs"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="lblUni" id="86c1ebc7b4aea96d" memberName="lblUni" virtualName=""
         explicitFocusOrder="0" pos="0 272 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Device universes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="c07831b30c342dbc" memberName="chkMap"
                virtualName="" explicitFocusOrder="0" pos="0 296 120 24" buttonText="Map from uni:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="txtUniNet" id="c7845550147bcdf8" memberName="txtUniNet"
              virtualName="" explicitFocusOrder="0" pos="120 272 24 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt1" id="58d603994d4c6271" memberName="lblUniPt1"
         virtualName="" explicitFocusOrder="0" pos="144 272 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniSub" id="bd208cff56ac9065" memberName="txtUniSub"
              virtualName="" explicitFocusOrder="0" pos="160 272 16 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt1" id="6354456708acfc6a" memberName="lblUniPt2"
         virtualName="" explicitFocusOrder="0" pos="176 272 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniInputs" id="a4dbf1f8ebda57e8" memberName="txtUniInputs"
              virtualName="" explicitFocusOrder="0" pos="192 272 56 24" initialText="8,9,A,B"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniSlash1" id="b559a0b72688537" memberName="lblUniSlash1"
         virtualName="" explicitFocusOrder="0" pos="248 272 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtUniOutputs" id="c8e7697cf4782629" memberName="txtUniOutputs"
              virtualName="" explicitFocusOrder="0" pos="264 272 56 24" initialText="0,1,2,3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="txtMapNet" id="9ba3c0ed36d5af56" memberName="txtMapNet"
              virtualName="" explicitFocusOrder="0" pos="120 296 24 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt3" id="f3be54f9b57e22a3" memberName="lblUniPt3"
         virtualName="" explicitFocusOrder="0" pos="144 296 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapSub" id="b6cf960763fda67f" memberName="txtMapSub"
              virtualName="" explicitFocusOrder="0" pos="160 296 16 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniPt4" id="d043c68ab6557487" memberName="lblUniPt4"
         virtualName="" explicitFocusOrder="0" pos="176 296 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="." editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapInputs" id="202c159d9d5303e3" memberName="txtMapInputs"
              virtualName="" explicitFocusOrder="0" pos="192 296 56 24" initialText="8,9,A,B"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="lblUniSlash2" id="f4f2d75537f7f359" memberName="lblUniSlash2"
         virtualName="" explicitFocusOrder="0" pos="248 296 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtMapOutputs" id="cf35c4119449d4d0" memberName="txtMapOutputs"
              virtualName="" explicitFocusOrder="0" pos="264 296 56 24" initialText="0,1,2,3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="btnChangeUni" id="5ea00af7a01ee815" memberName="btnChangeUni"
              virtualName="" explicitFocusOrder="0" pos="320 272 104 24" buttonText="Ask to Change"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnAddDevice" id="7ceb28d89a1747a0" memberName="btnAddDevice"
              virtualName="" explicitFocusOrder="0" pos="552 24 23 24" buttonText="+"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="btnRemoveDevice" id="506bcac0d99da01e" memberName="btnRemoveDevice"
              virtualName="" explicitFocusOrder="0" pos="576 24 23 24" buttonText="&#8722;"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <LABEL name="lblMAC" id="6a5bac3590aa317b" memberName="lblMAC" virtualName=""
         explicitFocusOrder="0" pos="176 224 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MAC: 00:00:00:00:00:00" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

