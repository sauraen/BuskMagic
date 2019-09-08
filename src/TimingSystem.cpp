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

static Identifier idTimingSystem("timingsystem");
static Identifier idTempoMS("tempoms");
static Identifier idMeasureLen("measurelen");
static Identifier idOnlyInt("onlyint");

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
    
    double freeze_posmsr;
    bool frozen;
    bool onlyint;
    
    Array<uint64_t> taptimes;
    Array<double> taptempos;
    int beatsinmeasure_counter;
    
    void ClearTapping(){
        taptimes.clear();
        taptempos.clear();
        beatsinmeasure_counter = 0;
    }
    
    double GetPositionInMeasureInternal(){
        if(frozen) return freeze_posmsr;
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
        double d = GetPositionInMeasureInternal();
        d *= (double)measurelen;
        return (float)(d - std::floor(d));
    }
    int GetCurrentBeat(){
        double d = GetPositionInMeasureInternal();
        d *= (double)measurelen;
        d += 0.5;
        d = std::floor(d);
        return (int)d;
    }
    
    float GetTempo(){
        return (float)(60000.0 / tempo_msperbeat);
    }
    void SetTempo(float bpm){
        ClearTapping();
        if(onlyint) bpm = std::round(bpm);
        double orig_posinmsr = GetPositionInMeasureInternal();
        tempo_msperbeat = 60000.0 / (double)bpm;
        SetOriginForMsrPos(orig_posinmsr);
    }
    bool IsTempoOnlyInt() { return onlyint; }
    void SetTempoOnlyInt(bool tempoonlyint) { onlyint = tempoonlyint; }
    
    int GetBeatsPerMeasure(){
        return measurelen;
    }
    void SetBeatsPerMeasure(int beats){
        if(beats <= 0) return;
        if(beats == measurelen) return;
        ClearTapping();
        double orig_posinmsr = GetPositionInMeasureInternal();
        orig_posinmsr *= (double)measurelen / (double)beats;
        orig_posinmsr -= std::floor(orig_posinmsr);
        measurelen = beats;
        SetOriginForMsrPos(orig_posinmsr);
    }
    
    void TapBeatInternal(bool ismeasure){
        uint64_t t = GetTimeMS();
        uint64_t dt = taptimes.size() > 0 ? t-taptimes[taptimes.size()-1] : 0;
        int b = ismeasure ? 0 : GetCurrentBeat();
        static const uint64_t notap_delay = 1500;
        if(dt >= notap_delay) ClearTapping();
        taptimes.add(t);
        if(taptimes.size() >= 2){
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
                if(interstdev > newstdev + 10.0 && std::abs(newavg - oldavg) > 40.0){
                    //User has tapped two beat-intervals of a totally new tempo
                    std::cout << "Throwing out old beats, oldavg = " << oldavg << ", newavg = " << newavg << "\n";
                    taptempos.removeRange(0, ntt-2);
                    taptimes.removeRange(0, ntt-2);
                }
            }
            if(taptempos.size() > 10){
                taptempos.remove(0);
                taptimes.remove(0);
            }
            //Weighted-average tempos
            double newtempo = 0.0;
            double weight = 1.0;
            double totalweight = 0.0;
            for(int i=taptempos.size()-1; i>=0; --i){
                newtempo += taptempos[i] * weight;
                totalweight += weight;
                weight *= 0.9;
            }
            newtempo /= totalweight;
            //Change tempo
            tempo_msperbeat = onlyint ? (60000.0 / std::round(60000.0 / newtempo)) : newtempo;
        }
        //Recalculate beats per measure
        if(ismeasure){
            if(beatsinmeasure_counter >= 1) measurelen = beatsinmeasure_counter;
            beatsinmeasure_counter = 1; //Beat 1 of new measure
        }else{
            if(beatsinmeasure_counter >= 1) ++beatsinmeasure_counter;
        }
        //Keep beat in measure but adjust to beat
        SetOriginForMsrPos((double)b / (double)measurelen);
    }
    void TapBeat(){
        TapBeatInternal(false);
    }
    void TapMeasure(){
        TapBeatInternal(true);
    }
    
    void ToggleFreeze(){
        if(!frozen){
            freeze_posmsr = GetPositionInMeasureInternal();
            frozen = true;
        }else{
            SetOriginForMsrPos(freeze_posmsr);
            frozen = false;
        }
    }
    bool IsFrozen() { return frozen; }
    
    void Init(ValueTree ts_node){
        origin = GetTimeMS();
        if(ts_node.isValid()){
            tempo_msperbeat = (double)ts_node.getProperty(idTempoMS, 60000.0/120.0);
            measurelen = ts_node.getProperty(idMeasureLen, 4);
            onlyint = ts_node.getProperty(idOnlyInt, false);
        }else{
            tempo_msperbeat = 60000.0 / 120.0;
            measurelen = 4;
            onlyint = false;
        }
        frozen = false;
    }
    void Finalize(){
        //nothing to do
    }
    ValueTree Save(){
        ValueTree ret(idTimingSystem);
        ret.setProperty(idTempoMS, tempo_msperbeat, nullptr);
        ret.setProperty(idMeasureLen, measurelen, nullptr);
        ret.setProperty(idOnlyInt, onlyint, nullptr);
        return ret;
    }
    
}
