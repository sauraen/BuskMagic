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

#include "ControllerSystem.h"
#include "gui/Controller/EnableButton.h"
#include "gui/Controller/CCKnob.h"
#include "gui/Popup/PopupWindow.h"
#include "gui/Popup/CtrlrEditor.h"
#include "gui/MagicValueBox.h"

#include <atomic>

class ControllerCanvas;

class ControllerCmp : public Component, private Timer
{
public:
    ControllerCmp(Controller *c) : controller(c), texty(10), textwidth(64){
        setOpaque(true);
        controller->RegisterComponent(this);
        btnEnable.reset(new EnableButton(controller));
        addAndMakeVisible(btnEnable.get());
        btnEnable->setTopLeftPosition(0, 0); //To be overridden
        setSize(50, 50); //To be overridden
        notNeedsRepaint.test_and_set();
        startTimer(33);
    }
    ~ControllerCmp() {
        controller->RegisterComponent(nullptr);
        btnEnable = nullptr;
    }
    inline Controller *GetController() { return controller; }

    void paint (Graphics& g) override {
        g.fillAll(controller->GetGroupColor());
        g.setColour(GetTextColorFor(controller->GetGroupColor()));
        g.setFont (10.0f);
        g.drawMultiLineText(controller->GetName(), 2, texty, textwidth - 2, Justification::centred);
    }

    void mouseDown(const MouseEvent &event) override {
        if(isRightClick(event)){
            popup.show<CtrlrEditor>(event.getScreenX(), event.getScreenY(), controller);
        }else if(event.mods.isLeftButtonDown()){
            dragbegin_local = event.getMouseDownPosition();
            beginDragAutoRepeat(20);
        }
    }

    void mouseDrag(const MouseEvent &event) override;
    
    inline void notifyRepaint() { notNeedsRepaint.clear(); }

protected:
    Controller *controller;
    int texty;
    int textwidth;
    std::unique_ptr<EnableButton> btnEnable;
private:
    Point<int> dragbegin_local;
    PopupWindow popup;
    std::atomic_flag notNeedsRepaint;
    
    void timerCallback() override{
        if(!notNeedsRepaint.test_and_set()) repaint();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControllerCmp)
};

class SimpleControllerCmp : public ControllerCmp
{
public:
    SimpleControllerCmp(SimpleController *sc)
        : ControllerCmp(sc), scontroller(sc){
        boxValue.reset(new MagicValueBox(sc->GetValue()));
        addAndMakeVisible(boxValue.get());
        boxValue->setTopLeftPosition(16, 4);
        btnEnable->setTopLeftPosition(8, 24);
        setSize(64, 88);
        texty = 70;
        textwidth = getWidth();
    }
    ~SimpleControllerCmp() {}

private:
    SimpleController *scontroller;

    std::unique_ptr<MagicValueBox> boxValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleControllerCmp)
};

class ContinuousControllerCmp : public ControllerCmp, public Slider::Listener
{
public:
    ContinuousControllerCmp(ContinuousController *cc)
        : ControllerCmp(cc), ccontroller(cc){
        knob.reset(new CCKnob(ccontroller));
        addAndMakeVisible(knob.get());
        knob->addListener(this);
        knob->setTopLeftPosition(8, -4);

        boxLo.reset(new MagicValueBox(cc->GetLoValue()));
        boxHi.reset(new MagicValueBox(cc->GetHiValue()));
        addAndMakeVisible(boxLo.get());
        addAndMakeVisible(boxHi.get());
        boxLo->setTopLeftPosition(4, 56);
        boxHi->setTopLeftPosition(44, 56);

        btnEnable->setTopLeftPosition(16, 76);
        setSize(80, 136);
        texty = 120;
        textwidth = getWidth();
    }
    ~ContinuousControllerCmp() {}

    void sliderValueChanged(Slider *slider) override {
        if(slider == knob.get()){
            ccontroller->SetKnobDisplay(knob->getValue());
        }
    }

private:
    ContinuousController *ccontroller;

