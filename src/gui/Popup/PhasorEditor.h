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

#include "JuceHeader.h"
#include "Common.h"

struct Phasor;
class Channel;

struct PhasorEditorStartup{
    Phasor *phasor;
    Channel *channel;
    PhasorEditorStartup(Phasor *p, Channel *c) : phasor(p), channel(c) {}
};

class PhasorEditor : public Component, 
                     public TextEditor::Listener,
                     public Button::Listener
{
public:
    PhasorEditor(void *data);
    ~PhasorEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void textEditorTextChanged(TextEditor &editorThatWasChanged) override;
    void buttonClicked(Button* buttonThatWasClicked) override;
    
    void globalMouseDrag(const MouseEvent &event);
    void globalMouseUp(const MouseEvent &event);
    
    void mouseDrag(const MouseEvent &event) override;
    void focusGained(FocusChangeType cause) override;

private:
    Phasor *phasor;
    Channel *channel;
    
    std::unique_ptr<TextEditor> txtMag;
    std::unique_ptr<TextEditor> txtAngle;
    
    class GlobalMouseListener : public MouseListener {
    public:
        GlobalMouseListener(PhasorEditor &p) : parent(p) {}
        void mouseDrag(const MouseEvent &event) { parent.globalMouseDrag(event); }
        void mouseUp(const MouseEvent &event) { parent.globalMouseUp(event); }
    private:
        PhasorEditor &parent;
    };
    GlobalMouseListener gml;
    bool initialDragDone;
    
    bool enteredMiddleZone;
    float middleZoneAngleEntered;
    bool negmagEntered;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhasorEditor)
};
