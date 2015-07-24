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

#include "cube.hpp"
#include <cmath>
#include <iostream>

PCube::PCube(CommonData* icommon):
common(icommon) {
    shader = new GfxShader("shaders/cube.vert", "shaders/green.frag");
    shader->use();
    glUniformMatrix4fv(shader->getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat80);
    cubeModel = common->models->getModel("cube.obj");
    twister = new GfxScreenMovable(icommon, "shaders/twister_var.frag", 0, 0, common->res[0]/4.0, common->res[1], "graphics/twister_texture.tga");
    std::cout<< __FILE__ << std::endl;
}

PCube::~PCube() {
    delete shader;
    delete twister;
    common->models->freeModel("cube.obj");
}

void PCube::draw() {
    shader->use();
    getXRotMat(xr, common->t*0.2);
    getYRotMat(yr, common->t*0.8);
    getZRotMat(zr, common->t*0.6);

    glUniformMatrix4fv(shader->getUfmHandle("xRotation"), 1, GL_FALSE, xr);
    glUniformMatrix4fv(shader->getUfmHandle("yRotation"), 1, GL_FALSE, yr);
    glUniformMatrix4fv(shader->getUfmHandle("zRotation"), 1, GL_FALSE, zr);
    glUniform1f(shader->getUfmHandle("iGlobalTime"), common->t);
    //gfxBindFB0();
    cubeModel->draw(shader);
    glClear(GL_DEPTH_BUFFER_BIT);
    twister->setX(sin(common->t)*(common->res[0]*0.5-common->res[0]/4.0)+(common->res[0]*0.5-(common->res[0]/4.0)/2));
    twister->draw();
}
