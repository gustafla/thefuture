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

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "common.hpp"

class Particle {
    public:
        Particle(CommonData* icommon, float x, float y, float z, float dx, float dy, float dz, float ax, float ay, float az);
        GLfloat* tick();
    private:
        CommonData* common;
        GLfloat coords[3];
        GLfloat dirs[3];
        GLfloat accels[3];
};

#endif
