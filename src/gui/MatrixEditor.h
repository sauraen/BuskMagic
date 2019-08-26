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

#include "ControllerSystem.h"
#include "ChannelSystem.h"

#include "gui/TextListBox.h"
#include "gui/Popup/PopupWindow.h"

class MatrixEditor : public Component, public TextListBox::Listener, public Button::Listener {
public:
    static MatrixEditor *mtxed_static; //Only one of these

    MatrixEditor();
    ~MatrixEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void mouseDown(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    
    void rowSelected(TextListBox* parent, int row) override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    
    void RefreshControllerFilters();
    void RefreshChannelFilters();
    void RefreshVisibleControllerSet();
    void RefreshVisibleChannelSet();
    
private:
    std::unique_ptr<TextListBox> lstCtType;
    std::unique_ptr<TextListBox> lstCtGroup;
    std::unique_ptr<TextListBox> lstCtName;
    std::unique_ptr<TextListBox> lstFixID;
    std::unique_ptr<TextListBox> lstFixName;
    std::unique_ptr<TextListBox> lstChName;
    std::unique_ptr<TextButton> btnAddFree;
    
    PopupWindow popup;
    
    Array<Controller*> ctSet;
    Array<Channel*> chSet;
    
    Point<int> view;
    Point<int> viewdragstart;
    int GetColX(int c);
    int GetRowY(int r);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixEditor)
};
