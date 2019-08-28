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

#include "MIDISystem.h"

class Controller;
class Channel;

class MagicValue {
public:
    MagicValue(Controller *parent, float litvalue = 0.0f);
    ~MagicValue() {}
    MagicValue(const MagicValue &other, Controller *newparent);

    inline bool IsMagic() const { return chan != nullptr; }
    inline float GetLiteral() const { return mugglevalue; }
    void SetLiteral(float v);
    inline Channel *GetChannel() const { return chan; }
    void SetChannel(Channel *ch);

    String GetText();

    float Evaluate(float angle) const;

private:
    Controller *controller;
    float mugglevalue;
    Channel *chan;

    void RefreshComponent();
};

class ControllerCmp;
class ControllerCanvas;

class Controller {
public:
    Controller();
    virtual ~Controller();
    Controller(const Controller &other);
    virtual Controller *clone() const = 0;
    virtual String GetClassType() = 0;

    Point<int> pos;
    bool nostate;

    String GetName() const;
    void SetName(String n);
    inline Colour GetColor() { return color; }
    void SetColor(Colour col);
    inline int GetGroup() const { return group; }
    void SetGroup(int g);
    inline Colour GetGroupColor() const { return groupColor; }
    void SetGroupColor(Colour col);

    inline bool IsEnabled() const { return enabled; }
    void SetEnabled(bool en);

    virtual void HandleMIDI(int port, MidiMessage msg);
    enum MIDISettingType {
        en_on = 0,
        en_off = 1,
        en_toggle = 2,
        en_out_on = 3,
        en_out_off = 4,
        ct_in = 5,
        ct_goto_lo = 6,
        ct_goto_hi = 7,
        ct_out = 8
    };
    virtual String GetMIDISettingStr(MIDISettingType type);
    virtual bool SetMIDISettingFromStr(MIDISettingType type, String str);

    virtual float Evaluate(float angle) const = 0;

    void RegisterComponent(ControllerCmp *cmp);
    ControllerCanvas *GetCanvas();

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) = 0;

protected:
    OwnedArray<MIDISetting> midisettings;

    void RefreshComponent();

private:
    friend class MagicValue;

    String name;
    int group;
    Colour color, groupColor;

    bool enabled;

    ControllerCmp *component;
};

class SimpleController : public Controller {
public:
    SimpleController();
    virtual ~SimpleController();
    SimpleController(const SimpleController &other);
    virtual Controller *clone() const override;
    String GetClassType() override { return "Simple"; }

    inline MagicValue *GetValue() { return &value; }

    virtual float Evaluate(float angle) const override;

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) override;

private:
    MagicValue value;
};

class ContinuousController : public Controller {
public:
    ContinuousController();
    virtual ~ContinuousController();
    ContinuousController(const ContinuousController &other);
    virtual Controller *clone() const override;
    String GetClassType() override { return "Continuous"; }

    inline float GetKnob() { return knob; }
    void SetKnob(float k);

    inline MagicValue *GetLoValue() { return &lovalue; }
    inline MagicValue *GetHiValue() { return &hivalue; }

    virtual void HandleMIDI(int port, MidiMessage msg) override;
    virtual String GetMIDISettingStr(MIDISettingType type) override;
    virtual bool SetMIDISettingFromStr(MIDISettingType, String str) override;

    virtual float Evaluate(float angle) const override;

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) override;
private:
    MagicValue lovalue, hivalue;
    float knob;
};

class ModulatorController : public Controller {
public:
    ModulatorController();
    virtual ~ModulatorController();
    ModulatorController(const ModulatorController &other);
    virtual Controller *clone() const override;
    String GetClassType() override { return "Modulator"; }

    enum ModulatorShape { cosine, triangle, noise, pulse, sawf, sawr };

    inline float GetShape() { return shape; }
    inline void SetShape(ModulatorShape s) { shape = s; }

    inline MagicValue *GetLoValue() { return &lovalue; }
    inline MagicValue *GetHiValue() { return &hivalue; }
    inline MagicValue *GetPWValue() { return &pwvalue; }
    inline MagicValue *GetTValue() { return &tvalue; }

    virtual float Evaluate(float angle) const override;

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) override;
private:
    MagicValue lovalue, hivalue, pwvalue, tvalue;
    ModulatorShape shape;
};

namespace ControllerSystem {

    int NumControllers();
    Controller *GetController(int i);
    template<class CTRLR> CTRLR *AddController();
    Controller *DuplicateController(Controller *orig);
    void RemoveController(Controller *ctrlr);
    void ChangeControllerOrder(int orig, int newpos);

    void RemoveAllMagicValuesForChannel(const Channel *chn);

    void HandleMIDI(int port, MidiMessage msg);
}
