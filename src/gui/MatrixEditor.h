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

#include "gui/MultiListBox.h"
#include "gui/Popup/PopupWindow.h"

class MatrixEditor : public Component, public TextListModel::Listener {
public:
    static MatrixEditor *mtxed_static; //Only one of these

    MatrixEditor();
    ~MatrixEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void mouseDown(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;
    
    void rowSelected(TextListModel* parent, int row) override;
    
    void RefreshControllerFilters();
    void RefreshChannelFilters();
    void RefreshVisibleControllerSet();
    void RefreshVisibleChannelSet();
    
private:
    std::unique_ptr<MultiListBox> mlbCtType;
    std::unique_ptr<MultiListBox> mlbCtGroup;
    std::unique_ptr<MultiListBox> mlbCtName;
    std::unique_ptr<MultiListBox> mlbFixID;
    std::unique_ptr<MultiListBox> mlbFixName;
    std::unique_ptr<MultiListBox> mlbChName;
    
    PopupWindow popup;
    
    Array<Controller*> ctSet;
    Array<Channel*> chSet;
    
    Point<int> view;
    Point<int> viewdragstart;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixEditor)
};
