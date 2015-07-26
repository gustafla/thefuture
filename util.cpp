// Copyright 2015 Lauri Gustafsson
/*
This file is part of asmmehu.

    asmmehu is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    asmmehu is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with asmmehu, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "text.hpp"

//using namespace std;

bool isdigits(std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

bool isfloat(std::string &s)
{
    return s.find_first_not_of("0123456789.") == std::string::npos;
}

void checkValueParam(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        std::cout << ARGERR;
        sleep(5);
        exit(20);
    }

    std::string tmps = argv[n];

    if (!isdigits(tmps))
    {
        std::cout << ARGERR;
        sleep(5);
        exit(30);
    }
}

bool loadFile(std::string inFileName, std::string& outString, int linesize)
{
    std::ifstream inFile(inFileName.c_str());
    if (!inFile.is_open())
    {
        std::cout << inFileName << ": No such file\n";
        return false;
    }

    char tmp[(linesize)];

    while (!inFile.eof())
    {
        inFile.getline(tmp, linesize);
        outString += tmp;
        outString += "\n";
    }
    return true;
}

void checkValueParamf(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        std::cout << ARGERR;
        sleep(5);
        exit(21);
    }

    std::string tmps = argv[n];

    if (!isfloat(tmps))
    {
        std::cout << ARGERR;
        sleep(5);
        exit(31);
    }
}

int countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0)
        return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length())) {
        count++;
    }
    return count;
}

float randf() {
    return ((float(rand()%100000)/100000.0f)-0.5)*2.0;
}

float max(float n, float m) {
    return (n>m) ? n : m;
}

float min(float n, float m) {
    return (n>m) ? m : n;
}

float clamp(float n, float a, float b) {
    return ((n<a) ? a : ((n>b) ? b : n));
}
