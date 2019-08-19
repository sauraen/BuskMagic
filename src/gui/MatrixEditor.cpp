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

#include "LightingSystem.h"
#include "FixtureSystem.h"
#include "ChannelSystem.h"

#include <algorithm>

MatrixEditor *MatrixEditor::mtxed_static = nullptr;

static const int row_height = 20;
static const int col_width = 20;

static const int ct_width = 125;
static const int ch_dbottom = 200;
static const int ch_numrows = 5;
static const int ch_height = ch_numrows * row_height;
static const int main_dbottom = ch_dbottom + ch_height;

static const int ch_listbox_width = 150;

MatrixEditor::MatrixEditor() : view(0, 0) {
    jassert(mtxed_static == nullptr);
    mtxed_static = this;
    //
    mlbCtType.reset(new MultiListBox(this, "Controller type"));
    mlbCtGroup.reset(new MultiListBox(this, "Controller group"));
    mlbCtName.reset(new MultiListBox(this, "Controller name"));
    mlbFixID.reset(new MultiListBox(this, "Fixture ID"));
    mlbFixName.reset(new MultiListBox(this, "Fixture name"));
    mlbChName.reset(new MultiListBox(this, "Channel name"));
    addAndMakeVisible(mlbCtType.get());
    addAndMakeVisible(mlbCtGroup.get());
    addAndMakeVisible(mlbCtName.get());
    addAndMakeVisible(mlbFixID.get());
    addAndMakeVisible(mlbFixName.get());
    addAndMakeVisible(mlbChName.get());
    //
    mlbCtType->lsm->add("Simple");
    mlbCtType->lsm->add("Continuous");
    mlbCtType->lst->updateContent();
    mlbFixID->lsm->add("Free channels");
    mlbFixID->lst->updateContent();
    //
    RefreshControllerFilters();
    RefreshChannelFilters();
    RefreshVisibleControllerSet();
    RefreshVisibleChannelSet();
}

MatrixEditor::~MatrixEditor() {
    mtxed_static = nullptr;
}

void MatrixEditor::paint (Graphics& g) {
    g.fillAll(LFWindowColor());
    Colour linecolor = Colours::darkgrey;
    Colour textcolor = Colours::white;
    int main_bottom_y = getHeight() - main_dbottom;
    int ch_bottom_y = getHeight() - ch_dbottom;
    g.setFont(Font(15.0f, Font::plain).withTypefaceStyle("Regular"));
    g.setColour(linecolor);
    g.drawLine(ct_width, 0, ct_width, main_bottom_y, 2);
    g.drawLine(ct_width, main_bottom_y, getWidth(), main_bottom_y, 2);
    LS_LOCK_READ();
    for(int r = std::max(view.y / row_height, 0); r < ctSet.size() && 
            r <= (view.y + main_bottom_y) / row_height; ++r){
        int y = r * row_height - view.y;
        if(y + row_height < main_bottom_y){
            g.setColour(linecolor);
            g.drawHorizontalLine(y + row_height, 0, getWidth());
        }
        g.setColour(textcolor);
        g.drawText(ctSet[r]->GetName(), 1, y, ct_width - 1, row_height, Justification::centredLeft, false);
    }
    int colsmergefixid = 0, colsmergefixname = 0;
    int maxviewcol = (view.x + getWidth() - ct_width) / col_width;
    for(int c = std::max(view.x / col_width, 0); c < chSet.size() && c <= maxviewcol; ++c){
        int fixid = chSet[c]->GetFixID();
        String fixname = chSet[c]->GetFixName();
        bool firstcolmergefixid = false, firstcolmergefixname = false;
        if(colsmergefixid == 0){
            for(int c2 = c+1; c2 < chSet.size() && c2 <= maxviewcol; ++c2){
                if(chSet[c2]->GetFixID() != fixid) break;
                ++colsmergefixid;
                firstcolmergefixid = true;
            }
        }
        if(colsmergefixname == 0){
            for(int c2 = c+1; c2 < chSet.size() && c2 <= maxviewcol; ++c2){
                if(chSet[c2]->GetFixName() != fixname) break;
                ++colsmergefixname;
                firstcolmergefixname = true;
            }
        }
        int x = c * col_width - view.x + ct_width;
        g.setColour(textcolor);
        g.drawText(Channel::OpGetLetters(chSet[c]->GetOp()), x, main_bottom_y, 
            col_width, row_height, Justification::centred, false);
        g.drawText("X", x, main_bottom_y + row_height, 
            col_width, row_height, Justification::centred, false);
        g.drawText(chSet[c]->GetLetters(), x, main_bottom_y + 2*row_height, 
            col_width, row_height, Justification::centred, false);
        if(colsmergefixid == 0 || firstcolmergefixid){
            g.drawText(String(fixid), x, main_bottom_y + 3*row_height, 
                col_width * (colsmergefixid + 1), row_height, Justification::centred, false);
        }else{
            --colsmergefixid;
        }
        if(colsmergefixname == 0 || firstcolmergefixname){
            g.drawText(fixname, x, ch_bottom_y - row_height, 
                col_width * (colsmergefixname + 1), row_height, Justification::centred, false);
        }else{
            --colsmergefixname;
        }
        g.setColour(linecolor);
        int lineend = colsmergefixname == 0 ? ch_bottom_y
                      : colsmergefixid == 0 ? ch_bottom_y - row_height 
                      : ch_bottom_y - 2*row_height;
        g.drawVerticalLine(x + col_width, 0, lineend);
    }
}

