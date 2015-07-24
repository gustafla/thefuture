// Copyright 2015 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "demo_thread.hpp"
#include "config.hpp"
#include "gfx_EGL_window.hpp"
#include <cstdlib>
#include "rpi_gfx.hpp"
#include "common.hpp"
#include <pthread.h>
#include "wav_player.hpp"
#include "audio_thread.hpp"
#include "gfx_postprocessor.hpp"
#include <cmath>
#include "gfx_noise_texture.hpp"
#include <iostream>

#include "fade.hpp"
#include "demo_timing.hpp"

#include "parts/starfield.hpp"
#include "parts/intro.hpp"
#include "parts/flag.hpp"
#include "parts/plasma_bars.hpp"
#include "parts/cube.hpp"

void alt_main(int argc, char* argv[]) {
    Config c(argc, argv);
    check("Creating a window");
    //Create a window
    GfxEGLWindow window(&c);
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);

    check("Setting clear color");
    //Set the clear color
    glClearColor(1.0, 0.0, 0.0, 1.0);

    //Enable blending
    check("Enable blending");
    glEnable(GL_BLEND);
    check("Set blend func");
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    //Enable depth testing (why isn't this on by default?)
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);

    //Set a viewport
    check("Set viewport");
    glViewport(0, 0, c.w, c.h);

    check("create common");
    //Common data. Will be important when there are many effects/scenes in different (their own) objects
    CommonData common(c.w, c.h);
    check("Create shader");
    GfxShader shader("shaders/simple_new.vert", "shaders/realplasma.frag");
    check("Use shader");
    shader.use();
    check("Set iResolution uniform");
    glUniform2fv(shader.getUfmHandle("iResolution"), 1, common.res);
    
    //Timer stuff
    struct timeval tTmp;
    struct timeval startT;

    float t=0.0;

    gettimeofday(&tTmp, NULL);
    gettimeofday(&startT, NULL);

    for (;;)
    {
        //Check() checks that our fragile GL isn't seeing anything wrong going on
        check("Timers set. Now entered the main loop");

        //Update timer for the frame
        gettimeofday(&tTmp, NULL);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        common.t = t;
        check("Set iGlobalTime");
        glUniform1fv(shader.getUfmHandle("iGlobalTime"), 1, &common.t);
        check("Bind FB 0");
        gfxBindFB0();
        check("Use shader");
        shader.use();
        check("draw screen.obj model with the thing");
        common.models->getModel("screen.obj")->draw(&shader);
        check("Swap buffers");
        window.swapBuffers();
        check("Clear buffers");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
