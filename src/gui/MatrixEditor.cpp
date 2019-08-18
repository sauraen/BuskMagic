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

MatrixEditor *MatrixEditor::mtxed_static = nullptr;

static const int ct_width = 125;
static const int ch_list_width = 150;
static const int mtx_main_height_offset = 320;
static const int mtx_ch_height_offset = 200;

MatrixEditor::MatrixEditor() {
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
    g.fillAll(Colours::orange);
}

void MatrixEditor::resized() {
    mlbCtType->setBounds(0, getHeight() - mtx_main_height_offset, ct_width, mtx_main_height_offset / 3);
    mlbCtGroup->setBounds(0, getHeight() - (mtx_main_height_offset * 2 / 3), ct_width, mtx_main_height_offset / 3);
    mlbCtName->setBounds(0, getHeight() - (mtx_main_height_offset / 3), ct_width, mtx_main_height_offset / 3);
    mlbFixID->setBounds(ct_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
    mlbFixName->setBounds(ct_width + ch_list_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
    mlbChName->setBounds(ct_width + 2*ch_list_width, getHeight() - mtx_ch_height_offset, ch_list_width, mtx_ch_height_offset);
}

void MatrixEditor::rowSelected(TextListModel* parent, int row) {
    
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
}
