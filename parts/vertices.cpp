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

#include "parts/vertices.hpp"
#include <cmath>
#include <iostream>
#include "util.hpp"

PVertices::PVertices(CommonData* icommon):
common(icommon),
startT(-1.0f),
shaderProgram("shaders/mvptex.vert", "shaders/showtex_var.frag"),
texture("graphics/triangles.tga"),
texture2("graphics/thingtex.tga"),
mvp(common->pProjMat40, 0.0f, 0.0f, -7.0f),
bg(icommon, "shaders/showtex.frag", "graphics/bg1.tga"),
frameUp(icommon, "shaders/showtex_var.frag", 0, 0, icommon->res[0], icommon->res[1]/12.0f, "graphics/frame_1_up.tga"),
frameDown(icommon, "shaders/showtex_var.frag", 0, (icommon->res[1]/12.0f)*11.0f, icommon->res[0], icommon->res[1]/12.0f, "graphics/frame_1_down.tga") {
    cube = common->models->getModel("cube_tex.obj");
    thing = common->models->getModel("doublecube.obj");
    //cube = common->models->getModel("revision.obj");
    //cube->changeDrawmode(GL_POINTS);
    shaderProgram.use();
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    std::cout<< __FILE__ << std::endl;
}

PVertices::~PVertices() {
    
}

void PVertices::draw() {
    if (startT < 0.0f)
        startT = common->t;
    
    float t = common->t - startT;
    
    bg.draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    shaderProgram.use();
    texture.bindToUnit(0);
    //mvp.setView(0.0f, 0.0f, sin(common->t*0.6)*2.0-8.0f, sin(common->t)*2.0f, 0.0f, sin(common->t)*2.0f);
    for (float x=-4.0f; x<5.0f; x+=0.9f) {
        for (float y=-3.0f; y<3.3f; y+=0.9f) {
            mvp.setModelTranslation(x, y, 0.0f);
            mvp.setModelScale(0.2f+sin(x+t)*0.1f+(common->beatHalfSine*0.02f));
            mvp.setModelRotation(t*0.2f, y+t*0.4f, t*0.5f);
            mvp.buildModel();
            mvp.buildMVP();
            glUniformMatrix4fv(shaderProgram.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
            cube->draw(&shaderProgram);
        }
    }
    
    glClear(GL_DEPTH_BUFFER_BIT);
    texture2.bindToUnit(0);
    mvp.setModelTranslation(std::max(5.0f*5.0f-t*5.0f, 0.0f), 0.0f, 2.0f+std::min(12.0f*10.0f-t*10.0f, 0.0f));
    mvp.setModelScale(0.7f+(0.01f*common->beatHalfSine));
    if (t>12.0f)
        mvp.setModelRotation(t*0.7f, t, t*0.3f);
    else
        mvp.setModelRotation(t*0.7f, 0.0f, 0.0f);
    mvp.buildModel();
    mvp.buildMVP();
    glUniformMatrix4fv(shaderProgram.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    thing->draw(&shaderProgram);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    frameUp.draw();
    frameDown.draw();
}

void PVertices::resetTimer() {
    startT = -1.0f;
}
