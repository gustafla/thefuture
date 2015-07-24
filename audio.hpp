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

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "alsa/asoundlib.h"
#include <string>

/*
 * Only stereo, S16_LE, for now
 */

class AudioOut {
    public:
        AudioOut(std::string idevice="default", unsigned int ibufferSize=512, unsigned int isampleRate=44100);
        ~AudioOut();
        int16_t* getS16Buffer();
        int writeBufOut();
        unsigned int getBufferSize();
        bool wantData();
        void stop();
    private:
        unsigned int bufferSize;
        int16_t* S16Buffer;
        int err;
        snd_pcm_t* alsaPlaybackHandle;
        snd_pcm_hw_params_t* alsaHWparams;
        unsigned int sampleRate;
};

#endif
