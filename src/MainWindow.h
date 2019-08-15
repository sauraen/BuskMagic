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

#pragma once

#include "JuceHeader.h"
#include "Common.h"

class MainWindowComponent : public Component {
public:
    MainWindowComponent() {}
    ~MainWindowComponent() {}
    
    void paint(Graphics &g){
        g.fillAll(Colours::orange);
        //TODO add matrix editor, status bar, etc.
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindowComponent)
};

class MainMenus : public MenuBarModel {
public:
    MainMenus() {}
    ~MainMenus() {}
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenus)
};

class MainWindow : public DocumentWindow {
public:
    MainWindow();
    ~MainWindow();
    
    void closeButtonPressed() override;
private:
    std::unique_ptr<MainMenus> mainmenus;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};