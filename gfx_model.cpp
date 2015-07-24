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

#include "gfx_model.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>

GfxModel::GfxModel(std::string objFileName, float* igeometry, unsigned int size, bool ievenodd):
drawmode(GL_TRIANGLES),
textured(false),
normaled(false),
evenodd(ievenodd),
stride(0) {
    IndexedObject* obj;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if (igeometry == NULL) {
        obj = new IndexedObject();
    
        if(!obj->loadObjFile(objFileName))
            exit(-200);
        
        if (!obj->getTSize() && !obj->getNSize()) {
            for (int n=0; n<obj->getISize(); n++) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);   //x
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]); //y
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]); //z
                if (evenodd) {
                    geometry.push_back(float((n/3)%2));
                }
            }
            if (evenodd) {
                numVertices = geometry.size()/4;
                stride = 4;
            } else {
                numVertices = geometry.size()/3;
                stride = 3;
            }
        } else if (obj->getTSize() && !obj->getNSize()) {
            textured = true;
            for (int n=0; n<obj->getISize(); n+=2) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);    //x
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);  //y
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);  //z
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3]);   //tx
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+1]); //ty
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+2]); //tw=0
                if (evenodd) {
                    geometry.push_back(float(((n/2)/3)%2));
                }
            }
            if (evenodd) {
                numVertices = geometry.size()/7;
                stride = 7;
            } else {
                numVertices = geometry.size()/6;
                stride = 6;
            }
        } else if (!obj->getTSize() && obj->getNSize()) {
            normaled = true;
            for (int n=0; n<obj->getISize(); n+=2) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);    //x
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);  //y
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);  //z
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+1]*3]);   //x
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+1]*3+1]); //y
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+1]*3+2]); //z
                if (evenodd) {
                    geometry.push_back(float(((n/2)/3)%2));
                }
            }
            if (evenodd) {
                numVertices = geometry.size()/7;
                stride = 7;
            } else {
                numVertices = geometry.size()/6;
                stride = 6;
            }
        } else if (obj->getTSize() && obj->getNSize()) {
            normaled = true;
            textured = true;
            for (int n=0; n<obj->getISize(); n+=3) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);    //x
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);  //y
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);  //z
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3]);   //tx
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+1]); //ty
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+2]); //tw=0
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+2]*3]);   //x
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+2]*3+1]); //y
                geometry.push_back(obj->getNormals()[obj->getIndices()[n+2]*3+2]); //z
                if (evenodd) {
                    geometry.push_back(float(((n/3)/3)%2));
                }
            }
            if (evenodd) {
                numVertices = geometry.size()/10;
                stride = 10;
            } else {
                numVertices = geometry.size()/9;
                stride = 9;
            }
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * geometry.size(), &geometry[0], GL_STATIC_DRAW);
        delete obj;
    } else {
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, igeometry, GL_STATIC_DRAW);
        numVertices = size/3;
    }
    check(__FILE__, __LINE__);
    geometry.clear(); //Don't need this anymore thanks to VBO
}

void GfxModel::draw(GfxShader* shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("a_vertex"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(0));
    if (textured) {
        if (shaderProgram->getAtrHandle("a_texpos") != -1) {
            glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_texpos"));
            glVertexAttribPointer(shaderProgram->getAtrHandle("a_texpos"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(3*sizeof(GLfloat)));
        }
    }
    if (normaled) {
        if (shaderProgram->getAtrHandle("a_normal") != -1) {
            glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_normal"));
            glVertexAttribPointer(shaderProgram->getAtrHandle("a_normal"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P((textured ? 6 : 3)*sizeof(GLfloat)));
        }
    }
    if (evenodd) {
        if (shaderProgram->getAtrHandle("a_odd") != -1) {
            glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_odd"));
            glVertexAttribPointer(shaderProgram->getAtrHandle("a_odd"), 1, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P( ((!(textured || normaled)) ? 3 : ((textured && normaled) ? 9 : 6)) *sizeof(GLfloat)));
        }
    }

    glDrawArrays(drawmode, 0, numVertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GfxModel::draw(GfxShader* shaderProgram, float start) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("a_vertex"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(0));
    if (textured) {
        glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_texpos"));
        glVertexAttribPointer(shaderProgram->getAtrHandle("a_texpos"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(3*sizeof(GLfloat)));
    }
    if (normaled) {
        if (shaderProgram->getAtrHandle("a_normal") != -1) {
            glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_normal"));
            glVertexAttribPointer(shaderProgram->getAtrHandle("a_normal"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P((textured ? 6 : 3)*sizeof(GLfloat)));
        }
    }
    if (evenodd) {
        if (shaderProgram->getAtrHandle("a_odd") != -1) {
            glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_odd"));
            glVertexAttribPointer(shaderProgram->getAtrHandle("a_odd"), 1, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P( ((!(textured || normaled)) ? 3 : ((textured && normaled) ? 9 : 6)) *sizeof(GLfloat)));
        }
    }
    
    float s;
    if (start <= 0.0) {
        s=0.0;
        glDrawArrays(drawmode, 0, numVertices);
    }
    else {
        s=start;
        if (start > 1.0)
            s=1.0;
        glDrawArrays(drawmode, s*numVertices, numVertices-numVertices*s+1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GfxModel::changeDrawmode(GLuint mode) {
    drawmode = mode;
}

GfxModel::~GfxModel() {
    //std::cout << "Model destructor called :O\n";
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &indexBuffer);
}
