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

#ifndef DEMO_CUBE_HPP
#define DEMO_CUBE_HPP

#include "common.hpp"
#include "gfx_shader.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_mat.hpp"
#include "gfx_model.hpp"
#include "rpi_gfx.hpp"

class PCube{
	public:
		PCube(CommonData* icommon);
		~PCube();
		void draw();
	private:
        GfxShader* shader;
        GfxModel* cubeModel;
        GfxScreenMovable* twister;
        
        CommonData* common;
        
        GLfloat xr[16];
        GLfloat yr[16];
        GLfloat zr[16];
};

#endif
