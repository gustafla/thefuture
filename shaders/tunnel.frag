#ifdef GL_ES
precision highp float;
#endif

uniform float iGlobalTime;
uniform vec2 iResolution;
varying vec2 texpos;

#define RADIUS 3.0
#define PI 3.14159265
#define EPSILON 0.001

#define t (iGlobalTime*6.0)

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

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

vec3 amigaTexture(vec2 pos, float n) {
    float l = clamp(sin(pos.x*n)*sin(pos.y*n)*10000.0, 0.0, 1.0);
    return vec3(1.0, 0.0, 0.0)*l+(vec3(1.0, 1.0, 1.0)*(1.0-l));
}

float getTunnelDist(vec3 origin, vec3 direction) {
    float a = direction.x*direction.x + direction.y*direction.y;
    float b = 2.0*(origin.x*direction.x + origin.y*direction.y);
    float c = origin.x*origin.x + origin.y*origin.y - RADIUS*RADIUS;
    float disc = b*b - 4.0*a*c;
    /*if (disc < 0.0)
        return 1000000.0;
    else if (disc < EPSILON)
        return -b/(2.0*a);
    else*/
        return /*min(*/(-b+sqrt(disc))/(2.0*a)/*, (-b-sqrt(disc))/(2.0*a))*/;
    //We're only interested in positive z intersections so this is OK, I guess.
}

float render(vec3 origin, vec3 direction) {
    return getTunnelDist(origin, direction);
}

vec3 scene(vec3 origin, vec3 direction, out vec3 normal, out vec2 uv) { //Does depth testing
    float tunnel = getTunnelDist(origin, direction);
    
    vec3 pos = origin + tunnel*direction;
    normal = normalize(vec3(vec2(0.0), pos.z)-pos);
    uv = vec2(atan(pos.y, pos.x), pos.z * 0.4);
    return pos;
}

void main() {
    vec2 screenPos = ((2.0*texpos*iResolution.xy - iResolution)/iResolution.y)/2.0;
    
    vec3 light1 = vec3(sin(t*0.2)*2.0,cos(t*0.2)*2.0,6.0+t*4.0-sin(t*0.2)*2.0);
    
    vec3 cam = vec3(sin(t*0.1), cos(t*0.04)*0.4, t*4.0);
    vec3 rayDir = getXRotMat(-cos(t*0.2)*0.1) * getYRotMat(-sin(t*0.1)*0.1) * normalize(vec3(screenPos, 1.0));
    
    vec3 normal;
    vec2 uv;
    vec3 pos = scene(cam, rayDir, normal, uv);

    vec3 shadowDir = normalize(light1-pos);
    vec3 shadowPos = pos + render(pos+shadowDir*EPSILON, shadowDir)*shadowDir;
    float shadow = 1.0;
    //if (length(shadowPos-pos)-EPSILON < length(light1-pos))
    //    shadow = 0.0;
    
    float light = (1./length(pos-light1))
        * max(dot(normal, -normalize(pos-light1)), 0.0);
    light *= shadow;

    gl_FragColor = vec4(light*amigaTexture(uv, 6.0), 1.0);
}
