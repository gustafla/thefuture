#ifndef TUNNEL_HPP
#define TUNNEL_HPP

#include "common.hpp"
#include "gfx_texture_2D.hpp"
#include "rpi_gfx.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_postprocessor.hpp"

class PTunnel {
    public:
        PTunnel(CommonData* icommon);
        ~PTunnel();
        void draw(GLuint ifb);
    private:
        CommonData* common;
        GfxScreenMovable tunnel;
        GLuint frameBuffer2;
        GLuint renderBuffer2;
        GfxTexture2D* texture2;
        GfxPostProcessor scaler;
};

#endif
