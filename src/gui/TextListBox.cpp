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

#include "TextListBox.h"

void TextListBox::Listener::rowDoubleClicked(TextListBox* parent, int row) {
    ignoreUnused(parent);
    ignoreUnused(row);
}

TextListBox::TextListBox(Listener *l, bool showAllNoneButtons, String headerCaption) 
        : ListBox("TextListBox", this), listener(l), font(15.0f), selectonadd(true) {
    setMultipleSelectionEnabled(showAllNoneButtons);
    setClickingTogglesRowSelection(showAllNoneButtons);
    setRowSelectedOnMouseDown(true);
    setRowHeight(16);
    setOutlineThickness(1);
    setColour(ListBox::outlineColourId, Colours::lightgrey);
    //
    if(!headerCaption.isEmpty()){
        Label *lbl = new Label("lblName", headerCaption);
        lbl->setSize(100, 16);
        lbl->setColour(Label::backgroundColourId, LFWindowColor());
        setHeaderComponent(lbl); //gets deleted automatically
    }
    //
    if(showAllNoneButtons){
        btnAll.reset(new TextButton("btnAll"));
        addAndMakeVisible(btnAll.get());
        btnAll->setButtonText("All");
        btnAll->setConnectedEdges(Button::ConnectedOnBottom | Button::ConnectedOnRight);
        btnAll->addListener(this);
        btnAll->setAlwaysOnTop(true);
        btnNone.reset(new TextButton("btnNone"));
        addAndMakeVisible(btnNone.get());
        btnNone->setButtonText("X");
        btnNone->setConnectedEdges(Button::ConnectedOnBottom | Button::ConnectedOnLeft | Button::ConnectedOnRight);
        btnNone->addListener(this);
        btnNone->setAlwaysOnTop(true);
    }
}
TextListBox::~TextListBox(){
    //
}

void TextListBox::setSelectAddedItems(bool shouldSelect){
    selectonadd = shouldSelect;
}
void TextListBox::setListener(Listener* l){
    listener = l;
}
void TextListBox::setFont(Font newfont){
    font = newfont;
}

int TextListBox::getNumRows(){
    return strings.size();
}
String TextListBox::get(int i){
    return strings[i];
}
int TextListBox::indexOf(String s){
    return strings.indexOf(s);
}
void TextListBox::set(int i, String s){
    strings.set(i, s);
    repaintRow(i);
}

void TextListBox::add(String s){
    strings.add(s);
    updateContent();
    if(selectonadd) selectRow(strings.size()-1, false, false);
}
void TextListBox::addIfNotPresent(String s){
    if(strings.addIfNotAlreadyThere(s, false)){
        updateContent();
        if(selectonadd) selectRow(strings.size()-1, false, false);
    }
}

static void InsertInSparseSet(SparseSet<int> &ss, int i, bool select){
    for(int r=ss.getNumRanges()-1; r>=0; --r){
        Range<int> range = ss.getRange(r);
        if(range.getStart() > i){
            ss.addRange({range.getEnd(), range.getEnd()+1});
            ss.removeRange({range.getStart(), range.getStart()+1});
        }else if(range.getEnd() >= i){
            ss.addRange({range.getEnd(), range.getEnd()+1});
            if(!select) ss.removeRange({i, i+1});
            return;
        }else{
            break;
        }
    }
    if(select) ss.addRange({i, i+1});
}
static void RemoveInSparseSet(SparseSet<int> &ss, int i){
    int lastend = -2;
    for(int r=0; r<ss.getNumRanges(); ++r){
        Range<int> range = ss.getRange(r);
        if(range.getEnd() <= i){
            lastend = range.getEnd();
            continue;
        }else if(range.getStart() <= i){
            ss.removeRange({range.getEnd()-1, range.getEnd()});
            if(range.getStart()+1 == range.getEnd()) --r; //Just deleted a range
        }else{
            ss.addRange({range.getStart()-1, range.getStart()});
            ss.removeRange({range.getEnd()-1, range.getEnd()});
            if(lastend == i && range.getStart() == i+1) --r; //We have just merged two ranges
        }
    }
}

void TextListBox::insert(int i, String s){
    SparseSet<int> selection = getSelectedRows();
    strings.insert(i, s);
    InsertInSparseSet(selection, i, selectonadd);
    updateContent();
    setSelectedRows(selection);
}
void TextListBox::remove(int i){
    SparseSet<int> selection = getSelectedRows();
    strings.remove(i);
    RemoveInSparseSet(selection, i);
    updateContent();
    setSelectedRows(selection);
}
void TextListBox::clear(){
    strings.clear();
    updateContent();
}

void TextListBox::syncToSortedList(StringArray in, bool ignoreFirst){
    int s = ignoreFirst ? 1 : 0;
    int i = s;
    while(i < in.size() || s < strings.size()){
        if(i >= in.size()){
            remove(s);
        }else if(s >= strings.size()){
            add(in[i++]);
            ++s;
        }else{
            int cmpres = in[i].compareNatural(strings[s]);
            if(cmpres != 0 && i+1 < in.size() && s+1 < strings.size()
                    && in[i+1].compareNatural(strings[s+1]) == 0){
                set(s, in[i]);
                ++i; ++s;
            }else if(cmpres < 0){
                insert(s++, in[i++]);
            }else if(cmpres > 0){
                remove(s);
            }else{
                ++i; ++s;
            }
        }
    }
}

bool TextListBox::isItemSelected(String s){
    for(int i=0; i<strings.size(); ++i){
        if(strings[i].compareNatural(s) == 0){
            return isRowSelected(i);
        }
    }
    return false;
}

void TextListBox::paintListBoxItem(int rowNumber, Graphics &g, 
        int width, int height, bool rowIsSelected){
    if(rowNumber >= strings.size()) return;
    g.setColour(LookAndFeel::getDefaultLookAndFeel().findColour(
            rowIsSelected ? static_cast<ListBox::ColourIds>(HyperlinkButton::textColourId) 
            : ListBox::backgroundColourId));
    g.fillRect(0, 0, width, height);
    g.setColour(LookAndFeel::getDefaultLookAndFeel().findColour(ListBox::textColourId));
    g.setFont(font);
    g.drawText(strings[rowNumber], 4, 0, width, height, Justification::left, true);
}

void TextListBox::selectedRowsChanged(int lastRowSelected){
    if(listener != nullptr) listener->rowSelected(this, lastRowSelected);
}

void TextListBox::listBoxItemDoubleClicked(int row, const MouseEvent& e){
    ignoreUnused(e);
    if(listener != nullptr) listener->rowDoubleClicked(this, row);
}

void TextListBox::buttonClicked(Button *buttonThatWasClicked){
    if(buttonThatWasClicked == btnAll.get()){
        selectRangeOfRows(0, getNumRows(), true);
    }else if(buttonThatWasClicked == btnNone.get()){
        deselectAllRows();
    }
}

void TextListBox::resized(){
    ListBox::resized();
    if(btnAll != nullptr){
        btnAll ->setBounds(getWidth()-48, getHeight()-24, 24, 24);
        btnNone->setBounds(getWidth()-24, getHeight()-24, 24, 24);
    }
}
