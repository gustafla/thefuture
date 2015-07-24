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

#include "gfx_model_handler.hpp"

GfxModel* GfxModelHandler::getModel(std::string name) {
    if (models.find(name) == models.end()) { //If there is no model name
        models[name] = new GfxModel(name, NULL, 0, false);   //Create and map
    }
    return models[name]; //Give a pointer to the model in heap
}

bool GfxModelHandler::freeModel(std::string name) {
    if (models.find(name) == models.end()) { //If there is no model name
        return false;                        //Don't delete a nonexisting model
    }
    
    GfxModel* modelPtr = models[name];
    models.erase(name);
    delete modelPtr;
    
    return true;
}
