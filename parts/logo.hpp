#ifndef LOGO_HPP
#define LOGO_HPP

#include "common.hpp"
#include "gfx_screen.hpp"
#include "gfx_postprocessor.hpp"
#include "gfx_shader.hpp"
#include "gfx_model.hpp"
#include "mvp.hpp"
#include "effects/scroller.hpp"
#include "effects/particle_burst.hpp"

class PLogo {
    public:
        PLogo(CommonData* icommon);
        void draw(GLuint ifb);
    private:
        CommonData* common;
        GfxShader shader;
        GfxShader shader2;
        GfxPostProcessor pp;
        GfxModel* objMehu;
        MVP mvp;
        Scroller scroller;
};

#endif
