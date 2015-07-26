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

#include "particle.hpp"
#include <iostream>

Particle::Particle(CommonData* icommon, float x, float y, float z, float dx, float dy, float dz, float ax, float ay, float az) {
    common = icommon;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    dirs[0] = dx;
    dirs[1] = dy;
    dirs[2] = dz;
    accels[0] = ax;
    accels[1] = ay;
    accels[2] = az;
}

GLfloat* Particle::tick() {
    for (int i=0; i<3; i++)
        dirs[i] += accels[i]*common->deltat;
    for (int i=0; i<3; i++)
        coords[i] += dirs[i]*common->deltat;
    //std::cout << "X: " << coords[0] << std::endl;
    //std::cout << "Y: " << coords[1] << std::endl;
    //std::cout << "Z: " << coords[2] << std::endl;
    return coords;
}
