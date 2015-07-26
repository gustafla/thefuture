#ifdef GL_ES
precision highp float;
#endif

varying vec2 texpos;
uniform float iRatio;

uniform sampler2D iChannel0;
uniform sampler2D iChannel1;

void main() {
    gl_FragColor = vec4(mix(texture2D(iChannel0, texpos).rgb, texture2D(iChannel1, texpos).rgb, iRatio), 1.0);
}
