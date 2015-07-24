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

#ifndef GFX_NOISE_TEXTURE_HPP
#define GFX_NOISE_TEXTURE_HPP

#include "gfx_texture_2D.hpp"

class GfxNoiseTexture {
    public:
        GfxNoiseTexture(unsigned int w, unsigned int h);
        ~GfxNoiseTexture();
        GfxTexture2D* getTexture();
        void generate();

    private:
        unsigned int width;
        unsigned int height;
        GfxTexture2D* texture;
        unsigned char* image;
};

#endif
