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

precision highp float;

attribute vec3 a_vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 rotation;
uniform vec2 iResolution;
uniform float beat;

void main() {
    vec4 v = vec4(a_vertex, 1.0);
    v.z+=sin(4.0*v.x+v.y+iGlobalTime*2.0)*0.2;
    v.z+=cos(iGlobalTime+v.x*v.y*6.0)*0.05;
    v.z+=sin(10.0*sin(v.x+iGlobalTime)+iGlobalTime*0.2)*0.02;
    v = rotation*v;
    v.z -= sin(iGlobalTime)*0.4+2.0;
    v.y += ((beat)*0.2);
	gl_PointSize = (iResolution.x/16.0)*pow(clamp(((v.z/4.0)+1.0), 0.0, 1.0), 2.0);
    gl_Position = projection * v;
}
