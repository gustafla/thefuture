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

#ifndef MVP_HPP
#define MVP_HPP

#include "rpi_gfx.hpp"
#include "gfx_mat.hpp"

class MVP {
    public:
        MVP(GLfloat* _projection, GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f, GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f, GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f, GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f, GLfloat _scale=1.0f);
        void buildMVP();
        void buildModel();
        //void buildView();
        GLfloat mvp[16];
        GLfloat* getView();
        GLfloat* getModel();
        void setProjection(GLfloat* _projection);
        
        void setView(GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f, GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f);
        void setViewTranslation(GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f);
        void setViewRotation(GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f);
        //void setViewRotation2(GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f);
        
        void setModel(GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f, GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f, GLfloat _scale=1.0f);
        void setModelTranslation(GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f);
        void setModelRotation(GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f);
        void setModelScale(GLfloat _scale=1.0f);
        
    private:
        GLfloat* projection;
        
        GLfloat viewt[16];
        GLfloat viewr[16];
        //GLfloat viewr2[16];
        GLfloat view[16];
        
        GLfloat rotation[16];
        GLfloat scale[16];
        GLfloat translation[16];
        
        GLfloat model[16];
        GLfloat identity[16];
        GLfloat tmp[16];
};

#endif
