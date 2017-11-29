EXE = chess
OBJECTS_SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(OBJECTS_SOURCES))

PIECES_SOURCES = $(wildcard src/pieces/*.cpp)
PIECES = $(patsubst %.cpp, %.o, $(PIECES_SOURCES))

CXX = g++
CXXGFLAGS = -Wall -g - MMD

$(EXE): $(OBJECTS) $(PIECES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJECTS): src/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PIECES): src/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



.PHONE: clean, test

clean:
	rm $(OBJECTS) $(EXE)
