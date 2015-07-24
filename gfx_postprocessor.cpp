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

#include "gfx_postprocessor.hpp"
#include "util.hpp"
#include <string>

GfxPostProcessor::GfxPostProcessor(CommonData* icommon, std::string fs, uint32_t filter, float c, uint32_t wrap, float cy):
common(icommon),
texCount(0),
shaderProgram("shaders/simple.vert", fs) {
    glUseProgram(shaderProgram.getHandle());
    
    if (cy==0.0)
		cy = c;
    
    GLfloat res[2] = {
        common->res[0]/c,
        common->res[1]/cy
    };

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    check();

    ownTexture = new GfxTexture2D(NULL, res[0], res[1], GL_RGB, filter, wrap);
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ownTexture->getHandle(), 0);
    
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, res[0], res[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    //Here's our screen rectangle
    /*vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -1.0f;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = -1.0f;*/
    screen = common->models->getModel("screen.obj");
}

GfxPostProcessor::~GfxPostProcessor() {
    delete ownTexture;
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}

void GfxPostProcessor::draw() {
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    ownTexture->bindToUnit(0);
    
    for (int i=0; i < texCount; i++) {
        textures[i]->bindToUnit(i+1);
    }
        
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    //YOU NEED TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    /*glVertexAttribPointer(shaderProgram.getAtrHandle("a_vertex"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_vertex"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);*/
    screen->draw(&shaderProgram);
}

void GfxPostProcessor::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

GfxTexture2D* GfxPostProcessor::getTexture() {
    return ownTexture;
}

GfxShader* GfxPostProcessor::getShader() {
    return &shaderProgram;
}

void GfxPostProcessor::takeTexture(GfxTexture2D* t, std::string name) {
    glUseProgram(shaderProgram.getHandle());
    glUniform1i(shaderProgram.getUfmHandle(name), texCount+1);
    textures.push_back(t);
    texCount++;
}
