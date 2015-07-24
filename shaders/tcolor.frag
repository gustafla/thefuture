varying vec2 texpos;
uniform float iGlobalTime;
uniform sampler2D iChannel0;
uniform vec2 iResolution;

vec3 tex(vec2 pos) {
    vec3 c1 = vec3(0.1, 0.2, 1.0);
    vec3 c2 = vec3(0.1, 1.0, 0.1);
    float a = sin(pos.y*16.0+iGlobalTime)*0.5+0.5;
    vec3 c = c1*a+c2*(1.0-a);
    return c;
}

void main() {
    vec4 f = texture2D(iChannel0, texpos);
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    gl_FragColor = vec4(f.r*tex(pos), f.a);
}
