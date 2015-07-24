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

uniform vec2 iResolution;
uniform float iGlobalTime;

const float PI = 3.14159265;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    pos+=vec2(sin(pos.x*4.0)*abs(sin(iGlobalTime*1.7*PI))*sin(pos.y), sin(pos.y*13.0+iGlobalTime))*0.1;
    pos.x+=sin(pos.y*7.0)*0.5;
    vec2 center = vec2(sin(iGlobalTime*0.3), cos(iGlobalTime+sin(iGlobalTime*1.2)))*0.3+1.2;
    
    vec3 primaryColor = vec3(0.0, 1.0, 0.1);
    
    float roundMap = sin(length(pos-center)*20.0)*4.0-3.0;
    
    gl_FragColor = vec4(primaryColor*roundMap, 1.0);
}
