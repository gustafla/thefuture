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

#include "parts/intro.hpp"
#include <iostream>

PIntro::PIntro(CommonData* icommon):
common(icommon) {
    metaballs = new GfxScreen(icommon, "shaders/metaballs.frag", "graphics/stone.tga", 2.0);
    //rb = new GfxPostProcessor(icommon, "shaders/rb_post.frag", GL_LINEAR, 2.0);
    rb = new GfxPostProcessor(icommon, "shaders/2x.frag", GL_LINEAR, 2.0);
    mehutext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", icommon->res[0]/3, icommon->res[1]/6, icommon->res[0]/6, icommon->res[1]/6, "graphics/mehutext.tga");
    yeartext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", (icommon->res[0]/12)*7, (icommon->res[1]/6)*2, icommon->res[0]/6, icommon->res[1]/6, "graphics/yeartext.tga");
    revisiontext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", (icommon->res[0]/12)*2, (icommon->res[1]/6)*3, icommon->res[0]/6, icommon->res[1]/6, "graphics/revisiontext.tga");
    //pb1 = new ParticleBurst(icommon, -0.2f, 0.4f, -1.0f, 16);
    pb2 = new ParticleBurst(icommon, 0.45f, 0.14f, -1.0f, 16);
    pb3 = new ParticleBurst(icommon, -0.6f, -0.1f, -1.0f, 16);
    //pb4 = new ParticleBurst(icommon, 0.0f, 0.0f, 0.0f, 16);
    std::cout<< __FILE__ << std::endl;
}

PIntro::~PIntro() {
    delete metaballs;
    delete mehutext;
    delete revisiontext;
    delete yeartext;
    delete rb;
}

void PIntro::draw(Fade* drawTo) {
    //gfxBindFB0();
    rb->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    metaballs->draw();
    
    if (drawTo==NULL)
        gfxBindFB0();
    else
        drawTo->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rb->draw();

    glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t > 15.7) {
        //pb1->draw();
        pb2->draw();
    }
    //glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t > 19.6) {
        pb3->draw();
    }
    //glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t > 23.45) {
        //pb3->draw();
    }
    
    glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t > 15.7) {
        //mehutext->draw();
        yeartext->draw();
    }
    //glClear(GL_DEPTH_BUFFER_BIT);
    if (common->t > 19.6) {
        //yeartext->draw();
        revisiontext->draw();
    }
    //glClear(GL_DEPTH_BUFFER_BIT);
    /*if (common->t > 23.45) {
        revisiontext->draw();
    }*/
}
