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

#include "LightingSystem.h"

#include "ArtNetSystem.h"
#include "FixtureSystem.h"

#include <cstring>

namespace LightingSystem {
    ReadWriteLock mutex;

    void SignalRecursion(){
        std::cout << "Recursion detected!\n"; //TODO
    }

    class LightingThread : public HighResolutionTimer {
    public:
        LightingThread() { last_eval_ms = Time::getMillisecondCounterHiRes(); startTimer(33); }
        virtual ~LightingThread() {}
        double last_eval_ms;
        bool priorityset = false;
        virtual void hiResTimerCallback() override {
            if(!priorityset){
                bool ret = Thread::setCurrentThreadPriority(9);
                if(ret){
                    Logger::writeToLog("Successfully set lighting thread priority");
                }else{
                    Logger::writeToLog("Could not set lighting thread priority");
                }
                priorityset = true;
            }
            double ms = Time::getMillisecondCounterHiRes();
            if(ms - last_eval_ms > 100.0){
                Logger::writeToLog("Time between evaluations was " + String(ms - last_eval_ms) + " ms!");
            }
            last_eval_ms = ms;
            double callbackDuration;
            {
                ScopedTimeMeasurement m(callbackDuration);
                Array<uint16_t> eval_universes;
                ArtNetSystem::GetNeededUniversesSorted(eval_universes);
                for(int u=0; u<eval_universes.size(); ++u){
                    uint16_t universe = eval_universes[u];
                    memset(unidata, 0, 512);
                    {
                        LS_LOCK_READ();
                        for(int f=0; f<FixtureSystem::NumFixtures(); ++f){
                            Fixture *fix = FixtureSystem::Fix(f);
                            if(fix->GetUniverse() != universe) continue;
                            fix->Evaluate(unidata);
                        }
                    }
                    ArtNetSystem::SendDMX512(universe, unidata);
                }
            }
            if(callbackDuration > 0.1){
                Logger::writeToLog("Lighting callback took " + String(callbackDuration * 1000.0) + " ms!");
            }
        }
    private:
        uint8_t unidata[512];
    };
    static LightingThread *lth = nullptr;

    static ValueViewMode valueviewmode;
    ValueViewMode GetValueViewMode(){
        return valueviewmode;
    }
    void SetValueViewMode(ValueViewMode vvm){
        valueviewmode = vvm;
    }
    String ValueToString(float val){
        int32_t ival = (int32_t)std::floor(256.0f*val);
        switch(valueviewmode){
        case ValueViewMode::Ratio:
            return FloatToString(val, 1, 3);
        case ValueViewMode::Percent:
            return FloatToString(100.0f*val, 0, 1);
        case ValueViewMode::Byte:
            return String(ival);
        case ValueViewMode::Hex: {
            bool neg = ival < 0;
            if(neg) ival = -ival;
            String ret = (ival > 0xFF) ? hex((uint16_t)ival) : hex((uint8_t)ival);
            if(neg) ret = '-' + ret;
            return ret;
        } default:
            jassertfalse;
            return "ERR";
        }
    }
    bool ParseValue(String text, float &out){
        out = 0.0f;
        switch(valueviewmode){
        case ValueViewMode::Ratio:
            if(!isDec(text)) return false;
            out = text.getFloatValue();
            return true;
        case ValueViewMode::Percent:
            if(!isDec(text)) return false;
            out = text.getFloatValue() * 0.01f;
            return true;
        case ValueViewMode::Byte:
            if(!isInt(text)) return false;
            out = (float)text.getIntValue() / 256.0f;
            return true;
        case ValueViewMode::Hex:
            if(!isHex(text, false)) return false;
            out = (float)text.getHexValue32() / 256.0f;
            return true;
        default:
            jassertfalse;
            return false;
        }
    }

    Logger *log;

    void Init(ValueTree ls_node){
        if(lth != nullptr){
            std::cout << "LightingSystem multiply initted!\n";
            return;
        }
        log = new FileLogger(File::getSpecialLocation(File::userHomeDirectory).getChildFile("buskmagic.log"), "BuskMagic log");
        Logger::setCurrentLogger(log);
        Logger::writeToLog("Starting up");
        lth = new LightingThread();
        if(ls_node.isValid()){
            valueviewmode = (ValueViewMode)(int)ls_node.getProperty(idValueViewMode, 0);
        }else{
            valueviewmode = ValueViewMode::Ratio;
        }
    }

    void Finalize(){
        lth->stopTimer();
        delete lth;
        lth = nullptr;
        Logger::setCurrentLogger(nullptr);
        delete log; log = nullptr;
    }

    ValueTree Save(){
        ValueTree ret(idLightingSystem);
        ret.setProperty(idValueViewMode, (int)valueviewmode, nullptr);
        return ret;
    }
}
