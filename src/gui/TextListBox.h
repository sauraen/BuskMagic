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

class TextListBox : public ListBox, ListBoxModel, Button::Listener
{
public:
    class Listener{
        public:
        virtual void rowSelected(TextListBox* parent, int row)=0;
        virtual void rowDoubleClicked(TextListBox* parent, int row);
    };
    
    TextListBox(bool showAllNoneButtons = false, String headerCaption = "");
    ~TextListBox();
    
    int getNumRows() override;
    String get(int i);
    void set(int i, String s);
    
    void add(String s);
    void addIfNotPresent(String s);
    void insert(int i, String s);
    void remove(int i);
    void clear();
    
    /**
     * Make the list box contents match the given sorted list, except preserving
     * selection state on items that are common to both lists.
     * 
     * Assumes both the given list and the current list box contents are
     * sorted with sortNatural. I.e., this won't work if you've 
     * added/inserted/removed items out of order with the other functions!
     * 
     * If ignoreFirst: ignore the first item in both the given list and the list
     * box contents, begin sorting after this item.
    */
    void syncToSortedList(StringArray in, bool ignoreFirst = false);
    
    bool isItemSelected(String s);
    
    void setSelectAddedItems(bool shouldSelect);
    void setListener(Listener* l);
    void setFont(Font newfont);
    
    void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    
    void selectedRowsChanged(int lastRowSelected) override;
    void listBoxItemDoubleClicked(int row, const MouseEvent& e) override;
    
    void buttonClicked(Button *buttonThatWasClicked) override;
    
    void resized() override;
    
private:
    StringArray strings;
    Listener* listener;
    Font font;
    
    bool selectonadd;
    
    std::unique_ptr<TextButton> btnAll;
    std::unique_ptr<TextButton> btnNone;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextListBox)
};