void MatrixEditor::resized() {
    mlbCtType->setBounds(0, getHeight() - main_dbottom, ct_width, main_dbottom / 3);
    mlbCtGroup->setBounds(0, getHeight() - (main_dbottom * 2 / 3), ct_width, main_dbottom / 3);
    mlbCtName->setBounds(0, getHeight() - (main_dbottom / 3), ct_width, main_dbottom / 3);
    mlbFixID->setBounds(ct_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
    mlbFixName->setBounds(ct_width + ch_listbox_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
    mlbChName->setBounds(ct_width + 2*ch_listbox_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
}

void MatrixEditor::rowSelected(TextListModel* parent, int row) {
    if(parent == mlbCtType->lsm.get()){
        RefreshVisibleControllerSet();
    }else if(parent == mlbCtGroup->lsm.get()){
        RefreshVisibleControllerSet();
    }else if(parent == mlbCtName->lsm.get()){
        RefreshVisibleControllerSet();
    }else if(parent == mlbFixID->lsm.get()){
        RefreshVisibleChannelSet();
    }else if(parent == mlbFixName->lsm.get()){
        RefreshVisibleChannelSet();
    }else if(parent == mlbChName->lsm.get()){
        RefreshVisibleChannelSet();
    }
}

void MatrixEditor::mouseDown(const MouseEvent &event){
    if(event.mods.isLeftButtonDown()){
        viewdragstart = view;
    }
}
void MatrixEditor::mouseDrag(const MouseEvent &event){
    if(event.mods.isLeftButtonDown()){
        view = viewdragstart - event.getOffsetFromDragStart();
        if(view.x < 0) view.x = 0;
        if(view.y < 0) view.y = 0;
        repaint();
    }
}
void MatrixEditor::mouseUp(const MouseEvent &event){
    
}

void MatrixEditor::RefreshControllerFilters(){
    LS_LOCK_WRITE();
    Array<int> ctgroups;
    DefaultElementComparator<int> sorter;
    mlbCtName->lsm->clear();
    for(int c=0; c<ControllerSystem::NumControllers(); ++c){
        Controller *ctrlr = ControllerSystem::GetController(c);
        mlbCtName->lsm->addIfNotPresent(ctrlr->GetName());
        int g = ctrlr->GetGroup();
        if(ctgroups.indexOfSorted(sorter, g) < 0) ctgroups.addSorted(sorter, g);
    }
    mlbCtName->lst->updateContent();
    mlbCtGroup->syncToSortedIntList(ctgroups, false);
}

void MatrixEditor::RefreshChannelFilters(){
    LS_LOCK_WRITE();
    Array<int> ctfixids;
    DefaultElementComparator<int> sorter;
    mlbChName->lsm->clear();
    for(int c=0; c<ChannelSystem::NumFreeChannels(); ++c){
        mlbChName->lsm->addIfNotPresent(ChannelSystem::GetFreeChannel(c)->GetName());
    }
    mlbFixName->lsm->clear();
    for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
        Fixture *fix = FixtureSystem::Fix(f);
        mlbFixName->lsm->addIfNotPresent(fix->GetName());
        int id = fix->GetFixID();
        if(ctfixids.indexOfSorted(sorter, id) < 0) ctfixids.addSorted(sorter, id);
        for(int c=0; c<fix->GetNumChannels(); ++c){
            mlbChName->lsm->addIfNotPresent(fix->GetChannel(c)->GetName());
        }
    }
    mlbFixName->lst->updateContent();
    mlbFixID->syncToSortedIntList(ctfixids, true);
    mlbChName->lst->updateContent();
}


void MatrixEditor::RefreshVisibleControllerSet(){
    LS_LOCK_WRITE();
    ctSet.clear();
    for(int c=0; c<ControllerSystem::NumControllers(); ++c){
        Controller *ctrlr = ControllerSystem::GetController(c);
        if(!mlbCtType->isItemSelected(ctrlr->GetClassType())) continue;
        if(!mlbCtGroup->isItemSelected(String(ctrlr->GetGroup()))) continue;
        if(!mlbCtName->isItemSelected(ctrlr->GetName())) continue;
        ctSet.add(ctrlr);
    }
    repaint();
}

void MatrixEditor::RefreshVisibleChannelSet(){
    LS_LOCK_WRITE();
    chSet.clear();
    if(mlbFixID->isItemSelected("Free channels")){
        for(int c=0; c<ChannelSystem::NumFreeChannels(); ++c){
            Channel *ch = ChannelSystem::GetFreeChannel(c);
            if(!mlbChName->isItemSelected(ch->GetName())) continue;
            chSet.add(ch);
        }
    }
    for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
        Fixture *fix = FixtureSystem::Fix(f);
        if(!mlbFixID->isItemSelected(String(fix->GetFixID()))) continue;
        if(!mlbFixName->isItemSelected(fix->GetName())) continue;
        for(int c=0; c<fix->GetNumChannels(); ++c){
            Channel *ch = fix->GetChannel(c);
            if(!mlbChName->isItemSelected(ch->GetName())) continue;
            chSet.add(ch);
        }
    }
    repaint();
}
