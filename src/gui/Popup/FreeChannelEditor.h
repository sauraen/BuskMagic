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
#include "gui/MatrixEditor.h"

class FreeChannelEditor : public Component, public TextEditor::Listener
{
public:
    FreeChannelEditor(void *data) : channel((Channel*)data) {
        txtLetters.reset(new TextEditor("txtLetters"));
        addAndMakeVisible(txtLetters.get());
        ConfigureTextEditor(txtLetters, this, channel->GetLetters());
        //
        txtName.reset(new TextEditor("txtName"));
        addAndMakeVisible(txtName.get());
        ConfigureTextEditor(txtName, this, channel->GetName());
        //
        setOpaque(true);
        setSize(100, 48);
    }

    ~FreeChannelEditor(){
        txtLetters = nullptr;
        txtName = nullptr;
    }

    void paint(Graphics& g) override {
        g.fillAll(LFWindowColor());
        g.setFont(GetNormalFont());
        g.setColour(Colours::white);
        g.drawText("Free chn:", 0, 0, 76, 24, Justification::centredLeft, false);
    }

    void resized() override {
        txtLetters->setBounds(76, 0, 24, 24);
        txtName->setBounds(0, 24, 100, 24);
    }
    
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override {
        TEXTCHANGEDHANDLER_PRE;
        if(&editorThatWasChanged == txtLetters.get()){
            turnRed = (text.isEmpty() || text.length() > 2);
            channel->SetLetters(text.isEmpty() ? "X" : text);
            if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->repaint();
        }else if(&editorThatWasChanged == txtName.get()){
            turnRed = text.isEmpty();
            channel->SetName(text.isEmpty() ? "New channel" : text);
        }
        TEXTCHANGEDHANDLER_POST;
    }
    
    bool keyPressed(const KeyPress &key) override {
        if(key.getKeyCode() == KeyPress::returnKey){
            if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->grabKeyboardFocus();
            return true;
        }
        return false;
    }

private:
    Channel *channel;
    
    std::unique_ptr<TextEditor> txtLetters;
    std::unique_ptr<TextEditor> txtName;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeChannelEditor)
};
