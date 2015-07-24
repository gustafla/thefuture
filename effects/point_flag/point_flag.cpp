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

#include "effects/point_flag.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include "tga_file.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "util.hpp"

EPointFlag::EPointFlag(CommonData* icommon):
common(icommon),
shaderProgram("effects/point_flag/proj_wave_point.vert", "shaders/textured_point.frag") {
    startT=-1.0;
    glUseProgram(shaderProgram.getHandle());

    //Load, set up texture
    pointTexture = new GfxTexture2D("graphics/mehu64.tga");
    pointTexture->bindToUnit(0);
    glUniform1i(shaderProgram.getUfmHandle("pointTexture"), 0);

    //Set miscellanous shader uniforms
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, common->res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    check();
    
    //Generate point "mat"
    std::vector<float> points;
    for(float y=-1.1; y<1.1; y+=0.14) {
        for (float x=1.6; x>-1.6; x-=0.14) {
            points.push_back(x);
            points.push_back(y);
            points.push_back(0.0);
        }   
    }
    vertices = new GfxModel("", &points[0], points.size());
    vertices->changeDrawmode(GL_POINTS);
    
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat80);
}

EPointFlag::~EPointFlag() {
    delete pointTexture;
    delete vertices;
}

void EPointFlag::draw() {
    if (startT<0.0)
        startT = common->t;
    
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    pointTexture->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //Let's update rotation matrices
    getXYZRotMat(rotation, sin(common->t*0.2)*0.1, sin(common->t*0.6)*0.4, sin(common->t*0.12)*0.1);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("rotation"), 1, GL_FALSE, rotation);
    
    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    vertices->draw(&shaderProgram, 1.0-(common->t/2.0-startT/2.0));
    //Most waving and stuff happens in the shaders
}

void EPointFlag::resetTimer() {
    startT = -1.0f;
}
