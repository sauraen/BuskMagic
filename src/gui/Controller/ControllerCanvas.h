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

#pragma once

#include "JuceHeader.h"
#include "Common.h"
#include "gui/Controller/ControllerCmps.h"

class ControllerCanvas : public Component
{
public:
    static const int size = 2000;
    static ControllerCanvas *canvas_static;

    ControllerCanvas() {
        jassert(canvas_static == nullptr);
        canvas_static = this;
        setOpaque(true);
        setSize(size, size);
        refreshComponents();
    }

    ~ControllerCanvas() {
        canvas_static = nullptr;
    }

    void paint(Graphics &g) override {
        g.fillAll(LFWindowColor());
    }

    void mouseDown(const MouseEvent &event) override {
        ignoreUnused(event);
        dragbegin_vp = findParentComponentOfClass<Viewport>()->getViewPosition();
    }

    void mouseDrag(const MouseEvent &event) override {
        findParentComponentOfClass<Viewport>()->setViewPosition(dragbegin_vp - event.getOffsetFromDragStart());
    }

    Point<int> GetCenterPoint() {
        Viewport *vp = findParentComponentOfClass<Viewport>();
        Point<int> ret = vp->getViewPosition();
        ret.x += vp->getWidth() / 2;
        ret.y += vp->getHeight() / 2;
        return ret;
    }

    void addComp(Controller *c){
        ControllerCmp *cmp;
        if(SimpleController *sc = dynamic_cast<SimpleController*>(c)){
            cmp = new SimpleControllerCmp(sc);
        }else if(ContinuousController *cc = dynamic_cast<ContinuousController*>(c)){
            cmp = new ContinuousControllerCmp(cc);
        }else if(ModulatorController *cc = dynamic_cast<ModulatorController*>(c)){
            cmp = new ModulatorControllerCmp(cc);
        }else{
            jassertfalse;
            return;
        }
        ctrlr_cmps.add(cmp);
        addAndMakeVisible(cmp);
        cmp->setTopLeftPosition(c->pos);
    }
    void deleteComp(Controller *ctrlr){
        ctrlr->RegisterComponent(nullptr);
        for(int i=ctrlr_cmps.size()-1; i>=0; --i){
            ControllerCmp *cc = ctrlr_cmps[i];
            if(cc->GetController() != ctrlr) continue;
            ctrlr_cmps.remove(i, true); //Deleting component removes it too
        }
        ControllerSystem::RemoveController(ctrlr);
    }
    void refreshComponents(){
        ctrlr_cmps.clear(true); //Deleting each component also removes it
        for(int i=0; i<ControllerSystem::NumControllers(); ++i){
            addComp(ControllerSystem::GetController(i));
        }
    }

private:
    Point<int> dragbegin_vp;

    OwnedArray<ControllerCmp> ctrlr_cmps;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControllerCanvas)
};
