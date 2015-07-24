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

#ifndef GFX_OBJECT_HPP
#define GFX_OBJECT_HPP

#include "obj_iobject.hpp"
#include "gfx_shader.hpp"
#include "rpi_gfx.hpp"

class GfxModel {
    public:
        GfxModel(std::string objFileName, float* igeometry=NULL, unsigned int size=0, bool ievenodd=false);
        ~GfxModel();
        void draw(GfxShader* shaderProgram);
        void draw(GfxShader* shaderProgram, float start);
        void changeDrawmode(GLuint mode=GL_TRIANGLES);
    private:
        bool textured;
        bool normaled;
        bool evenodd;
        GLuint drawmode;
        GLuint vbo;
        //GLuint indexBuffer;
        std::vector<float> geometry;
        unsigned int numVertices;
        unsigned int stride;
};

#endif
