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

#include "gfx_shader.hpp"
#include "util.hpp"
#include <iostream>

GfxShader::GfxShader():
handle(0), vname("no filename"), fname("no filename")
{

}

GfxShader::GfxShader(std::string vsName, std::string fsName):
handle(0), vname(vsName), fname(fsName)
{
    //Load, compile shaders
    std::string fsTemp;
    std::string vsTemp;
    if (!loadFile(fsName, fsTemp))
        exit(40);
    if (!loadFile(vsName, vsTemp))
        exit(41);
    if(compProgram(vsTemp, fsTemp) == GL_FALSE)
        exit(1);
}

GfxShader::~GfxShader() {
    glDeleteProgram(handle);
}

GLuint GfxShader::getHandle()
{
    return handle;
}

unsigned int GfxShader::getUfmHandle(std::string name)
{
    if (uniforms.find(name) == uniforms.end())
        uniforms[name] = glGetUniformLocation(handle, name.c_str());
    return uniforms[name];
}

unsigned int GfxShader::getAtrHandle(std::string name)
{
    if (attributes.find(name) == attributes.end())
        attributes[name] = glGetAttribLocation(handle, name.c_str());
    return attributes[name];
}

GLuint GfxShader::compShader(GLenum type, const char* src)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);

    if (shader == 0)
        return 0;

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            std::cout << "Error compiling shader: ";
            if (type == GL_VERTEX_SHADER)
                std::cout << vname;
            else
                std::cout << fname;
            std::cout << std::endl << infoLog << std::endl;
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLint GfxShader::compProgram(std::string vsString, std::string fsString)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    vertexShader = compShader(GL_VERTEX_SHADER, vsString.c_str());
    fragmentShader = compShader(GL_FRAGMENT_SHADER, fsString.c_str());

    handle = glCreateProgram();

    if (handle == 0)
        return 0;

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);

    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv ( handle, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 )
        {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);

            glGetProgramInfoLog ( handle, infoLen, NULL, infoLog);
            std::cout << "Error linking program: " << vname << " " << fname << std::endl << infoLog << std::endl;

            free(infoLog);
        }
        glDeleteProgram(handle);
        return GL_FALSE;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return GL_TRUE;
}

void GfxShader::use() {
    glUseProgram(handle);
}
