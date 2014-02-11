CC = clang
CPP_FILES = $(wildcard ./*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDE = -I ../include
LIBS = -L ../lib -lglfw3 -lm -lGLEW -lGL -lGLU -lX11 -lXrandr -lXi
CFLAGS = -std=c++11 -g -Wall $(INCLUDE) 

ModelViewer: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

obj/%.o: ./%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
