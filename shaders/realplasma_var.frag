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

uniform float iGlobalTime;
uniform vec2 iResolution;
varying vec2 texpos;

void main() {
    vec2 pos = texpos;
    pos.y += (sin(pos.y*6.0+iGlobalTime) + sin(pos.y*2.0-iGlobalTime*0.6)*0.3)*0.3;
    pos.x += (sin(pos.y*5.0+iGlobalTime*1.2)*0.7 + sin(pos.y*4.0-iGlobalTime*0.5)*0.4 + sin(pos.y*4.0+iGlobalTime*0.8))*0.3;
    float primaryMap = ((sin(pos.x*12.0+iGlobalTime*0.3)+0.5) + sin(pos.y*10.0+iGlobalTime) +
                        sin(pos.y*3.0*pos.x*2.0+iGlobalTime*1.3)*0.4+0.4 + sin(pos.x+pos.y+iGlobalTime*1.3)*2.0) * (cos(pos.y*pos.x*4.0+iGlobalTime)*0.8+1.2 + (sin(pos.x*2.0+iGlobalTime)*0.3+1.0));
    primaryMap *= 2.0;
    gl_FragColor = vec4(vec3(sin(primaryMap), sin(primaryMap+1.7), sin(primaryMap+3.66666)*0.3), 1.0);
}
