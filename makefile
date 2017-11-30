chess: ChessMain.o ChessBoard.o square.o piece.o pawn.o knight.o king.o utils.o test.o
	g++ -Wall -g -o chess $^

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h square.h piece.h
	g++ -Wall -g -c ChessBoard.cpp

square.o: square.cpp square.h piece.h
	g++ -Wall -g -c square.cpp

piece.o: piece.cpp piece.h square.h
	g++ -Wall -g -c piece.cpp

pawn.o: pawn.cpp pawn.h piece.h square.h
	g++ -Wall -g -c pawn.cpp

knight.o: knight.cpp knight.h piece.h square.h
	g++ -Wall -g -c knight.cpp

king.o: king.cpp king.h piece.h square.h
	g++ -Wall -g -c king.cpp

utils.o: utils.cpp utils.h
	g++ -Wall -g -c utils.cpp


test.o: test.cpp test.h ChessBoard.h
	g++ -Wall -g -c test.cpp

clean:
	rm *.o chess
test:
	make
	clear
	./chess
