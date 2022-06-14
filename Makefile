.PRECIOUS: gpc/%.gpc

CXXFLAGS := -ggdb -std=c++20 -Isrc -O0
LIBS := $(shell pkg-config --libs sdl2)

SOURCES = $(wildcard src/*.cpp)
OPJECTS = $(patsubst src/%.cpp, gpc/%.o, $(SOURCES))


ganim: $(OPJECTS)
	$(CXX) $(LIBS) $(CXXFLAGS) -o $@ $^

gpc/%.o: gpc/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

gpc/%: gpc/%.gpc
	gpc --double --pragmas -i $< --of $@

gpc/%.gpc: src/%
	cpp $< -o $@
