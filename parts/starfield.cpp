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

#include "parts/starfield.hpp"
#include <iostream>

PStarfield::PStarfield(CommonData* icommon):
common(icommon),
start(-1.0f) {
    stars = new EPointField(icommon);
    ovl = new GfxScreenMovable(icommon, "shaders/ovl_var.frag", (icommon->res[0]/2)-((icommon->res[1]*0.52083)/2), 0, (icommon->res[1]*0.52083), icommon->res[1], "graphics/mehuovl.tga");
    scroller = new GfxScreenMovable(icommon, "shaders/colorscroll.frag", (icommon->res[0]), (icommon->res[1]/8.0)*7.0, (icommon->res[1]*64.0)/8.0, icommon->res[1]/8.0, "graphics/scroller1.tga", 1.0, GL_NEAREST, GL_CLAMP_TO_EDGE);
    std::cout<< __FILE__ << std::endl;
}

PStarfield::~PStarfield() {
    delete stars;
    delete ovl;
    delete scroller;
}

void PStarfield::draw() {
    if (start < 0.0f)
        start = common->t;
    stars->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    ovl->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    scroller->setXgl(3.6 - (common->t - start) * 0.4);
    scroller->draw();
}

void PStarfield::resetTimer() {
    start=-1.0f;
}
