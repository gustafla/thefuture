// Copyright 2015 Lauri Gustafsson
/*
This file is part of Low Quality is the Future.

    Low Quality is the Future is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Low Quality is the Future is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Low Quality is the Future, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "parts/flag.hpp" 
#include <iostream>

PFlag::PFlag(CommonData* icommon):
common(icommon),
warpField(icommon),
cube(icommon, "cube.obj", 0.7),
icos(icommon, "icos.obj"),
torus(icommon, "htorus.obj"),
bg(icommon, "shaders/rotate.frag", "graphics/novo.tga"),
startT(-1.0f) {
    flag = new EPointFlag(icommon);
    std::cout<< __FILE__ << std::endl;
}

PFlag::~PFlag() {
    delete flag;
}

void PFlag::draw() {
    if (startT < 0.0f)
        startT = common->t;
        
    warpField.draw();
    bg.draw();
    
    glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t - startT < 14.7f)
        flag->draw();
    else if (common->t - startT < 14.7f + 5.0f)
        cube.draw();
    else if (common->t - startT < 14.7f + 5.0f + 5.0f)
        icos.draw();
    else
        torus.draw();
}

void PFlag::resetTimer() {
    startT=-1.0f;
    flag->resetTimer();
    cube.resetTimer();
    icos.resetTimer();
    torus.resetTimer();
}
