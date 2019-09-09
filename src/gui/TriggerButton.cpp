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

#include "TriggerButton.h"

#include "gui/Popup/MIDIEditor.h"
#include "LightingSystem.h"

TriggerButton::TriggerButton(Button::Listener *l, HiSpeedListener *h_or_nullptr, 
        bool manuallight) : parent(l), hsl(h_or_nullptr), manual(manuallight) {
    addListener(l);
    SetColor(Colours::red);
    setTriggeredOnMouseDown(true);
    AddMIDIAction(MIDIUser::in_trigger);
    AddMIDIAction(MIDIUser::out_on);
    AddMIDIAction(MIDIUser::out_off);
    notNeedsTrigger.test_and_set();
    turnOffCountdown = -1;
    startTimer(33);
}

void TriggerButton::mouseDown(const MouseEvent &event) {
    if(isRightClick(event)){
        Point<int> mouse = getMouseXYRelative();
        MIDIEditor::Startup startup(this, 0);
        popup.show<MIDIEditor>(mouse.x + getScreenX(), mouse.y + getScreenY(), &startup);
    }else{
        if(hsl != nullptr) hsl->triggeredHiSpeed(this);
        SynthButton::mouseDown(event); //This calls Listener::buttonClicked()
        TriggeredInternal();
    }
}

void TriggerButton::ReceivedMIDIAction(ActionType t, int val){
    ignoreUnused(val);
    LS_LOCK_READ();
    if(t == MIDIUser::in_trigger){
        if(hsl != nullptr) hsl->triggeredHiSpeed(this);
        notNeedsTrigger.clear();
    }
}

void TriggerButton::SetLight(bool l){
    if(!manual){
        jassertfalse;
        return;
    }
    setToggleState(l, dontSendNotification);
    SendMIDIAction(l ? MIDIUser::out_on : MIDIUser::out_off);
}

void TriggerButton::timerCallback(){
    if(!notNeedsTrigger.test_and_set()){
        triggerClick();
        TriggeredInternal();
    }
    if(manual) return;
    if(turnOffCountdown > 0){
        --turnOffCountdown;
        if(turnOffCountdown == 0){
            turnOffCountdown = -1;
            setToggleState(false, dontSendNotification);
            SendMIDIAction(MIDIUser::out_off);
        }
    }
}
void TriggerButton::TriggeredInternal(){
    if(manual) return;
    setToggleState(true, dontSendNotification);
    SendMIDIAction(MIDIUser::out_on);
    turnOffCountdown = 3;
}
