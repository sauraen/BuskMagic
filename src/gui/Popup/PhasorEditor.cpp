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

#include "PhasorEditor.h"

#include "ChannelSystem.h"

PhasorEditor::PhasorEditor(void *data) : gml(*this) {
    PhasorEditorStartup *startup = (PhasorEditorStartup*)data;
    phasor = startup->phasor;
    channel = startup->channel;
    //
    Desktop::getInstance().addGlobalMouseListener(&gml);
    //
    txtMag.reset(new TextEditor("txtMag"));
    addAndMakeVisible(txtMag.get());
    txtMag->addListener(this);
    txtMag->setMultiLine(false);
    txtMag->setReturnKeyStartsNewLine(false);
    txtMag->setEscapeAndReturnKeysConsumed(false);
    txtMag->setReadOnly(false);
    txtMag->setScrollbarsShown(false);
    txtMag->setCaretVisible(true);
    txtMag->setPopupMenuEnabled(true);
    txtMag->setBounds(40, 148, 64, 24);
    txtMag->setText(String(phasor->mag, 2));
    
    txtAngle.reset(new TextEditor("txtAngle"));
    addAndMakeVisible(txtAngle.get());
    txtAngle->addListener(this);
    txtAngle->setMultiLine(false);
    txtAngle->setReturnKeyStartsNewLine(false);
    txtAngle->setEscapeAndReturnKeysConsumed(false);
    txtAngle->setReadOnly(false);
    txtAngle->setScrollbarsShown(false);
    txtAngle->setCaretVisible(true);
    txtAngle->setPopupMenuEnabled(true);
    txtAngle->setBounds(40, 172, 64, 24);
    txtAngle->setText(String(phasor->angle, 2));
    //
    setSize(140, 268);
}

PhasorEditor::~PhasorEditor() {
    
}

void PhasorEditor::paint (Graphics& g) {
    g.fillAll(LFWindowColor());
    g.setFont(GetNormalFont());
    //
    g.setColour(Colours::darkgrey);
    g.drawHorizontalLine(70, 0, 140);
    g.drawVerticalLine(70, 0, 140);
    g.drawEllipse(20, 20, 100, 100, 2);
    g.setColour(Colours::white);
    float mag = 50.0f * phasor->mag;
    float angle = 2.0f * M_PI * phasor->angle;
    float endx = 70 + mag*std::cos(angle);
    float endy = 70 - mag*std::sin(angle);
    g.drawLine(70, 70, endx, endy, 2);
    g.drawLine(endx-1, endy-1, endx+1, endy+1, 7);
    //
    g.setColour(Colours::white);
    g.drawText("Mag:",   1, 148, 64, 24, Justification::centredLeft, false);
    g.drawText("Angle:", 1, 172, 64, 24, Justification::centredLeft, false);
}

void PhasorEditor::resized() {
    
}

void PhasorEditor::textEditorTextChanged(TextEditor &editorThatWasChanged){
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtMag.get()){
        
    }else if(&editorThatWasChanged == txtAngle.get()){
        
    }
    TEXTCHANGEDHANDLER_POST;
}

void PhasorEditor::buttonClicked (Button* buttonThatWasClicked){
    
}

void PhasorEditor::globalMouseDrag(const MouseEvent &event){
    Point<float> center = (getScreenPosition() + Point<int>(70, 70)).toFloat();
    Point<float> end = event.getScreenPosition().toFloat();
    float mag = center.getDistanceFrom(end);
    float angle = center.getAngleToPoint(end)/ (2.0f * M_PI);
    mag /= 50.0f; //radius of circle
    angle = 0.25f - angle; //correct for stupid Juce angle system clockwise from up
    phasor->mag = mag;
    phasor->angle = angle;
    repaint();
}
