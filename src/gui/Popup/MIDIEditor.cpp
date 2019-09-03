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

#include "MIDIEditor.h"

static const int namewidth = 64;
static const int txtwidth = 144;
static const int learnwidth = 48;
static const int cmpwidth = namewidth + txtwidth + learnwidth;

MIDIEditor::MIDIEditor(void *data){
    Startup *startup = (Startup*)data;
    user = startup->user;
    int h = 0;
    for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
        MIDIUser::ActionType action = static_cast<MIDIUser::ActionType>(i);
        if(!user->HasMIDIAction(action) 
                || (startup->mode == (MIDIUser::IsKnobRelated(action) ? 1 : 2))){
            txtsSetting.add(nullptr);
            btnsLearn.add(nullptr);
        }else{
            std::unique_ptr<TextEditor> txt(new TextEditor("txt"));
            addAndMakeVisible(txt.get());
            ConfigureTextEditor(txt, this, user->GetMIDISettingStr(action));
            txt->setBounds(namewidth, h, txtwidth, 24);
            txtsSetting.add(txt.release());
            if(MIDIUser::IsOutput(action)){
                btnsLearn.add(nullptr);
            }else{
                TextButton *btn = new TextButton("btn");
                addAndMakeVisible(btn);
                btn->setButtonText("Learn");
                btn->setConnectedEdges(Button::ConnectedOnLeft);
                btn->addListener(this);
                btn->setBounds(namewidth+txtwidth, h, learnwidth, 24);
                btnsLearn.add(btn);
            }
            h += 24;
        }
    }
    btnHelp.reset(new TextButton("btnHelp"));
    addAndMakeVisible(btnHelp.get());
    btnHelp->setButtonText("?");
    btnHelp->addListener(this);
    btnHelp->setBounds(cmpwidth-24, h-24, 24, 24);
    //
    setOpaque(true);
    setSize(cmpwidth, h);
}
MIDIEditor::~MIDIEditor(){
    MIDISystem::LearnMIDIStop();
    for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
        if(txtsSetting[i] != nullptr) delete txtsSetting[i];
        if(btnsLearn[i] != nullptr) delete btnsLearn[i];
    }
}

void MIDIEditor::paint(Graphics &g){
    g.fillAll(LFWindowColor());
    g.setColour(Colours::white);
    g.setFont(GetNormalFont());
    int h = 0;
    for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
        MIDIUser::ActionType action = static_cast<MIDIUser::ActionType>(i);
        if(txtsSetting[i] == nullptr) continue;
        g.drawText(MIDIUser::GetActionName(action), 2, h, namewidth, 24, 
            Justification::centredLeft, false);
        h += 24;
    }
}
void MIDIEditor::resized(){
    //
}

void MIDIEditor::buttonClicked(Button* buttonThatWasClicked){
    if(buttonThatWasClicked == btnHelp.get()){
        InfoBox(MIDISetting::GetHelpText());
    }else{
        for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
            MIDIUser::ActionType action = static_cast<MIDIUser::ActionType>(i);
            if(buttonThatWasClicked == btnsLearn[i]){
                user->LearnMIDIStart(action, this);
                break;
            }
        }
    }
}
void MIDIEditor::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
        MIDIUser::ActionType action = static_cast<MIDIUser::ActionType>(i);
        if(&editorThatWasChanged == txtsSetting[i]){
            turnRed = !user->SetMIDISettingFromStr(action, text);
            break;
        }
    }
    TEXTCHANGEDHANDLER_POST;
}
void MIDIEditor::RefreshAfterMIDILearn(){
    const MessageManagerLock mml(Thread::getCurrentThread());
    if(!mml.lockWasGained()) return;
    for(int i=0; i<MIDIUser::ActionType_SIZE; ++i){
        MIDIUser::ActionType action = static_cast<MIDIUser::ActionType>(i);
        if(txtsSetting[i] != nullptr){
            txtsSetting[i]->setText(user->GetMIDISettingStr(action), dontSendNotification);
        }
    }
}
