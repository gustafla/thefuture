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

#include "amiga.hpp"
#include <cmath>
#include <iostream>

PAmiga::PAmiga(CommonData* icommon):
common(icommon),
startT(-1.0f),
planeTex("graphics/amiga.tga"),
//revTex("graphics/orange.tga"),
cubeTex("graphics/sky.tga"),
plane("screen.obj", NULL, 0, false),
icos("icos.obj", NULL, 0, true),
cube("cube_tex.obj", NULL, 0, false),
revision("revision.obj", NULL, 0, true),
torus("htorus.obj", NULL, 0, true),
mvp(icommon->pProjMat40),
//mvp2(icommon->pProjMat40),
modelShader("shaders/mvpodd.vert", "shaders/bluewhite.frag"),
orangeShader("shaders/mvp.vert", "shaders/orange.frag"),
shader("shaders/mvptex.vert", "shaders/showtex_var.frag") {
//shader2("shaders/mvptex.vert", "shaders/showtex_var.frag") {
    glUniform1i(shader.getUfmHandle("iChannel0"), 0);
    std::cout<< __FILE__ << std::endl;
}

void PAmiga::draw() {
    if (startT < 0.0f)
        startT = common->t;
    
    float t = common->t-startT;
    
    float a = t*0.3;
    mvp.setView(
        0.0f, 0.0f, 0.0f,
        sin(t)*0.1-0.08, a+M_PI, 0.0f
    );
    shader.use();
    cubeTex.bindToUnit(0);
    mvp.setModelScale(5.0f);
    mvp.setModelRotation(0.0f, 0.0f, 0.0f);
    mvp.setModelTranslation(0.0f, 0.0f, 0.0f);
    mvp.buildModel();
    mvp.buildMVP();
    glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    cube.draw(&shader);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    mvp.setViewTranslation(
        sin(a)*1.5, -0.5f, cos(a)*1.5
    );
    
    planeTex.bindToUnit(0);
    
    shader.use();
    mvp.setModelScale(30.0f);
    mvp.setModelRotation((M_PI/180.0f)*90.0f, 0.0f, 0.0f);
    mvp.setModelTranslation(0.0f, 0.0f, 0.0f);
    //std::cout << common->t*10.0f << std::endl;
    mvp.buildModel();
    mvp.buildMVP();
    glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    plane.draw(&shader);
    
    modelShader.use();
    mvp.setModelScale(0.3f);
    mvp.setModelRotation(t*0.2f, -t*0.3f, t*0.4f);
    mvp.setModelTranslation(0.0f, 0.3f, 0.0f);
    mvp.buildModel();
    mvp.buildMVP();
    glUniformMatrix4fv(modelShader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    icos.draw(&modelShader);
    
    mvp.setModelScale(0.5f);
    for(float i=0.0f; i<M_PI*2; i+=(M_PI*2)/12.0) {
        mvp.setModelRotation(sin(i-t)*0.5, -t*0.3f, cos(i-t)*0.5);
        mvp.setModelTranslation(sin(i)*3.0f, sin(i*3.0+t)*0.2+0.6, cos(i)*3.0f);
        mvp.buildModel();
        mvp.buildMVP();
        glUniformMatrix4fv(modelShader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
        torus.draw(&modelShader);
    }
    
    orangeShader.use();
    mvp.setModelScale(3.0f);
    mvp.setModelRotation((M_PI/180.0f)*90.0f, t*0.8, 0.0f);
    mvp.setModelTranslation(0.0f, 2.0f, -20.0f);
    mvp.buildModel();
    mvp.buildMVP();
    glUniformMatrix4fv(orangeShader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    revision.draw(&orangeShader);
}

void PAmiga::resetTimer() {
    startT = -1.0f;
}
