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
uniform sampler2D iChannel0;
varying vec2 texpos;
/*
void main() {
    //float mov = sin(texpos.x*40.0-iGlobalTime*2.0)*0.5+0.5;
    float alpha = texture2D(iChannel0, vec2(texpos.x, texpos.y)).r;
    vec3 col = vec3(sin(texpos.x*20.0+iGlobalTime), sin(texpos.x*20.0+iGlobalTime*1.5), sin(texpos.x*20.0+iGlobalTime*0.5))*0.5+0.5;
    gl_FragColor = vec4(col, alpha);
}
*/

#define PI2 6.2831853

vec3 rainbow(float x)
{
    return vec3(
        sin(x+0.333*PI2)*0.5+0.5,
        sin(x+0.666*PI2)*0.5+0.5,
        sin(x)*0.5+0.5
    );
}

void main() {
    float alpha = texture2D(iChannel0, texpos).r;
    vec3 col = rainbow(texpos.x*10.0-iGlobalTime);
    gl_FragColor = vec4(col, alpha);
}
