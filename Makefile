.PRECIOUS: gpc/%

CXXFLAGS := -ggdb -std=c++20 -Isrc -O0
LIBS := $(shell pkg-config --libs sdl2)

SOURCES = $(wildcard *.cpp)
OPJECTS = $(patsubst %.cpp, gpc/%.o, $(SOURCES))

ganim: gpc/expensive.o gpc/expensive.o
	$(CXX) $(LIBS) $(CXXFLAGS) -o $@ $^

gpc/%.o: gpc/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

gpc/%: gpc/%.gpc
	gpc --double --pragmas -i $< --of $@ > /dev/null

gpc/expensive.cpp.gpc: expensive.cpp src/sandwich.cpp src/div.cpp
	cpp $< -o $@

gpc/ganim.cpp.gpc: ganim.cpp src/clock.cpp src/ganim.cpp src/mv.cpp src/render.cpp
	cpp $< -o $@
