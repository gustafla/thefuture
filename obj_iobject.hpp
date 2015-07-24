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

#ifndef OBJ_IOBJECT_HPP
#define OBJ_IOBJECT_HPP

#include <vector>
#include <string>

class IndexedObject {
    public:
        IndexedObject();
        float* getVertices();
        float* getTcoords();
        float* getNormals();
        unsigned short* getIndices();
        int getISize();
        int getTSize();
        int getNSize();
        int getVSize();
        bool loadObjFile(std::string file);
    private:
        std::string name;

        std::vector<float> vertices;
        std::vector<float> tcoords;
        std::vector<float> normals;
        std::vector<unsigned short> indices;
        bool textured;
        bool nottextured;
        bool normaled;
        bool notnormaled;
        
        //Don't look down there VVV :)
        //I should learn templates of something
        void alarm(std::string text);
        void alarm(std::string text, int i, std::string text2);
        void alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4, std::string t5, int i5);
        void alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4, std::string t5, int i5, std::string t6, int i6, std::string t7, int i7, std::string t8, int i8);
        void alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4);
        void alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3);
        void alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2);
        void alarm(std::string t0, int i0, std::string t1, int i1);
        void alarm(std::string t0, int i0);
        void alarm(std::string text, float i, std::string text2);
        void alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4, std::string t5, float i5);
        void alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4);
        void alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3);
        void alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2);
        void alarm(std::string t0, float i0, std::string t1, float i1);
        void alarm(std::string t0, float i0);
};

#endif
