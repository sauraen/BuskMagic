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

#include "USBDMXSystem.h"

namespace USBDMXSystem {
    
    static ReadWriteLock devices_mutex;
    //These are intentionally named the same so you cannot start with a read
    //lock and escalate to a write lock
    #define DEVICES_LOCK_READ() const ScopedReadLock devlock(ArtNetSystem::devices_mutex)
    #define DEVICES_LOCK_WRITE() const ScopedWriteLock devlock(ArtNetSystem::devices_mutex)
    
    enum class UDType : uint32_t {
        None,
        uDMX,
    };
    static String TypeToString(UDType t){
        switch(t){
            case UDType::None: return "None";
            case UDType::uDMX: return "anyma.ch uDMX or knockoff";
            default: return "ERROR";
        }
    }
    
    struct UDSlot {
        UDType type;
        String name;
        uint16_t uni;
        uint8_t devnum;
        uint32_t bus;
        void *handle;
        
        UDSlot(){
            type = UDType::None;
            name = "unnamed";
            uni = 0;
            handle = nullptr;
        }
    };
    
    static std::vector<UDSlot> slots;
    
    int NumSlots() { return slots.size(); }
    void AddSlot(){ 
        DEVICES_LOCK_WRITE(); 
        slots.push_back(UDSlot());
    }
    void RemoveSlot(int s){
        DEVICES_LOCK_WRITE();
        if(slots[s].handle != nullptr){
            //TODO
        }
        slots.erase(slots.begin() + s);
    }
    String SlotType(int s){ 
        DEVICES_LOCK_READ(); 
        if(s >= slots.size()) return "ERROR";
        return TypeToString(slots[s].type);
    }
    String SlotName(int s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        return slots[s].name;
    }
    void SetSlotName(int s, String n){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        slots[s].name = n;
    }
    uint16_t SlotUni(int s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return 0x7FFF;
        return slots[s].uni;
    }
    void SetSlotUni(int s, uint16_t uni){
        DEVICES_LOCK_WRITE();
        if(s >= slots.size()) return;
        slots[s].uni = uni;
    }
    String SlotDescription(int s){
        DEVICES_LOCK_READ();
        if(s >= slots.size()) return "ERROR";
        String ret = slots[s].name + " (" + hex(slots[s].uni) + "): ";
        if(slots[s].handle == nullptr){
            ret += " (unmapped)";
        }else{
            ret += "bus " + String(slots[s].bus) + " device " + String(slots[s].devnum);
        }
        return ret;
    }
    
    bool loadmapmodetype;
    bool IsLoadMapModeType() { return loadmapmodetype; }
    void SetLoadMapMode(bool mapType) { loadmapmodetype = mapType; }
    String GetLoadMapModeHelpText(){
        return "This option specifies how communication is\n"
               "re-opened with USB-DMX devices when this showfile\n"
               "is loaded.\n\n"
               "Map by port: The devices are identified by their Bus\n"
               "and Device number, which together define the physical\n"
               "USB port the device is connected to. This is best if\n"
               "you have multiple dongles of the same type. However,\n"
               "the devices must be manually remapped in this window\n"
               "if they are ever plugged into a different USB port.\n\n"
               "Map by type: The devices are identified by their type.\n"
               "This is best if you only have one dongle of any type,\n"
               "since you can plug it into any USB port without having\n"
               "to remap. However, if you have multiple dongles of the\n"
               "same type, only the first one of each type will get\n"
               "mapped when the showfile is loaded.";
    }

    void Init(ValueTree us_node){
        loadmapmodetype = us_node.isValid() ? (bool)us_node.getProperty(idLoadMapMode, false) : false;
    }
    void Finalize(){
        
    }

    ValueTree Save(){
        ValueTree ret(idUSBDMXSystem);
        ret.setProperty(idLoadMapMode, loadmapmodetype, nullptr);
        return ret;
    }

}
