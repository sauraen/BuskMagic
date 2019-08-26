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

#include "ChannelSystem.h"
#include "gui/TextListBox.h"
#include "gui/MatrixEditor.h"

class ChannelOpEditor : public Component, public TextListBox::Listener
{
public:
    ChannelOpEditor(void *data) : channel((Channel*)data), initted(false) {
        lstOps.reset(new TextListBox(this, false, "Channel operator:"));
        addAndMakeVisible(lstOps.get());
        lstOps->setSelectAddedItems(false);
        for(int i=0; i<Channel::NUM_OPS; ++i){
            lstOps->add(Channel::OpGetLetters((Channel::ChannelOp)i) 
                + " (" + Channel::OpGetDescription((Channel::ChannelOp)i) + ")");
        }
        lstOps->selectRow(channel->GetOp());
        initted = true;
        setOpaque(true);
        setSize(200, 200);
    }

    ~ChannelOpEditor(){
        lstOps = nullptr;
    }

    void paint(Graphics& g) override {
        g.fillAll(LFWindowColor());
    }

    void resized() override {
        lstOps->setBounds(0, 0, 200, 200);
    }
    
    void rowSelected(TextListBox *parent, int row) override {
        if(parent == lstOps.get()){
            if(!initted) return;
            if(row < 0 || row >= Channel::NUM_OPS) return;
            channel->SetOp((Channel::ChannelOp)row);
            if(MatrixEditor::mtxed_static != nullptr){
                MatrixEditor::mtxed_static->repaint();
                MatrixEditor::mtxed_static->grabKeyboardFocus();
            }
        }
    }

private:
    Channel *channel;
    bool initted = false;
    
    std::unique_ptr<TextListBox> lstOps;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelOpEditor)
};
