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

#include "types.hpp"
#include "obj_iobject.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "util.hpp"

IndexedObject::IndexedObject():
textured(false), nottextured(false), normaled(false), notnormaled(false) {}

float* IndexedObject::getVertices() {
    return &vertices[0];
}

float* IndexedObject::getTcoords() {
    return &tcoords[0];
}

float* IndexedObject::getNormals() {
    return &normals[0];
}

unsigned short* IndexedObject::getIndices() {
    return &indices[0];
}

int IndexedObject::getISize() {
    return indices.size();
}

int IndexedObject::getVSize() {
    return vertices.size();
}

int IndexedObject::getTSize() {
    if (textured)
        return tcoords.size();
    else return 0;
}

int IndexedObject::getNSize() {
    if (normaled)
        return normals.size();
    else return 0;
}

bool IndexedObject::loadObjFile(std::string file) {
    name = file;
    std::vector<std::string*> objLine;

    std::ifstream in(file.c_str());
    if (!in.is_open()) {
        alarm("no such file.");
        return false;
    }
    char buf[256];
    while (!in.eof()){
        in.getline(buf, 256);
        objLine.push_back(new std::string(buf));
    }
    
    float tx, ty, tz;
    int a, b, c, d, e, f, g, h, i;
    
    for (int index=0; index<objLine.size(); index++) {
        if (objLine[index]->c_str()[0]=='#' || objLine[index]->c_str()[0]=='\n')
            continue;
        else if (objLine[index]->c_str()[0]=='v' && objLine[index]->c_str()[1]==' ') { //vertex
            sscanf(objLine[index]->c_str(), "v %f %f %f", &tx, &ty, &tz);
            alarm("Vertex: ", tx, " ", ty, " ", tz);
            vertices.push_back(tx);
            vertices.push_back(ty);
            vertices.push_back(tz);
        } else if (objLine[index]->c_str()[0]=='v' && objLine[index]->c_str()[1]=='n') { //normal
            sscanf(objLine[index]->c_str(), "vn %f %f %f", &tx, &ty, &tz);
            alarm("Normal: ", tx, " ", ty, " ", tz);
            normals.push_back(tx);
            normals.push_back(ty);
            normals.push_back(tz);
        } else if (objLine[index]->c_str()[0]=='v' && objLine[index]->c_str()[1]=='t') { //texture coordinate
            if (count(objLine[index]->begin(), objLine[index]->end(), ' ') == 3) {
                sscanf(objLine[index]->c_str(), "vt %f %f %f", &tx, &ty, &tz);
                alarm("Texture coord: ", tx, " ", ty, " ", tz);
                tcoords.push_back(tx);
                tcoords.push_back(ty);
                tcoords.push_back(tz);
            } else if (count(objLine[index]->begin(), objLine[index]->end(), ' ') == 2) {
                sscanf(objLine[index]->c_str(), "vt %f %f", &tx, &ty);
                alarm("Texture coord: ", tx, " ", ty, " ", 0.0f);
                tcoords.push_back(tx);
                tcoords.push_back(ty);
                tcoords.push_back(0.0f);
            } else {
                alarm("Something wrong with line ", index, ".");
                exit(-200);
            }
        } else if (objLine[index]->c_str()[0]=='f') { //face
            if (count(objLine[index]->begin(), objLine[index]->end(), ' ') == 3) { //triangular face
                if (count(objLine[index]->begin(), objLine[index]->end(), '/') == 0) { //only vertex coords
                    nottextured = true;
                    notnormaled = true;
                    sscanf(objLine[index]->c_str(), "f %d %d %d", &a, &b, &c);
                    alarm("Triangle indices: ", a, " ", b, " ", c);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                } else if (countSubstring(*objLine[index], "/") == 3) { //vertex coords + texture coords
                    textured = true;
                    notnormaled = true;
                    sscanf(objLine[index]->c_str(), "f %d/%d %d/%d %d/%d", &a, &b, &c, &d, &e, &f);
                    alarm("Triangle indices and texture coord indices: ", a, " ", c, " ", e, " / ", b, " ", d, " ", f);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                    indices.push_back(d-1);
                    indices.push_back(e-1);
                    indices.push_back(f-1);
                } else if (countSubstring(*objLine[index], "//") == 3) { //vertex coords + normals
                    normaled = true;
                    nottextured = true;
                    sscanf(objLine[index]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &d, &e, &f);
                    alarm("Triangle indices and normal indices: ", a, " ", c, " ", e, " / ", b, " ", d, " ", f);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                    indices.push_back(d-1);
                    indices.push_back(e-1);
                    indices.push_back(f-1);
                } else if (countSubstring(*objLine[index], "/") == 6) { //vertex coords + texture coords + normals
                    normaled = true;
                    textured = true;
                    sscanf(objLine[index]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &b, &c, &d, &e, &f, &g, &h, &i);
                    alarm("Triangle indices, texture coord indices and normal indices: ", a, " ", d, " ", g, " / ", b, " ", e, " ", h, " / ", c, " ", f, " ", i);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                    indices.push_back(d-1);
                    indices.push_back(e-1);
                    indices.push_back(f-1);
                    indices.push_back(g-1);
                    indices.push_back(h-1);
                    indices.push_back(i-1);
                } else
                    alarm("Skipped line ", index, ". Something very wrong with this line.");
            } else //not triangular face
                alarm("Skipped line ", index, ". Not a triangular face :(");
        } else {
            alarm("Unrecognized: " + *objLine[index]);
            continue;
        }
    }
    
    if ((textured && nottextured) || (normaled && notnormaled)) {
        alarm("Mixed indices not supported.");
        return false;
    }
    if (!textured && tcoords.size()) {
        alarm("Warning: Texture coords entirely unused.");
    }
    if (!normaled && normals.size()) {
        alarm("Warning: Normals entirely unused.");
    }
    
    return true;
}

 //Don't look down there VVV :)
 //I should learn templates of something
void IndexedObject::alarm(std::string text) {
    std::cout << "Loader: " << name << ": " << text << std::endl;
}

void IndexedObject::alarm(std::string text, int i, std::string text2) {
    std::cout << "Loader: " << name << ": " << text << i << text2 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4, std::string t5, int i5) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << t5 << i5 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4, std::string t5, int i5, std::string t6, int i6, std::string t7, int i7, std::string t8, int i8) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << t5 << i5 << t6 << i6<< t7 << i7 << t8 << i8 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << std::endl;
}

void IndexedObject::alarm(std::string text, float i, std::string text2) {
    std::cout << "Loader: " << name << ": " << text << i << text2 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4, std::string t5, float i5) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << t5 << i5 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << std::endl;
}
