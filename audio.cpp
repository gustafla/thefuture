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

#include "audio.hpp"
#include <cstdlib>
#include <iostream>

AudioOut::AudioOut(std::string idevice, unsigned int ibufferSize, unsigned int isampleRate) {
    if ((err = snd_pcm_open(&alsaPlaybackHandle, idevice.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        std::cout << "AudioOut: Cannot open audio device \"" << idevice << "\"\n";
        exit(1);
	}
    
    if ((err = snd_pcm_hw_params_malloc(&alsaHWparams)) < 0) {
		std::cout << "AudioOut: Cannot get h/w parameters\n";
		exit(1);
	}
    
    if ((err = snd_pcm_hw_params_any(alsaPlaybackHandle, alsaHWparams)) < 0) {
		std::cout << "AudioOut: Cannot init h/w parameters\n";
        exit(1);
	}
    
    if ((err = snd_pcm_hw_params_set_access(alsaPlaybackHandle, alsaHWparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		std::cout << "AudioOut: Cannot set access to audio device\n";
        exit(1);
	}
    
    if ((err = snd_pcm_hw_params_set_format(alsaPlaybackHandle, alsaHWparams, SND_PCM_FORMAT_S16_LE)) < 0) {
        std::cout << "AudioOut: Cannot get sample format PCM_S16_LE\n";
        exit(1);
	}
    
    sampleRate = isampleRate;
    if ((err = snd_pcm_hw_params_set_rate_near(alsaPlaybackHandle, alsaHWparams, &sampleRate, 0)) < 0) {
		std::cout << "AudioOut: Cannot get sample rate\n";
        exit(1);
        if (sampleRate != isampleRate) {
            std::cout << "AudioOut: Cannot get desired sample rate\n";
            exit(1);
        }
	}
    
    if ((err = snd_pcm_hw_params_set_channels(alsaPlaybackHandle, alsaHWparams, 2)) < 0) {
		std::cout << "AudioOut: Cannot get stereo sound\n";
		exit(1);
    }
    
    if ((err = snd_pcm_hw_params(alsaPlaybackHandle, alsaHWparams)) < 0) {
		std::cout << "AudioOut: Cannot set audio h/w parameters\n";
        exit(1);
    }
    
    snd_pcm_hw_params_free(alsaHWparams);
    
    if ((err = snd_pcm_prepare(alsaPlaybackHandle)) < 0) {
		std::cout << "AudioOut: Unable to prepare() audio device\n";
        exit(1);
    }
    
    S16Buffer = new int16_t[ibufferSize];
    for (int i=0; i<ibufferSize; i++) {
        S16Buffer[i]=0;
    }
    bufferSize = ibufferSize;
}

AudioOut::~AudioOut() {
    delete[] S16Buffer;
    snd_pcm_close(alsaPlaybackHandle);
}

void AudioOut::stop() {
    snd_pcm_close(alsaPlaybackHandle);
}

int16_t* AudioOut::getS16Buffer() {
    return S16Buffer;
}

int AudioOut::writeBufOut() {
    //int available = snd_pcm_avail(alsaPlaybackHandle);
    //if (available > bufferSize) {
        if ((err = snd_pcm_writei(alsaPlaybackHandle, S16Buffer, bufferSize/2)) != bufferSize/2) {
            if (err == -EPIPE) {
                std::cout << "AudioOut: Underrun\n";
                err = snd_pcm_prepare(alsaPlaybackHandle);
                if (err < 0)
                    std::cout << "AudioOut: Unable to recover from underrun\n";
            } else if (err == -ESTRPIPE) {
                std::cout << "AudioOut: Suspend\n";
                while ((err = snd_pcm_resume(alsaPlaybackHandle)) == -EAGAIN)
                    usleep(60);
                if (err < 0) {
                    err = snd_pcm_prepare(alsaPlaybackHandle);
                    if (err < 0)
                        std::cout << "AudioOut: Unable to recover from suspend\n";
                }
            }
        }
    return err;
}

unsigned int AudioOut::getBufferSize() {
    return bufferSize;
}

bool AudioOut::wantData() {
    if (snd_pcm_avail(alsaPlaybackHandle) >= bufferSize/2)
        return true;
    else return false;
}
