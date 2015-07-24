#ifndef LOGO_HPP
#define LOGO_HPP

#include "common.hpp"
#include "gfx_screen.hpp"
#include "gfx_shader.hpp"
#include "gfx_model.hpp"
#include "mvp.hpp"
#include "effects/scroller.hpp"

class PLogo {
    public:
        PLogo(CommonData* icommon);
        void draw();
    private:
        CommonData* common;
        GfxShader shader;
        GfxShader shader2;
        GfxModel* objMehu;
        MVP mvp;
        Scroller scroller;
};

#endif
