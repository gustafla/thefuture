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

/*void main() {
    vec2 uv = gl_FragCoord.xy/iResolution.xy;
    uv *= sin(iGlobalTime)*4.0+10.0;
    vec3 c = vec3(sin(uv.x)*sin(uv.y)*0.2+0.8);
    c.r*=0.5; c.b*=1.5;
    c-=gl_FragCoord.z*1.3;
    gl_FragColor = vec4(c, 1.0);
}*/

void main() {
    gl_FragColor=vec4(0.0, 1.0-max(gl_FragCoord.z*2.0-1.2, 0.0), 0.0, 1.0);
    //gl_FragColor=vec4(0.0, 1.0, 0.0, 1.0);
}
