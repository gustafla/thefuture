#ifdef GL_ES
    precision mediump float;
#endif

uniform vec3 iColor;

void main() {
    gl_FragColor = vec4(iColor, 1.0);
}
