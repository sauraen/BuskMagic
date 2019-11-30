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

#include "MainWindow.h"

#include "gui/ArtNetSetup.h"
#include "gui/USBDMXSetup.h"
#include "gui/MIDISetup.h"
#include "gui/Patcher.h"
#include "gui/ControllerWindow.h"
#include "gui/StatesWindow.h"
#include "gui/TimingWindow.h"

#include "ArtNetSystem.h"
#include "ChannelSystem.h"
#include "ControllerSystem.h"
#include "FixtureSystem.h"
#include "LightingSystem.h"
#include "MIDISystem.h"
#include "TimingSystem.h"
#include "USBDMXSystem.h"

static Image *app_icon = nullptr;

class SubWindow : public Component {
public:
    SubWindow(String name, bool resizable, Component *ownedcontents) : Component(name){
        //Normal setup
        setVisible(false);
        contents.reset(ownedcontents);
        addAndMakeVisible(contents.get());
        setSize(contents->getWidth(), contents->getHeight());
        //Setup for peer
        setOpaque(true);
        addToDesktop(ComponentPeer::windowHasTitleBar | 
            (resizable ? (ComponentPeer::windowIsResizable 
                | ComponentPeer::windowHasMaximiseButton) : 0)
            | ComponentPeer::windowHasCloseButton 
            | ComponentPeer::windowHasDropShadow);
        //Peer
        ComponentPeer *peer = getPeer();
        peer->setVisible(false);
        peer->setTitle(name);
        peer->setIcon(*app_icon);
    }
    ~SubWindow() {
        contents = nullptr;
    }
    void paint(Graphics &g) override {
        g.fillAll(LFWindowColor());
    }
    void userTriedToCloseWindow() override {
        getPeer()->setVisible(false);
        setVisible(false);
    }
    void show() {
        if(isVisible()){
            getPeer()->toFront(true);
            return;
        }
        getPeer()->setVisible(true);
        setVisible(true);
        TopLevelWindow *tlw = TopLevelWindow::getActiveTopLevelWindow();
        if(tlw != nullptr){
            setCentrePosition(tlw->getPosition() + 
                Point<int>(tlw->getWidth()/2, tlw->getHeight()/2));
        }
    }
    std::unique_ptr<Component> contents;
};

namespace {
    std::unique_ptr<SubWindow> artnetWindow, usbdmxWindow, midiWindow, patcherWindow, 
        controllersWindow, statesWindow, timingWindow;
}

void MainWindow::Init(ValueTree showfile_node){
    ArtNetSystem::Init(VT_GetChildWithName(showfile_node, idArtNetSystem));
    USBDMXSystem::Init(VT_GetChildWithName(showfile_node, idUSBDMXSystem));
    MIDISystem::Init(VT_GetChildWithName(showfile_node, idMIDISystem));
    TimingSystem::Init(VT_GetChildWithName(showfile_node, idTimingSystem));
    ChannelSystem::Init(VT_GetChildWithName(showfile_node, idChannelSystem));
    FixtureSystem::Init(VT_GetChildWithName(showfile_node, idFixtureSystem));
    ControllerSystem::Init(VT_GetChildWithName(showfile_node, idControllerSystem));
    if(showfile_node.isValid()) ChannelSystem::ConvertAllPhasorsUUIDToPointer();
    LightingSystem::Init(VT_GetChildWithName(showfile_node, idLightingSystem));
    artnetWindow.reset(new SubWindow("BuskMagic - Art-Net Setup", false, new ArtNetSetup()));
    usbdmxWindow.reset(new SubWindow("BuskMagic - USB-DMX Setup", false, new USBDMXSetup()));
    midiWindow.reset(new SubWindow("BuskMagic - MIDI Setup", false, new MIDISetup()));
    patcherWindow.reset(new SubWindow("BuskMagic - Patcher", false, new Patcher()));
    controllersWindow.reset(new SubWindow("BuskMagic - Controllers", true, new ControllerWindow()));
    statesWindow.reset(new SubWindow("BuskMagic - States", false, new StatesWindow(
        VT_GetChildWithName(showfile_node, idStatesWindow)
    )));
    timingWindow.reset(new SubWindow("BuskMagic - Timing (Tempo)", false, new TimingWindow(
        VT_GetChildWithName(showfile_node, idTimingWindow)
    )));
    setContentOwned(new MainWindowComponent(), false);
    setVisible(true);
}
void MainWindow::Finalize(){
    setVisible(false);
    clearContentComponent();
    timingWindow = nullptr;
    statesWindow = nullptr;
    controllersWindow = nullptr;
    patcherWindow = nullptr;
    midiWindow = nullptr;
    usbdmxWindow = nullptr;
    artnetWindow = nullptr;
    LightingSystem::Finalize();
    ControllerSystem::Finalize();
    FixtureSystem::Finalize();
    ChannelSystem::Finalize();
    TimingSystem::Finalize();
    MIDISystem::Finalize();
    USBDMXSystem::Finalize();
    ArtNetSystem::Finalize();
}

