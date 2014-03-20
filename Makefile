CC = g++
CPP_FILES = $(wildcard GLModelViewer/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDE = -I ./include -I ./include/GL
LIBS = -L /usr/lib/x86_64-linux-gnu -L ./lib -lpthread -lglfw3 -lm -lGLEW -lGL -lGLU -lX11 -lXrandr -lXi `pkg-config gtkmm-3.0 --libs`
CFLAGS = -std=c++11 -g -Wall $(INCLUDE) `pkg-config gtkmm-3.0 --cflags`

bin/ModelViewer: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

obj/%.o: GLModelViewer/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
