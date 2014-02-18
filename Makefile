CC = clang
CPP_FILES = $(wildcard GLModelViewer/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDE = -I ./include -I /usr/include/qt4/
LIBS = -L /usr/lib/x86_64-linux-gnu -L ./lib -lQtDeclarative -lQtGui -lQtCore -lQtOpenGL -lpthread -lglfw3 -lm -lGLEW -lGL -lGLU -lX11 -lXrandr -lXi
CFLAGS = -std=c++11 -g -Wall $(INCLUDE) 

bin/ModelViewer: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

obj/%.o: GLModelViewer/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
