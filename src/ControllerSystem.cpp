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

#include "ControllerSystem.h"

namespace ControllerSystem {
     
     namespace {
         ReadWriteLock mutex;
     }
     
}

#define CTRLRSYS_LOCK_READ() const ScopedReadLock lock(ControllerSystem::mutex)
#define CTRLRSYS_LOCK_WRITE() const ScopedWriteLock lock(ControllerSystem::mutex)

Controller::Controller() 
    : x(0), y(0), color(Colours::red), nostate(false),
      name("New Controller"), group(0), groupColor(Colours::lightgrey),
      enabled(false)
{
    en_msets.add(new MIDISetting(false, false)); //en_on
    en_msets.add(new MIDISetting(false, false)); //en_off
    en_msets.add(new MIDISetting(false, false)); //en_toggle
    en_msets.add(new MIDISetting(true,  false)); //en_out_on
    en_msets.add(new MIDISetting(true,  false)); //en_out_off
}

Controller::~Controller(){
    //
}

String Controller::GetName(){
    CTRLRSYS_LOCK_READ();
    return String(name); //This is because String is not thread-safe
}
void Controller::SetName(String n){
    CTRLRSYS_LOCK_WRITE();
    name = n;
}

void Controller::SetGroup(int g){
    CTRLRSYS_LOCK_WRITE();
    group = g;
    //TODO copy group color from other members
}
void Controller::SetGroupColor(Colour col){
    CTRLRSYS_LOCK_WRITE();
    groupColor = col;
    //TODO copy group color to other members
}



namespace ControllerSystem {
    
    
    
}
