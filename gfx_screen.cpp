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

#include "gfx_screen.hpp"
#include "util.hpp"
#include "tga_file.hpp"
#include <string>

GfxScreen::GfxScreen(CommonData* icommon, std::string fs, std::string i0, float c): //float c has to match framebuffer size to avoit odd effects!
common(icommon),
iCount(0),
shaderProgram("shaders/simple.vert", fs) {
    glUseProgram(shaderProgram.getHandle());

    GLfloat res[2] = {
        common->res[0]/c,
        common->res[1]/c
    };

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    check();
    
    if (i0 != "") {
        i = new GfxTexture2D(i0);
        glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
        iCount=1;
    }

    /*//Here's our screen rectangle
    vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -1.0f;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = -1.0f;*/
    screen = common->models->getModel("screen.obj");
}

void GfxScreen::draw() { 
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    if (iCount)
        i->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    /*glVertexAttribPointer(shaderProgram.getAtrHandle("a_vertex"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_vertex"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);*/
    screen->draw(&shaderProgram);
}

GfxScreen::~GfxScreen() {
    if (iCount)
        delete i;
}

void GfxScreen::useProgram() { 
    glUseProgram(shaderProgram.getHandle());
}

GfxShader* GfxScreen::getProgram() { 
    return &shaderProgram;
}
