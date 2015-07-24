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

#ifndef POINT_FLAG_HPP
#define POINT_FLAG_HPP

#include <vector>
#include "gfx_texture_2D.hpp"
#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "common.hpp"

class EPointFlag {
    public:
        EPointFlag(CommonData* icommon);
        ~EPointFlag();
        void draw();
        void resetTimer();
    private:
        CommonData* common;
        //std::vector<GLfloat> points;
        GfxTexture2D* pointTexture;
        GfxModel* vertices;
        GfxShader shaderProgram;

        float rotation[16];
        float startT;
};

#endif
