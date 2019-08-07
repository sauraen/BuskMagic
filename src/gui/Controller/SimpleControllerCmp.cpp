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

#include "SimpleControllerCmp.h"

#include "gui/Controller/ControllerCanvas.h"

void SimpleControllerCmp::mouseDrag(const MouseEvent &event) {
    if(!event.mods.isLeftButtonDown()) return;
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
