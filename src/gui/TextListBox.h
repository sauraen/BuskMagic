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
        virtual ~Listener() {}
        virtual void rowSelected(TextListBox* parent, int row)=0;
        virtual void rowDoubleClicked(TextListBox* parent, int row);
    };
    
    TextListBox(Listener *l, bool showAllNoneButtons = false, String headerCaption = "");
    ~TextListBox();
    
    int getNumRows() override;
    String get(int i);
    int indexOf(String s);
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

/**
 * Makes the list box match the data represented by GetNumItems and GetItemiString,
 * where the previous single selection is kept if it's still present in the
 * resulting list.
 * GetItemiString should be a full function call for item i returning String, e.g.
 * Database::GetItem(i)->GetSomeText(). Similarly GetNumItems should be e.g.
 * Database::GetNumItems(). selidx (int) returns the selected item afterwards,
 * which should be checked for being in range before use.
*/
#define TEXTLIST_SYNC_1SELECT(lst, GetNumItems, GetItemiString, selidx) \
    selidx = lst->getLastRowSelected(); \
    String oldstr = (selidx < 0 || selidx >= lst->getNumRows()) ? "" : lst->get(selidx); \
    int i; \
    for(i=0; i<GetNumItems; ++i){ \
        String str = GetItemiString; \
        if(lst->getNumRows() <= i) lst->add(str); \
        else lst->set(i, str); \
    } \
    for(; i<lst->getNumRows(); ) lst->remove(i); \
    int newr = lst->indexOf(oldstr); \
    if(newr >= 0 && newr != selidx){ \
        lst->selectRow(newr); \
        selidx = newr; \
    } \
    REQUIRESEMICOLON
    
    
