uniform vec2 iResolution;
uniform float iGlobalTime;
varying vec2 texpos;

#define EPSILON 0.001
#define MAX_MARCH_LENGTH 30.0
#define ITR 8

mat3 getXRotMat(float a) {
    return mat3(
         1.0,  0.0,     0.0,
         0.0,  cos(a), -sin(a),
         0.0,  sin(a),  cos(a)
    );
}

mat3 getYRotMat(float a) {
    return mat3(
         cos(a),  0.0,  sin(a),
         0.0,     1.0,  0.0,
        -sin(a),  0.0,  cos(a)
    );
}

mat3 getZRotMat(float a) {
    return mat3(
         cos(a), -sin(a),  0.0,
         sin(a),  cos(a),  0.0,
         0.0,     0.0,     1.0
    );
}

float torus(vec3 pos, vec2 t) {
    vec2 q = vec2(length(pos.xz)-t.x, pos.y);
    return length(q)-t.y;
}

float scene(vec3 pos) {
    return torus(getXRotMat(iGlobalTime*1.4)*getZRotMat(iGlobalTime*1.6)*pos, vec2(2.0, 0.8));
}

vec3 march(vec3 origin, vec3 direction) {
    float t;
    float dist;
    for (int i=0; i<ITR; i++) {
        dist = scene(origin+direction*t);
        t += dist;
    }
    return origin + direction*t;
}

vec3 grad(vec3 p) {
    vec2 e = vec2(EPSILON, 0.0);
    return (vec3(scene(p+e.xyy), scene(p+e.yxy), scene(p+e.yyx)) - scene(p)) / e.x;
}

float render(vec2 screenPos) {
    vec3 cam = vec3(0.0, 0.0, -4.0);
    vec3 dir = normalize(vec3(screenPos, 1.0));
    vec3 pos = march(cam, dir);
    vec3 normal = normalize(grad(pos));
    float diffuse = max(dot(-normal, normalize(pos-cam)), 0.0);
    return (1.0/length(pos-cam))*diffuse*(pow(diffuse, 20.0)+1.0);
}

void main() {
    vec2 screenPos = (2.0*iResolution*texpos - iResolution)/iResolution.y;
    //vec2 screenPos = (2.0*gl_FragCoord.xy - iResolution.xy)/iResolution.y;
    gl_FragColor = vec4(vec3(render(screenPos)), 1.0);
}
