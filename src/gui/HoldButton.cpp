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

#include "HoldButton.h"

#include "gui/Popup/MIDIEditor.h"
#include "LightingSystem.h"

HoldButton::HoldButton(HoldButton::Listener *l, ValueTree mu_node) 
    : MIDIUser(mu_node), parent(l) {
    SetColor(Colours::red);
    AddMIDIAction(MIDIUser::in_on);
    AddMIDIAction(MIDIUser::in_off);
    AddMIDIAction(MIDIUser::out_on);
    AddMIDIAction(MIDIUser::out_off);
    notNeedsHoldStateOff.test_and_set();
    notNeedsHoldStateOn.test_and_set();
    startTimer(33);
}

void HoldButton::mouseDown(const MouseEvent &event) {
    if(isRightClick(event)){
        Point<int> mouse = getMouseXYRelative();
        MIDIEditor::Startup startup(this, 0);
        popup.show<MIDIEditor>(mouse.x + getScreenX(), mouse.y + getScreenY(), &startup);
    }else{
        setHoldState(!getToggleState());
        SynthButton::mouseDown(event);
    }
}

void HoldButton::clicked(){
    //Do nothing, do not pass this on to the listener
}

void HoldButton::ReceivedMIDIAction(ActionType t, int val){
    ignoreUnused(val);
    LS_LOCK_READ();
    if(t == MIDIUser::in_on){
        notNeedsHoldStateOn.clear();
    }else if(t == MIDIUser::in_off){
        notNeedsHoldStateOff.clear();
    }
}

void HoldButton::timerCallback(){
    if(!notNeedsHoldStateOn.test_and_set()) setHoldState(true);
    if(!notNeedsHoldStateOff.test_and_set()) setHoldState(false);
}

void HoldButton::setHoldState(bool h){
    if(h == getToggleState()) return;
    setToggleState(h, dontSendNotification);
    SendMIDIAction(h ? MIDIUser::out_on : MIDIUser::out_off);
    parent->holdButtonStateChanged(this);
}
