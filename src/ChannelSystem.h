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

class Controller;
class Fixture;

struct Phasor {
    Controller *src;
    float mag;
    float angle; //in cycles
    
    Phasor(Controller *c) : src(c), mag(0.0f), angle(0.0f) {}
    Phasor(Controller *c, float m, float a) : src(c), mag(m), angle(a) {}
    Phasor(const Phasor &other) = default;
    Phasor &operator=(const Phasor &other) = default;
    
    Point<float> GetEditorXY() {
        float e_mag = 50.0f * mag;
        float e_angle = MathConstants<float>::twoPi * angle;
        return Point<float>(70 + e_mag * std::cos(e_angle), 
                            70 - e_mag * std::sin(e_angle));
    }
};

class Channel {
public:
    Channel(Fixture *parentornullptr);
    ~Channel();
    
    enum ChannelOp {
        OpPrioTop, OpPrioBottom, 
        OpPrioMax, OpPrioMin, OpPrioMaxWDefault, OpPrioMinWDefault,
        OpAdd, OpMultiply, NUM_OPS
    };
    static String OpGetLetters(ChannelOp o);
    static String OpGetDescription(ChannelOp o);
    
    String GetName() const;
    void SetName(String newname);
    String GetLetters() const;
    void SetLetters(String newletters);
    inline float GetDefaultValue() const { return defaultvalue; }
    inline void SetDefaultValue(float f) { defaultvalue = f; }
    inline ChannelOp GetOp() const { return op; }
    inline void SetOp(ChannelOp o) { op = o; }
    
    String GetFixName() const;
    int GetFixID() const;
    
    inline int NumPhasors() const { return phasors.size(); }
    Phasor *GetPhasor(int i) const;
    Phasor *GetPhasorForController(Controller *c, bool addIfNotPresent);
    
    void RemovePhasor(int i);
    void RemovePhasor(Phasor *ph);
    void RemovePhasorForController(Controller *c);
    
    void SortPhasors();
    
    float Evaluate(float angle) const;
private:
    Fixture *parent;
    
    String name, letters;
    float defaultvalue;
    ChannelOp op;
    
    friend class EvaluatedTracker;
    mutable bool beingevaluated;
    
    OwnedArray<Phasor> phasors;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Channel)
};

namespace ChannelSystem {
    
    int NumTotalChannels();
    int NumFreeChannels();
    Channel *GetFreeChannel(int i);
    Channel *AddFreeChannel();
    void RemoveFreeChannel(int i);
    
    void RemoveAllPhasorsForController(Controller *c);
    void SortAllChannelPhasors();
}
