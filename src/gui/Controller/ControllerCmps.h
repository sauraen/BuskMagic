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

class ControllerCanvas;

class ControllerCmp : public Component
{
public:
    ControllerCmp(Controller *c) : controller(c), texty(10), textwidth(64){
        setOpaque(true);
        controller->RegisterComponent(this);
        btnEnable.reset(new EnableButton(controller));
        addAndMakeVisible(btnEnable.get());
        btnEnable->setTopLeftPosition(0, 0); //To be overridden
        setSize(50, 50); //To be overridden
    }
    ~ControllerCmp() {
        controller->RegisterComponent(nullptr);
        btnEnable = nullptr;
    }
    inline Controller *GetController() { return controller; }

    void paint (Graphics& g) override {
        g.fillAll(controller->GetGroupColor());
        g.setColour(controller->GetGroupColor().getBrightness() > 0.5f ? Colours::black : Colours::white);
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

protected:
    Controller *controller;
    int texty;
    int textwidth;
    std::unique_ptr<EnableButton> btnEnable;
private:
    Point<int> dragbegin_local;
    PopupWindow popup;

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
            ccontroller->SetKnob(knob->getValue());
        }
    }

private:
    ContinuousController *ccontroller;

    std::unique_ptr<CCKnob> knob;
    std::unique_ptr<MagicValueBox> boxLo;
    std::unique_ptr<MagicValueBox> boxHi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContinuousControllerCmp)
};

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
        boxLo->setTopLeftPosition(176, 32);
        boxHi->setTopLeftPosition(176, 8);
        boxPW->setTopLeftPosition(176, 56);
        boxT ->setTopLeftPosition(236, 8);

        imgCosine = ImageCache::getFromMemory(imgCosine_data, imgCosine_size);
        imgTriangle = ImageCache::getFromMemory(imgTriangle_data, imgTriangle_size);
        imgNoise = ImageCache::getFromMemory(imgNoise_data, imgNoise_size);
        imgPulse = ImageCache::getFromMemory(imgPulse_data, imgPulse_size);
        imgSawF = ImageCache::getFromMemory(imgSawF_data, imgSawF_size);
        imgSawR = ImageCache::getFromMemory(imgSawR_data, imgSawR_size);
        btnCosine  .reset(new ImageButton());
        btnTriangle.reset(new ImageButton());
        btnNoise   .reset(new ImageButton());
        btnPulse   .reset(new ImageButton());
        btnSawF    .reset(new ImageButton());
        btnSawR    .reset(new ImageButton());
        addAndMakeVisible(btnCosine.get());
        addAndMakeVisible(btnTriangle.get());
        addAndMakeVisible(btnNoise.get());
        addAndMakeVisible(btnPulse.get());
        addAndMakeVisible(btnSawF.get());
        addAndMakeVisible(btnSawR.get());
        const Colour normalColor = Colour(0x00000000);
        const Colour overColor   = Colour(0xFFFFFF30);
        const Colour downColor   = Colour(0xFF0000FF);
        btnCosine->setImages(true, false, true, imgCosine, 1.0f, normalColor,
                                                imgCosine, 1.0f, overColor,
                                                imgCosine, 1.0f, downColor, 0.0f);
        btnTriangle->setImages(true, false, true, imgTriangle, 1.0f, normalColor,
                                                  imgTriangle, 1.0f, overColor,
                                                  imgTriangle, 1.0f, downColor, 0.0f);
        btnNoise->setImages(true, false, true, imgNoise, 1.0f, normalColor,
                                               imgNoise, 1.0f, overColor,
                                               imgNoise, 1.0f, downColor, 0.0f);
        btnPulse->setImages(true, false, true, imgPulse, 1.0f, normalColor,
                                               imgPulse, 1.0f, overColor,
                                               imgPulse, 1.0f, downColor, 0.0f);
        btnSawF->setImages(true, false, true, imgSawF, 1.0f, normalColor,
                                              imgSawF, 1.0f, overColor,
                                              imgSawF, 1.0f, downColor, 0.0f);
        btnSawR->setImages(true, false, true, imgSawR, 1.0f, normalColor,
                                              imgSawR, 1.0f, overColor,
                                              imgSawR, 1.0f, downColor, 0.0f);
        btnCosine->  setClickingTogglesState(true);
        btnTriangle->setClickingTogglesState(true);
        btnNoise->   setClickingTogglesState(true);
        btnPulse->   setClickingTogglesState(true);
        btnSawF->    setClickingTogglesState(true);
        btnSawR->    setClickingTogglesState(true);
        btnCosine->  setRadioGroupId(1, dontSendNotification);
        btnTriangle->setRadioGroupId(1, dontSendNotification);
        btnNoise->   setRadioGroupId(1, dontSendNotification);
        btnPulse->   setRadioGroupId(1, dontSendNotification);
        btnSawF->    setRadioGroupId(1, dontSendNotification);
        btnSawR->    setRadioGroupId(1, dontSendNotification);
        btnCosine->  setToggleState(mc->GetShape() == ModulatorController::cosine, dontSendNotification);
        btnTriangle->setToggleState(mc->GetShape() == ModulatorController::triangle, dontSendNotification);
        btnNoise->   setToggleState(mc->GetShape() == ModulatorController::noise, dontSendNotification);
        btnPulse->   setToggleState(mc->GetShape() == ModulatorController::pulse, dontSendNotification);
        btnSawF->    setToggleState(mc->GetShape() == ModulatorController::sawf, dontSendNotification);
        btnSawR->    setToggleState(mc->GetShape() == ModulatorController::sawr, dontSendNotification);
        const int shape_x = 72, shape_y = 4;
        btnCosine->  setTopLeftPosition(shape_x,    shape_y);
        btnTriangle->setTopLeftPosition(shape_x,    shape_y+24);
        btnNoise->   setTopLeftPosition(shape_x,    shape_y+48);
        btnPulse->   setTopLeftPosition(shape_x+36, shape_y);
        btnSawF->    setTopLeftPosition(shape_x+36, shape_y+24);
        btnSawR->    setTopLeftPosition(shape_x+36, shape_y+48);

        btnEnable->setTopLeftPosition(8, 40);
        setSize(300, 82);
        texty = 12;
        textwidth = 64;
    }
    ~ModulatorControllerCmp() {}

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
        }
    }

    void paint(Graphics &g) override {
        ControllerCmp::paint(g);
        g.setFont(GetNormalFont());
        g.drawText("Hi:", 152,  4, 24, 24, Justification::centredLeft, false);
        g.drawText("Lo:", 152, 28, 24, 24, Justification::centredLeft, false);
        g.drawText("PW:", 152, 52, 24, 24, Justification::centredLeft, false);
        g.drawText("T:",  216,  4, 24, 24, Justification::centredLeft, false);
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
