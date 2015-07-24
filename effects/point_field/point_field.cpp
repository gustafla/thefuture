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

#include "effects/point_field.hpp"
#include "util.hpp"
#include "tga_file.hpp"
#include "gfx_mat.hpp"
#include <cmath>

EPointField::EPointField(CommonData* icommon, unsigned int const count):
common(icommon),
shaderProgram("effects/point_field/star.vert", "shaders/textured_point.frag") {
    glUseProgram(shaderProgram.getHandle());

    //Load, set up texture
    pointTexture = new GfxTexture2D("graphics/star.tga");
    pointTexture->bindToUnit(0);
    glUniform1i(shaderProgram.getUfmHandle("pointTexture"), 0);

    //Set miscellanous shader uniforms
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, common->res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);
    //glUniformMatrix4fv(shaderProgram.getUfmHandle("rotation"), 1, GL_FALSE, rotationMatrix);

    check();

    //Create the random "starfield"
    std::vector<float> geometry;
    for (int create_i = 0; create_i < count; create_i++) {
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
	}
    vertices = new GfxModel("", &geometry[0], geometry.size());
    vertices->changeDrawmode(GL_POINTS);
    
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat80);
}

EPointField::~EPointField() {
    delete pointTexture;
    delete vertices;
}

void EPointField::draw() { 
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    pointTexture->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //Let's update rotation matrices
    getXYZRotMat(rotation, common->t*0.16, (common->t+sin(common->t*0.2))*0.1, common->t*0.12);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("rotation"), 1, GL_FALSE, rotation);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    vertices->draw(&shaderProgram);
    //Most waving and perspective magic happens in the shaders
}
