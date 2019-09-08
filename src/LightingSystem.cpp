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
        LightingThread() { startTimer(33); }
        virtual ~LightingThread() {}
        virtual void hiResTimerCallback() override {
            Array<uint16_t> eval_universes = ArtNetSystem::GetSortedListNeededUniverses();
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
    private:
        uint8_t unidata[512];
    };
    static LightingThread *lth = nullptr;
    
    void Init(ValueTree ls_node){
        ignoreUnused(ls_node);
        if(lth != nullptr){
            std::cout << "LightingSystem multiply initted!\n";
            return;
        }
        lth = new LightingThread();
    }
    
    void Finalize(){
        lth->stopTimer();
        delete lth;
        lth = nullptr;
    }
    
    ValueTree Save(){
        return ValueTree(idLightingSystem);
    }
}
