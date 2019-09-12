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

class DefaultValueEditor : public Component, public TextEditor::Listener
{
public:
    DefaultValueEditor(void *data) : channel((Channel*)data) {
        txtValue.reset(new TextEditor("txtValue"));
        addAndMakeVisible(txtValue.get());
        ConfigureTextEditor(txtValue, this, LightingSystem::ValueToString(channel->GetDefaultValue()));
        setOpaque(true);
        setSize(100, 48);
    }

    ~DefaultValueEditor(){
        txtValue = nullptr;
    }

    void paint(Graphics& g) override {
        g.fillAll(LFWindowColor());
        g.setFont(GetNormalFont());
        g.setColour(Colours::white);
        g.drawText("Default value:", 0, 0, 100, 24, Justification::centredLeft, false);
    }

    void resized() override {
        txtValue->setBounds(0, 24, 64, 24);
    }

    void textEditorTextChanged(TextEditor &editorThatWasChanged) override {
        TEXTCHANGEDHANDLER_PRE;
        if(&editorThatWasChanged == txtValue.get()){
            if(!isviewvalue){
                turnRed = true;
            }else{
                channel->SetDefaultValue(viewvalue);
                if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->repaint();
            }
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

    std::unique_ptr<TextEditor> txtValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DefaultValueEditor)
};
