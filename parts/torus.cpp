#include "parts/torus.hpp"

PTorus::PTorus(CommonData* icommon):
torus(icommon, "shaders/torus.frag", 0, 0, icommon->res[0], icommon->res[1], "", 8),
rb(icommon, "shaders/rb_post.frag"),
common(icommon) {
    glGenFramebuffers(1, &frameBuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    texture2 = new GfxTexture2D(NULL, icommon->res[0]/8, icommon->res[1]/8, GL_RGB, GL_NEAREST, GL_REPEAT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2->getHandle(), 0);
    glGenRenderbuffers(1, &renderBuffer2);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer2);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, icommon->res[0]/8, icommon->res[1]/8);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer2);
    rb.takeTexture(texture2, "iChannel0");
}

PTorus::~PTorus() {
    delete texture2;
    glDeleteFramebuffers(1, &frameBuffer2);
    glDeleteRenderbuffers(1, &renderBuffer2);
}

void PTorus::draw(GLuint ifb) {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, common->res[0]/8, common->res[1]/8);
    torus.draw();
    glViewport(0, 0, common->res[0], common->res[1]);

    glBindFramebuffer(GL_FRAMEBUFFER, ifb);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rb.draw();
}
