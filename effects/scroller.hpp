#ifndef SCROLLER_HPP
#define SCROLLER_HPP

#include <vector>
#include "common.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_shader.hpp"
#include <string>
#include "gfx_model.hpp"
#include "mvp.hpp"

class Scroller {
    public:
        Scroller(CommonData* icommon, std::string itext, std::string fontname="graphics/fontti1");
        void draw();
    private:
        CommonData* common;
        GfxTexture2D* font[26+1+1+1+1+1];
        std::string text;
        GfxModel* objScreen;
        GfxShader shader;
        MVP mvp;
        float length;
};

#endif
