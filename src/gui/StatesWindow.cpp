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

#include "StatesWindow.h"

static const int colwidth = 64;

StatesWindow *StatesWindow::sw_static = nullptr;

void StatesWindow::MakeButton(int i, ValueTree buttons_node){
    ValueTree btn = VT_GetChildWithProperty(buttons_node, idState, i);
    TriggerButton *trg = new TriggerButton(this, nullptr, true, btn);
    addAndMakeVisible(trg);
    trg->setTopLeftPosition((colwidth*i) + 8, 80);
    trgsState.add(trg);
}

void StatesWindow::ChangeSize(){
    setSize(jmax(colwidth*ControllerSystem::NumStates(), 448), 120);
    if(getParentComponent() != nullptr){
        getParentComponent()->setSize(getWidth(), getHeight());
    }
}

void StatesWindow::SetOnlyLight(int i){
    for(int j=0; j<ControllerSystem::NumStates(); ++j){
        trgsState[j]->SetLight(j == i);
    }
}

StatesWindow::StatesWindow(ValueTree sw_node){
    jassert(sw_static == nullptr);
    sw_static = this;
    int ds = ControllerSystem::GetSelectedDisplayState();
    //
    btnCopy.reset(new HoldButton(this, VT_GetChildWithProperty(sw_node, idType, "btnCopy")));
    btnBlind.reset(new HoldButton(this, VT_GetChildWithProperty(sw_node, idType, "btnBlind")));
    addAndMakeVisible(btnCopy.get());
    addAndMakeVisible(btnBlind.get());
    btnCopy->setTopLeftPosition(64, 8);
    btnBlind->setTopLeftPosition(120, 8);
    //
    btnAdd.reset(new TextButton("btnAdd"));
    addAndMakeVisible(btnAdd.get());
    btnAdd->addListener(this);
    btnAdd->setButtonText("+");
    btnAdd->setConnectedEdges(Button::ConnectedOnRight);
    btnAdd->setBounds(8, 20, 24, 24);
    btnRemove.reset(new TextButton("btnRemove"));
    addAndMakeVisible(btnRemove.get());
    btnRemove->addListener(this);
    btnRemove->setButtonText(CharPointer_UTF8("\xe2\x88\x92"));
    btnRemove->setConnectedEdges(Button::ConnectedOnLeft);
    btnRemove->setBounds(32, 20, 24, 24);
    chkProtected.reset(new ToggleButton("Protected"));
    addAndMakeVisible(chkProtected.get());
    chkProtected->addListener(this);
    chkProtected->setBounds(176, 4, 100, 24);
    UpdateChkProtected();
    txtFade.reset(new TextEditor("txtFade"));
    addAndMakeVisible(txtFade.get());
    ConfigureTextEditor(txtFade, this, FloatToString(ControllerSystem::GetDestFadeTime(), 1, 2));
    txtFade->setBounds(228, 30, 36, 24);
    //
    ValueTree buttons_node = VT_GetChildWithName(sw_node, idStates);
    for(int i=0; i<ControllerSystem::NumStates(); ++i) MakeButton(i, buttons_node);
    SetOnlyLight(ds-1);
    //
    guistate = 0;
    blinker = false;
    setOpaque(true);
    ChangeSize();
    startTimer(100);
}
StatesWindow::~StatesWindow(){
    sw_static = nullptr;
}
ValueTree StatesWindow::Save(){
    ValueTree ret(idStatesWindow);
    VT_AddChildSetProperty(ret, idType, "btnCopy", btnCopy->Save());
    VT_AddChildSetProperty(ret, idType, "btnBlind", btnBlind->Save());
    ValueTree buttons_node(idStates);
    for(int i=0; i<ControllerSystem::NumStates(); ++i){
        VT_AddChildSetProperty(buttons_node, idState, i, trgsState[i]->Save());
    }
    ret.addChild(buttons_node, -1, nullptr);
    return ret;
}

void StatesWindow::paint(Graphics &g){
    g.fillAll(LFWindowColor());
    g.setColour(Colours::white);
    g.setFont(GetNormalFont());
    g.drawText("States:", 10, 4, 54, 16, Justification::centredLeft, false);
    g.drawText("Copy", 64, 40, 48, 16, Justification::centred, false);
    g.drawText("Blind", 120, 40, 48, 16, Justification::centred, false);
    g.drawText("Fade in:", 176, 30, 52, 24, Justification::centredLeft, false);
    String helpstr;
    switch(guistate){
    case 0: {
        int ss = ControllerSystem::GetSelectedStageState();
        int ds = ControllerSystem::GetSelectedDisplayState();
        helpstr = "State " + String(ss);
        if(ss != ds){
            helpstr += ", blind " + String(ds);
            if(ControllerSystem::IsStateProtected(ds)){
                helpstr += " (WARNING: Editing protected state!)";
            }
        }
        }break;
    case 1: helpstr = "Select state to view blind"; break;
    case 2: helpstr = "Select state to copy FROM"; break;
    case 3: helpstr = "Select state to copy TO"; break;
    default: helpstr = "Error"; break;
    }
    g.drawText(helpstr, 280, 0, getWidth()-200, 48, Justification::centredLeft, true);
    for(int i=0; i<ControllerSystem::NumStates(); ++i){
        g.drawText(String(i+1), colwidth*i, 56, colwidth, 24, Justification::centred, false);
    }
}
void StatesWindow::resized() {}

