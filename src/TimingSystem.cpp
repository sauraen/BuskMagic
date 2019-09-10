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
    
    double freeze_tpos;
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
    
    double GetTimePosition(){
        if(frozen) return freeze_tpos;
        double tpos = (double)(GetTimeMS() - origin);
        tpos /= (tempo_msperbeat * (double)measurelen);
        return tpos;
    }
    void SetOriginForTimePosition(double tpos){
        origin = GetTimeMS() - (uint64_t)(tempo_msperbeat * (double)measurelen * tpos);
    }
    
    void ToggleFreeze(){
        if(!frozen){
            freeze_tpos = GetTimePosition();
            frozen = true;
        }else{
            SetOriginForTimePosition(freeze_tpos);
            frozen = false;
        }
    }
    bool IsFrozen() { return frozen; }
    
    
    float GetPositionInMeasure(){
        double tpos = GetTimePosition();
        return (float)(tpos - std::floor(tpos));
    }
    float GetPositionInBeat(){
        double tpos = GetTimePosition();
        tpos *= (double)measurelen;
        return (float)(tpos - std::floor(tpos));
    }
    int GetCurrentMeasure(){ //Counterintuitively, round to nearest measure number!
        return (int)std::floor(GetTimePosition() + 0.5);
    }
    int GetCurrentBeat(){
        return (int)std::floor((GetPositionInMeasure() * (float)measurelen) + 0.5);
    }
    
    float GetTempo(){
        return (float)(60000.0 / tempo_msperbeat);
    }
    void SetTempo(float bpm){
        ClearTapping();
        if(onlyint) bpm = std::round(bpm);
        double orig_tpos = GetTimePosition();
        tempo_msperbeat = 60000.0 / (double)bpm;
        SetOriginForTimePosition(orig_tpos);
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
        float orig_posinmsr = GetPositionInMeasure();
        orig_posinmsr *= (float)measurelen / (float)beats;
        orig_posinmsr -= std::floor(orig_posinmsr);
        measurelen = beats;
        SetOriginForTimePosition((double)orig_posinmsr); //Reset to 0th measure
    }
    
    void TapBeatInternal(bool ismeasure){
        uint64_t t = GetTimeMS();
        uint64_t dt = taptimes.size() > 0 ? t-taptimes[taptimes.size()-1] : 0;
        int m = GetCurrentMeasure();
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
        //Set origin to rounded measure/beat
        SetOriginForTimePosition((double)m + ((double)b / (double)measurelen));
    }
    void TapBeat(){
        TapBeatInternal(false);
    }
    void TapMeasure(){
        TapBeatInternal(true);
    }
    
    float GetRandomFrom(int64_t seed){
        Random r(seed);
        r.nextInt64();
        r.combineSeed(seed);
        r.nextInt64();
        return r.nextFloat();
    }
    float GetRandomAtMeasure(int64_t objectid, float period){
        double tpos = GetTimePosition();
        tpos /= period;
        objectid ^= (int64_t)(std::floor(tpos));
        return GetRandomFrom(objectid);
    }
    float GetRandomAtBeat(int64_t objectid, float period){
        return GetRandomAtMeasure(objectid ^ 0x12345678ll, period * (float)measurelen);
    }
    float GetRandomAtSecond(int64_t objectid, float period){
        double t = GetTimeMS();
        t /= 1000.0 * period;
        objectid ^= (int64_t)(std::floor(t));
        return GetRandomFrom(objectid);
    }
    
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
