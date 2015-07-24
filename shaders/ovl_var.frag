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
varying vec2 texpos;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

float PI = 3.14159265;

void main() {
    vec2 pos = texpos;
    vec2 wpos = vec2(pos.x, pos.y+sin(pos.x*4.0+iGlobalTime*2.0)*0.04);
    vec4 mehupic = texture2D(iChannel0, wpos);
    /*if (mehupic.r < 0.1 && mehupic.b < 0.1)
        discard;*/
    vec3 col = vec3(1.0, 0.0, 0.0);
    float sh = clamp((sin((pos.x+pos.y*2.0)*10.0+iGlobalTime*14.0)*20.0-19.0)*clamp(sin((pos.x+pos.y*2.0)+iGlobalTime*1.4)*10.0-9.0, 0.0, 1.0), 0.0, 1.0);
    col.gb += sh;
    gl_FragColor = vec4(col*mehupic.r, mehupic.a);

    float colT = mehupic.b;
    gl_FragColor.rgb += colT * vec3(sin(4.0*pos.x+iGlobalTime*2.0+(PI/3.0))*0.5+0.5, sin(4.0*pos.x+iGlobalTime*2.0+((PI/3.0)*2.0))*0.5+0.5, sin(4.0*pos.x+iGlobalTime*2.0+PI)*0.5+0.5);
}
