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

#include "gui/MatrixEditor.h"
#include "gui/StatusBar.h"

class MainWindowComponent : public Component {
public:
    MainWindowComponent() {
        setOpaque(true);
        mtxEditor.reset(new MatrixEditor());
        addAndMakeVisible(mtxEditor.get());
        barStatus.reset(new StatusBar());
        addAndMakeVisible(barStatus.get());
    }
    ~MainWindowComponent() {}
    
    void paint(Graphics &g) override {
        g.fillAll(LFWindowColor());
    }
    
    void resized() override {
        mtxEditor->setBounds(0, 0, getWidth(), getHeight() - 24);
        barStatus->setBounds(0, getHeight() - 24, getWidth(), 24);
    }
private:
    std::unique_ptr<MatrixEditor> mtxEditor;
    std::unique_ptr<StatusBar> barStatus;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindowComponent)
};

class MainWindow;

class MainMenus : public MenuBarModel {
public:
    MainMenus(MainWindow *mw);
    ~MainMenus() {}
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
private:
    MainWindow *parent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenus)
};

class MainWindow : public DocumentWindow, private Timer {
public:
    MainWindow();
    ~MainWindow();
    
    void closeButtonPressed() override;
    
    void requestedQuit();
private:
    friend class MainMenus;
    void Init(ValueTree showfile_node = ValueTree());
    void Finalize();
    bool LoadInternal(File showfile, bool doFinalize);
    void Load();
    bool SaveInternal(File showfile);
    void Save(bool saveas);
    File curshowfile;
    
    int backupcounter;
    void timerCallback() override;
    
    std::unique_ptr<MainMenus> mainmenus;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
