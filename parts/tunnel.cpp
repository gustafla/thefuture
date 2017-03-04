#include "parts/tunnel.hpp"

#define FBC 4

PTunnel::PTunnel(CommonData* icommon):
tunnel(icommon, "shaders/tunnel.frag", 0, 0, icommon->res[0], icommon->res[1], "", FBC),
scaler(icommon, "shaders/showtex_var.frag"),
common(icommon) {
    glGenFramebuffers(1, &frameBuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    texture2 = new GfxTexture2D(NULL, icommon->res[0]/FBC, icommon->res[1]/FBC, GL_RGB, GL_NEAREST, GL_REPEAT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2->getHandle(), 0);
    glGenRenderbuffers(1, &renderBuffer2);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer2);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, icommon->res[0]/FBC, icommon->res[1]/FBC);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer2);
    scaler.takeTexture(texture2, "iChannel0");
}

PTunnel::~PTunnel() {
    delete texture2;
    glDeleteFramebuffers(1, &frameBuffer2);
    glDeleteRenderbuffers(1, &renderBuffer2);
}

void PTunnel::draw(GLuint ifb) {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, common->res[0]/FBC, common->res[1]/FBC);
    tunnel.draw();
    glViewport(0, 0, common->res[0], common->res[1]);

    glBindFramebuffer(GL_FRAMEBUFFER, ifb);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scaler.draw();
}