    std::unique_ptr<CCKnob> knob;
    std::unique_ptr<MagicValueBox> boxLo;
    std::unique_ptr<MagicValueBox> boxHi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContinuousControllerCmp)
};

inline void ConfigureImageButton(std::unique_ptr<ImageButton> &btn, 
        Component *parent, Button::Listener *alsoparent,
        Image &img, const char *img_data, int img_size, bool initvalue){
    img = ImageCache::getFromMemory(img_data, img_size);
    btn.reset(new ImageButton());
    parent->addAndMakeVisible(btn.get());
    btn->addListener(alsoparent);
    const Colour normalColor = Colour(0x00000000);
    const Colour overColor   = Colour(0xFFFFFF30);
    const Colour downColor   = Colour(0xFF0000FF);
    btn->setImages(true, false, true, img, 1.0f, normalColor,
                                      img, 1.0f, overColor,
                                      img, 1.0f, downColor, 0.0f);
    btn->setClickingTogglesState(true);
    btn->setRadioGroupId(1, dontSendNotification);
    btn->setToggleState(initvalue, dontSendNotification);
}

class ModulatorControllerCmp : public ControllerCmp, public Button::Listener
{
public:
    ModulatorControllerCmp(ModulatorController *mc)
        : ControllerCmp(mc), mcontroller(mc){
        boxLo.reset(new MagicValueBox(mc->GetLoValue()));
        boxHi.reset(new MagicValueBox(mc->GetHiValue()));
        boxPW.reset(new MagicValueBox(mc->GetPWValue()));
        boxT .reset(new MagicValueBox(mc->GetTValue()));
        addAndMakeVisible(boxLo.get());
        addAndMakeVisible(boxHi.get());
        addAndMakeVisible(boxPW.get());
        addAndMakeVisible(boxT.get());

        ConfigureImageButton(btnCosine, this, this, imgCosine, imgCosine_data, imgCosine_size, mc->GetShape() == ModulatorController::cosine);
        ConfigureImageButton(btnTriangle, this, this, imgTriangle, imgTriangle_data, imgTriangle_size, mc->GetShape() == ModulatorController::triangle);
        ConfigureImageButton(btnNoise, this, this, imgNoise, imgNoise_data, imgNoise_size, mc->GetShape() == ModulatorController::noise);
        ConfigureImageButton(btnPulse, this, this, imgPulse, imgPulse_data, imgPulse_size, mc->GetShape() == ModulatorController::pulse);
        ConfigureImageButton(btnSawF, this, this, imgSawF, imgSawF_data, imgSawF_size, mc->GetShape() == ModulatorController::sawf);
        ConfigureImageButton(btnSawR, this, this, imgSawR, imgSawR_data, imgSawR_size, mc->GetShape() == ModulatorController::sawr);

        Colour textcolor = GetTextColorFor(mcontroller->GetGroupColor());
        optMeasure.reset(new ToggleButton());
        optBeat   .reset(new ToggleButton());
        optSecond .reset(new ToggleButton());
        addAndMakeVisible(optMeasure.get());
        addAndMakeVisible(optBeat.get());
        addAndMakeVisible(optSecond.get());
        ConfigureOptionButton(optMeasure, this, 2, textcolor, "Measure", mc->GetTimeBase() == ModulatorController::measure);
        ConfigureOptionButton(optBeat, this, 2, textcolor, "Beat", mc->GetTimeBase() == ModulatorController::beat);
        ConfigureOptionButton(optSecond, this, 2, textcolor, "Second", mc->GetTimeBase() == ModulatorController::second);
        
        setSize(296, 96);
        texty = 12;
        textwidth = 64;
        btnEnable->setTopLeftPosition(8, 40);
        
        const int shape_x = 72, shape_y = 4;
        btnCosine->  setTopLeftPosition(shape_x,    shape_y);
        btnTriangle->setTopLeftPosition(shape_x,    shape_y+24);
        btnNoise->   setTopLeftPosition(shape_x,    shape_y+48);
        btnPulse->   setTopLeftPosition(shape_x+36, shape_y);
        btnSawF->    setTopLeftPosition(shape_x+36, shape_y+24);
        btnSawR->    setTopLeftPosition(shape_x+36, shape_y+48);
        
        boxLo->setTopLeftPosition(176, 48);
        boxHi->setTopLeftPosition(176, 16);
        boxPW->setTopLeftPosition(108, 76);
        boxT ->setTopLeftPosition(236, 6);
        
        optMeasure->setBounds(216, 28, 76, 20);
        optBeat   ->setBounds(216, 48, 76, 20);
        optSecond ->setBounds(216, 68, 76, 20);
    }
    ~ModulatorControllerCmp() {}
    
