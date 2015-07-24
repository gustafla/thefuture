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

#include "parts/tunnel1.hpp"
#include <cmath>
#include <iostream>

PTunnel1::PTunnel1(CommonData* icommon):
common(icommon),
startt(-1.0f),
twister(icommon, "shaders/twister_var.frag", 0, 0, common->res[0]/4.0, common->res[1], "graphics/twister_texture.tga") {
    //tunnel = new EPointTunnel(icommon);
    //ovl = new GfxScreenMovable(icommon, "shaders/ovl_var.frag", (icommon->res[0]/2)-((icommon->res[1]*0.52083)/2), 0, (icommon->res[1]*0.52083), icommon->res[1], "graphics/mehuovl.tga");
    //scroller = new GfxScreenMovable(icommon, "shaders/colorscroll.frag", (icommon->res[0]), (icommon->res[1]/8.0)*7.0, (icommon->res[1]*64.0)/8.0, icommon->res[1]/8.0, "graphics/scroller1.tga", 1.0, GL_NEAREST, GL_CLAMP_TO_EDGE);
    std::cout<< __FILE__ << std::endl;
}

PTunnel1::~PTunnel1() {
    //delete tunnel;
    //delete ovl;
    //delete scroller;
}

void PTunnel1::draw() {
    if (startt < 0.0f)
        startt = common->t;
    //tunnel->draw();
    //glClear(GL_DEPTH_BUFFER_BIT);
    twister.setX(sin(common->t)*(common->res[0]*0.5-common->res[0]/4.0)+(common->res[0]*0.5-(common->res[0]/4.0)/2));
    twister.draw(startt);
    /*glClear(GL_DEPTH_BUFFER_BIT);
    ovl->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    scroller->setXgl(3.6 - (common->t - start) * 0.4);
    scroller->draw();*/
}

void PTunnel1::resetTimer() {
    startt=-1.0f;
    //tunnel->resetTimer();
}
