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

#ifndef GFX_SCREEN_MOVABLE_HPP
#define GFX_SCREEN_MOVABLE_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>

class GfxScreenMovable {
    public:
        GfxScreenMovable(CommonData* icommon, std::string fs, unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string i0="", float c=1.0, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);
        ~GfxScreenMovable();
        void draw(float st=0.0f);
        void setWH(unsigned int w, unsigned int h);
        void setW(unsigned int w);
        void setH(unsigned int h);
        void setXY(unsigned int x, unsigned int y);
        void setX(unsigned int x);
        void setXgl(float x);
        void setY(unsigned int y);
        void setYgl(float y);
        void setXYWH(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        GfxShader* getShader();
    private:
        GfxTexture2D* i;
        unsigned short iCount;
        GfxShader shaderProgram;
        CommonData* common;
        GLfloat vertices[16];

        float store_x;
        float store_y;
        float store_w;
        float store_h;
};

#endif
