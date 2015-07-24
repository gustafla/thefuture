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

#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include <cmath>

void multMat4(float* result, float* a, float* b) {
    result[0]  = (a[0]*b[0]  + a[4]*b[1]  + a[8]*b[2]   + a[12]*b[3]);  //first a row dot first b column
    result[1]  = (a[1]*b[0]  + a[5]*b[1]  + a[9]*b[2]   + a[13]*b[3]);  //second a row dot first b column
    result[2]  = (a[2]*b[0]  + a[6]*b[1]  + a[10]*b[2]  + a[14]*b[3]);  //third a row dot first b column
    result[3]  = (a[3]*b[0]  + a[7]*b[1]  + a[11]*b[2]  + a[15]*b[3]);  //fourth a row dot first b column
                                                                        
    result[4]  = (a[0]*b[4]  + a[4]*b[5]  + a[8]*b[6]   + a[12]*b[7]);  //first a row dot second b column
    result[5]  = (a[1]*b[4]  + a[5]*b[5]  + a[9]*b[6]   + a[13]*b[7]);  //second a row dot second b column
    result[6]  = (a[2]*b[4]  + a[6]*b[5]  + a[10]*b[6]  + a[14]*b[7]);  //third a row dot second b column
    result[7]  = (a[3]*b[4]  + a[7]*b[5]  + a[11]*b[6]  + a[15]*b[7]);  //fourth a row dot second b column
    
    result[8]  = (a[0]*b[8]  + a[4]*b[9]  + a[8]*b[10]  + a[12]*b[11]); //first a row dot third b column
    result[9]  = (a[1]*b[8]  + a[5]*b[9]  + a[9]*b[10]  + a[13]*b[11]); //second a row dot third b column
    result[10] = (a[2]*b[8]  + a[6]*b[9]  + a[10]*b[10] + a[14]*b[11]); //third a row dot third b column
    result[11] = (a[3]*b[8]  + a[7]*b[9]  + a[11]*b[10] + a[15]*b[11]); //fourth a row dot third b column
    
    result[12] = (a[0]*b[12] + a[4]*b[13] + a[8]*b[14]  + a[12]*b[15]); //first a row dot fourth b column
    result[13] = (a[1]*b[12] + a[5]*b[13] + a[9]*b[14]  + a[13]*b[15]); //second a row dot fourth b column
    result[14] = (a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15]); //third a row dot fourth b column
    result[15] = (a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15]); //fourth a row dot fourth b column
}

void getPProjMat(float* mat, float fov, float aspect, float znear, float zfar) {
    float xymax = znear * tan(fov * (M_PI/360.0));
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zfar - znear;
    float q = -(zfar + znear) / depth;
    float qn = -2 * (zfar * znear) / depth;

    float w = 2 * znear / width;
    w = w / aspect;
    float h = 2 * znear / height;

    mat[0] = w;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = h;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = q;
    mat[11] = -1.0;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = qn;
    mat[15] = 0.0f;
}

void getXRotMat(float* mat, float a) {
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = cos(a);
    mat[6] = -sin(a);
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = sin(a);
    mat[10] = cos(a);
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getYRotMat(float* mat, float a) {
    mat[0] = cos(a);
    mat[1] = 0.0f;
    mat[2] = sin(a);
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = 1.0f;  
    mat[6] = 0.0f;   
    mat[7] = 0.0f;

    mat[8] = -sin(a);
    mat[9] = 0.0f;  
    mat[10] = cos(a);
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getZRotMat(float* mat, float a) {
    mat[0] = cos(a);
    mat[1] = -sin(a);
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = sin(a);
    mat[5] = cos(a);
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getXYZRotMat(float* mat, float x, float y, float z) {
    GLfloat zm[16] = {0.0f};
    GLfloat ym[16] = {0.0f};
    GLfloat xm[16] = {0.0f};
    GLfloat tmp[16];
    
    zm[0] = cos(z);
    zm[1] = -sin(z);
    zm[4] = sin(z);
    zm[5] = cos(z);
    zm[10] = 1.0f;
    zm[15] = 1.0f;
    
    ym[0] = cos(y);
    ym[2] = sin(y);
    ym[5] = 1.0f;  
    ym[8] = -sin(y);
    ym[10] = cos(y);
    ym[15] = 1.0f;
    
    xm[0] = 1.0f;
    xm[5] = cos(x);
    xm[6] = -sin(x);
    xm[9] = sin(x);
    xm[10] = cos(x);
    xm[15] = 1.0f;
    
    multMat4(tmp, xm, ym);
    multMat4(mat, tmp, zm);
}

void getTranslationMat(float* mat, float x, float y, float z) {
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
    mat[15] = 1.0f;
}

void getScaleMat(float* mat, float x, float y, float z) {
    mat[0] = x;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = y;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = z;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getScaleMat(float* mat, float x) {
    mat[0] = x;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = x;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = x;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}