void MainWindow::Load(){
    if(!NativeMessageBox::showYesNoBox(AlertWindow::WarningIcon, "BuskMagic",
            "Are you sure you want to erase the current showfile and load a new one?")) return;
    FileChooser fc("Load showfile...", File::getSpecialLocation(File::userHomeDirectory), "*.bmshow");
    if(!fc.browseForFileToOpen()) return;
    File showfile = fc.getResult();
    if(!LoadInternal(showfile, true)) return;
    curshowfile = showfile;
}
bool MainWindow::LoadInternal(File showfile, bool doFinalize){
    ValueTree showfile_node = VT_Load(showfile, idBuskMagicShow);
    if(!showfile_node.isValid()){
        WarningBox(showfile.getFullPathName() + " is not a valid BuskMagic showfile!");
        return false;
    }
    LS_LOCK_WRITE();
    if(doFinalize) Finalize();
    Init(showfile_node);
    return true;
}
void MainWindow::Save(bool saveas){
    File showfile;
    if(saveas || curshowfile.getFullPathName() == ""){
        FileChooser fc("Save showfile as...", File::getSpecialLocation(File::userHomeDirectory), "*.bmshow");
        if(!fc.browseForFileToSave(true)) return;
        showfile = fc.getResult();
    }else{
        showfile = curshowfile;
    }
    if(!SaveInternal(showfile)){
        WarningBox("Could not save showfile " + showfile.getFullPathName());
        return;
    }
    curshowfile = showfile;
}
bool MainWindow::SaveInternal(File showfile){
    LS_LOCK_READ();
    ValueTree showfile_node(idBuskMagicShow);
    showfile_node.addChild(ArtNetSystem::Save(), -1, nullptr);
    showfile_node.addChild(USBDMXSystem::Save(), -1, nullptr);
    showfile_node.addChild(MIDISystem::Save(), -1, nullptr);
    showfile_node.addChild(TimingSystem::Save(), -1, nullptr);
    showfile_node.addChild(ChannelSystem::Save(), -1, nullptr);
    showfile_node.addChild(FixtureSystem::Save(), -1, nullptr);
    showfile_node.addChild(ControllerSystem::Save(), -1, nullptr);
    showfile_node.addChild(LightingSystem::Save(), -1, nullptr);
    StatesWindow *sw = dynamic_cast<StatesWindow*>(statesWindow->contents.get());
    showfile_node.addChild(sw->Save(), -1, nullptr);
    TimingWindow *tw = dynamic_cast<TimingWindow*>(timingWindow->contents.get());
    showfile_node.addChild(tw->Save(), -1, nullptr);
    return VT_Save(showfile_node, showfile, "bmshow", "BuskMagic Showfile"); 
}
void MainWindow::timerCallback(){
    File backupdir = GetBackupDir();
    String base = curshowfile.existsAsFile() ? curshowfile.getFileNameWithoutExtension() : "unsaved";
    File backupfile = backupdir.getNonexistentChildFile(base + "_", ".bmshow", false);
    if(!SaveInternal(backupfile)){
        std::cout << "Failed to save backup file " << backupfile.getFullPathName() << "\n";
        return;
    }
    Array<File> backupfilesthisshow = backupdir.findChildFiles(
            File::findFiles | File::ignoreHiddenFiles, false, base + "*.bmshow");
    if(backupfilesthisshow.size() >= 8){
        File oldest = FindOldestNewestFile(backupfilesthisshow, false);
        if(oldest.existsAsFile()) oldest.deleteFile();
    }
}

