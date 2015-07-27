#ifndef TORUS_HPP
#define TORUS_HPP

#include "common.hpp"
#include "gfx_texture_2D.hpp"
#include "rpi_gfx.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_postprocessor.hpp"

class PTorus {
    public:
        PTorus(CommonData* icommon);
        ~PTorus();
        void draw(GLuint ifb);
    private:
        CommonData* common;
        GfxScreenMovable torus;
        GLuint frameBuffer2;
        GLuint renderBuffer2;
        GfxTexture2D* texture2;
        GfxPostProcessor rb;
};

#endif
