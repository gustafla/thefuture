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

#ifndef FADE_HPP
#define FADE_HPP

#include "gfx_postprocessor.hpp"
#include "common.hpp"

enum FadeType {FADE_BLACK_IN, FADE_BLACK_OUT, FADE_BLACK_OUT_GLITCHED, FADE_WHITE_IN, FADE_WHITE_OUT};

class Fade {
    public:
        Fade(CommonData* icommon, float time=1.0, FadeType type=FADE_BLACK_OUT);
        ~Fade();
        void draw();
        void bindFramebuffer();
    private:
        GfxPostProcessor* fader;
};

#endif