void StatesWindow::timerCallback() {
    static bool lastTransitioning = false;
    int ss = ControllerSystem::GetSelectedStageState();
    int ds = ControllerSystem::GetSelectedDisplayState();
    int fs = ControllerSystem::GetFadeDestState();
    if(guistate == 3){
        trgsState[copyfrom]->SetLight(blinker);
    }else if(guistate == 2){
        //don't flash the blind state
    }else if(ss != ds){
        trgsState[ss-1]->SetLight(blinker);
    }else if(fs >= 1){
        trgsState[fs-1]->SetLight(blinker);
        lastTransitioning = true;
    }
    blinker = !blinker;
    if(lastTransitioning && fs <= 0){
        UpdateChkProtected();
        SetOnlyLight(ss-1);
        repaint();
        lastTransitioning = false;
    }
}

void StatesWindow::UpdateChkProtected(){
    chkProtected->setToggleState(ControllerSystem::IsStateProtected(
        ControllerSystem::GetSelectedDisplayState()), dontSendNotification);
}

void StatesWindow::buttonClicked(Button *buttonThatWasClicked){
    int ns = ControllerSystem::NumStates();
    int ds = ControllerSystem::GetSelectedDisplayState();
    if(buttonThatWasClicked == btnAdd.get()){
        ControllerSystem::AddState();
        MakeButton(ns, ValueTree());
        ChangeSize();
        repaint();
    }else if(buttonThatWasClicked == btnRemove.get()){
        if(ns == 1) return;
        trgsState.remove(ns-1);
        ControllerSystem::RemoveState();
        ChangeSize();
        repaint();
    }else if(buttonThatWasClicked == chkProtected.get()){
        ControllerSystem::ProtectState(ds, chkProtected->getToggleState());
    }else{
        for(int i=0; i<ns; ++i){
            if(buttonThatWasClicked == trgsState[i]){
                switch(guistate){
                case 0:
                    ControllerSystem::ActivateState(i+1);
                    UpdateChkProtected();
                    txtFade->setText(FloatToString(ControllerSystem::GetDestFadeTime(), 1, 2));
                    SetOnlyLight(i);
                    repaint();
                    break;
                case 1:
                    ControllerSystem::BlindState(i+1);
                    UpdateChkProtected();
                    SetOnlyLight(i);
                    btnBlind->setHoldState(false);
                    break;
                case 2:
                    copyfrom = i;
                    guistate = 3;
                    repaint();
                    break;
                case 3:
                    ControllerSystem::CopyState(i+1, copyfrom+1);
                    btnCopy->setHoldState(false);
                    break;
                }
                break;
            }
        }
    }
}
void StatesWindow::holdButtonStateChanged(HoldButton *buttonWhoseStateChanged){
    if(buttonWhoseStateChanged == btnCopy.get()){
        if(btnCopy->getToggleState()){
            SetOnlyLight(-1);
            guistate = 2;
            repaint();
        }else{
            SetOnlyLight(ControllerSystem::GetSelectedDisplayState()-1);
            guistate = 0;
            repaint();
        }
    }else if(buttonWhoseStateChanged == btnBlind.get()){
        if(btnBlind->getToggleState()){
            guistate = 1;
            repaint();
        }else{
            guistate = 0;
            repaint();
        }
    }
}

void StatesWindow::textEditorTextChanged(TextEditor &editorThatWasChanged){
    bool turnRed = false;
    String text = editorThatWasChanged.getText();
    bool isdec = isDec(text, false);
    float decval = text.getFloatValue();
    if(&editorThatWasChanged == txtFade.get()){
        if(!isdec) turnRed = true; else ControllerSystem::SetDestFadeTime(decval);
    }
    TurnRed(&editorThatWasChanged, turnRed);
}

void StatesWindow::HandleMIDI(int port, MidiMessage msg){
    for(int i=0; i<ControllerSystem::NumStates(); ++i){
        trgsState[i]->HandleMIDI(port, msg);
    }
    btnCopy->HandleMIDI(port, msg);
    btnBlind->HandleMIDI(port, msg);
}
