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

#include "rpi_gfx.hpp"

void check(std::string file, int line)
{
    static GLenum error;
    error = glGetError();

    if (error)
    {
        if (file != "" || line >= 0)
            std::cout << "check() error: " << file << " line " << line << "\n";
        else
            std::cout << "check() error.\n";
        if (error == GL_OUT_OF_MEMORY)
            std::cout << "GPU OUT OF MEMORY! ;__;\n";
        else if (error == GL_INVALID_OPERATION)
            std::cout << "Invalid GL operation. Fix your/my code.\n";
        else
            std::cout << "glGetError() " << error << std::endl;
        exit(error);
    }
}

void gfxBindFB0() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

