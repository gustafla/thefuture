#ifndef P2_HPP
#define P2_HPP

#include "common.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_shader.hpp"
#include "gfx_model.hpp"
#include "gfx_postprocessor.hpp"
#include "mvp.hpp"
#include "effects/scroller.hpp"

#define CUBES_W 18
#define CUBES_H 14
#define CUBE_SCALE 0.3f

class P2 {
    public:
        P2(CommonData* icommon);
        ~P2();
        void draw(GLuint ifb);
    private:
        CommonData* common;
        GfxModel* objCube;
        MVP mvp;
        GLfloat cubes[CUBES_W][CUBES_H][6];
        GfxShader shader;
        GfxPostProcessor ed;
        float tlast;
        float ts;
        GLfloat colorsbase[CUBES_W][CUBES_H][3];
        GfxScreenMovable gree1;
        GfxScreenMovable gree2;
        GfxScreenMovable gree3;
        GfxScreenMovable gree4;
};

#endif
