CXX = g++
CXXFLAGS = -g -Wall -MMD

################################### MAIN ###################################mv 
EXE = bin/chess
SRC_DIR = src/
OBJS = $(addprefix $(SRC_DIR), ChessMain.o ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o)

$(EXE): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(OBJS:.o=.d)



################################### TESTER ################################
TEST = bin/test
TEST_DIR = test/
TEST_OBJS = $(addprefix $(TEST_DIR), TestMain.o gamesTest.o ChessBoardTest.o squareTest.o pieceTest.o \
pawnTest.o kingTest.o knightTest.o utilsTest.o)

test: $(TEST_OBJS) $(filter-out $(SRC_DIR)ChessMain.o, $(OBJS))
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $(TEST)

$(TEST_OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(TEST_OBJS:.o=.d)


################################### PHONY #################################
.PHONY: clean clean_dep

clean:
	rm -rf $(EXE) $(OBJS) $(OBJS:.o=.d)
	rm -rf $(TEST) $(TEST_OBJS) $(TEST_OBJS:.o=.d)
