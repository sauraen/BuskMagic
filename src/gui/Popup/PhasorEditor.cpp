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
#include "LightingSystem.h"
#include "gui/MatrixEditor.h"

int PhasorEditor::snapangles = 7;
static const float middlezone = 0.15f;

PhasorEditor::PhasorEditor(void *data) : gml(*this) {
    Startup *startup = (Startup*)data;
    phasor = startup->phasor;
    channel = startup->channel;
    invalidated = false;
    //
    Desktop::getInstance().addGlobalMouseListener(&gml);
    initialDragDone = false;
    enteredMiddleZone = false;
    firstTimeOut = (phasor->mag >= 0.0f && phasor->mag < middlezone);
    exitOnUp = true;
    //
    txtMag.reset(new TextEditor("txtMag"));
    addAndMakeVisible(txtMag.get());
    ConfigureTextEditor(txtMag, this, LightingSystem::ValueToString(phasor->mag));
    txtMag->setBounds(44, 148, 64, 24);

    txtAngle.reset(new TextEditor("txtAngle"));
    addAndMakeVisible(txtAngle.get());
    ConfigureTextEditor(txtAngle, this, LightingSystem::ValueToString(phasor->angle));
    txtAngle->setBounds(44, 172, 64, 24);
    //
    setWantsKeyboardFocus(true);
    setOpaque(true);
    setSize(140, 220);
}

PhasorEditor::~PhasorEditor() {
    Desktop::getInstance().removeGlobalMouseListener(&gml);
    if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->repaint();
}

void PhasorEditor::focusGained(FocusChangeType cause){
    ignoreUnused(cause);
    if(invalidated) return;
    if(initialDragDone) return;
    Point<float> mouse = phasor->GetEditorXY() + getScreenPosition().toFloat();
    Desktop::getInstance().getMainMouseSource().setScreenPosition(mouse);
    //TODO this is not getting activated
}

void PhasorEditor::paint (Graphics& g) {
    if(invalidated) return;
    g.fillAll(LFWindowColor());
    g.setFont(GetNormalFont());
    //
    g.setColour(Colours::darkgrey);
    for(int i=0; i<snapangles; ++i){
        float angle = MathConstants<float>::twoPi * (float)i / (float)snapangles;
        g.drawLine(70, 70, 70 + 100*std::cos(angle), 70 + 100*std::sin(angle));
    }
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
    g.drawText("Mag:",   1, 148, 44, 24, Justification::centredLeft, false);
    g.drawText("Angle:", 1, 172, 44, 24, Justification::centredLeft, false);
    g.setColour(Colours::darkgrey);
    g.drawText("Try: Shift, Delete, #s", 1, 196, 140, 24, Justification::centredLeft, false);
}

void PhasorEditor::resized() {

}

void PhasorEditor::textEditorTextChanged(TextEditor &editorThatWasChanged){
    if(invalidated) return;
    TEXTCHANGEDHANDLER_PRE;
    if(&editorThatWasChanged == txtMag.get()){
        if(!isviewvalue){
            turnRed = true;
        }else{
            phasor->mag = viewvalue;
            repaint();
        }
    }else if(&editorThatWasChanged == txtAngle.get()){
        if(!isviewvalue){
            turnRed = true;
        }else{
            phasor->angle = viewvalue;
            repaint();
        }
    }
    TEXTCHANGEDHANDLER_POST;
}

void PhasorEditor::buttonClicked (Button* buttonThatWasClicked){
    ignoreUnused(buttonThatWasClicked); //TODO
}

void PhasorEditor::closeEditor(){
    if(MatrixEditor::mtxed_static != nullptr) MatrixEditor::mtxed_static->grabKeyboardFocus();
}

void PhasorEditor::globalMouseUp(const MouseEvent &event){
    ignoreUnused(event);
    initialDragDone = true;
    if(exitOnUp) closeEditor();
}

void PhasorEditor::globalMouseDrag(const MouseEvent &event){
    if(initialDragDone) return;
    mouseDrag(event);
}

bool PhasorEditor::keyPressed(const KeyPress &key){
    if(invalidated) return false;
    int keycode = key.getKeyCode();
    if(keycode == KeyPress::escapeKey){
        closeEditor();
        return true;
    }else if(keycode == KeyPress::deleteKey || keycode == KeyPress::backspaceKey){
        invalidated = true;
        channel->RemovePhasor(phasor);
        closeEditor();
        return true;
    }else if(keycode == '0' || keycode == KeyPress::numberPad0){
        phasor->mag = 0.0f;
        phasor->angle = 0.0f;
        closeEditor();
        return true;
    }else if(keycode == '1' || keycode == KeyPress::numberPad1){
        phasor->mag = 1.0f;
        phasor->angle = 0.0f;
        closeEditor();
        return true;
    }else if(keycode == '2' || keycode == KeyPress::numberPad2){
        phasor->mag = 0.5f;
        phasor->angle = 0.0f;
        closeEditor();
        return true;
    }else if((keycode >= '3' && keycode <= '9')
            || (keycode >= KeyPress::numberPad3 && keycode <= KeyPress::numberPad9)){
        snapangles = (keycode >= '3' && keycode <= '9') ? (keycode - '0')
                   : (keycode - KeyPress::numberPad0);
        repaint();
        return true;
    }
    if(!initialDragDone){
        exitOnUp = false;
        return true;
    }
    return false;
}

void PhasorEditor::mouseDrag(const MouseEvent &event){
    if(invalidated) return;
    if(!isRightClick(event)) return;
    //Basic position
    Point<float> center = (getScreenPosition() + Point<int>(70, 70)).toFloat();
    Point<float> end = event.getScreenPosition().toFloat();
    float mag = center.getDistanceFrom(end);
    float angle = center.getAngleToPoint(end)/ MathConstants<float>::twoPi;
    mag /= 50.0f; //radius of circle
    angle = 0.25f - angle; //correct for stupid Juce angle system clockwise from up
    if(mag < 1e-7){ //correct for zero magnitude giving 0.25 angle
        mag = 0.0f;
        angle = 0.0f;
    }
    if(angle < 0.0f) angle += 1.0f;
    jassert(angle >= 0.0f && angle < 1.0f);
    //Snapping
    if(!event.mods.isShiftDown()){
        const float snapradius_mag = 0.08f;
        const float snapradius_angle = 0.02f;
        float snapped_mag = 1.0f;
        if(std::abs(mag - snapped_mag) <= snapradius_mag) mag = snapped_mag;
        float snapped_angle = std::floor((angle * (float)snapangles) + 0.5) / (float)snapangles;
        if(std::abs(angle - snapped_angle) <= snapradius_angle) angle = snapped_angle;
        if(angle >= 1.0f) angle -= 1.0f;
    }
    jassert(angle >= 0.0f && angle < 1.0f);
    //Negative magnitude mode
    bool negmag = phasor->mag < 0;
    if(firstTimeOut){
        if(mag >= middlezone){
            firstTimeOut = false;
        }
    }else if(!enteredMiddleZone){
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
    if(angle >= 1.0f) angle -= 1.0f;
    jassert(angle >= 0.0f && angle < 1.0f);
    phasor->mag = mag;
    phasor->angle = angle;
    txtMag->setText(LightingSystem::ValueToString(phasor->mag));
    txtAngle->setText(LightingSystem::ValueToString(phasor->angle));
    repaint();
}
