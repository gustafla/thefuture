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

#ifndef WARP_FIELD_HPP
#define WARP_FIELD_HPP

#include "common.hpp"
#include "rpi_gfx.hpp"
#include "gfx_model.hpp"
#include "mvp.hpp"

class EWarpField {
    public:
        EWarpField(CommonData* icommmon, unsigned int inum=100);
        ~EWarpField();
        void draw();
    private:
        unsigned int num;
        CommonData* common;
        float* stars;
        MVP mvp;
        GfxModel* star;
        GfxShader shader;
};

#endif
