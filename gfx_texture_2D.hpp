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
#ifndef GFX_TEXTURE_HPP
#define GFX_TEXTURE_HPP

#include "rpi_gfx.hpp"
#include <string>
#include "tga_file.hpp"

class GfxTexture2D
{
    public:
        GfxTexture2D(const unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);
        GfxTexture2D(std::string filename, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);
        ~GfxTexture2D();
        GLuint getHandle();
        void image2D(unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB);
        void bindToUnit(unsigned int unit);
    private:
        void loadFromFile(std::string filename);
        GLuint handle;
};

#endif
