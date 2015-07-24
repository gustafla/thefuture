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

#include "effects/warp_field.hpp"
#include "util.hpp"
#include <cmath>

EWarpField::EWarpField(CommonData* icommon, unsigned int inum):
common(icommon),
num(inum),
mvp(icommon->pProjMat80),
shader("shaders/mvp.vert", "shaders/white.frag") {
    GLfloat starVtc[2*3] = {
        0.0f, 0.0f, -0.2f,
        0.0f, 0.0f,  0.2f
    };
    star = new GfxModel("", starVtc, 2*3, false);
    star->changeDrawmode(GL_LINES);
    stars = new GLfloat[num*3];
    for (unsigned int n=0; n<num*3; n++) { //Generate star translations
        stars[n] = randf()*5.0f;
    }
    shader.use();
    glUniform2fv(shader.getUfmHandle("iResolution"), 1, common->res);
    mvp.setViewTranslation(0.0f, 0.0f, -5.0f);
}

EWarpField::~EWarpField() {
    delete star;
    delete stars;
}

void EWarpField::draw() {
    shader.use();
    glUniform1f(shader.getUfmHandle("iGlobalTime"), common->t);
    for (unsigned int n=0; n<num; n++) {
        mvp.setModelTranslation(stars[n*3], stars[n*3+1], fmod((stars[n*3+2]+common->t*10.0f)+5.0f, 10.0f)-5.0f);
        mvp.buildModel();
        mvp.buildMVP();
        glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
        star->draw(&shader);
    }
}
