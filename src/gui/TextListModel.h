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

class TextListModel : public ListBoxModel {
    public:
    class Listener{
        public:
        virtual void rowSelected(TextListModel* parent, int row)=0;
        virtual void rowDoubleClicked(TextListModel* parent, int row);
    };
    
    TextListModel();
    ~TextListModel();
    
    void add(String s);
    void insert(int i, String s);
    void remove(int i);
    void clear();
    String get(int i);
    void set(int i, String s);
    
    void setListener(Listener* l);
    void setFont(Font newfont);
    
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    
    void selectedRowsChanged(int lastRowSelected) override;
    void listBoxItemDoubleClicked(int row, const MouseEvent& e) override;
    
    private:
    StringArray strings;
    Listener* listener;
    Font font;
};
