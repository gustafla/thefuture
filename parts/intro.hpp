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

#ifndef INTRO_HPP
#define INTRO_HPP

#include "common.hpp"
#include "fade.hpp"
#include "gfx_screen.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_postprocessor.hpp"
#include "effects/particle_burst.hpp"

class PIntro{
    public:
        PIntro(CommonData* icommon);
        ~PIntro();
        void draw(Fade* drawTo=NULL);
    private:
        //ParticleBurst* pb1;
        ParticleBurst* pb2;
        ParticleBurst* pb3;
        //ParticleBurst* pb4;
        CommonData* common;
        GfxScreen* metaballs;
        GfxScreenMovable* mehutext;
        GfxScreenMovable* yeartext;
        GfxScreenMovable* revisiontext;
        GfxPostProcessor* rb;
};

#endif
