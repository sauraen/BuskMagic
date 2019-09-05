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

#include "gui/Popup/PopupWindow.h"
#include "gui/Popup/PhasorEditor.h"
#include "gui/Popup/DefaultValueEditor.h"
#include "gui/Popup/FreeChannelEditor.h"
#include "gui/Popup/ChannelOpEditor.h"

#include <algorithm>
#include <cmath>

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
    drag_ct = -1;
    drag_dest = -1;
    setOpaque(true);
    //
    lstCtType.reset(new TextListBox(this, true, "Controller type:"));
    lstCtGroup.reset(new TextListBox(this, true, "Controller group:"));
    lstCtName.reset(new TextListBox(this, true, "Controller name:"));
    lstFixID.reset(new TextListBox(this, true, "Fixture ID:"));
    lstFixName.reset(new TextListBox(this, true, "Fixture name:"));
    lstChName.reset(new TextListBox(this, true, "Channel name:"));
    addAndMakeVisible(lstCtType.get());
    addAndMakeVisible(lstCtGroup.get());
    addAndMakeVisible(lstCtName.get());
    addAndMakeVisible(lstFixID.get());
    addAndMakeVisible(lstFixName.get());
    addAndMakeVisible(lstChName.get());
    //
    btnAddFree.reset(new TextButton("Add Free Chn."));
    addAndMakeVisible(btnAddFree.get());
    btnAddFree->addListener(this);
    //
    lstCtType->add("Simple");
    lstCtType->add("Continuous");
    lstCtType->add("Modulator");
    lstFixID->add("Free channels");
    //
    RefreshControllerFilters();
    RefreshChannelFilters();
    RefreshVisibleControllerSet();
    RefreshVisibleChannelSet();
}

MatrixEditor::~MatrixEditor() {
    mtxed_static = nullptr;
}

int MatrixEditor::GetColX(int c){
    return c * col_width - view.x + ct_width;
}
int MatrixEditor::GetRowY(int r){
    return r * row_height - view.y + row_height;
}

