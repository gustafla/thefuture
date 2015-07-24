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

//float BPS = 175.0/60.0;
//float PI  = 3.14159256;
float TIME  = 5.0;

void main() {
    vec4 v = vec4(a_vertex, 1.0);
    v.z += iGlobalTime;
    v.z = mod(v.z, 10.0);
    v.z -= 5.0;
    //v.y += sin(v.z+iGlobalTime)*0.06*beat;
	v = rotation * v;
    //v.z-=beat*0.05; //This looks bad.
    //v.z-=pow(max(0.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))),max(1.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))));
    float perspective = clamp(((v.z/4.0)+1.0), 0.0, 1.0);
	gl_PointSize = (iResolution.x/20.0)*(perspective*perspective);
    gl_Position = projection * v;
}
