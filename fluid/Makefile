CXXFLAGS=-std=c++11
CXXLIBS=-lpng
CXXCOMP=ccache clang++-3.5

all: boost.hpp.gch
	$(CXXCOMP) fluid.cpp -c -o fluid.o $(CXXFLAGS)
	$(CXXCOMP) $(CXXLIBS) fluid.o -o fluid

boost.hpp.gch:
	$(CXXCOMP) boost.hpp $(CXXFLAGS)
