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

#include "JuceHeader.h"
#include "Common.h"

#include "ControllerSystem.h"
#include "ChannelSystem.h"

#include "gui/TextListBox.h"

class MagicValueEditor : public Component, public TextEditor::Listener, 
        public TextListBox::Listener
{
public:
    MagicValueEditor(void *data) : magic((MagicValue*)data) {
        txtLiteral.reset(new TextEditor ("txtLiteral"));
        addAndMakeVisible(txtLiteral.get());
        txtLiteral->setMultiLine(false);
        txtLiteral->setReturnKeyStartsNewLine(false);
        txtLiteral->setEscapeAndReturnKeysConsumed(false);
        txtLiteral->setReadOnly(false);
        txtLiteral->setScrollbarsShown(true);
        txtLiteral->setCaretVisible(true);
        txtLiteral->setPopupMenuEnabled(true);
        txtLiteral->addListener(this);
        txtLiteral->setText(String(magic->GetLiteral(), 2));
    
        lstChannel.reset(new TextListBox(this));
        addAndMakeVisible(lstChannel.get());
        lstChannel->setSelectAddedItems(false);
        lstChannel->add("^ Non-magic");
        for(int i=0; i<ChannelSystem::NumFreeChannels(); ++i){
            Channel *ch = ChannelSystem::GetFreeChannel(i);
            lstChannel->add(ch->GetName());
            if(ch == magic->GetChannel()) lstChannel->selectRow(i+1);
        }
        if(magic->GetChannel() == nullptr){
            lstChannel->selectRow(0);
        }else{
            txtLiteral->setEnabled(false);
        }
        
        setOpaque(true);
        setSize(120, 200);
    }
    
    ~MagicValueEditor(){
        txtLiteral = nullptr;
        lstChannel = nullptr;
    }

    void paint(Graphics& g) override{
        g.fillAll(LFWindowColor());
    }
    
    void resized() override{
        txtLiteral->setBounds (0, 0, 48, 24);
        lstChannel->setBounds (0, 24, 120, 176);
    }
    
    void rowSelected(TextListBox *parent, int row) override {
        if (parent == lstChannel.get()) {
            if(row == 0){
                txtLiteral->setEnabled(true);
                magic->SetChannel(nullptr);
            }else{
                txtLiteral->setEnabled(false);
                if(row - 1 >= ChannelSystem::NumFreeChannels()){
                    jassertfalse;
                    return;
                }
                magic->SetChannel(ChannelSystem::GetFreeChannel(row - 1));
            }
        }
    }
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override{
        TEXTCHANGEDHANDLER_PRE;
        if(&editorThatWasChanged == txtLiteral.get()){
            if(!isdec) turnRed = true;
            else magic->SetLiteral(decval);
        }
        TEXTCHANGEDHANDLER_POST;
    }

private:
    MagicValue *magic;
    
    std::unique_ptr<TextEditor> txtLiteral;
    std::unique_ptr<TextListBox> lstChannel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagicValueEditor)
};
