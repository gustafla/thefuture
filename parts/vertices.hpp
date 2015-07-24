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

#ifndef DEMO_VERTICES_HPP
#define DEMO_VERTICES_HPP

#include "common.hpp"
#include "gfx_shader.hpp" 
#include "gfx_screen.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_model.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "mvp.hpp"

class PVertices{
	public:
		PVertices(CommonData* icommon);
		~PVertices();
		void draw();
		void resetTimer();
	private:
        CommonData* common;
        GfxShader shaderProgram;
		GfxScreen bg;
		GfxScreenMovable frameUp;
		GfxScreenMovable frameDown;
        GfxModel* cube;
        GfxTexture2D texture;
        GfxTexture2D texture2;
        GfxModel* thing;
        MVP mvp;
        float startT;
};

#endif