MainWindow::MainWindow() 
    : DocumentWindow("BuskMagic", LFWindowColor(), DocumentWindow::allButtons, true)
{
    LS_LOCK_WRITE();
    SeedRNG();
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    centreWithSize(getWidth(), getHeight());
    app_icon = new Image(ImageCache::getFromMemory(BinaryData::logo_128_png, BinaryData::logo_128_pngSize));
    setIcon(*app_icon);
    getPeer()->setIcon(*app_icon);
    mainmenus.reset(new MainMenus(this));
    setMenuBar(mainmenus.get());
    #ifdef JUCE_MAC
        MenuBarModel::setMacMainMenu(mainmenus.get());
    #endif
    setSize(800, 600);
    //Load backed up file
    bool flag = false;
    do{
        if(!GetSettingsDir().getChildFile("crashed.flg").existsAsFile()) break;
        Array<File> backupfiles = GetBackupDir().findChildFiles(
                File::findFiles | File::ignoreHiddenFiles, false, "*.bmshow");
        if(backupfiles.size() == 0) break;
        File newest = FindOldestNewestFile(backupfiles, true);
        if(!NativeMessageBox::showYesNoBox(AlertWindow::WarningIcon, "BuskMagic", 
            "It looks like BuskMagic did not shut down correctly, and a backup showfile\n"
            "was saved. Load this showfile?")) break;
        if(!LoadInternal(newest, false)) break;
        flag = true;
    }while(false);
    if(!flag){
        Init(ValueTree()); //TODO command line parameters
    }
    GetSettingsDir().getChildFile("crashed.flg").create();
    //Start backup system
    backupcounter = 0;
    startTimer(600000);
}

MainWindow::~MainWindow() {
    Finalize();
    #ifdef JUCE_MAC
        MenuBarModel::setMacMainMenu(nullptr);
    #endif
    setMenuBar(nullptr);
    delete app_icon; app_icon = nullptr;
    GetSettingsDir().getChildFile("crashed.flg").deleteFile();
}

void MainWindow::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

void MainWindow::requestedQuit(){
    int res = NativeMessageBox::showYesNoCancelBox(AlertWindow::WarningIcon, "BuskMagic",
            "Save current showfile before quitting?");
    if(res == 0) return;
    if(res == 1) Save(false);
    JUCEApplication::getInstance()->quit();
}

MainMenus::MainMenus(MainWindow *mw) : parent(mw) {}

StringArray MainMenus::getMenuBarNames() {
    return StringArray("File", "Setup", "Live");
}

PopupMenu MainMenus::getMenuForIndex(int topLevelMenuIndex, const String &menuName){
    ignoreUnused(menuName);
    if(topLevelMenuIndex == 0){
        PopupMenu menu;
        menu.addItem(0x1000, "Load...");
        menu.addItem(0x1001, "Save");
        menu.addItem(0x1002, "Save As...");
        menu.addSeparator();
        menu.addItem(0x1010, "Exit");
        return menu;
    }else if(topLevelMenuIndex == 1){
        PopupMenu menu;
        menu.addItem(0x2000, "Art-Net...");
        menu.addItem(0x2001, "USB-DMX...");
        menu.addItem(0x2002, "MIDI...");
        menu.addSeparator();
        menu.addItem(0x2010, "Patcher...");
        return menu;
    }else if(topLevelMenuIndex == 2){
        PopupMenu menu;
        menu.addItem(0x3000, "Controllers...");
        menu.addItem(0x3001, "States...");
        menu.addSeparator();
        menu.addItem(0x3010, "Timing (Tempo)...");
        return menu;
    }else{
        PopupMenu menu;
        menu.addItem(0x9001, "Error!");
        return menu;
    }
    
}

void MainMenus::menuItemSelected(int menuItemID, int topLevelMenuIndex){
    ignoreUnused(topLevelMenuIndex);
    switch(menuItemID){
    case 0x1000:
        parent->Load();
        break;
    case 0x1001:
        parent->Save(false);
        break;
    case 0x1002:
        parent->Save(true);
        break;
    case 0x1010:
        parent->requestedQuit();
        break;
    case 0x2000:
        artnetWindow->show();
        break;
    case 0x2001:
        usbdmxWindow->show();
        break;
    case 0x2002:
        midiWindow->show();
        break;
    case 0x2010:
        patcherWindow->show();
        break;
    case 0x3000:
        controllersWindow->show();
        break;
    case 0x3001:
        statesWindow->show();
        break;
    case 0x3010:
        timingWindow->show();
        break;
    case 0x9001:
        WarningBox("Menu subsystem error!");
        break;
    }
}
