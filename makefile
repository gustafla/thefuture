# Copyright 2015 Lauri Gustafsson
#
# This file is part of Low Quality is the Future.
#
#     Low Quality is the Future is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     Low Quality is the Future is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with Low Quality is the Future, see COPYING. If not, see <http://www.gnu.org/licenses/>.
#

# A makefile to build Low Quality is the Future.

SRCS=rpi_gfx.cpp main.cpp util.cpp config.cpp text.cpp gfx_EGL_window.cpp gfx_shader.cpp gfx_texture_2D.cpp tga_file.cpp gfx_mat.cpp obj_iobject.cpp gfx_screen.cpp effects/point_field/point_field.cpp common.cpp gfx_postprocessor.cpp effects/point_flag/point_flag.cpp gfx_noise_texture.cpp audio.cpp wav_player.cpp getch.cpp types.cpp demo_thread.cpp audio_thread.cpp cleanup.cpp fade.cpp demo_timing.cpp gfx_model.cpp gfx_model_handler.cpp gfx_screen_movable.cpp effects/particle_burst/particle_burst.cpp particle.cpp mvp.cpp effects/point_tunnel/point_tunnel.cpp effects/point_model/point_model.cpp effects/warp_field/warp_field.cpp parts/logo.cpp draw_line.cpp effects/scroller.cpp parts/1.cpp parts/2.cpp parts/torus.cpp
TARGET=demo
xwin:TARGET=demo.xwin
OBJS=$(SRCS:.cpp=.o)
CFLAGS+=-O1 -fomit-frame-pointer -funroll-loops -funsafe-math-optimizations -MMD -MP
xwin:CFLAGS=-DUSE_X -O1 -fomit-frame-pointer -funroll-loops -funsafe-math-optimizations -MMD -MP
debug: CFLAGS=-g
INCLUDES+=-I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/src/hello_pi/libs/vgfont
xwin:INCLUDES=-I./
LFLAGS=-L/opt/vc/lib
xwin:LFLAGS=
LIBS=-lGLESv2 -lEGL -lbcm_host -lpthread -lasound
xwin:LIBS=-lGLESv2 -lEGL -lpthread -lX11 -lasound
CC=g++

all: $(TARGET)
	@echo "Finished."
	strip --strip-all $(TARGET)

xwin: $(TARGET)
	@echo "Finished."
	strip --strip-all $(TARGET)

debug: $(TARGET)
	@echo "Finished"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS) $(LIBS_CUSTOM)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).xwin
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete
	
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

-include *.d