void MatrixEditor::paint (Graphics& g) {
    g.fillAll(LFWindowColor());
    Colour linecolor = Colours::darkgrey;
    Colour textcolor = Colours::white;
    int main_bottom_y = getHeight() - main_dbottom;
    int ch_bottom_y = getHeight() - ch_dbottom;
    int minviewcol = std::max(view.x / col_width, 0);
    int minviewrow = std::max(view.y / row_height, 0);
    int maxviewcol = (view.x + getWidth() - ct_width) / col_width;
    int maxviewrow = (view.y + main_bottom_y - row_height) / row_height;
    g.setFont(GetNormalFont());
    g.setColour(linecolor);
    g.drawLine(ct_width, 0, ct_width, main_bottom_y, 2);
    g.drawLine(0, row_height, getWidth(), row_height, 2);
    g.drawLine(ct_width, main_bottom_y, getWidth(), main_bottom_y, 2);
    g.drawText("Phasor Matrix", 1, 0, ct_width - 1, row_height, Justification::centredLeft, false);
    LS_LOCK_READ();
    //Rows = controllers
    g.saveState();
    g.reduceClipRegion(0, row_height, getWidth(), main_bottom_y - row_height);
    for(int r = minviewrow; r < ctSet.size() && r <= maxviewrow; ++r){
        int y = GetRowY(r);
        g.setColour(linecolor);
        g.drawHorizontalLine(y + row_height, 0, getWidth());
        g.setColour(drag_ct == r ? linecolor : textcolor);
        g.drawText(ctSet[r]->GetName(), 1, y, ct_width - 1, row_height, Justification::centredLeft, false);
    }
    if(drag_dest >= 0){
        int y = GetRowY(drag_dest);
        g.setColour(textcolor);
        g.drawLine(0, y, ct_width, y, 5);
    }
    g.restoreState();
    //Columns = channels
    g.saveState();
    g.reduceClipRegion(ct_width, 0, getWidth() - ct_width, ch_bottom_y);
    int colsmergefixid = 0, colsmergefixname = 0;
    for(int c = minviewcol; c < chSet.size() && c <= maxviewcol; ++c){
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
        int x = GetColX(c);
        g.setColour(textcolor);
        g.drawText(String(chSet[c]->GetDefaultValue(), 2), x, 0,
            col_width, row_height, Justification::centred, false);
        g.drawText(Channel::OpGetLetters(chSet[c]->GetOp()), x, main_bottom_y, 
            col_width, row_height, Justification::centred, false);
        g.drawText("X", x, main_bottom_y + row_height, 
            col_width, row_height, Justification::centred, false);
        g.drawText(chSet[c]->GetLetters(), x, main_bottom_y + 2*row_height, 
            col_width, row_height, Justification::centred, false);
        if(colsmergefixid == 0 || firstcolmergefixid){
            g.drawText(fixid < 0 ? "-" : String(fixid), x, main_bottom_y + 3*row_height, 
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
    g.restoreState();
    //Cells = phasors
    g.saveState();
    g.reduceClipRegion(ct_width, row_height, getWidth()-ct_width, main_bottom_y - row_height);
    for(int c = minviewcol; c < chSet.size() && c <= maxviewcol; ++c){
        int x = GetColX(c);
        for(int r = minviewrow; r < ctSet.size() && r <= maxviewrow; ++r){
            int y = GetRowY(r);
            Phasor *phasor = chSet[c]->GetPhasorForController(ctSet[r], false);
            if(phasor == nullptr) continue;
            float magheight = (float)(row_height-2) * std::min(std::abs(phasor->mag), 1.0f);
            if(phasor->mag >= 0.0f){
                g.setColour(Colours::blue);
                g.fillRect(x+1.0f, y+row_height-1.0f-magheight, col_width-2.0f, magheight);
            }else{
                g.setColour(Colours::red);
                g.fillRect(x+1.0f, y+1.0f, col_width-2.0f, magheight);
            }
            float midx = x + (col_width / 2);
            float midy = y + (row_height / 2);
            float angle = 2.0f * M_PI * phasor->angle;
            float fit_in_box = 0.8f * 0.5f * std::min(row_height, col_width);
            if(std::abs(phasor->mag) < 0.0001f) fit_in_box = 0.0f;
            float endx = midx + std::cos(angle) * fit_in_box;
            float endy = midy - std::sin(angle) * fit_in_box;
            g.setColour(phasor->mag >= 0.0f ? Colours::white : Colours::darkgrey);
            g.drawLine(midx, midy, endx, endy);
            g.drawLine(endx-1.0f, endy-1.0f, endx+1.0f, endy+1.0f, 3); //Dot at end
            if(phasor->mag < 0.0f){
                endx = 2.0f*midx - endx;
                endy = 2.0f*midy - endy;
                g.setColour(Colours::white);
                g.drawLine(midx, midy, endx, endy);
                g.drawLine(endx-1.0f, endy-1.0f, endx+1.0f, endy+1.0f, 3);
            }
        }
    }
    g.restoreState();
}

void MatrixEditor::resized() {
    lstCtType->setBounds(0, getHeight() - main_dbottom, ct_width, main_dbottom*2/8);
    lstCtGroup->setBounds(0, getHeight() - (main_dbottom*6/8), ct_width, main_dbottom*3/8);
    lstCtName->setBounds(0, getHeight() - (main_dbottom*3/8), ct_width, main_dbottom*3/8);
    lstFixID->setBounds(ct_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
    lstFixName->setBounds(ct_width + ch_listbox_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
    lstChName->setBounds(ct_width + 2*ch_listbox_width, getHeight() - ch_dbottom, ch_listbox_width, ch_dbottom);
    btnAddFree->setBounds(ct_width + 3*ch_listbox_width + 8, getHeight() - ch_dbottom, 100, 24);
}

void MatrixEditor::rowSelected(TextListBox* parent, int row) {
    if(parent == lstCtType.get()){
        RefreshVisibleControllerSet();
    }else if(parent == lstCtGroup.get()){
        RefreshVisibleControllerSet();
    }else if(parent == lstCtName.get()){
        RefreshVisibleControllerSet();
    }else if(parent == lstFixID.get()){
        RefreshVisibleChannelSet();
    }else if(parent == lstFixName.get()){
        RefreshVisibleChannelSet();
    }else if(parent == lstChName.get()){
        RefreshVisibleChannelSet();
    }
}

void MatrixEditor::buttonClicked(Button *buttonThatWasClicked) {
    if(buttonThatWasClicked == btnAddFree.get()){
        ChannelSystem::AddFreeChannel();
        if(!lstFixID->isRowSelected(0)){
            lstFixID->selectRow(0, false, false);
        }
    }
}

void MatrixEditor::mouseDown(const MouseEvent &event){
    int r = (event.y + view.y - row_height) / row_height;
    int c = (event.x - ct_width + view.x) / col_width;
    int esx = getScreenX() + event.x;
    int esy = getScreenY() + event.y;
    if(isRightClick(event)){
        if(event.x < ct_width){
            if(event.y < row_height) return;
            if(r < 0 || r >= ctSet.size()) return;
            drag_ct = r;
            drag_dest = r;
            setMouseCursor(MouseCursor::UpDownResizeCursor);
            return;
        }
        if(event.x >= getWidth()) return;
        if(event.y < 0 || event.y >= getHeight() - ch_dbottom) return;
        LS_LOCK_READ();
        if(c < 0 || c >= chSet.size()) return;
        Channel *ch = chSet[c];
        if(event.y >= getHeight() - main_dbottom){
            //Right click in channels area
            r = (event.y - (getHeight() - main_dbottom)) / row_height;
            if(r == 0){
                //Operator
                popup.show<ChannelOpEditor>(esx, esy, ch);
            }else if(r == 1){
                //Output value
                return;
            }else if(r == 2){
                //Letters
                if(ch->GetFixID() != -1) return; //Only for free channels
                popup.show<FreeChannelEditor>(esx, esy, ch);
            }else if(r == 3){
                //Fixture ID
                return;
            }else if(r == 4){
                //Fixture name
                return;
            }
        }else if(event.y <= row_height){
            //Right click in default value
            popup.show<DefaultValueEditor>(esx, esy, ch);
        }else{
            //Right click in phasors area
            if(r < 0 || r >= ctSet.size()) return;
            Controller *ct = ctSet[r];
            PhasorEditor::Startup startup(ch->GetPhasorForController(ct, true), ch);
            Point<int> corner(getScreenX() + c*col_width - view.x + ct_width + (col_width/2) - 70,
                              getScreenY() + r*row_height - view.y + row_height + (row_height/2) - 70);
            popup.show<PhasorEditor>(corner.x, corner.y, &startup);
        }
    }else if(event.mods.isLeftButtonDown()){
        viewdragstart = view;
    }
}
void MatrixEditor::mouseDrag(const MouseEvent &event){
    if(isRightClick(event)){
        if(drag_ct >= 0){
            int r = (event.y + view.y - row_height/2) / row_height;
            if(r < 0 || r > ctSet.size()) return;
            if(drag_dest != r){
                drag_dest = r;
                repaint();
            }
        }
    }else if(event.mods.isLeftButtonDown()){
        view = viewdragstart - event.getOffsetFromDragStart();
        int maxx = chSet.size() * col_width - (getWidth() - ct_width);
        int maxy = ctSet.size() * row_height - (getHeight() - main_dbottom - row_height);
        if(view.x > maxx) view.x = maxx;
        if(view.y > maxy) view.y = maxy;
        if(view.x < 0) view.x = 0;
        if(view.y < 0) view.y = 0;
        repaint();
    }
}
void MatrixEditor::mouseUp(const MouseEvent &event){
    if(isRightClick(event)){
        if(drag_ct >= 0){
            setMouseCursor(MouseCursor::NormalCursor);
            if(drag_dest == drag_ct || drag_dest == drag_ct + 1){
                drag_ct = -1; //Don't move it
            }else if(drag_dest > drag_ct){
                --drag_dest;
            }
            if(drag_ct >= 0 && drag_dest >= 0){
                Controller *drag_ct_ct = ctSet[drag_ct];
                Controller *drag_dest_ct = ctSet[drag_dest];
                jassert(drag_ct_ct != nullptr && drag_dest_ct != nullptr);
                int drag_ct_ctidx = -1, drag_dest_ctidx = -1;
                for(int i=0; i<ControllerSystem::NumControllers(); ++i){
                    Controller *ctrlr = ControllerSystem::GetController(i);
                    if(ctrlr == drag_ct_ct) drag_ct_ctidx = i;
                    else if(ctrlr == drag_dest_ct) drag_dest_ctidx = i;
                }
                jassert(drag_ct_ctidx >= 0 && drag_dest_ctidx >= 0);
                ControllerSystem::ChangeControllerOrder(drag_ct_ctidx, drag_dest_ctidx);
                RefreshVisibleControllerSet();
            }
            drag_ct = -1;
            drag_dest = -1;
            repaint();
        }
    }
}

void MatrixEditor::RefreshControllerFilters(){
    LS_LOCK_WRITE();
    StringArray ctgroups, ctnames;
    for(int c=0; c<ControllerSystem::NumControllers(); ++c){
        Controller *ctrlr = ControllerSystem::GetController(c);
        ctgroups.addIfNotAlreadyThere(String(ctrlr->GetGroup()));
        ctnames.addIfNotAlreadyThere(ctrlr->GetName());
    }
    ctgroups.sortNatural();
    ctnames.sortNatural();
    lstCtGroup->syncToSortedList(ctgroups);
    lstCtName->syncToSortedList(ctnames);
    repaint();
}

void MatrixEditor::RefreshChannelFilters(){
    LS_LOCK_WRITE();
    StringArray fixids, fixnames, chnames;
    for(int c=0; c<ChannelSystem::NumFreeChannels(); ++c){
        chnames.addIfNotAlreadyThere(ChannelSystem::GetFreeChannel(c)->GetName());
    }
    for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
        Fixture *fix = FixtureSystem::Fix(f);
        fixids.addIfNotAlreadyThere(String(fix->GetFixID()));
        fixnames.addIfNotAlreadyThere(fix->GetName());
        for(int c=0; c<fix->GetNumChannels(); ++c){
            chnames.addIfNotAlreadyThere(fix->GetChannel(c)->GetName());
        }
    }
    fixids.sortNatural();
    fixnames.sortNatural();
    chnames.sortNatural();
    fixids.insert(0, "Free channels");
    lstFixID->syncToSortedList(fixids, true);
    lstFixName->syncToSortedList(fixnames);
    lstChName->syncToSortedList(chnames);
    repaint();
}


void MatrixEditor::RefreshVisibleControllerSet(){
    LS_LOCK_WRITE();
    ctSet.clear();
    for(int c=0; c<ControllerSystem::NumControllers(); ++c){
        Controller *ctrlr = ControllerSystem::GetController(c);
        if(!lstCtType->isItemSelected(ctrlr->GetClassType())) continue;
        if(!lstCtGroup->isItemSelected(String(ctrlr->GetGroup()))) continue;
        if(!lstCtName->isItemSelected(ctrlr->GetName())) continue;
        ctSet.add(ctrlr);
    }
    repaint();
}

void MatrixEditor::RefreshVisibleChannelSet(){
    LS_LOCK_WRITE();
    chSet.clear();
    if(lstFixID->isItemSelected("Free channels")){
        for(int c=0; c<ChannelSystem::NumFreeChannels(); ++c){
            Channel *ch = ChannelSystem::GetFreeChannel(c);
            if(!lstChName->isItemSelected(ch->GetName())) continue;
            chSet.add(ch);
        }
    }
    for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
        Fixture *fix = FixtureSystem::Fix(f);
        if(!lstFixID->isItemSelected(String(fix->GetFixID()))) continue;
        if(!lstFixName->isItemSelected(fix->GetName())) continue;
        for(int c=0; c<fix->GetNumChannels(); ++c){
            Channel *ch = fix->GetChannel(c);
            if(!lstChName->isItemSelected(ch->GetName())) continue;
            chSet.add(ch);
        }
    }
    repaint();
}
