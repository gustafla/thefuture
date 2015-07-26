#include "parts/1.hpp"
#include <cmath>
#include <cstdlib>
#include "util.hpp"
#include "draw_line.hpp"

P1::P1(CommonData* icommon):
common(icommon),
tlast(0.0f),
shader("shaders/mvp.vert", "shaders/color.frag"),
mvp(icommon->pProjMat40),
objCube(icommon->models->getModel("cube.obj")),
rb(icommon, "shaders/rb_post.frag"),
st(-1.0f),
mixer(icommon, "shaders/tmix.frag"),
test(icommon, "shaders/metaballs_new_var.frag", 0, 0, icommon->res[0], icommon->res[1], "", 4.0f) {
    glGenFramebuffers(1, &frameBuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    texture2 = new GfxTexture2D(NULL, icommon->res[0]/4, icommon->res[1]/4, GL_RGB, GL_NEAREST, GL_REPEAT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2->getHandle(), 0);
    glGenRenderbuffers(1, &renderBuffer2);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer2);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, icommon->res[0]/4, icommon->res[1]/4);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer2);
    mixer.takeTexture(texture2, "iChannel1");

    for (int i=0; i<N_CUBES; i++) {
        cube[i*6]   = ((float(rand()%20000)/10000.0f)-1.0f)*120.0f;
        cube[i*6+1] = ((float(rand()%20000)/10000.0f)-1.0f)*120.0f;
        cube[i*6+2] = ((float(rand()%20000)/10000.0f)-1.0f)*120.0f;
        cube[i*6+3] = (float(rand()%100)/100.0f)*M_PI*2.0f;
        cube[i*6+4] = (float(rand()%100)/100.0f)*M_PI*2.0f;
        cube[i*6+5] = (float(rand()%100)/100.0f)*M_PI*2.0f;
    }
}

P1::~P1() {
    delete texture2;
    glDeleteFramebuffers(1, &frameBuffer2);
    glDeleteRenderbuffers(1, &renderBuffer2);
}

void P1::draw(GLuint ifb) {
    if (st < -0.5f)
        st = common->t;
    float t = common->t - st;
    glViewport(0,0,common->res[0]/4, common->res[1]/4);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    test.draw();
    glViewport(0,0,common->res[0], common->res[1]);
    mixer.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    GLfloat color[4];
    color[0] = 0.2;
    color[1] = 0.06;
    color[2] = 0.8;
    color[3] = 0.2;
    glUniform4fv(shader.getUfmHandle("iColor"), 1, color);
    glDisable(GL_DEPTH_TEST);
    for(int i=0; i<N_CUBES; i++) {
        mvp.setModel(cube[i*6], cube[i*6+1], cube[i*6+2], cube[i*6+3], cube[i*6+4], cube[i*6+5], 1.7);
        mvp.setView(-100.0f+t*6.0f, 0.0f, sin(t*0.7f)*20.0f, sin(t*0.7)*0.3, t*0.3+M_PI, 0.0f);
        mvp.buildMVP();
        glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
        objCube->draw(&shader);
    }

    if (t > tlast+(1.0/common->BPS)) {
        for (int i=0; i<N_CUBES-1; i++) {
            if (rand()%40 < 6)
                lines[i]=true;
            else
                lines[i]=false;
        }
        tlast=common->t;
    }
    color[0] = 1.0;
    color[1] = 0.3;
    color[2] = 0.1;
    color[3] = 0.6;
    glUniform4fv(shader.getUfmHandle("iColor"), 1, color);
    mvp.setModel(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    mvp.buildMVP();
    glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
    for (int i=0; i<N_CUBES-1; i++) {
        if (lines[i])
            drawLine3D(&shader, cube[i*6], cube[i*6+1], cube[i*6+2], cube[i*6+6], cube[i*6+7], cube[i*6+8]);
    }
    glEnable(GL_DEPTH_TEST);

    rb.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mixer.getShader()->use();
    glUniform1f(mixer.getShader()->getUfmHandle("iRatio"), (sin(common->t-st*0.4)*0.1+0.1)+clamp(1.5-(common->t-st)*0.3, 0.0, 1.0));
    mixer.draw();

    glBindFramebuffer(GL_FRAMEBUFFER, ifb);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rb.draw();
}
