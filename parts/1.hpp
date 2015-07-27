#ifndef P1_HPP
#define P1_HPP

#include "common.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_shader.hpp"
#include "gfx_model.hpp"
#include "gfx_postprocessor.hpp"
#include "mvp.hpp"
#include "effects/scroller.hpp"

//#define N_CUBES 300
#define N_CUBES 200

class P1 {
    public:
        P1(CommonData* icommon);
        ~P1();
        void draw(GLuint ifb);
    private:
        CommonData* common;
        GfxScreenMovable test;
        GfxPostProcessor mixer;
        GfxPostProcessor rb;

        GLuint frameBuffer2;
        GLuint renderBuffer2;
        GfxTexture2D* texture2;

        float st;

        GfxModel* objCube;
        GLfloat cube[N_CUBES*6];
        GfxShader shader;
        MVP mvp;

        float tlast;
        bool lines[N_CUBES-1];

        GfxTexture2D skybox;
        GfxShader shader2;
};

#endif
