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

#ifndef WAV_PLAYER_HPP
#define WAV_PLAYER_HPP

#include "audio.hpp"
#include <string>
#include <fstream>

/*
 * 16-bit for now
 */

class WavPlayer {
    public:
        WavPlayer(std::string filename, float startAt=0.0f, unsigned int ibufferSize=512);
        ~WavPlayer();
        int playFrame();
        bool done();
        void restart();
    private:
        AudioOut* playbackDevice;
        std::ifstream file;
        unsigned int size;
        unsigned int sampleRate;
        unsigned int bufferSize;
        void errorPrint(std::string filename);
        int err;
        std::streampos audioDataBegin;
};

#endif
