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

#include "MatrixEditor.h"

static const int ct_width = 125;
static const int ch_list_width = 150;
static const int mtx_main_height_offset = 320;
static const int mtx_ch_height_offset = 200;

MatrixEditor::MatrixEditor() {
    mlbCtType.reset(new MultiListBox(this, "Controller type"));
    mlbCtGroup.reset(new MultiListBox(this, "Controller group"));
    mlbCtName.reset(new MultiListBox(this, "Controller name"));
    mlbFixID.reset(new MultiListBox(this, "Fixture ID"));
    mlbFixName.reset(new MultiListBox(this, "Fixture name"));
    mlbChType.reset(new MultiListBox(this, "Channel type"));
    mlbChName.reset(new MultiListBox(this, "Channel name"));
    addAndMakeVisible(mlbCtType.get());
    addAndMakeVisible(mlbCtGroup.get());
    addAndMakeVisible(mlbCtName.get());
    addAndMakeVisible(mlbFixID.get());
    addAndMakeVisible(mlbFixName.get());
    addAndMakeVisible(mlbChType.get());
    addAndMakeVisible(mlbChName.get());
}

MatrixEditor::~MatrixEditor() {
    
}

void MatrixEditor::paint (Graphics& g) {
    g.fillAll(Colours::orange);
}

void MatrixEditor::resized() {
    mlbCtType->setBounds(0, getHeight() - mtx_main_height_offset, ct_width, mtx_main_height_offset / 3);
    mlbCtGroup->setBounds(0, getHeight() - (mtx_main_height_offset * 2 / 3), ct_width, mtx_main_height_offset / 3);
    mlbCtName->setBounds(0, getHeight() - (mtx_main_height_offset / 3), ct_width, mtx_main_height_offset / 3);
    mlbFixID->setBounds(ct_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
    mlbFixName->setBounds(ct_width + ch_list_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
    mlbChType->setBounds(ct_width + 2*ch_list_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
    mlbChName->setBounds(ct_width + 3*ch_list_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
}

void MatrixEditor::rowSelected(TextListModel* parent, int row) {
    
}
