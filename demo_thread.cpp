// Copyright 2015 Lauri Gustafsson
/*
This file is part of Low Quality is the Future.

    Low Quality is the Future is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Low Quality is the Future is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Low Quality is the Future, see COPYING. If not, see <http://www.gnu.org/licenses/>.
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

#include "parts/logo.hpp"
/*
 * Demo player thread function
 */
void* playDemo(void* arg) {
    //Get parameters
    DemoArg* args = (DemoArg*)arg;
    int argc = args->argc;
    char** argv = args->argv;
    Config c(argc, argv);
    //Create a window
    GfxEGLWindow window(&c, "Low Quality is the Future");
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);

    //Set the clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE); //don't need this

    //Set a viewport
    glViewport(0, 0, c.w, c.h);

    check();

    //Initialize cstdlib random seed
    srand(4);

    //GfxNoiseTexture mainNoise(48, 48);

    //Common data. Will be important when there are many effects/scenes in different (their own) objects
    CommonData common(c.w, c.h);
    
    //Display the stupid loading screen
    GfxScreen* loading = new GfxScreen(&common, "shaders/showtex.frag", "graphics/loading.tga");
    gfxBindFB0();
    loading->draw();
    delete loading;
    window.swapBuffers();
    
    GfxPostProcessor pp(&common, "shaders/coolpp.frag");
    bool doPP = false;

    //demo parts
    PLogo p0(&common);
    Fade*      fade;
    
    //Start the music player thread
    WavPlayer* music = NULL;
    if (c.audio) {
        float startAt=0.0;
        for (unsigned int partTi = 0; partTi < c.partStart; partTi++) {
            startAt += PART_TIMES[partTi]; //Skip music to the '-p' start time too
        }
        //startAt -= PART_TIMES[c.partStart]; //Back to the beginning of the first shown part
        music = new WavPlayer("music.wav", startAt, 8192);
        pthread_t audioThread;
        pthread_create(&audioThread, NULL, playMusic, (void*)music);
    }
    
	int    part = c.partStart;
	float  tPartStart  = 0.0;
	float  tLoopStart  = 0.0;

    //Timer stuff
    struct timeval tTmp;
    struct timeval startT;
    struct timezone tz;
    float fpsLastT = 0.0f;
    unsigned int frames = 0;
    float t=0.0;
    float tlast=0.0;
    float tMusicEOF = -1.0;

    gettimeofday(&tTmp, &tz);
    gettimeofday(&startT, &tz);

    for (;;)
    {
        //Check() checks that our fragile GL isn't seeing anything wrong going on
        check();

        //Update timer for the frame
        gettimeofday(&tTmp, &tz);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        common.deltat = t-tlast;
        tlast = t;
        common.t = (t-tLoopStart);
        //and a rythmic pulse
        common.beatHalfSine = std::abs(sin(t*M_PI*common.BPS)); //Wow, conflicting defs of abs()!

        if (doPP) {
            pp.bindFramebuffer();
        } else
            gfxBindFB0();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        switch (part) { //Demo in a switch :)
			case 0: //INTRO
                doPP = true;
				p0.draw();
				/*if (t-tLoopStart > tPartStart+PART_TIMES[part]){ //30.0
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_BLACK_OUT_GLITCHED);
                    partIntro.draw(fade); //Hackish... But works :/
					part++;
					tPartStart = t-tLoopStart;
                    doPP = false;
                    gfxBindFB0();
				}*/
				break;
			default:
                if (c.audio)
                    exit(0);
				part = 0; //0?
				tLoopStart = t;
                for (unsigned int partTi = 0; partTi < 2; partTi++) {
                    tLoopStart -= PART_TIMES[partTi]; //Adjust correct part timing. Hacky, but not needed often
                }
				tPartStart = t-tLoopStart;
                doPP = true; //false?
				break;
		}

        if (doPP) {
            gfxBindFB0();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            pp.draw();
        }

        window.swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (c.audio) {
            if (tMusicEOF == -1.0 && music->done()) {
                tMusicEOF = t;
            }
            
            if (tMusicEOF != -1.0 && t >= (tMusicEOF+5.0)) {
                break;
            }
        }
            
        //FPS counter "magic"
        if (c.fpsCounter) {
            frames++;
            if (frames > c.fpsIn)
            {
                std::cout << "FPS=" << (c.fpsIn / (t - fpsLastT)) << std::endl;
                fpsLastT = t;
                frames = 0;
            }
        }
        usleep(5000); //Horrible fix to priorize the audio thread.
        if (window.shouldKill())
            exit(0);
    }
    exit(0);
}
