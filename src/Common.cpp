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

#include "Common.h"

//BuskMagic components
Identifier idBuskMagicShow("buskmagicshow");
Identifier idArtNetSystem("artnetsystem");
Identifier idUSBDMXSystem("usbdmxsystem");
Identifier idMIDISystem("midisystem");
Identifier idTimingSystem("timingsystem");
Identifier idChannelSystem("channelsystem");
Identifier idFixtureSystem("fixturesystem");
Identifier idControllerSystem("controllersystem");
Identifier idLightingSystem("lightingsystem");
Identifier idStatesWindow("stateswindow");
Identifier idTimingWindow("timingwindow");
//Common attributes
Identifier idUUID("uuid");
Identifier idName("name");
Identifier idLetters("letters");
Identifier idType("type");
Identifier idMode("mode");
Identifier idAction("action");
Identifier idParam("param");
//I/O attributes
Identifier idNet("net");
Identifier idMapNet("map_net");
Identifier idSubnet("subnet");
Identifier idMapSubnet("map_subnet");
Identifier idUniverse("universe");
Identifier idChannel("channel");
Identifier idPort("port");
Identifier idNote("note");
Identifier idVel("vel");
//Objects
Identifier idPhasor("phasor");
Identifier idController("controller");
Identifier idFixDefs("fixdefs");
Identifier idFixtures("fixtures");
Identifier idFixture("fixture");
Identifier idStates("states");
Identifier idState("state");
Identifier idMIDIUser("midiuser");
Identifier idMIDISetting("midisetting");
//ArtNetSystem
Identifier idPollMode("pollmode");
Identifier idArtNetDevice("artnetdevice");
Identifier idStyle("style");
Identifier idMap("map");
Identifier idInUni("inuni");
Identifier idOutUni("outuni");
Identifier idMapInUni("map_inuni");
Identifier idMapOutUni("map_outuni");
Identifier idBindIndex("bindindex");
Identifier idIP("ip");
Identifier idShortName("shortname");
Identifier idLongName("longname");
//USBDMXSystem
Identifier idLoadMapMode("loadmapmode");
Identifier idSlot("slot");
Identifier idChannels("channels");
Identifier idUSBDevice("usbdevice");
Identifier idBusNum("busnum");
Identifier idDevNum("devnum");
Identifier idSerialDevice("serialdevice");
//MIDISystem
Identifier idInPorts("inports");
Identifier idInPort("inport");
Identifier idOutPorts("outports");
Identifier idOutPort("outport");
Identifier idDevName("devname");
Identifier idOut("out");
Identifier idContinuous("continuous");
//TimingSystem
Identifier idTempoMS("tempoms");
Identifier idMeasureLen("measurelen");
Identifier idOnlyInt("onlyint");
//ChannelSystem
Identifier idMag("mag");
Identifier idAngle("angle");
Identifier idDefaultValue("defaultvalue");
Identifier idOp("op");
//FixtureSystem
Identifier idInUse("inuse");
Identifier idManufacturer("manufacturer");
Identifier idProfile("profile");
Identifier idFootprint("footprint");
Identifier idNormal("normal");
Identifier idFine("fine");
Identifier idUltra("ultra");
Identifier idHue("hue");
Identifier idHueMix("huemix");
Identifier idColorMode("colormode");
Identifier idRed("red");
Identifier idGreen("green");
Identifier idBlue("blue");
Identifier idAmber("amber");
Identifier idWhite("white");
Identifier idUV("uv");
Identifier idCyan("cyan");
Identifier idMagenta("magenta");
Identifier idYellow("yellow");
Identifier idFixDir("fixdir");
Identifier idFixDef("fixdef");
Identifier idFixID("fixid");
//ControllerSystem
Identifier idMagicValue("magicvalue");
Identifier idMuggleValue("mugglevalue");
Identifier idPosX("posx");
Identifier idPosY("posy");
Identifier idNoState("nostate");
Identifier idGroup("group");
Identifier idColor("color");
Identifier idGroupColor("groupcolor");
Identifier idEnabled("enabled");
Identifier idKnob("knob");
Identifier idShape("shape");
Identifier idTimeBase("timebase");
Identifier idNStates("nstates");
Identifier idDState("dstate");
Identifier idSState("sstate");
Identifier idProtected("protected");
//LightingSystem
Identifier idValueViewMode("valueviewmode");
Identifier idSortByChannel("sortbychannel");
