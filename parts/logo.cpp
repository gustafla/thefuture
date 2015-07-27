#include "parts/logo.hpp"
#include "draw_line.hpp"
#include <cmath>
#include <iostream>

PLogo::PLogo(CommonData* icommon):
common(icommon),
shader("shaders/simple.vert", "shaders/color.frag"),
shader2("shaders/mvp.vert", "shaders/color.frag"),
pp(icommon, "shaders/sradblur_gain.frag"),
objMehu(icommon->models->getModel("mehu.obj")),
scroller(icommon, "     A NEW RASPBERRY PI COMPOFILLER BY MEHU, YAY! CLUTCHED TOGETHER IN ONE WEEK... FOR ASSEMBLY!   IT'S TIME TO SEE THE 'NEW' FX!"),
mvp(icommon->pProjMat40) {
    shader.use();
    GLfloat color [4];
    color[0] = 0.3f;
    color[1] = 0.2f;
    color[2] = 0.6f;
    color[3] = 1.0f;
    glUniform4fv(shader.getUfmHandle("iColor"), 1, color);
    shader2.use();
    color[0] = 0.5f;
    color[1] = 0.01f;
    color[2] = 0.004f;
    color[3] = 1.0f;
    glUniform4fv(shader2.getUfmHandle("iColor"), 1, color);

    mvp.setViewTranslation(0.0, 0.0, -3.0);
}

void PLogo::draw(GLuint ifb) {
    pp.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    float dist = 0.13+sin(common->t*0.7)*0.02;
    float ar = (common->res[0]/common->res[1]);
    float r = sin(common->t*0.9)*0.1;
    for (float x = fmod(common->t*0.4, dist)-1.5f; x < 1.5f; x+=dist) {
        drawLine(&shader, x, -1.5f, x+r, 1.5f);
    }
    for (float y=fmod(common->t*0.2, dist*ar)-1.5f; y < 1.5f; y+=dist*ar) {
        drawLine(&shader, -1.5f, y, 1.5f, y-r*ar);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, ifb);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pp.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    shader2.use();
    mvp.setModel(0.0, 0.0, 0.0, 0.0, sin(common->t)*0.5, sin(common->t)*0.1, 1.0+common->beatHalfSine*0.2);
    mvp.buildMVP();
    glUniformMatrix4fv(shader2.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    objMehu->draw(&shader2);

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    scroller.draw();
    glEnable(GL_DEPTH_TEST);
}
