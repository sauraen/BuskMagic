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
    dragSelectMode = false;
    ResetDragSelect();
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
    optVVMRatio.reset(new ToggleButton("optVVMRatio"));
    optVVMPercent.reset(new ToggleButton("optVVMPercent"));
    optVVMByte.reset(new ToggleButton("optVVMByte"));
    optVVMHex.reset(new ToggleButton("optVVMHex"));
    addAndMakeVisible(optVVMRatio.get());
    addAndMakeVisible(optVVMPercent.get());
    addAndMakeVisible(optVVMByte.get());
    addAndMakeVisible(optVVMHex.get());
    ConfigureOptionButton(optVVMRatio, this, 1, Colours::white, "Ratio", LightingSystem::GetValueViewMode() == LightingSystem::Ratio);
    ConfigureOptionButton(optVVMPercent, this, 1, Colours::white, "Percent", LightingSystem::GetValueViewMode() == LightingSystem::Percent);
    ConfigureOptionButton(optVVMByte, this, 1, Colours::white, "Byte", LightingSystem::GetValueViewMode() == LightingSystem::Byte);
    ConfigureOptionButton(optVVMHex, this, 1, Colours::white, "Hex", LightingSystem::GetValueViewMode() == LightingSystem::Hex);
    optSortByFix.reset(new ToggleButton("optSortByFix"));
    optSortByChan.reset(new ToggleButton("optSortByChan"));
    addAndMakeVisible(optSortByFix.get());
    addAndMakeVisible(optSortByChan.get());
    ConfigureOptionButton(optSortByFix, this, 2, Colours::white, "Fixture", !LightingSystem::SortByChannel());
    ConfigureOptionButton(optSortByChan, this, 2, Colours::white, "Channel", LightingSystem::SortByChannel());
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

void MatrixEditor::ResetDragSelect(){
    dragSelectRMin = dragSelectRMax = dragSelectCMin = dragSelectCMax = -1;
}
int MatrixEditor::GetColX(int c){
    return c * col_width - view.x + ct_width;
}
int MatrixEditor::GetRowY(int r){
    return r * row_height - view.y + row_height;
}
int MatrixEditor::ScreenXToCol(int x){
    return (x + view.x - ct_width) / col_width;
}
int MatrixEditor::ScreenYToRow(int y){
    return (y + view.y - row_height) / row_height;
}

