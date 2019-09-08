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

class Controller : public MIDIUser {
public:
    Controller();
    virtual ~Controller();
    Controller(const Controller &other);
    virtual Controller *clone() const = 0;
    virtual String GetClassType() = 0;
    inline int64_t UUID() { return uuid; }

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

    bool IsEnabledStage() const;
    bool IsEnabledDisplay() const;
    void SetEnabledDisplay(bool en);
    
    virtual void DisplayStateChanged();
    virtual void NumStatesChanged();
    virtual void CopyState(int dst, int src);
    
    virtual void ReceivedMIDIAction(ActionType t, int val) override;

    virtual float Evaluate(float angle) const = 0;

    void RegisterComponent(ControllerCmp *cmp);
    ControllerCanvas *GetCanvas();

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) = 0;
    
protected:
    String name;

    void RefreshComponent();
    int GetEffectiveStageState() const;
    int GetEffectiveDisplayState() const;

private:
    friend class MagicValue;
    int64_t uuid;

    int group;
    Colour color, groupColor;

    Array<bool> states_enabled;

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

    float GetKnobDisplay();
    void SetKnobDisplay(float k);
    
    virtual void DisplayStateChanged() override;
    virtual void NumStatesChanged() override;
    virtual void CopyState(int dst, int src) override;

    inline MagicValue *GetLoValue() { return &lovalue; }
    inline MagicValue *GetHiValue() { return &hivalue; }

    virtual void ReceivedMIDIAction(ActionType t, int val) override;

    virtual float Evaluate(float angle) const override;

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) override;
private:
    MagicValue lovalue, hivalue;
    Array<float> states_knob;
};

class ModulatorController : public Controller {
public:
    ModulatorController();
    virtual ~ModulatorController();
    ModulatorController(const ModulatorController &other);
    virtual Controller *clone() const override;
    String GetClassType() override { return "Modulator"; }

    enum ModulatorShape { cosine, triangle, noise, pulse, sawf, sawr };
    enum TimeBase { measure, beat, second };

    inline ModulatorShape GetShape() { return shape; }
    inline void SetShape(ModulatorShape s) { shape = s; }
    inline TimeBase GetTimeBase() { return timebase; }
    inline void SetTimeBase(TimeBase t) { timebase = t; }

    inline MagicValue *GetLoValue() { return &lovalue; }
    inline MagicValue *GetHiValue() { return &hivalue; }
    inline MagicValue *GetPWValue() { return &pwvalue; }
    inline MagicValue *GetTValue() { return &tvalue; }

    virtual float Evaluate(float angle) const override;

    virtual void RemoveAllMagicValuesForChannel(const Channel *chn) override;
private:
    MagicValue lovalue, hivalue, pwvalue, tvalue;
    ModulatorShape shape;
    TimeBase timebase;
    uint64_t freet_origin;
};

namespace ControllerSystem {

    void Init(ValueTree cs_node = ValueTree());
    void Finalize();
    ValueTree Save();
    
    int NumControllers();
    Controller *GetController(int i);
    template<class CTRLR> CTRLR *AddController();
    Controller *DuplicateController(Controller *orig);
    void RemoveController(Controller *ctrlr);
    void ChangeControllerOrder(int orig, int newpos);

    void RemoveAllMagicValuesForChannel(const Channel *chn);

    void HandleMIDI(int port, MidiMessage msg);
    
    /**
     * States are 1-indexed, because state 0 is special. (E.g. if NumStates()
     * == 1, there are states 0 and 1, where state 1 is the only normal state.)
     * State 0 serves two purposes:
     * - When a protected state is activated, it's actually copied to state 0
     *   and then state 0 is activated instead. Thus, edits happen to state 0
     *   and then get subsequently overwritten.
     * - Controllers with ``nostate'' set are always in state 0.
    */
    int NumStates();
    void AddState();
    void RemoveState();
    void CopyState(int dst, int src); //1-indexed, but 0 allowed here only
    
    int GetStageState();
    int GetDisplayState();
    void ActivateState(int s); //1-indexed, see above
    void BlindState(int s); //1-indexed, see above
    bool IsStateProtected(int s); //1-indexed, see above
    void ProtectState(int s, bool protect); //1-indexed, see above
}
