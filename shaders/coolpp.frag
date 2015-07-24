#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform float iGlobalTime;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 center = vec2(0.5);
    vec2 pos = gl_FragCoord.xy/iResolution.xy-center;
    vec3 sum;
    for (int i=0; i<8; i++) {
        float x = 1.0+(float(i)/80.0);
        sum += texture2D(iChannel0, (pos/x)+center).rgb*(1.0/(float(i)*0.9+1.0));
    }
    sum /= 1.5;

    sum.r+=rand(pos+mod(iGlobalTime, 1.0)+0.2)*0.1;
    sum.g+=rand(pos*mod(0.7+iGlobalTime, 1.0)+0.2)*0.1;
    sum.b+=rand(pos*mod(0.5+iGlobalTime, 1.0)+0.2)*0.1;

    sum.b *= (mod(gl_FragCoord.y, 2.0));

    sum -= max(length(pos)*0.07, 0.0);
    
    gl_FragColor = vec4(sum, 1.0);
}
