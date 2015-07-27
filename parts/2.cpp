#include "parts/2.hpp"
#include <cmath>
#include <cstdlib>
#include "util.hpp"
#include "draw_line.hpp"

P2::P2(CommonData* icommon):
common(icommon),
gree1(icommon, "shaders/showtex_var_a.frag", 0, 0, icommon->res[0], icommon->res[1], "graphics/gree1.tga"),
gree2(icommon, "shaders/showtex_var_a.frag", 0, 0, icommon->res[0], icommon->res[1], "graphics/gree2.tga"),
gree3(icommon, "shaders/showtex_var_a.frag", 0, 0, icommon->res[0], icommon->res[1], "graphics/gree3.tga"),
gree4(icommon, "shaders/showtex_var_a.frag", 0, 0, icommon->res[0], icommon->res[1], "graphics/gree4.tga"),
tlast(-10.0f),
ts(-1.0f),
objCube(icommon->models->getModel("cube.obj")),
shader("shaders/mvp.vert", "shaders/color.frag"),
ed(icommon, "shaders/edcolor_post.frag"),
mvp(common->pProjMat40) {
    for (int x=0; x<CUBES_W; x++) {
        for (int y=0; y<CUBES_H; y++) {
            cubes[x][y][0] = float(x-(CUBES_W/2))*CUBE_SCALE*2.0f;
            cubes[x][y][1] = (float(rand()%1000)/500.0f)-1.0f;
            cubes[x][y][2] = float(y)*CUBE_SCALE*2.0f;
            colorsbase[x][y][0] = 0.0f;
            cubes[x][y][3] = colorsbase[x][y][0] + ((rand()%500<10) ? 0.6f:0.0f);
            colorsbase[x][y][1] = float(rand()%100)/10000.0f;
            cubes[x][y][4] = colorsbase[x][y][1] + ((rand()%500<10) ? 0.6f:0.0f);
            colorsbase[x][y][2] = float(rand()%100)/1000.0f;
            cubes[x][y][5] = colorsbase[x][y][2] + ((rand()%500<10) ? 0.6f:0.0f);
        }
    }
    mvp.setView(0.0f, -4.5f, -4.0f, -0.9f, 0.0f, 0.0f);
}

P2::~P2() {

}

void P2::draw(GLuint ifb) {
    if (ts < -0.5f)
        ts = common->t;
    float t = common->t - ts;

    ed.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float beat = clamp(1.0-fmod((common->t)*2.0f, (1/common->BPS)*2.0f), 0.0f, 1.0f);

    if (common->t > tlast+(2.0/common->BPS)) {
        for (int x=0; x<CUBES_W; x++) {
            for (int y=0; y<CUBES_H; y++) {
                //cubes[x][y][1] = (float(rand()%1000)/500.0f)-1.0f;
                cubes[x][y][3] = colorsbase[x][y][0] + ((rand()%500<10) ? 0.6f:0.0f);
                cubes[x][y][4] = colorsbase[x][y][1] + ((rand()%500<10) ? 0.6f:0.0f);
                cubes[x][y][5] = colorsbase[x][y][2] + ((rand()%500<10) ? 0.6f:0.0f);
            }
        }
        tlast = common->t;
    }

    GLfloat color[4];
    shader.use();
    for (int x=0; x<CUBES_W; x++) {
        for (int y=0; y<CUBES_H; y++) {
            mvp.setModel(cubes[x][y][0], cubes[x][y][1]*(1.0f-common->beatHalfSine)*0.4f, fmod(cubes[x][y][2]+common->t*4.0, float(CUBES_H)*CUBE_SCALE*2.0f)-(float(CUBES_H)*CUBE_SCALE*2.0f)/2.0f, 0.0f, 0.0f, 0.0f, CUBE_SCALE);
            color[0] = cubes[x][y][3];
            color[1] = cubes[x][y][4];
            color[2] = cubes[x][y][5];
            color[3] = 1.0f;
            glUniform4fv(shader.getUfmHandle("iColor"), 1, color);
            mvp.buildMVP();
            glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
            objCube->draw(&shader);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, ifb);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ed.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    if (t > 9.0f) {
        gree4.getShader()->use();
        glUniform1f(gree4.getShader()->getUfmHandle("iAlpha"), 10.8f*0.8f-t*0.8f);
        gree4.draw();
    }
    else if (t > 7.0f) {
        gree3.getShader()->use();
        glUniform1f(gree3.getShader()->getUfmHandle("iAlpha"), 8.8f*0.8f-t*0.8f);
        gree3.draw();
    }
    else if (t > 5.0f) {
        gree2.getShader()->use();
        glUniform1f(gree2.getShader()->getUfmHandle("iAlpha"), 6.8f*0.8f-t*0.8f);
        gree2.draw();
    }
    else if (t > 3.0f) {
        gree1.getShader()->use();
        glUniform1f(gree1.getShader()->getUfmHandle("iAlpha"), 4.8f*0.8f-t*0.8f);
        gree1.draw();
    }
}
