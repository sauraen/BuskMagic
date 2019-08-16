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
            LS_LOCK_READ();
            
        }
    }
    static LightingThread *lth = nullptr;
    
    void Init(){
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
}
