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

#ifndef POINT_MODEL_HPP
#define POINT_MODEL_HPP

#include "common.hpp"
#include "gfx_shader.hpp" 
#include "gfx_screen.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_postprocessor.hpp"
#include "gfx_model.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "mvp.hpp"

class EPointModel{
	public:
		EPointModel(CommonData* icommon, std::string name, float scale=1.0f);
		~EPointModel();
		void draw();
		void resetTimer();
	private:
        CommonData* common;
        GfxShader shaderProgram;
		//GfxScreen bg;
		//GfxScreenMovable frameUp;
		//GfxScreenMovable frameDown;
        GfxModel* model;
        GfxTexture2D pointTexture;
        GfxTexture2D pointTexture2;
        //GfxModel cube;
        MVP mvp;
        float startT;
        //GfxScreen bg2;
        //GfxPostProcessor glitch;
};

#endif
