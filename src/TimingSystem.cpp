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
    
    Array<uint64_t> taptimes;
    Array<double> taptempos;
    
    double GetPositionInMeasureInternal(){
        double dt = (double)(GetTimeMS() - origin);
        dt /= (tempo_msperbeat * (double)measurelen);
        return dt - std::floor(dt);
    }
    void SetOriginForMsrPos(double posinmsr){
        origin = GetTimeMS() - (uint64_t)(tempo_msperbeat * (double)measurelen * posinmsr);
    }
    int GetCurrentBeat(){
        double orig_posinmsr = GetPositionInMeasureInternal();
        orig_posinmsr *= (double)measurelen;
        orig_posinmsr += 0.5;
        orig_posinmsr = std::floor(orig_posinmsr);
        return (int)orig_posinmsr;
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
        taptimes.clear();
        taptempos.clear();
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
        static const uint64_t notap_delay = 2000;
        uint64_t t = GetTimeMS();
        uint64_t dt = taptimes.size() > 0 ? t-taptimes[taptimes.size()-1] : 0;
        int b = GetCurrentBeat();
        if(dt >= notap_delay){
            taptimes.clear();
            taptempos.clear();
        }
        taptimes.add(t);
        if(taptimes.size() == 1){
            SetOriginForMsrPos((double)b / (double)measurelen); //Move to nearest beat
            return;
        }
        taptempos.add((double)dt);
        int ntt = taptempos.size();
        if(ntt >= 3){
            double newavg = (taptempos[ntt-1] + taptempos[ntt-2]) * 0.5;
            double newstdev = (taptempos[ntt-1] - newavg) * (taptempos[ntt-1] - newavg)
                            + (taptempos[ntt-2] - newavg) * (taptempos[ntt-2] - newavg);
            newstdev = std::sqrt(newstdev);
            double oldavg = 0.0;
            for(int i=0; i<ntt-2; ++i){
                oldavg += taptempos[i];
            }
            oldavg /= (double)(ntt-2);
            double interavg = (newavg + oldavg) * 0.5;
            double interstdev = (newavg - interavg) * (newavg - interavg)
                              + (oldavg - interavg) * (oldavg - interavg);
            interstdev = std::sqrt(interstdev);
            if(interstdev > newstdev && std::abs(newavg - oldavg) > 7.0){
                //User has tapped two beat-intervals of a totally new tempo
                taptempos.removeRange(0, ntt-2);
                taptimes.removeRange(0, ntt-2);
            }
        }
        //Weighted-average tempos
        double newtempo = 0.0;
        double weight = 1.0;
        double totalweight = 0.0;
        for(int i=taptempos.size()-1; i>=0; --i){
            newtempo += taptempos[i] * weight;
            totalweight += weight;
            weight *= 0.8;
        }
        newtempo /= totalweight;
        //Change tempo, keeping beat in measure but rounding to beat
        tempo_msperbeat = newtempo;
        SetOriginForMsrPos((double)b / (double)measurelen);
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
