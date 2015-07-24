#include "scroller.hpp"
#include <cmath>

#define C_DIST 0.11f
#define C_SCALE 0.08f

Scroller::Scroller(CommonData* icommon, std::string itext, std::string fontname):
text(itext),
common(icommon),
mvp(common->pProjMat40),
objScreen(common->models->getModel("screen.obj")),
shader("shaders/mvptex.vert", "shaders/tcolor.frag") {
    mvp.setViewTranslation(0.0, 0.0, -1.0);
    std::string b = fontname;
    b += "/";
    std::string f;
    f = b + "A.tga";
    font[0] = new GfxTexture2D(f);
    f = b + "B.tga";
    font[1] = new GfxTexture2D(f);
    f = b + "C.tga";
    font[2] = new GfxTexture2D(f);
    f = b + "D.tga";
    font[3] = new GfxTexture2D(f);
    f = b + "E.tga";
    font[4] = new GfxTexture2D(f);
    f = b + "F.tga";
    font[5] = new GfxTexture2D(f);
    f = b + "G.tga";
    font[6] = new GfxTexture2D(f);
    f = b + "H.tga";
    font[7] = new GfxTexture2D(f);
    f = b + "I.tga";
    font[8] = new GfxTexture2D(f);
    f = b + "J.tga";
    font[9] = new GfxTexture2D(f);
    f = b + "K.tga";
    font[10] = new GfxTexture2D(f);
    f = b + "L.tga";
    font[11] = new GfxTexture2D(f);
    f = b + "M.tga";
    font[12] = new GfxTexture2D(f);
    f = b + "N.tga";
    font[13] = new GfxTexture2D(f);
    f = b + "O.tga";
    font[14] = new GfxTexture2D(f);
    f = b + "P.tga";
    font[15] = new GfxTexture2D(f);
    f = b + "Q.tga";
    font[16] = new GfxTexture2D(f);
    f = b + "R.tga";
    font[17] = new GfxTexture2D(f);
    f = b + "S.tga";
    font[18] = new GfxTexture2D(f);
    f = b + "T.tga";
    font[19] = new GfxTexture2D(f);
    f = b + "U.tga";
    font[20] = new GfxTexture2D(f);
    f = b + "V.tga";
    font[21] = new GfxTexture2D(f);
    f = b + "W.tga";
    font[22] = new GfxTexture2D(f);
    f = b + "X.tga";
    font[23] = new GfxTexture2D(f);
    f = b + "Y.tga";
    font[24] = new GfxTexture2D(f);
    f = b + "Z.tga";
    font[25] = new GfxTexture2D(f);
    f = b + "dot.tga";
    font[26] = new GfxTexture2D(f);
    f = b + "comma.tga";
    font[27] = new GfxTexture2D(f);
    f = b + "apostrophe.tga";
    font[28] = new GfxTexture2D(f);
    f = b + "exclamation.tga";
    font[29] = new GfxTexture2D(f);
    f = b + "question.tga";
    font[30] = new GfxTexture2D(f);

    mvp.setModelScale(C_SCALE);
    length = text.length()*C_DIST;

    shader.use();
    glUniform1i(shader.getUfmHandle("iChannel0"), 0);
    glUniform2fv(shader.getUfmHandle("iResolution"), 1, common->res);
}

void Scroller::draw() {
    shader.use();
    glUniform1f(shader.getUfmHandle("iGlobalTime"), common->t);
    for(int i=0; i<text.length(); i++) {
        if (text.c_str()[i] == ' ')
            continue;

        switch (text.c_str()[i]) {
            case 'A':
                font[0]->bindToUnit(0);
                break;
            case 'B':
                font[1]->bindToUnit(0);
                break;
            case 'C':
                font[2]->bindToUnit(0);
                break;
            case 'D':
                font[3]->bindToUnit(0);
                break;
            case 'E':
                font[4]->bindToUnit(0);
                break;
            case 'F':
                font[5]->bindToUnit(0);
                break;
            case 'G':
                font[6]->bindToUnit(0);
                break;
            case 'H':
                font[7]->bindToUnit(0);
                break;
            case 'I':
                font[8]->bindToUnit(0);
                break;
            case 'J':
                font[9]->bindToUnit(0);
                break;
            case 'K':
                font[10]->bindToUnit(0);
                break;
            case 'L':
                font[11]->bindToUnit(0);
                break;
            case 'M':
                font[12]->bindToUnit(0);
                break;
            case 'N':
                font[13]->bindToUnit(0);
                break;
            case 'O':
                font[14]->bindToUnit(0);
                break;
            case 'P':
                font[15]->bindToUnit(0);
                break;
            case 'Q':
                font[16]->bindToUnit(0);
                break;
            case 'R':
                font[17]->bindToUnit(0);
                break;
            case 'S':
                font[18]->bindToUnit(0);
                break;
            case 'T':
                font[19]->bindToUnit(0);
                break;
            case 'U':
                font[20]->bindToUnit(0);
                break;
            case 'V':
                font[21]->bindToUnit(0);
                break;
            case 'W':
                font[22]->bindToUnit(0);
                break;
            case 'X':
                font[23]->bindToUnit(0);
                break;
            case 'Y':
                font[24]->bindToUnit(0);
                break;
            case 'Z':
                font[25]->bindToUnit(0);
                break;
            case '.':
                font[26]->bindToUnit(0);
                break;
            case ',':
                font[27]->bindToUnit(0);
                break;
            case '\'':
                font[28]->bindToUnit(0);
                break;
            case '!':
                font[29]->bindToUnit(0);
                break;
            case '?':
                font[30]->bindToUnit(0);
                break;
        }
        //mvp.setModelTranslation(sin(i*C_DIST*6.0-common->t*3.0)*0.12-0.45, fmod((1.0f+length)-i*C_DIST+common->t*0.3f, 1.0f+length)-length);
        float x = 1.0-common->t*0.3+i*C_DIST;
        mvp.setModel(x, sin(x)*0.2, 0.0f, x, x*2.0, x*0.7, C_SCALE+sin(x*15.0)*0.017+0.017);
        //mvp.buildModel();
        mvp.buildMVP();
        glUniformMatrix4fv(shader.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
        objScreen->draw(&shader);
    }
}
