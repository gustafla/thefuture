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

#ifdef GL_ES
precision highp float;
#endif

attribute vec3 a_vertex;
/*uniform mat4 projection;
uniform mat4 scale;
uniform mat4 translation;
uniform mat4 view;
uniform mat4 rotation;*/
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 iResolution;

void main() {
    vec4 v = view * model * vec4(a_vertex, 1.0);
	gl_PointSize = (iResolution.x/10.0)*pow(clamp(((v.z/10.0)+1.0), 0.0, 1.0), 2.0);
    gl_Position = projection * v;
}
