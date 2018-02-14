LINKER_FLAGS=-lm -lpthread -lX11 -lstdc++fs
COMPILER_FLAGS=-std=gnu++17
COMPILER=ccache g++

all: png_read.cpp
	$(COMPILER) png_read.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o png_read.o

