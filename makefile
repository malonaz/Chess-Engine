EXE = chess
TESTER = tester
EXE_SOURCE = $(wildcard src/*.cpp)
TESTER_SOURCE = $(wildcard tst/*.cpp)

EXE_OBJECTS = $(patsubst %.cpp, %.o, $(EXE_SOURCE))
TESTER_OBJECTS = $(patsubst %.cpp, %.o, $(TESTER_SOURCE))

CXX = g++
CXXFLAGS = -Wall -g -MMD

$(EXE): $(EXE_OBJECTS) ChessMain.o
	$(CXX) $(CXXFLAGS) $^ -o $@

## I add this here because your ChessMain.cpp is in the root directory...
## and notice I exclude it from my objects...
ChessMain.o: ChessMain.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE_OBJECTS): src/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTER): $(filter-out src/ChessMain.o, $(EXE_OBJECTS)) $(TESTER_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TESTER_OBJECTS): tst/%.o : tst/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(EXE_OBJECTS:.o=.d) $(TESTER_OBJECTS:.o=.d) ChessMain.d

.PHONY: clean test

clean:
	rm $(EXE_OBJECTS) $(TESTER_OBJECTS)

test:
	make $(TESTER)
	./tester
