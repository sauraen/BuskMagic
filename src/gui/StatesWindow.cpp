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

static const int leftsecwidth = 64;
static const int colwidth = 64;

void StatesWindow::MakeButton(int i){
    TriggerButton *trg = new TriggerButton(this, true);
    addAndMakeVisible(trg);
    trg->setTopLeftPosition(leftsecwidth + (colwidth*i) + 8, 56);
    state_triggers.add(trg);
}

void StatesWindow::ChangeSize(){
    setSize(leftsecwidth + colwidth*ControllerSystem::NumStates(), 144);
    if(getParentComponent() != nullptr){
        getParentComponent()->setSize(getWidth(), getHeight());
    }
}

void StatesWindow::SetOnlyLight(int i){
    for(int j=0; j<ControllerSystem::NumStates(); ++j){
        state_triggers[j]->SetLight(j == i);
    }
}

StatesWindow::StatesWindow(){
    btnCopy.reset(new HoldButton(this));
    btnBlind.reset(new HoldButton(this));
    addAndMakeVisible(btnCopy.get());
    addAndMakeVisible(btnBlind.get());
    btnCopy->setTopLeftPosition(8, 48);
    btnBlind->setTopLeftPosition(8, 96);
    //
    btnAdd.reset(new TextButton("btnAdd"));
    addAndMakeVisible(btnAdd.get());
    btnAdd->addListener(this);
    btnAdd->setButtonText("+");
    btnAdd->setConnectedEdges(Button::ConnectedOnRight);
    btnAdd->setBounds(8, 16, 24, 24);
    btnRemove.reset(new TextButton("btnRemove"));
    addAndMakeVisible(btnRemove.get());
    btnRemove->addListener(this);
    btnRemove->setButtonText(CharPointer_UTF8("\xe2\x88\x92"));
    btnRemove->setConnectedEdges(Button::ConnectedOnLeft);
    btnRemove->setBounds(32, 16, 24, 24);
    //
    for(int i=0; i<ControllerSystem::NumStates(); ++i) MakeButton(i);
    SetOnlyLight(ControllerSystem::GetDisplayState());
    //
    guistate = 0;
    blinker = false;
    setOpaque(true);
    ChangeSize();
    startTimer(100);
}
StatesWindow::~StatesWindow(){
    
}

void StatesWindow::paint(Graphics &g){
    g.fillAll(LFWindowColor());
    g.setColour(Colours::white);
    g.setFont(GetNormalFont());
    g.drawText("States:", 10, 0, leftsecwidth-10, 16, Justification::centredLeft, false);
    g.drawText("Copy", 0, 80, leftsecwidth, 16, Justification::centred, false);
    g.drawText("Blind", 0, 128, leftsecwidth, 16, Justification::centred, false);
    String helpstr;
    switch(guistate){
    case 0: {
        int ss = ControllerSystem::GetStageState();
        int bs = ControllerSystem::GetDisplayState();
        helpstr = "State " + String(ss+1);
        if(ss != bs){
            helpstr += ", blind " + String(bs+1);
        }
        }break;
    case 1: helpstr = "Select state to view blind"; break;
    case 2: helpstr = "Select state to copy FROM"; break;
    case 3: helpstr = "Select state to copy TO"; break;
    default: helpstr = "Error"; break;
    }
    g.drawText(helpstr, leftsecwidth+2, 128, 300, 16, Justification::centredLeft, true);
    for(int i=0; i<ControllerSystem::NumStates(); ++i){
        g.drawText(String(i+1), leftsecwidth + (colwidth*i), 0, colwidth, 24, Justification::centred, false);
    }
}
void StatesWindow::resized() {}

void StatesWindow::timerCallback() {
    if(guistate == 3){
        state_triggers[copyfrom]->SetLight(blinker);
    }else if(guistate == 2){
        //don't flash the blind state
    }else if(ControllerSystem::GetStageState() != ControllerSystem::GetDisplayState()){
        state_triggers[ControllerSystem::GetStageState()]->SetLight(blinker);
    }
    blinker = !blinker;
}

void StatesWindow::buttonClicked(Button *buttonThatWasClicked){
    int ns = ControllerSystem::NumStates();
    if(buttonThatWasClicked == btnAdd.get()){
        ControllerSystem::AddState();
        MakeButton(ns);
        ChangeSize();
    }else if(buttonThatWasClicked == btnRemove.get()){
        if(ns == 1) return;
        state_triggers.remove(ns-1);
        ControllerSystem::RemoveState();
        ChangeSize();
    }else{
        for(int i=0; i<ns; ++i){
            if(buttonThatWasClicked == state_triggers[i]){
                switch(guistate){
                case 0:
                    ControllerSystem::ActivateState(i);
                    SetOnlyLight(i);
                    repaint();
                    break;
                case 1:
                    ControllerSystem::BlindState(i);
                    SetOnlyLight(i);
                    btnBlind->setHoldState(false);
                    break;
                case 2:
                    copyfrom = i;
                    guistate = 3;
                    repaint();
                    break;
                case 3:
                    ControllerSystem::CopyState(i, copyfrom);
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
            SetOnlyLight(ControllerSystem::GetDisplayState());
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
