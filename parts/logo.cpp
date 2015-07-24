#include "parts/logo.hpp"
#include "draw_line.hpp"
#include <cmath>

PLogo::PLogo(CommonData* icommon):
common(icommon),
shader("shaders/simple.vert", "shaders/color.frag"),
shader2("shaders/mvp.vert", "shaders/color.frag"),
objMehu(icommon->models->getModel("mehu.obj")),
scroller(icommon, "TEST TEST TEST TEST ......"),
mvp(icommon->pProjMat40) {
    shader.use();
    GLfloat color [3];
    color[0] = 0.0f;
    color[1] = 0.1f;
    color[2] = 1.0f;
    glUniform3fv(shader.getUfmHandle("iColor"), 1, color);
    shader2.use();
    color[0] = 1.0f;
    color[1] = 0.01f;
    color[2] = 0.0f;
    glUniform3fv(shader2.getUfmHandle("iColor"), 1, color);

    mvp.setViewTranslation(0.0, 0.0, -3.0);
}

void PLogo::draw() {
    float dist = 0.13+sin(common->t*0.7)*0.02;
    float ar = (common->res[0]/common->res[1]);
    float r = sin(common->t*0.9)*0.1;
    for (float x = fmod(common->t*0.4, dist)-1.5f; x < 1.5f; x+=dist) {
        drawLine(&shader, x, -1.5f, x+r, 1.5f);
    }
    for (float y=fmod(common->t*0.2, dist*ar)-1.5f; y < 1.5f; y+=dist*ar) {
        drawLine(&shader, -1.5f, y, 1.5f, y-r*ar);
    }

    glClear(GL_DEPTH_BUFFER_BIT);

    shader2.use();
    mvp.setModel(0.0, 0.0, 0.0, 0.0, sin(common->t)*0.5, sin(common->t)*0.1);
    mvp.buildMVP();
    glUniformMatrix4fv(shader2.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    objMehu->draw(&shader2);

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    scroller.draw();
    glEnable(GL_DEPTH_TEST);
}
