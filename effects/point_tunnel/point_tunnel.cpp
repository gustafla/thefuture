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

#include "effects/point_tunnel.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include "tga_file.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "util.hpp"

EPointTunnel::EPointTunnel(CommonData* icommon):
common(icommon),
shaderProgram("effects/point_tunnel/proj_tunnel_point.vert", "shaders/textured_point.frag") {
    start=-1.0f;
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
    
    //Generate point tunnel
    for(float z=-5.0f; z<5.0f; z+=M_PI*0.1f) {
        for (float x=0.0f; x<M_PI_2*4.0f; x+=M_PI*0.1f) {
            points.push_back(sin(x+z*0.33f)+sin(z*M_PI*(2.0/5.0f))*0.2);
            points.push_back(cos(x+z*0.33f)+cos(z*M_PI*(2.0/5.0f))*0.2);
            points.push_back(z);
        }   
    }
    //vertices = new GfxModel("", &(points[0]), points.size()-3, false);
    //vertices->changeDrawmode(GL_POINTS);
    
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat80);
}

EPointTunnel::~EPointTunnel() {
    delete pointTexture;
    delete vertices;
}

void EPointTunnel::draw() {
    if (start<0.0f)
        start = common->t;
    
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    pointTexture->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //Let's update rotation matrices
    getXYZRotMat(rotation, sin(common->t*0.2)*0.3, sin(common->t*0.6)*0.2, sin(common->t*0.12)*0.2);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("rotation"), 1, GL_FALSE, rotation);
    
    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    /*drawAmount = 2.0f-(common->t/5.0f-start/5.0f);
    if (drawAmount<1.0f)*/
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_vertex"));
    glVertexAttribPointer(shaderProgram.getAtrHandle("a_vertex"), 3, GL_FLOAT, GL_TRUE, 0/*sizeof(GLfloat)*3*/, &points[0]);
        //vertices->draw(&shaderProgram/*, drawAmount*/);
        glDrawArrays(GL_POINTS, 0, points.size()/3-12); //Come on WTF
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //vertices->draw(&shaderProgram);
    //Most waving and stuff happens in the shaders
}

void EPointTunnel::resetTimer() {
    start = -1.0f;
}