    void paint(Graphics &g) override {
        ControllerCmp::paint(g);
        g.setFont(GetNormalFont());
        g.setColour(GetTextColorFor(mcontroller->GetGroupColor()));
        g.drawText("Hi:", 152, 16, 24, 16, Justification::centredLeft, false);
        g.drawText("Lo:", 152, 48, 24, 16, Justification::centredLeft, false);
        g.drawText("PW:",  76, 76, 32, 16, Justification::centredLeft, false);
        g.drawText("T:",  220,  6, 24, 16, Justification::centredLeft, false);
    }

    void buttonClicked(Button* buttonThatWasClicked) override {
        if(buttonThatWasClicked == btnCosine.get()){
            mcontroller->SetShape(ModulatorController::cosine);
        }else if(buttonThatWasClicked == btnTriangle.get()){
            mcontroller->SetShape(ModulatorController::triangle);
        }else if(buttonThatWasClicked == btnNoise.get()){
            mcontroller->SetShape(ModulatorController::noise);
        }else if(buttonThatWasClicked == btnPulse.get()){
            mcontroller->SetShape(ModulatorController::pulse);
        }else if(buttonThatWasClicked == btnSawF.get()){
            mcontroller->SetShape(ModulatorController::sawf);
        }else if(buttonThatWasClicked == btnSawR.get()){
            mcontroller->SetShape(ModulatorController::sawr);
        }else if(buttonThatWasClicked == optMeasure.get()){
            mcontroller->SetTimeBase(ModulatorController::measure);
        }else if(buttonThatWasClicked == optBeat.get()){
            mcontroller->SetTimeBase(ModulatorController::beat);
        }else if(buttonThatWasClicked == optSecond.get()){
            mcontroller->SetTimeBase(ModulatorController::second);
        }
    }

private:
    ModulatorController *mcontroller;

    std::unique_ptr<MagicValueBox> boxLo;
    std::unique_ptr<MagicValueBox> boxHi;
    std::unique_ptr<MagicValueBox> boxPW;
    std::unique_ptr<MagicValueBox> boxT;

    std::unique_ptr<ImageButton> btnCosine;
    std::unique_ptr<ImageButton> btnTriangle;
    std::unique_ptr<ImageButton> btnNoise;
    std::unique_ptr<ImageButton> btnPulse;
    std::unique_ptr<ImageButton> btnSawF;
    std::unique_ptr<ImageButton> btnSawR;
    Image imgCosine;
    Image imgTriangle;
    Image imgNoise;
    Image imgPulse;
    Image imgSawF;
    Image imgSawR;
    static const char *imgCosine_data;
    static const char *imgTriangle_data;
    static const char *imgNoise_data;
    static const char *imgPulse_data;
    static const char *imgSawF_data;
    static const char *imgSawR_data;
    static const int imgCosine_size;
    static const int imgTriangle_size;
    static const int imgNoise_size;
    static const int imgPulse_size;
    static const int imgSawF_size;
    static const int imgSawR_size;

    std::unique_ptr<ToggleButton> optMeasure;
    std::unique_ptr<ToggleButton> optBeat;
    std::unique_ptr<ToggleButton> optSecond;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatorControllerCmp)
};
