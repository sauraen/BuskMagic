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

#include "TextListModel.h"

class MultiListBox : public Component, public Button::Listener
{
public:
    std::unique_ptr<TextListModel> lsm;
    std::unique_ptr<ListBox> lst;
    
    MultiListBox(TextListModel::Listener *parent_, String name) : parent(parent_){
        //Font smallfont = Font(12.0f, Font::plain).withTypefaceStyle("Regular");
        
        lblName.reset(new Label("lblName", name + ":"));
        addAndMakeVisible(lblName.get());
        //lblName->setFont(smallfont);
        
        lsm.reset(new TextListModel());
        lsm->setListener(parent);
        lst.reset(new ListBox("MultiListBox", lsm.get()));
        addAndMakeVisible(lst.get());
        lst->setMultipleSelectionEnabled(true);
        lst->setClickingTogglesRowSelection(true);
        lst->setRowHeight(16);
        lst->setOutlineThickness(1);
        lst->setColour(ListBox::outlineColourId, Colours::lightgrey);
        
        btnAll.reset(new TextButton("btnAll"));
        addAndMakeVisible(btnAll.get());
        btnAll->setButtonText("All");
        btnAll->setConnectedEdges(Button::ConnectedOnTop | Button::ConnectedOnRight);
        btnAll->addListener(this);
        
        btnNone.reset(new TextButton("btnNone"));
        addAndMakeVisible(btnNone.get());
        btnNone->setButtonText("None");
        btnNone->setConnectedEdges(Button::ConnectedOnTop | Button::ConnectedOnLeft);
        btnNone->addListener(this);
    }

    ~MultiListBox() {
        
    }

    void paint (Graphics& g) override {
        g.fillAll(LFWindowColor());
    }

    void resized() override {
        const int h = 24;
        lblName->setBounds(0, 0, getWidth(), h);
        lst->setBounds(0, h, getWidth(), getHeight() - h);
        btnAll->setBounds(0, getHeight() - h, getWidth() / 2, h);
        btnNone->setBounds(getWidth() / 2, getHeight() - h, getWidth() / 2, h);
    }
    
    void buttonClicked(Button *buttonThatWasClicked){
        if(buttonThatWasClicked == btnAll.get()){
            lst->selectRangeOfRows(0, lsm->getNumRows(), true);
        }else if(buttonThatWasClicked == btnNone.get()){
            lst->deselectAllRows();
        }
    }
    
    bool isItemSelected(String s){
        for(int i=0; i<lsm->getNumRows(); ++i){
            if(lsm->get(i) == s){
                return lst->isRowSelected(i);
            }
        }
        return false;
    }
    
#define UPDATELVALUE() lvalue = lsm->getNumRows() > l ? lsm->get(l).getIntValue() : 0
    void syncToSortedIntList(Array<int> array, bool ignoreFirst){
        int l = ignoreFirst ? 1 : 0;
        int a = 0;
        int UPDATELVALUE();
        while(l<lsm->getNumRows() || a<array.size()){
            if(l >= lsm->getNumRows()){
                lsm->add(String(array[a++]));
                ++l;
            }else if(a >= array.size()){
                lsm->remove(l);
            }else if(array[a] < lvalue){
                lsm->insert(l++, String(array[a++]));
            }else if(array[a] > lvalue){
                lsm->remove(l);
                UPDATELVALUE();
            }else{ //array[a] == lvalue
                ++a; ++l;
                UPDATELVALUE();
            }
        }
        lst->updateContent();
    }
#undef UPDATELVALUE

private:
    TextListModel::Listener *parent;
    
    std::unique_ptr<Label> lblName;
    std::unique_ptr<TextButton> btnAll;
    std::unique_ptr<TextButton> btnNone;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiListBox)
};
