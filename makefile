chess: ChessMain.o chessboard.o square.o piece.o pawn.o knight.o rook.o utils.o
	g++ -Wall -g -o chess $^

ChessMain.o: ChessMain.cpp chessboard.h
	g++ -Wall -g -c ChessMain.cpp

chessboard.o: chessboard.cpp chessboard.h square.h piece.h
	g++ -Wall -g -c chessboard.cpp

square.o: square.cpp square.h piece.h
	g++ -Wall -g -c square.cpp

piece.o: piece.cpp piece.h square.h
	g++ -Wall -g -c piece.cpp

pawn.o: pawn.cpp pawn.h piece.h square.h
	g++ -Wall -g -c pawn.cpp

knight.o: knight.cpp knight.h piece.h square.h
	g++ -Wall -g -c knight.cpp

rook.o: rook.cpp rook.h  piece.h square.h
	g++ -Wall -g -c rook.cpp

utils.o: utils.cpp utils.h
	g++ -Wall -g -c utils.cpp

clean:
	rm *.o chess
