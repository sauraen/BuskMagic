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
#include "gui/MatrixEditor.h"

PhasorEditor::PhasorEditor(void *data) : gml(*this) {
    PhasorEditorStartup *startup = (PhasorEditorStartup*)data;
    phasor = startup->phasor;
    channel = startup->channel;
    //
    Desktop::getInstance().addGlobalMouseListener(&gml);
    initialDragDone = false;
    enteredMiddleZone = false;
    exitOnUp = true;
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
    txtMag->setBounds(44, 148, 64, 24);
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
    txtAngle->setBounds(44, 172, 64, 24);
    txtAngle->setText(String(phasor->angle, 2));
    //
    setWantsKeyboardFocus(true);
    setSize(140, 268);
}

PhasorEditor::~PhasorEditor() {
    Desktop::getInstance().removeGlobalMouseListener(&gml);
    if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->repaint();
}

void PhasorEditor::focusGained(FocusChangeType cause){
    if(initialDragDone) return;
    Point<float> mouse = phasor->GetEditorXY() + getScreenPosition().toFloat();
    Desktop::getInstance().getMainMouseSource().setScreenPosition(mouse);
    //TODO this is not getting activated
}

void PhasorEditor::paint (Graphics& g) {
    g.fillAll(LFWindowColor());
    g.setFont(GetNormalFont());
    //
    g.setColour(Colours::darkgrey);
    g.drawHorizontalLine(70, 0, 140);
    g.drawVerticalLine(70, 0, 140);
    g.drawEllipse(20, 20, 100, 100, 2);
    Point<float> end = phasor->GetEditorXY();
    if(phasor->mag < 0.0f){
        g.setColour(Colours::darkgrey);
        g.drawLine(70, 70, 140 - end.x, 140 - end.y);
        g.fillEllipse(140-end.x-3, 140-end.y-3, 7, 7);
    }
    g.setColour(phasor->mag >= 0.0f ? Colours::blue : Colours::red);
    g.drawLine(70, 70, end.x, end.y, 2);
    g.setColour(Colours::white);
    g.fillEllipse(end.x-3, end.y-3, 7, 7);
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
        if(!isdec){
            turnRed = true;
        }else{
            phasor->mag = decval;
            repaint();
        }
    }else if(&editorThatWasChanged == txtAngle.get()){
        if(!isdec){
            turnRed = true;
        }else{
            phasor->angle = decval;
            repaint();
        }
    }
    TEXTCHANGEDHANDLER_POST;
}

void PhasorEditor::buttonClicked (Button* buttonThatWasClicked){
    
}

void PhasorEditor::closeEditor(){
    if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->grabKeyboardFocus();
}

void PhasorEditor::globalMouseUp(const MouseEvent &event){
    initialDragDone = true;
    if(exitOnUp) closeEditor();
}

void PhasorEditor::globalMouseDrag(const MouseEvent &event){
    if(initialDragDone) return;
    mouseDrag(event);
}

bool PhasorEditor::keyPressed(const KeyPress &key){
    if(!initialDragDone){
        int keycode = key.getKeyCode();
        if(keycode == KeyPress::escapeKey){
            closeEditor();
            return true;
        }else if(keycode == '0' || keycode == KeyPress::numberPad0){
            phasor->mag = 0.0f;
            phasor->angle = 0.0f;
            closeEditor();
        }else if(keycode == '1' || keycode == KeyPress::numberPad1){
            phasor->mag = 1.0f;
            phasor->angle = 0.0f;
            closeEditor();
        }else if(keycode == '5' || keycode == KeyPress::numberPad5){
            phasor->mag = 0.5f;
            phasor->angle = 0.0f;
            closeEditor();
        }else if(keycode == '9' || keycode == KeyPress::numberPad9){
            phasor->mag = 1.0f;
            phasor->angle = 0.25f;
            closeEditor();
        }else if(keycode == '8' || keycode == KeyPress::numberPad8){
            phasor->mag = 1.0f;
            phasor->angle = 0.5f;
            closeEditor();
        }else if(keycode == '7' || keycode == KeyPress::numberPad7){
            phasor->mag = 1.0f;
            phasor->angle = 0.75f;
            closeEditor();
        }else{
            exitOnUp = false;
            return true;
        }
    }
    return false;
}
    
void PhasorEditor::mouseDrag(const MouseEvent &event){
    if(!isRightClick(event)) return;
    Point<float> center = (getScreenPosition() + Point<int>(70, 70)).toFloat();
    Point<float> end = event.getScreenPosition().toFloat();
    float mag = center.getDistanceFrom(end);
    float angle = center.getAngleToPoint(end)/ (2.0f * M_PI);
    mag /= 50.0f; //radius of circle
    angle = 0.25f - angle; //correct for stupid Juce angle system clockwise from up
    if(mag < 1e-7){ //correct for zero magnitude giving 0.25 angle
        mag = 0.0f;
        angle = 0.0f;
    }
    //Determine whether to use negative magnitude mode
    bool negmag = phasor->mag < 0;
    const float middlezone = 0.15f;
    if(!enteredMiddleZone){
        if(mag < middlezone){
            enteredMiddleZone = true;
            middleZoneAngleEntered = angle;
            negmagEntered = negmag;
        }
    }else{
        if(mag >= middlezone){
            enteredMiddleZone = false;
        }else{
            float dangle = angle - middleZoneAngleEntered;
            if(dangle > 0.5f) dangle -= 1.0f;
            if(dangle < -0.5f) dangle += 1.0f;
            dangle = std::abs(dangle);
            if(dangle > 0.25f){
                negmag = !negmagEntered;
            }else{
                negmag = negmagEntered;
            }
        }
    }
    //Create final value
    if(negmag){
        mag = -mag;
        angle += 0.5f;
    }
    if(angle < 0.0f) angle += 1.0f;
    if(angle > 1.0f) angle -= 1.0f;
    phasor->mag = mag;
    phasor->angle = angle;
    txtMag->setText(String(phasor->mag, 2));
    txtAngle->setText(String(phasor->angle, 2));
    repaint();
}
