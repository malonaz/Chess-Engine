########## RULE ###########
%.o : %.cpp
	g++ -Wall -g -c $<

########## MAIN ##########

chess: ChessMain.o ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o
	g++ -Wall -g -o chess $^

ChessMain.o: ChessMain.cpp ChessBoard.h

ChessBoard.o: ChessBoard.cpp ChessBoard.h square.h piece.h

square.o: square.cpp square.h piece.h

piece.o: piece.cpp piece.h square.h

pawn.o: pawn.cpp pawn.h piece.h square.h

knight.o: knight.cpp knight.h piece.h square.h

king.o: king.cpp king.h piece.h square.h

utils.o: utils.cpp utils.h
	g++ -Wall -g -c utils.cpp

########### TESTER #############

tester: ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o TestMain.o squareTest.o utilsTest.o
	g++ -Wall -g -o tester $^

TestMain.o: TestMain.cpp utilsTest.h squareTest.h

squareTest.o: squareTest.cpp squareTest.h ChessBoard.h

utilsTest.o: utilsTest.cpp utilsTest.h utils.h












######### PHONY ##############

clean:
	rm *.o chess tester

test:
	make tester
	clear
	./tester
