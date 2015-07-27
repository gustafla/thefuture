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

#include "gfx_screen_movable.hpp"
#include "util.hpp"
#include "tga_file.hpp"
#include <string>

GfxScreenMovable::GfxScreenMovable(CommonData* icommon, std::string fs, unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string i0, float c, uint32_t filter, uint32_t wrap): //float c has to match framebuffer size to avoit odd effects!
common(icommon),
iCount(0),
store_w(w),
store_h(h),
store_x(x),
store_y(y),
shaderProgram("shaders/simple_texpos.vert", fs) {
    glUseProgram(shaderProgram.getHandle());

    GLfloat res[2] = {
        float(w)/c,
        float(h)/c
    };

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    check();
    
    if (i0 != "") {
        i = new GfxTexture2D(i0, filter, wrap);
        glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
        iCount=1;
    }

    //Here's our screen rectangle. Pixel positions "transformed" back into vertex positions.
    //Two attribs, other is screen space coords.
    vertices[0] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[1] = -((float(y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
    
    vertices[2] = 0.0;
    vertices[3] = 0.0;
    
    vertices[4] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[5] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;
    
    vertices[6] = 0.0;
    vertices[7] = 1.0;
    
    vertices[8] = ((float(x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[9] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;
    
    vertices[10] = 1.0;
    vertices[11] = 1.0;
    
    vertices[12] = ((float(x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[13] = -((float(y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
    
    vertices[14] = 1.0;
    vertices[15] = 0.0;
}

void GfxScreenMovable::draw(float st) { 
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    if (iCount)
        i->bindToUnit(0);
    //Update time
    glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), common->t-st);
    
    GLfloat res[2] = {
        float(store_w),
        float(store_h)
    };

    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_vertex"));
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_texpos"));
    glVertexAttribPointer(shaderProgram.getAtrHandle("a_vertex"), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, &vertices[0]);
    glVertexAttribPointer(shaderProgram.getAtrHandle("a_texpos"), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, &vertices[2]);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GfxScreenMovable::setWH(unsigned int w, unsigned int h) {
    store_w=w;
    store_h=h;
    vertices[1] = -((float(store_y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
    vertices[8] = ((float(store_x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[12] = ((float(store_x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[13] = -((float(store_y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
}

void GfxScreenMovable::setW(unsigned int w) {
    store_w=w;
    vertices[8] = ((float(store_x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[12] = ((float(store_x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
}

void GfxScreenMovable::setH(unsigned int h) {
    store_h=h;
    vertices[1] = -((float(store_y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
    vertices[13] = -((float(store_y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
}

void GfxScreenMovable::setXY(unsigned int x, unsigned int y) {
    store_x=x;
    store_y=y;
    vertices[0] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[1] = -((float(y+store_h)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[4] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[5] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[8] = ((float(x+store_w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[9] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[12] = ((float(x+store_w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[13] = -((float(y+store_h)-(0.5*common->res[1]))/common->res[1])*2.0;
}

void GfxScreenMovable::setX(unsigned int x) {
    store_x=x;
    vertices[0] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;

    vertices[4] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;

    vertices[8] = ((float(x+store_w)-(0.5*common->res[0]))/common->res[0])*2.0;

    vertices[12] = ((float(x+store_w)-(0.5*common->res[0]))/common->res[0])*2.0;
}

void GfxScreenMovable::setXgl(float x) {
    //store_x=x;
    vertices[0] = x;

    vertices[4] = x;

    vertices[8] = x+store_w/(common->res[0]*(common->res[1]/common->res[0]));

    vertices[12] = x+store_w/(common->res[0]*(common->res[1]/common->res[0]));
}

void GfxScreenMovable::setY(unsigned int y) {
    store_y=y;
    vertices[1] = -((float(y+store_h)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[5] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[9] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[13] = -((float(y+store_h)-(0.5*common->res[1]))/common->res[1])*2.0;
}

void GfxScreenMovable::setYgl(float y) {
    //store_y=y;
    vertices[1] = y;

    vertices[5] = y;

    vertices[9] = y+store_h/(common->res[1]*(common->res[0]/common->res[1]));

    vertices[13] = y+store_h/(common->res[1]*(common->res[0]/common->res[1]));
}

void GfxScreenMovable::setXYWH(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    store_w=w;
    store_h=h;
    store_x=x;
    store_y=y;
    vertices[0] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[1] = -((float(y+h)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[4] = ((float(x)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[5] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[8] = ((float(x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[9] = -((float(y)-(0.5*common->res[1]))/common->res[1])*2.0;

    vertices[12] = ((float(x+w)-(0.5*common->res[0]))/common->res[0])*2.0;
    vertices[13] = -((float(y+h)-(0.5*common->res[1]))/common->res[1])*2.0;
}

GfxScreenMovable::~GfxScreenMovable() {
    if (iCount)
        delete i;
}

GfxShader* GfxScreenMovable::getShader() {
    return &shaderProgram;
}
