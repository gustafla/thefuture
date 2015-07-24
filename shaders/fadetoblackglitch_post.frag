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

uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform float iGlobalTime;
uniform float tmult;
uniform float tstart;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    float t=iGlobalTime-tstart;
    float glitch = clamp(sin(t*200.0)*sin(t*2.0)*10.0, 0.0, 2.0);
    pos.x+=rand(vec2(pos.y+t))*glitch;
    pos.y+=sin(t*2.0)*sin(t*0.92)*3.0;
    float tstretch=t*tmult;
    gl_FragColor = vec4(texture2D(iChannel0, pos).rgb*(1.0-tstretch)+rand(pos)*glitch*0.03, 1.0);
    //gl_FragColor = vec4(1.0,0.5,0.0, 1.0); //Test :D
}
