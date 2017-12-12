EXE = chess
TESTER = tester
EXE_OBJECTS = ChessMain.o ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o
TESTER_OBJECTS = TestMain.o gamesTest.o ChessBoardTest.o squareTest.o pieceTest.o \
pawnTest.o kingTest.o knightTest.o utilsTest.o

CXX = g++
CXXFLAGS = -Wall -g -MMD


############ MAIN ###################
$(EXE): $(EXE_OBJECTS) ChessMain.o
	$(CXX) $(CXXFLAGS) $^ -o $@

############# TESTER ################
$(TESTER): $(filter-out ChessMain.o, $(EXE_OBJECTS)) $(TESTER_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@


############ RULE ###################
$(EXE_OBJECTS) $(TESTER_OBJECTS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



############ DEPENDENCIES ###########
-include $(EXE_OBJECTS:.o=.d) $(TESTER_OBJECTS:.o=.d)




############ PHONY ##################
.PHONY: clean test

clean:
	rm $(EXE_OBJECTS) $(TESTER_OBJECTS) $(EXE) $(TESTER)

test:
	make $(TESTER)
	./tester

