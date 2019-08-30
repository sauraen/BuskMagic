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

#include "TimingSystem.h"

namespace TimingSystem {
    
    uint64_t GetTimeMS(){
        int64_t tps = Time::getHighResolutionTicksPerSecond();
        jassert(tps >= 1000ll);
        tps /= 1000ll;
        return Time::getHighResolutionTicks() / tps;
    }
    
    uint64_t origin;
    double tempo_msperbeat;
    int measurelen;
    
    double GetPositionInMeasureInternal(){
        double dt = (double)(GetTimeMS() - origin);
        dt /= (tempo_msperbeat * (double)measurelen);
        return dt - std::floor(dt);
    }
    void SetOriginForMsrPos(double posinmsr){
        origin = GetTimeMS() - (uint64_t)(tempo_msperbeat * (double)measurelen * posinmsr);
    }
    
    float GetPositionInMeasure(){
        return (float)GetPositionInMeasureInternal();
    }
    float GetPositionInBeat(){
        double dt = (double)(GetTimeMS() - origin);
        dt /= tempo_msperbeat;
        return (float)(dt - std::floor(dt));
    }
    
    float GetTempo(){
        return (float)(60000.0 / tempo_msperbeat);
    }
    void SetTempo(float bpm){
        double orig_posinmsr = GetPositionInMeasureInternal();
        tempo_msperbeat = 60000.0 / (double)bpm;
        SetOriginForMsrPos(orig_posinmsr);
    }
    int GetBeatsPerMeasure(){
        return measurelen;
    }
    void SetBeatsPerMeasure(int beats){
        if(beats <= 0) return;
        if(beats == measurelen) return;
        double orig_posinmsr = GetPositionInMeasureInternal();
        orig_posinmsr *= (double)measurelen / (double)beats;
        orig_posinmsr -= std::floor(orig_posinmsr);
        measurelen = beats;
        SetOriginForMsrPos(orig_posinmsr);
    }
    
    void TapBeat(){
        std::cout << "Tap Beat received\n"; //TODO
    }
    void TapMeasure(){
        std::cout << "Tap Measure received\n"; //TODO
    }
    
    void Init(){
        origin = GetTimeMS();
        tempo_msperbeat = 60000.0 / 120.0;
        measurelen = 4;
    }
    void Finalize(){
        
    }
    
}
