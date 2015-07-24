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

#include "gfx_texture_2D.hpp"
#include "gfx_model.hpp"
#include "mvp.hpp"
#include "gfx_shader.hpp"
#include "common.hpp"

class PAmiga {
    public:
        PAmiga(CommonData* icommon);
        void draw();
        void resetTimer();
    private:
        CommonData* common;
        GfxTexture2D planeTex;
        //GfxTexture2D revTex;
        GfxTexture2D cubeTex;
        GfxModel plane;
        GfxModel icos;
        GfxModel revision;
        GfxModel torus;
        GfxModel cube;
        MVP mvp;
        //MVP mvp2;
        GfxShader shader;
        //GfxShader shader2;
        GfxShader modelShader;
        GfxShader orangeShader;
        float startT;
};
