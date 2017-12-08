########## RULE ###########
%.o : %.cpp
	g++ -Wall -g -c $<

########## MAIN ##########

chess: ChessMain.o ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o
	g++ -Wall -g -o chess $^

ChessMain.o: ChessMain.cpp ChessBoard.h 

ChessBoard.o: ChessBoard.cpp ChessBoard.h square.h piece.h pawn.h knight.h king.h utils.h

square.o: square.cpp square.h ChessBoard.h piece.h utils.h

piece.o: piece.cpp piece.h ChessBoard.h square.h utils.h

pawn.o: pawn.cpp pawn.h piece.h ChessBoard.h square.h utils.h

knight.o: knight.cpp knight.h piece.h square.h utils.h

king.o: king.cpp king.h piece.h ChessBoard.h square.h utils.h

utils.o: utils.cpp utils.h square.h
	g++ -Wall -g -c utils.cpp

########### TESTER #############


tester: ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o TestMain.o gamesTest.o ChessBoardTest.o squareTest.o pieceTest.o pawnTest.o kingTest.o knightTest.o utilsTest.o
	g++ -Wall -g -o tester $^

TestMain.o: TestMain.cpp ChessBoardTest.h gamesTest.h squareTest.h pieceTest.h pawnTest.h kingTest.h knightTest.h utilsTest.h

gamesTest.o: gamesTest.cpp gamesTest.h ChessBoard.h utils.h coutRedirect.h

ChessBoardTest.o: ChessBoardTest.cpp ChessBoardTest.h ChessBoard.h square.h piece.h pawn.h king.h knight.h utils.h coutRedirect.h

squareTest.o: squareTest.cpp squareTest.h ChessBoard.h ChessBoard.h square.h piece.h pawn.h king.h knight.h utils.h coutRedirect.h

pieceTest.o: pieceTest.cpp pieceTest.h ChessBoard.h square.h piece.h utils.h coutRedirect.h

pawnTest.o: pawnTest.cpp pawnTest.h ChessBoard.h square.h piece.h pawn.h utils.h coutRedirect.h

kingTest.o: kingTest.cpp kingTest.h ChessBoard.h square.h piece.h knight.h king.h utils.h coutRedirect.h

knightTest.o: knightTest.cpp knightTest.h ChessBoard.h square.h utils.h coutRedirect.h

utilsTest.o: utilsTest.cpp utilsTest.h utils.h ChessBoard.h square.h












######### PHONY ##############
.PHONY: clean
.PHONY: test

clean:
	rm *.o chess tester

test: tester	
	clear	
	./tester		

