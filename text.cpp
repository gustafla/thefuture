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

#include "text.hpp"
#include <string>

const std::string VERSION = "Low Quality is the Future version 1.0\n"
                            "Copyright 2015 Lauri Gustafsson.\n\n"
                            
                            "Low Quality is the Future is free software: you can redistribute it and/or modify\n"
                            "it under the terms of the GNU General Public License as published by\n"
                            "the Free Software Foundation, either version 3 of the License, or\n"
                            "(at your option) any later version.\n\n"

                            "Low Quality is the Future is distributed in the hope that it will be useful,\n"
                            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                            "GNU General Public License for more details.\n\n"

                            "You should have received a copy of the GNU General Public License\n"
                            "along with Low Quality is the Future, see COPYING. If not, see <http://www.gnu.org/licenses/>.\n";

const std::string ARGERR = "Go fix your parameters.\n"
                           "Try 'Low Quality is the Future --help' for more information.\n";

const std::string DOC = "Usage: Low Quality is the Future [OPTION]\n"
                        "Play a nice hardware demonstration with music.\n"
                        "\n"
                        "  -w                window width\n"
                        "  -h                window height\n"
                        "  -x                window pos\n"
                        "  -y                window pos\n"
                        "  -s                window width and height, a square\n"
                        "  -f                print out a FPS reading after every n frame(s)\n"
                        "                    (default 100)\n"
                        "      --no-audio    don't play music, don't exit automatically\n"
                        "      --no-sound    same as --no-audio\n"
                        "      --no-music    same as --no-audio\n"
                        "      --help        display this help and exit\n"
                        "      --version     display version information and exit\n"
                        "\n"
                        "You can report bugs or send mail/spam/\"offers\" to luutifa@gmail.com\n"
                        "Low Quality is the Future home page: <http://mehuclan.com/demoscene>\n";

std::string const PIPE_CAT = "Please pipe stdout text to a file or cat.\n"
                             "Keyboard input requires weird terminal stuff.\n"
                             "----------------------------------------------------\n";
