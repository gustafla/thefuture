#ifdef GL_ES
    precision mediump float;
#endif

uniform vec4 iColor;

void main() {
    gl_FragColor = iColor;
}
