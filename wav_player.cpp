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

#include "wav_player.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <inttypes.h>

void WavPlayer::errorPrint(std::string filename)
{
    std::cout << filename << ": Failed to load WAV file\n";
    exit(609);
}

WavPlayer::WavPlayer(std::string filename, float startAt, unsigned int bufferSize):
bufferSize(bufferSize) {
    char id[4];
    char const RIFF[4] = {
        'R',
        'I',
        'F',
        'F'
    };
    char const WAVE[4] = {
        'W',
        'A',
        'V',
        'E'
    };
    uint32_t size;
    uint16_t format_tag;
    uint16_t channels;
    uint16_t block_align;
    uint16_t bits_per_sample;
    uint32_t format_length;
    uint32_t sample_rate;
    uint32_t avg_bytes_sec;
    uint32_t data_size;
    
    file.open(filename.c_str(), std::ifstream::binary);
    
    file.read(id, sizeof(id));
    if (file.eof() || file.fail())
        errorPrint(filename);
    
    if (memcmp(id, RIFF, sizeof(id)) != 0) {
        std::cout << filename << ": no RIFF id in file.\n";
        errorPrint(filename);
    }
    
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (file.eof() || file.fail())
        errorPrint(filename);
    
    file.read(id, sizeof(id));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    if (memcmp(id, WAVE, sizeof(id)) != 0) {
        std::cout << filename << ": no WAVE id in file.\n";
        errorPrint(filename);
    }
    
    file.read(id, sizeof(id)); //"fmt "
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&format_length), sizeof(format_length));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&format_tag), sizeof(format_tag));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&channels), sizeof(channels));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&sample_rate), sizeof(sample_rate));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&avg_bytes_sec), sizeof(avg_bytes_sec));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&block_align), sizeof(block_align));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(reinterpret_cast<char*>(&bits_per_sample), sizeof(bits_per_sample));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    file.read(id, sizeof(id)); //"data"
    if (file.eof() || file.fail())
        errorPrint(filename);

    if (bits_per_sample != 16) {
        std::cout << "WavPlayer: WAV not 16-bit\n";
        errorPrint(filename);
    }
    
    if (channels != 2) {
        std::cout << "WavPlayer: WAV not stereo\n";
        errorPrint(filename);
    }
    
    sampleRate = sample_rate;
        
    file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));
    if (file.eof() || file.fail())
        errorPrint(filename);
        
    size = data_size;
    
    audioDataBegin = file.tellg();
    std::streampos startPos = audioDataBegin;
    startPos += 2*sampleRate*2*startAt + bufferSize; //bytes_in_int16*sampleRate*channels*start_time
    file.seekg(startPos);
    playbackDevice = new AudioOut("default", bufferSize, sampleRate);
}

WavPlayer::~WavPlayer() {
    delete playbackDevice;
}

int WavPlayer::playFrame() {
    if (playbackDevice->wantData()) {
        if (!file.eof() && !file.fail()) {
            file.read(reinterpret_cast<char*>(playbackDevice->getS16Buffer()), (sizeof(int16_t)*bufferSize));
            err = playbackDevice->writeBufOut();
            return err;
        }
    }
}

bool WavPlayer::done() {
    if (file.eof())
        return true;
    else return false;
}

void WavPlayer::restart() {
    file.seekg(audioDataBegin);
}

