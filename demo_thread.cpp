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

#include "parts/starfield.hpp"
#include "parts/intro.hpp"
#include "parts/flag.hpp"
#include "parts/plasma_bars.hpp"
#include "parts/cube.hpp"
#include "parts/feedback_effect.hpp"
#include "parts/texobj.hpp"
#include "parts/texobj_ed.hpp"
#include "parts/vertices.hpp"
#include "parts/tunnel1.hpp"
#include "parts/amiga.hpp"

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

    //Enable depth testing (why isn't this on by default?)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE); //We don't need this

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
    
    GfxTexture2D     rgbfiltert("graphics/rgbfilter.tga");
    GfxPostProcessor crt(&common, "shaders/crt.frag", GL_NEAREST);
    GfxPostProcessor blur(&common, "shaders/fastblur.frag", GL_LINEAR, 4.0);
    blur.takeTexture(crt.getTexture(), "frameIn");
    crt.takeTexture(blur.getTexture(), "blurFrame");
    //crt.takeTexture(&crtTex, "rgbfilter");
    //GfxPostProcessor scaler(&common, "shaders/2x.frag", GL_NEAREST, 0.5);
    bool doPP = false;

    //demo parts :D
    PIntro          partIntro(&common);
    PStarfield      partStarfield(&common);
	PFlag           partFlag(&common);
    /*EPointModel     partPointCube(&common, "cube.obj", 0.7);
    EPointModel     partPointIcos(&common, "icos.obj");
    EPointModel     partPointTorus(&common, "htorus_sd.obj");*/
    PVertices       partCubes(&common);
    //PCube           partT1(&common);
    //PFeedbackEffect partT2(&common);
    //PTexobj         partT3(&common);
    //PTexobjED       partED(&common);
    PTunnel1        partTunnel1(&common);
    PAmiga          partAmiga(&common);
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
            crt.bindFramebuffer(); //drawing to the "root" PP
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        switch (part) { //Demo in a switch :)
			case 0: //INTRO
                doPP = false;
				partIntro.draw();
				if (t-tLoopStart > tPartStart+PART_TIMES[part]){ //30.0
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_BLACK_OUT_GLITCHED);
                    partIntro.draw(fade); //Hackish... But works :/
					part++;
					tPartStart = t-tLoopStart;
                    doPP = false;
                    gfxBindFB0();
				}
				break;
            case 1: //GLITCHY INTRO FADE
                doPP = false;
				fade->draw();
				if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;
					part++;
					tPartStart = t-tLoopStart;
                    
				}
				break;
			case 2: //STARFIELD WITH SCROLLER
                doPP = true;
				partStarfield.draw();
				if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    fade = new Fade(&common, PART_TIMES[part+1]);
                    fade->bindFramebuffer();
                    partStarfield.draw();
					part++;
					tPartStart = t-tLoopStart;
                    partStarfield.resetTimer();
				}
				break;
            case 3: //STARFIELD TO FLAG FADE
                doPP = true;
                fade->draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_BLACK_IN);
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 4: //FADE TO FLAG IN
                doPP = true;
                fade->bindFramebuffer();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                partFlag.draw();
                crt.bindFramebuffer();
                fade->draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 5: //FLAG
                doPP = true;
                partFlag.draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_WHITE_OUT); //IMPORTANT
                    fade->bindFramebuffer();
                    partFlag.draw();
                    partFlag.resetTimer();
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 6: //POINTS FADE OUT TO WHITE
                doPP = true;
                fade->draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;                    
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_WHITE_IN);
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 7: //CUBES FADE IN FROM WHITE
                doPP = true;
                fade->bindFramebuffer();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                partCubes.draw();
                crt.bindFramebuffer();
                fade->draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;
                    //fade = new Fade(&common, PART_TIMES[part+1], FADE_WITE_IN);
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 8: //CUBES
                doPP = true;
                partCubes.draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    partCubes.resetTimer();
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 9: //TUNNEL WITH TWISTER
                doPP = true;
                partTunnel1.draw(/*&crt*/);
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    partTunnel1.resetTimer();
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 10: //"AMIGA" (maybe :DD)
                doPP = true;
                partAmiga.draw(/*&crt*/);
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    fade = new Fade(&common, PART_TIMES[part+1], FADE_BLACK_OUT_GLITCHED);
                    fade->bindFramebuffer();
                    partAmiga.draw(); //Hackish... But works :/
                    partAmiga.resetTimer();
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
            case 11: //FADE OUT
                doPP = true;
                fade->draw();
                if (t-tLoopStart > tPartStart+PART_TIMES[part]){
                    delete fade;                    
                    //fade = new Fade(&common, PART_TIMES[part+1], FADE_WHITE_IN);
					part++;
					tPartStart = t-tLoopStart;
				}
                break;
			default:
                if (c.audio)
                    exit(0);
				part = 2; //0?
				tLoopStart = t;
                for (unsigned int partTi = 0; partTi < 2; partTi++) {
                    tLoopStart -= PART_TIMES[partTi]; //Adjust correct part timing. Hacky, but not needed often
                }
				tPartStart = t-tLoopStart;
                doPP = true; //false?
				break;
		}
        if (doPP) {
            blur.bindFramebuffer();
            blur.draw(); //Blur doesn't draw to screen, instead to it's own texture that goes to crt as blurFrame
            glClear(GL_DEPTH_BUFFER_BIT);
            //scaler.bindFramebuffer();
            //crt.draw();
            //glClear(GL_DEPTH_BUFFER_BIT);
            gfxBindFB0(); //Now we'll be drawing to screen
            //scaler.draw();
            crt.draw();
        }
        //What was just drawn will now get read by the screen driver
        window.swapBuffers();
        //For clarity, it's good to clear both frame- and renderbuffer... or maybe not... I'll check this later
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
