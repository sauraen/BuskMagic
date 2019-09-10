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

namespace TimingSystem {
    
    void Init(ValueTree ts_node = ValueTree());
    void Finalize();
    ValueTree Save();
    
    uint64_t GetTimeMS();
    
    float GetPositionInMeasure();
    float GetPositionInBeat();
    int GetCurrentBeat();
    
    float GetTempo();
    void SetTempo(float bpm);
    bool IsTempoOnlyInt();
    void SetTempoOnlyInt(bool tempoonlyint);
    
    int GetBeatsPerMeasure();
    void SetBeatsPerMeasure(int beats);
    
    void TapBeat();
    void TapMeasure();
    
    void ToggleFreeze();
    bool IsFrozen();
    
    float GetRandomAtMeasure(int64_t objectid, float period);
    float GetRandomAtBeat(int64_t objectid, float period);
    float GetRandomAtSecond(int64_t objectid, float period);
    
}
