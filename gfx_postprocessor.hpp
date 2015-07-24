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

#ifndef GFX_POSTPROCESSOR_HPP
#define GFX_POSTPROCESSOR_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>
#include <vector>

class GfxPostProcessor {
    public:
        GfxPostProcessor(CommonData* icommon, std::string vs, uint32_t filter=GL_NEAREST, float c=1.0, uint32_t wrap=GL_CLAMP_TO_EDGE, float cy=0.0);
        ~GfxPostProcessor();
        void draw();
        void bindFramebuffer();
        GfxTexture2D* getTexture();
        GfxShader* getShader();
        void takeTexture(GfxTexture2D* t, std::string name);
    private:
        CommonData* common;
        GfxShader shaderProgram;
        GfxTexture2D* ownTexture;
        std::vector<GfxTexture2D*> textures;
        unsigned int texCount;
        GfxTexture2D* selfOut;
        //GLfloat vertices[8];
        GLuint frameBuffer;
        GLuint renderBuffer;
        GfxModel* screen;
};

#endif
