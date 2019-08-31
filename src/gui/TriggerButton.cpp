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

#include "gui/Popup/TriggerMIDI.h"
#include "LightingSystem.h"

TriggerButton::TriggerButton(Button::Listener *l) : parent(l) {
    addListener(l);
    SetColor(Colours::red);
    setTriggeredOnMouseDown(true);
    midisettings.add(new MIDISetting(false, false)); //tr_trigger - tr_trigger
    midisettings.add(new MIDISetting(true,  false)); //tr_out_on - tr_trigger
    midisettings.add(new MIDISetting(true,  false)); //tr_out_off - tr_trigger
}

void TriggerButton::mouseDown(const MouseEvent &event) {
    if(isRightClick(event)){
        Point<int> mouse = getMouseXYRelative();
        popup.show<TriggerMIDI>(mouse.x + getScreenX(), mouse.y + getScreenY(), this);
    }else{
        SynthButton::mouseDown(event); //This calls Listener::buttonClicked()
        TriggeredInternal();
    }
}

void TriggerButton::HandleMIDI(int port, MidiMessage msg){
    LS_LOCK_READ();
    if(midisettings[MIDISetting::tr_trig-MIDISetting::tr_trig]->Matches(port, msg)){
        const MessageManagerLock mml(Thread::getCurrentThread());
        if(!mml.lockWasGained()) return;
        triggerClick();
        TriggeredInternal();
    }
}
String TriggerButton::GetMIDISettingStr(MIDISetting::Type type){
    LS_LOCK_READ();
    if(type < MIDISetting::tr_trig || type > MIDISetting::tr_out_off){
        jassertfalse;
        return "Error";
    }
    return midisettings[type-MIDISetting::tr_trig]->GetStr();
}
bool TriggerButton::SetMIDISettingFromStr(MIDISetting::Type type, String str){
    LS_LOCK_WRITE();
    if(type < MIDISetting::tr_trig || type > MIDISetting::tr_out_off){
        jassertfalse;
        return "Error";
    }
    return midisettings[type-MIDISetting::tr_trig]->FromStr(str);
}
void TriggerButton::LearnMIDI(int port, MidiMessage msg){
    midisettings[MIDISetting::tr_trig-MIDISetting::tr_trig]->Learn(port, msg, false);
    midisettings[MIDISetting::tr_out_on-MIDISetting::tr_trig]->Learn(port, msg, false);
    midisettings[MIDISetting::tr_out_off-MIDISetting::tr_trig]->Learn(port, msg, true);
}

void TriggerButton::timerCallback(){
    setToggleState(false, dontSendNotification);
    midisettings[MIDISetting::tr_out_off-MIDISetting::tr_trig]->SendMsg();
    stopTimer();
}
void TriggerButton::TriggeredInternal(){
    setToggleState(true, dontSendNotification);
    midisettings[MIDISetting::tr_out_on-MIDISetting::tr_trig]->SendMsg();
    startTimer(100);
}
