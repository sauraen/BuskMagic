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

namespace LightingSystem {
    extern ReadWriteLock mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define LS_LOCK_READ() const ScopedReadLock lslock(LightingSystem::mutex)
    #define LS_LOCK_WRITE() const ScopedWriteLock lslock(LightingSystem::mutex)
    
    void SignalRecursion();
}
