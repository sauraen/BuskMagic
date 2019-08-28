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

#include "ControllerCmps.h"

#include "gui/Controller/ControllerCanvas.h"

void ControllerCmp::mouseDrag(const MouseEvent &event) {
    if(isRightClick(event) || !event.mods.isLeftButtonDown()) return;
    ControllerCanvas *canvas = findParentComponentOfClass<ControllerCanvas>();
    Viewport *viewport = findParentComponentOfClass<Viewport>();
    MouseEvent c_event = event.getEventRelativeTo(canvas);
    MouseEvent v_event = event.getEventRelativeTo(viewport);
    controller->pos = c_event.getPosition() - dragbegin_local;
    if(controller->pos.x < 0) controller->pos.x = 0;
    if(controller->pos.y < 0) controller->pos.y = 0;
    if(controller->pos.x > canvas->getWidth() - getWidth()) controller->pos.x = canvas->getWidth() - getWidth();
    if(controller->pos.y > canvas->getHeight() - getHeight()) controller->pos.y = canvas->getHeight() - getHeight();
    setTopLeftPosition(controller->pos);
    viewport->autoScroll(v_event.x, v_event.y, 20, 10);
}

static const unsigned char cosine_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,
11,252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,103,73,68,65,84,72,199,237,84,49,18,0,32,8,242,250,255,159,105,105,204,65,82,
179,51,214,46,80,84,68,174,0,0,152,183,146,216,22,108,238,226,185,182,13,101,167,244,70,139,96,65,154,131,245,64,253,231,106,106,218,132,52,161,81,115,123,83,188,250,39,210,48,11,34,7,126,196,239,89,152,
27,151,7,81,200,221,150,11,92,134,56,60,124,44,2,169,73,168,93,202,143,228,118,152,28,218,147,111,74,232,225,155,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgCosine_data = (const char*)cosine_data;
const int ModulatorControllerCmp::imgCosine_size = 215;

static const unsigned char triangle_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,
11,252,97,5,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,79,73,68,65,84,72,199,99,96,160,33,248,255,255,255,127,236,28,162,117,
145,36,57,10,6,6,80,28,41,195,192,128,209,104,28,53,108,212,176,81,48,90,14,208,206,46,90,58,140,34,179,169,233,176,65,147,111,105,154,12,72,49,156,174,133,15,62,203,6,180,20,68,182,124,180,56,30,145,
0,0,41,1,119,137,249,117,237,188,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgTriangle_data = (const char*)triangle_data;
const int ModulatorControllerCmp::imgTriangle_size = 191;

static const unsigned char noise_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,145,73,68,65,84,72,199,237,84,65,14,192,32,8,83,194,255,191,220,93,182,100,91,20,
69,96,110,139,61,25,83,42,85,105,74,65,0,128,235,66,100,189,8,221,61,29,196,174,130,51,137,210,183,80,50,136,29,46,162,234,27,12,255,79,102,123,63,128,219,29,212,68,164,3,72,219,93,206,57,151,120,220,
18,170,21,250,134,69,201,154,182,248,206,167,210,166,201,206,26,145,5,223,212,30,0,121,252,74,41,115,180,6,120,180,153,218,44,2,128,101,78,57,250,105,93,26,178,36,83,15,87,210,231,150,112,84,122,61,22,
191,51,39,116,97,10,54,208,213,175,151,222,180,131,67,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgNoise_data = (const char*)noise_data;
const int ModulatorControllerCmp::imgNoise_size = 257;

static const unsigned char pulse_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,84,73,68,65,84,72,199,99,96,24,16,240,31,10,24,6,17,24,108,238,25,5,212,1,140,212,
136,108,70,70,70,198,225,30,70,232,97,66,182,159,145,13,34,55,87,49,81,203,107,163,6,17,6,44,148,102,145,97,158,61,70,14,192,21,233,244,172,28,153,6,91,160,140,58,104,212,65,195,206,65,163,96,200,1,0,
103,211,40,1,21,164,70,223,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgPulse_data = (const char*)pulse_data;
const int ModulatorControllerCmp::imgPulse_size = 196;

static const unsigned char sawf_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,105,73,68,65,84,72,199,237,150,65,14,192,32,8,4,89,211,255,127,121,189,120,104,
154,218,26,193,64,148,185,187,12,162,70,145,216,144,100,250,100,131,10,96,209,42,0,200,230,88,140,190,88,201,172,9,82,183,184,100,143,84,161,207,197,51,97,87,239,200,143,134,157,112,61,142,128,141,112,
143,82,24,169,187,72,8,169,55,9,87,177,94,113,55,169,175,194,46,82,127,69,183,255,101,38,51,84,221,250,99,182,39,26,103,190,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgSawF_data = (const char*)sawf_data;
const int ModulatorControllerCmp::imgSawF_size = 217;

static const unsigned char sawr_data[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,24,8,6,0,0,1,229,191,111,216,0,0,0,4,103,65,77,65,0,0,177,143,11,
252,97,5,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,127,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,0,107,73,68,65,84,72,199,237,149,73,10,0,33,12,4,19,153,255,127,185,189,40,12,50,
227,130,75,34,116,157,196,67,186,196,68,69,122,0,0,45,55,100,19,0,16,132,220,69,238,136,48,91,96,137,197,123,253,140,38,104,130,151,106,212,67,246,69,124,29,105,59,58,170,202,241,32,203,230,195,205,140,
100,17,23,66,95,95,153,155,39,204,76,232,47,216,68,168,22,122,92,168,21,120,199,79,68,42,68,107,212,103,175,213,121,75,77,0,0,0,0,73,69,78,68,174,66,96,130,0,0};
const char* ModulatorControllerCmp::imgSawR_data = (const char*)sawr_data;
const int ModulatorControllerCmp::imgSawR_size = 219;
