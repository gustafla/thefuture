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

#ifndef GFX_SCREEN_HPP
#define GFX_SCREEN_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>

class GfxScreen {
    public:
        GfxScreen(CommonData* icommon, std::string fs, std::string i0="", float c=1.0);
        ~GfxScreen();
        void draw();
        void useProgram();
        GfxShader* getProgram();
    private:
        GfxTexture2D* i;
        GfxModel* screen;
        unsigned short iCount;
        GfxShader shaderProgram;
        CommonData* common;
        //GLfloat vertices[8];
};

#endif
