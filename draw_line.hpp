#ifndef DRAW_LINE_HPP
#define DRAW_LINE_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"

void drawLine(GfxShader* shader, float x1, float y1, float x2, float y2);
void drawLine3D(GfxShader* shader, float x1, float y1, float z1, float x2, float y2, float z2);

#endif
