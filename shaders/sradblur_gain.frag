#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform float iGlobalTime;
varying vec2 texpos;

void main() {
    vec2 center = vec2(0.5);
    vec2 pos = texpos-center;
    vec3 sum;
    for (int i=0; i<4; i++) {
        float x = 1.0+(float(i)/100.0);
        sum += (texture2D(iChannel0, (pos/x)+center).rgb-length(pos)*0.3)*(1.0/(float(i)*0.9+1.0))*3.0;
    }

    gl_FragColor = vec4(min(sum, 1.0)*0.4, 1.0);
}
