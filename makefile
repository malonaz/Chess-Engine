chess: main.o chessboard.o square.o piece.o pawn.o
	g++ -Wall -g -o chess $^

main.o: main.cpp piece.h
	g++ -Wall -g -c main.cpp

chessboard.o: chessboard.cpp chessboard.h square.h piece.h
	g++ -Wall -g -c chessboard.cpp

square.o: square.cpp square.h piece.h
	g++ -Wall -g -c square.cpp

piece.o: piece.cpp piece.h square.h
	g++ -Wall -g -c piece.cpp

pawn.o: pawn.cpp pawn.h piece.h square.h
	g++ -Wall -g -c pawn.cpp

clean:
	rm *.o chess
