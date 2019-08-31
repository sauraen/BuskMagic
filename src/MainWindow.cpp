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
#include "gui/MIDISetup.h"
#include "gui/Patcher.h"
#include "gui/ControllerWindow.h"
#include "gui/TimingWindow.h"

#include "ArtNetSystem.h"
#include "MIDISystem.h"
#include "TimingSystem.h"
#include "LightingSystem.h"

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
        //TODO: peer->setIcon(const Image &blah);
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
private:
    std::unique_ptr<Component> contents;
};

namespace {
    std::unique_ptr<SubWindow> artnetWindow, midiWindow, patcherWindow, 
        controllersWindow, timingWindow;
}

MainWindow::MainWindow() 
    : DocumentWindow("BuskMagic", LFWindowColor(), DocumentWindow::allButtons, true)
{
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    centreWithSize(getWidth(), getHeight());
    //TODO: setIcon(const Image &blah);
    mainmenus.reset(new MainMenus());
    setMenuBar(mainmenus.get());
    #ifdef JUCE_MAC
        MenuBarModel::setMacMainMenu(mainmenus.get());
    #endif
    setContentOwned(new MainWindowComponent(), false);
    setVisible(true);
    setSize(800, 600);
    //Application startup
    ArtNetSystem::Init();
    MIDISystem::Init();
    TimingSystem::Init();
    LightingSystem::Init();
    //GUI startup
    artnetWindow.reset(new SubWindow("BuskMagic - Art-Net Setup", false, new ArtNetSetup()));
    midiWindow.reset(new SubWindow("BuskMagic - MIDI Setup", false, new MIDISetup()));
    patcherWindow.reset(new SubWindow("BuskMagic - Patcher", false, new Patcher()));
    controllersWindow.reset(new SubWindow("BuskMagic - Controllers", true, new ControllerWindow()));
    timingWindow.reset(new SubWindow("BuskMagic - Timing (Tempo)", false, new TimingWindow()));
}

MainWindow::~MainWindow() {
    setMenuBar(nullptr);
    //GUI finalize
    artnetWindow = nullptr;
    midiWindow = nullptr;
    patcherWindow = nullptr;
    controllersWindow = nullptr;
    timingWindow = nullptr;
    //Application finalize
    LightingSystem::Finalize();
    TimingSystem::Finalize();
    MIDISystem::Finalize();
    ArtNetSystem::Finalize();
}

void MainWindow::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

StringArray MainMenus::getMenuBarNames() {
    return StringArray("File", "Setup", "Live");
}

PopupMenu MainMenus::getMenuForIndex(int topLevelMenuIndex, const String &menuName){
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
        menu.addItem(0x2001, "MIDI...");
        menu.addSeparator();
        menu.addItem(0x2010, "Patcher...");
        return menu;
    }else if(topLevelMenuIndex == 2){
        PopupMenu menu;
        menu.addItem(0x3000, "Controllers...");
        menu.addItem(0x3001, "Timing (Tempo)...");
        return menu;
    }else{
        PopupMenu menu;
        menu.addItem(0x9001, "Error!");
        return menu;
    }
    
}

void MainMenus::menuItemSelected(int menuItemID, int topLevelMenuIndex){
    switch(menuItemID){
    case 0x1000:
        WarningBox("Load showfile not yet implemented!");
        break;
    case 0x1001:
        WarningBox("Save showfile not yet implemented!");
        break;
    case 0x1002:
        WarningBox("Save showfile as not yet implemented!");
        break;
    case 0x1010:
        JUCEApplication::getInstance()->systemRequestedQuit();
        break;
    case 0x2000:
        artnetWindow->show();
        break;
    case 0x2001:
        midiWindow->show();
        break;
    case 0x2010:
        patcherWindow->show();
        break;
    case 0x3000:
        controllersWindow->show();
        break;
    case 0x3001:
        timingWindow->show();
        break;
    case 0x9001:
        WarningBox("Menu subsystem error!");
        break;
    }
}
