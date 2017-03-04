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
uniform sampler2D iChannel0;

float fillCircle(vec2 pos, vec2 cPos, float r) {
    //pos.x -= ((iResolution.x-iResolution.y)/iResolution.y)/2.0;
    return pow(max(1.0 - length(pos - cPos), 0.0), r);
}

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.yy - vec2(0.5);
    pos.x -= ((iResolution.x-iResolution.y)/iResolution.y)/2.0;
    float pL  = 0.0;
    float pL2 = 0.0;
    float t = iGlobalTime;
    float te = t*0.42;
    float ts = t*t*t*0.001;
    pL  += fillCircle(pos, vec2(cos(t*0.015*te-0.28)*0.6, cos(t*0.014*te)*0.3), 8.0);
    pL2 += fillCircle(vec2(pos.x-0.01, pos.y), vec2(cos(t*0.015*te-0.28)*0.6, cos(t*0.014*te)*0.3), 8.0);
    pL  += fillCircle(pos, vec2(sin(t*0.012*te)*0.5, cos(t*0.017*te)*0.233), 7.0);
    pL2 += fillCircle(vec2(pos.x-0.01, pos.y), vec2(sin(t*0.012*te)*0.5, cos(t*0.017*te)*0.233), 7.0);
    pL  += fillCircle(pos, vec2(cos(t*0.0171*te+0.52)*0.4, sin(t*0.0144*te)*0.32), 8.0);
    pL2 += fillCircle(vec2(pos.x-0.01, pos.y), vec2(cos(t*0.0171*te+0.52)*0.4, sin(t*0.0144*te)*0.32), 8.0);
    pL  += fillCircle(pos, vec2(sin(t*0.0122*te-0.4)*0.6, sin(t*0.0164*te)*0.13), 9.0);
    pL2 += fillCircle(vec2(pos.x-0.01, pos.y), vec2(sin(t*0.0122*te-0.4)*0.6, sin(t*0.0164*te)*0.13), 9.0);
    //pL += fillCircle(vec2(cos(t*0.53)*0.47, sin(t)*0.724), 5.0);
    float tc = texture2D(iChannel0, pos*0.8).r * min((pL*ts)*0.15, 0.5);
    pL  = clamp((pL -0.5)*ts/*"sharpness"*/, 0.0, 1.0);
    pL2 = clamp((pL2-0.5)*ts/*"sharpness"*/, 0.0, 1.0);
    vec3 ballsfinal = vec3(pL, (pL+pL2)/2.0, pL2);
    gl_FragColor = vec4(ballsfinal+tc, 1.0);
}