void MatrixEditor::paint (Graphics& g) {
    g.fillAll(LFWindowColor());
    Colour linecolor = Colours::darkgrey;
    Colour textcolor = Colours::white;
    int main_bottom_y = getHeight() - main_dbottom;
    int ch_bottom_y = getHeight() - ch_dbottom;
    int minviewcol = ScreenXToCol(ct_width);
    int minviewrow = ScreenYToRow(row_height);
    int maxviewcol = ScreenXToCol(getWidth());
    int maxviewrow = ScreenYToRow(main_bottom_y);
    g.setFont(GetNormalFont());
    g.setColour(linecolor);
    g.drawLine(ct_width, 0, ct_width, main_bottom_y, 2);
    g.drawLine(0, row_height, getWidth(), row_height, 2);
    g.drawLine(ct_width, main_bottom_y, getWidth(), main_bottom_y, 2);
    g.drawText("Phasor Matrix", 1, 0, ct_width - 1, row_height, Justification::centredLeft, false);
    g.setColour(Colours::white);
    g.drawText("Sort by:", ct_width + 3*ch_listbox_width + 8, getHeight() - ch_dbottom + 132,
        100, 16,  Justification::centredLeft, false);
    LS_LOCK_READ();
    //Rows = controllers
    g.saveState();
    g.reduceClipRegion(0, row_height, getWidth(), main_bottom_y - row_height);
    for(int r = std::max(minviewrow, 0); r < ctSet.size() && r <= maxviewrow; ++r){
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
    int colsmergechan = 0, colsmergefixid = 0, colsmergefixname = 0;
    for(int c = std::max(minviewcol, 0); c < chSet.size() && c <= maxviewcol; ++c){
        String chname = chSet[c]->GetName();
        int fixid = chSet[c]->GetFixID();
        String fixname = chSet[c]->GetFixName();
        bool firstcolmergechan = false, firstcolmergefixid = false, firstcolmergefixname = false;
        if(colsmergechan == 0){
            for(int c2 = c+1; c2 < chSet.size() && c2 <= maxviewcol; ++c2){
                if(chSet[c2]->GetName() != chname) break;
                ++colsmergechan;
                firstcolmergechan = true;
            }
        }
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
        g.drawText(LightingSystem::ValueToString(chSet[c]->GetDefaultValue()), x, 0,
            col_width, row_height, Justification::centred, false);
        g.drawText(Channel::OpGetLetters(chSet[c]->GetOp()), x, main_bottom_y,
            col_width, row_height, Justification::centred, false);
        g.drawText("X", x, main_bottom_y + row_height,
            col_width, row_height, Justification::centred, false);
        if(colsmergechan == 0 || firstcolmergechan){
            g.drawText(colsmergechan >= 3 ? chname : chSet[c]->GetLetters(),
                x, main_bottom_y + 2*row_height,
                col_width * (colsmergechan + 1), row_height, Justification::centred, false);
        }else{
            --colsmergechan;
        }
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
        int y = ch_bottom_y - 3*row_height;
        g.drawVerticalLine(x + col_width, 0, y);
        if(colsmergechan == 0) g.drawVerticalLine(x + col_width, y, y + row_height);
        y += row_height;
        if(colsmergefixid == 0) g.drawVerticalLine(x + col_width, y, y + row_height);
        y += row_height;
        if(colsmergefixname == 0) g.drawVerticalLine(x + col_width, y, y + row_height);
    }
    g.restoreState();
    //Cells = phasors
    g.saveState();
    g.reduceClipRegion(ct_width, row_height, getWidth()-ct_width, main_bottom_y - row_height);
    for(int c = std::max(minviewcol, 0); c < chSet.size() && c <= maxviewcol; ++c){
        int x = GetColX(c);
        for(int r = std::max(minviewrow, 0); r < ctSet.size() && r <= maxviewrow; ++r){
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
            float angle = MathConstants<float>::twoPi * phasor->angle;
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
    // Selection rectangle
    if(dragSelectRMin >= 0 and dragSelectRMax >= 0 and dragSelectCMin >= 0 and dragSelectCMax >= 0){
        g.setColour(Colours::gold);
        float xmin = GetColX(dragSelectCMin) + 1.0f, ymin = GetRowY(dragSelectRMin) + 1.0f;
        g.drawRect(xmin, ymin,
            (GetColX(dragSelectCMax) + col_width) - xmin,
            (GetRowY(dragSelectRMax) + row_height) - ymin,
            3.0f);
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
    int x = ct_width + 3*ch_listbox_width + 8;
    int y = getHeight() - ch_dbottom;
    btnAddFree->setBounds(x, y, 100, 24);
    optVVMRatio->setBounds(x, y + 32, 100, 24);
    optVVMPercent->setBounds(x, y + 56, 100, 24);
    optVVMByte->setBounds(x, y + 80, 100, 24);
    optVVMHex->setBounds(x, y + 104, 100, 24);
    optSortByFix->setBounds(x, y + 152, 100, 24);
    optSortByChan->setBounds(x, y + 176, 100, 24);
}

void MatrixEditor::rowSelected(TextListBox* parent, int row) {
    ignoreUnused(row);
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
    }else if(buttonThatWasClicked == optVVMRatio.get()){
        LightingSystem::SetValueViewMode(LightingSystem::Ratio);
        repaint();
        ControllerSystem::RefreshAllComponents();
    }else if(buttonThatWasClicked == optVVMPercent.get()){
        LightingSystem::SetValueViewMode(LightingSystem::Percent);
        repaint();
        ControllerSystem::RefreshAllComponents();
    }else if(buttonThatWasClicked == optVVMByte.get()){
        LightingSystem::SetValueViewMode(LightingSystem::Byte);
        repaint();
        ControllerSystem::RefreshAllComponents();
    }else if(buttonThatWasClicked == optVVMHex.get()){
        LightingSystem::SetValueViewMode(LightingSystem::Hex);
        repaint();
        ControllerSystem::RefreshAllComponents();
    }else if(buttonThatWasClicked == optSortByFix.get()){
        LightingSystem::SetSortByChannel(false);
        RefreshVisibleChannelSet();
        repaint();
    }else if(buttonThatWasClicked == optSortByChan.get()){
        LightingSystem::SetSortByChannel(true);
        RefreshVisibleChannelSet();
        repaint();
    }
}

void MatrixEditor::mouseDown(const MouseEvent &event){
    int c = ScreenXToCol(event.x);
    int r = ScreenYToRow(event.y);
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
            if(dragSelectRMin <= r && r <= dragSelectRMax && dragSelectCMin <= c && c <= dragSelectCMax){
                for(int r2 = std::max(dragSelectRMin, 0); r2 < ctSet.size() && r2 <= dragSelectRMax; ++r2){
                    startup.applyToControllers.add(ctSet[r2]);
                }
                for(int c2 = std::max(dragSelectCMin, 0); c2 < chSet.size() && c2 <= dragSelectCMax; ++c2){
                    startup.applyToChannels.add(chSet[c2]);
                }
            }
            Point<int> corner(getScreenX() + c*col_width - view.x + ct_width + (col_width/2) - 70,
                              getScreenY() + r*row_height - view.y + row_height + (row_height/2) - 70);
            popup.show<PhasorEditor>(corner.x, corner.y, &startup);
        }
    }else if(event.mods.isLeftButtonDown()){
        viewdragstart = view;
        dragSelectMode = event.mods.isShiftDown();
        if(dragSelectMode){
            if(event.x < ct_width) return;
            if(event.y >= getHeight() - main_dbottom) return;
            if(event.y <= row_height) return;
            //Right click in phasors area
            if(r < 0 || r >= ctSet.size()) return;
            if(c < 0 || c >= chSet.size()) return;
            startDragSelectR = dragSelectRMin = dragSelectRMax = r;
            startDragSelectC = dragSelectCMin = dragSelectCMax = c;
            repaint();
        }
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
        if(dragSelectMode){
            int c = ScreenXToCol(event.x);
            int r = ScreenYToRow(event.y);
            if(c < 0 || c >= chSet.size()) return;
            if(r < 0 || r >= ctSet.size()) return;
            dragSelectRMin = std::min(r, startDragSelectR);
            dragSelectRMax = std::max(r, startDragSelectR);
            dragSelectCMin = std::min(c, startDragSelectC);
            dragSelectCMax = std::max(c, startDragSelectC);
        }else{
            view = viewdragstart - event.getOffsetFromDragStart();
            int maxx = chSet.size() * col_width - (getWidth() - ct_width);
            int maxy = ctSet.size() * row_height - (getHeight() - main_dbottom - row_height);
            if(view.x > maxx) view.x = maxx;
            if(view.y > maxy) view.y = maxy;
            if(view.x < 0) view.x = 0;
            if(view.y < 0) view.y = 0;
        }
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
    ResetDragSelect();
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
    ResetDragSelect();
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
    ResetDragSelect();
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
    ResetDragSelect();
    chSet.clear();
    if(lstFixID->isItemSelected("Free channels")){
        for(int c=0; c<ChannelSystem::NumFreeChannels(); ++c){
            Channel *ch = ChannelSystem::GetFreeChannel(c);
            if(!lstChName->isItemSelected(ch->GetName())) continue;
            chSet.add(ch);
        }
    }
    if(LightingSystem::SortByChannel()){
        for(int cn=0; cn<lstChName->getNumRows(); ++cn){
            if(!lstChName->isRowSelected(cn)) continue;
            for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
                Fixture *fix = FixtureSystem::Fix(f);
                if(!lstFixID->isItemSelected(String(fix->GetFixID()))) continue;
                if(!lstFixName->isItemSelected(fix->GetName())) continue;
                for(int c=0; c<fix->GetNumChannels(); ++c){
                    Channel *ch = fix->GetChannel(c);
                    if(ch->GetName() != lstChName->get(cn)) continue;
                    chSet.add(ch);
                }
            }
        }
    }else{
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
    }
    repaint();
}
