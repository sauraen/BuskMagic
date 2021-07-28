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

namespace LightingSystem {
    extern ReadWriteLock mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define LS_LOCK_READ() const ScopedReadLock lslock(LightingSystem::mutex)
    #define LS_TRY_LOCK_READ() const ScopedTryReadLock lslock(LightingSystem::mutex); if(!lslock.locked()) { std::cout << "TryReadLock bailing!\n"; return; } REQUIRESEMICOLON
    #define LS_LOCK_WRITE() const ScopedWriteLock lslock(LightingSystem::mutex)

    void SignalRecursion();

    enum ValueViewMode {
        Ratio, //0.0 to 1.0
        Percent, //0.0 to 100.0
        Byte, //0 to 255
        Hex //00 to FF
    };
    ValueViewMode GetValueViewMode();
    void SetValueViewMode(ValueViewMode vvm);
    String ValueToString(float val);
    bool ParseValue(String text, float &out);

    bool SortByChannel();
    void SetSortByChannel(bool bychn);

    void Init(ValueTree ls_node = ValueTree());
    void Finalize();
    ValueTree Save();

}
