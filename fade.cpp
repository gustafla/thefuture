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

#include "fade.hpp"

Fade::Fade(CommonData* icommon, float s, FadeType type) {
    if (type == FADE_BLACK_OUT)
        fader = new GfxPostProcessor(icommon, "shaders/fadetoblack_post.frag", GL_LINEAR, 1.0, GL_REPEAT);
    else if (type == FADE_WHITE_OUT)
        fader = new GfxPostProcessor(icommon, "shaders/fadetowhite_post.frag", GL_LINEAR, 1.0, GL_REPEAT);
    else if (type == FADE_BLACK_OUT_GLITCHED)
        fader = new GfxPostProcessor(icommon, "shaders/fadetoblackglitch_post.frag", GL_LINEAR, 1.0, GL_REPEAT);
    else if (type == FADE_BLACK_IN)
        fader = new GfxPostProcessor(icommon, "shaders/fadefromblack_post.frag", GL_LINEAR, 1.0, GL_REPEAT);
    else if (type == FADE_WHITE_IN)
        fader = new GfxPostProcessor(icommon, "shaders/fadefromwhite_post.frag", GL_LINEAR, 1.0, GL_REPEAT);
    glUseProgram(fader->getShader()->getHandle());
    glUniform1f(fader->getShader()->getUfmHandle("tmult"), (1.0/s));
    glUniform1f(fader->getShader()->getUfmHandle("tstart"), icommon->t);
}

Fade::~Fade() {
    delete fader;
}

void Fade::draw() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fader->draw();
}

void Fade::bindFramebuffer() {
    fader->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
