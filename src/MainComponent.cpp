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

#include "MainComponent.h"
#include "gui/MIDISetup.h"
#include "gui/ArtNetSetup.h"
#include "gui/FixtureEditor.h"
#include "gui/Patcher.h"

MainComponent::MainComponent(){
    addAndMakeVisible(new Patcher());
    setSize (1000, 800);
}

MainComponent::~MainComponent(){
    
}

void MainComponent::paint (Graphics& g){
    
}

void MainComponent::resized(){
    
}
