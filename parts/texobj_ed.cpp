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

#include "texobj_ed.hpp"
#include <cmath>

PTexobjED::PTexobjED(CommonData* icommon):
common(icommon) {
    texture = new GfxTexture2D("graphics/textest.tga");
    shader = new GfxShader("shaders/texturedthing.vert", "shaders/showtex_var.frag");
    shader->use();
    glUniform1i(shader->getUfmHandle("iChannel0"), 0);
    glUniformMatrix4fv(shader->getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat80);
    getTranslationMat(view, 0, 0, -4);
    glUniformMatrix4fv(shader->getUfmHandle("view"), 1, GL_FALSE, view);
    model = common->models->getModel("doublecube.obj");
    edPost = new GfxPostProcessor(common, "shaders/edcolor_post.frag");
}

PTexobjED::~PTexobjED() {
    delete shader;
    delete texture;
    delete edPost;
    common->models->freeModel("biggerthing.obj");
}

void PTexobjED::draw(GfxPostProcessor* pp) {
    edPost->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    shader->use();
    
    getXRotMat(xr, common->t*0.2);
    getYRotMat(yr, common->t*0.8);
    getZRotMat(zr, common->t*0.6);
    multMat4(tmp, xr, yr);
    multMat4(xr, tmp, zr);
    glUniformMatrix4fv(shader->getUfmHandle("rotation"), 1, GL_FALSE, xr);

    glUniform1f(shader->getUfmHandle("iGlobalTime"), common->t);
    texture->bindToUnit(0);
    //gfxBindFB0();
    model->draw(shader);
    pp->bindFramebuffer();
    edPost->draw();
}
