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

#include "ArtNetSystem.h"
#include "MIDISystem.h"

class SubWindow : public DocumentWindow {
public:
    SubWindow(String name) 
        : DocumentWindow(name, Colours::purple, DocumentWindow::closeButton, true)
    {
        //TODO: setIcon(const Image &blah);
        setUsingNativeTitleBar(true);
        setResizable(false, false);
        setVisible(false);
    }
    ~SubWindow() {}
    void closeButtonPressed() override {
        setVisible(false);
    }
    void center() {
        centreAroundComponent(nullptr, getWidth(), getHeight());
    }
};

namespace {
    std::unique_ptr<SubWindow> artnetWindow, midiWindow, patcherWindow, controllersWindow;
}

MainWindow::MainWindow() 
    : DocumentWindow("BuskMagic", Colours::purple, DocumentWindow::allButtons, true)
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
    //GUI startup
    artnetWindow.reset(new SubWindow("BuskMagic - Art-Net Setup"));
    artnetWindow->setContentOwned(new ArtNetSetup(), true);
    midiWindow.reset(new SubWindow("BuskMagic - MIDI Setup"));
    midiWindow->setContentOwned(new MIDISetup(), true);
    patcherWindow.reset(new SubWindow("BuskMagic - Patcher"));
    patcherWindow->setContentOwned(new Patcher(), true);
    controllersWindow.reset(new SubWindow("BuskMagic - Controllers"));
    controllersWindow->setContentOwned(new ControllerWindow(), false);
    controllersWindow->setResizable(true, false);
}

MainWindow::~MainWindow() {
    setMenuBar(nullptr);
    //GUI finalize
    artnetWindow = nullptr;
    midiWindow = nullptr;
    patcherWindow = nullptr;
    controllersWindow = nullptr;
    //Application finalize
    ArtNetSystem::Finalize();
    MIDISystem::Finalize();
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
        menu.addItem(0x3001, "Tempo...");
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
        artnetWindow->setVisible(true);
        artnetWindow->center();
        break;
    case 0x2001:
        midiWindow->setVisible(true);
        artnetWindow->center();
        break;
    case 0x2010:
        patcherWindow->setVisible(true);
        artnetWindow->center();
        break;
    case 0x3000:
        controllersWindow->setVisible(true);
        artnetWindow->center();
        break;
    case 0x3001:
        WarningBox("Tempo system not yet implemented!");
        break;
    case 0x9001:
        WarningBox("Menu subsystem error!");
        break;
    }
}
