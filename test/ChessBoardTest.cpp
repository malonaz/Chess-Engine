#include "ChessBoardTest.h"
#include "../src/ChessBoard.h"
#include "../src/square.h"
#include "../src/piece.h"
#include "../src/pawn.h"
#include "../src/king.h"
#include "../src/knight.h"
#include "../src/utils.h"
#include "../src/coutRedirect.h"

#include <iostream>
#include <assert.h>
#include <cmath>

void testChessBoard(){

  std::cout << " Starting tests for ChessBoard\n";

  testChessBoardInit();
  testDestroySquares();
  testSubmitMove();
  testGetSquare();
  testPrepareNextTurn();
  testPlayerCanMove();
  std::cout << " finished tests for ChessBoard\n\n";

}


void testChessBoardInit(){  
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;

  ChessBoard cb;

  // check number of pieces
  assert(Square::num_squares == 64);
  assert(Piece::num_pieces == 32);

  // check king pointers
  assert(cb.getSquare("E1") == cb.getKingSquareP(WHITE));
  assert(cb.getSquare("E8") == cb.getKingSquareP(BLACK));
	 
  // check it is white turn by attempting to move a black piece
  assert(cb.submitMove("E7", "E5") == MOVE_OUT_OF_TURN);


  // restore cout
  cr.restoreCout();  
  std::cout << "   Tests for ChessBoard init passed!\n";
}



void testDestroySquares(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  ChessBoard* chessboard_p = new ChessBoard();

  delete chessboard_p;
  // check number of pieces
  assert(Square::num_squares == 0);
  assert(Piece::num_pieces == 0);

  // restore cout
  cr.restoreCout();

  std::cout << "   Tests for freePieces passed!\n";
  std::cout << "   Tests for resetBoard passed!\n";
}

void testSubmitMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  ChessBoard cb;

  // check invalid squares
  assert(cb.submitMove("A0", "A1") == INVALID_SQUARE);
  assert(cb.submitMove("", "B3") == INVALID_SQUARE);
  assert(cb.submitMove("", "") == INVALID_SQUARE);
  assert(cb.submitMove(" ", "1") == INVALID_SQUARE);

  // check empty squares
  assert(cb.submitMove("A3", "A4") == EMPTY_SQUARE);
  assert(cb.submitMove("D6", "D7") == EMPTY_SQUARE);
  assert(cb.submitMove("C4", "C6") == EMPTY_SQUARE);
  assert(cb.submitMove("H5", "A4") == EMPTY_SQUARE);

  // check wrong color
  assert(cb.submitMove("A7", "A5") == MOVE_OUT_OF_TURN);
  assert(cb.submitMove("G8", "F6") == MOVE_OUT_OF_TURN);
  cb.submitMove("A2", "A4"); // move white piece
  assert(cb.submitMove("B1", "C3") == MOVE_OUT_OF_TURN);
  assert(cb.submitMove("H2", "H4") == MOVE_OUT_OF_TURN);

  // valid moves are tested in square and piece classes

  // restore cout
  cr.restoreCout();
  
 std::cout << "   Tests for submitMove passed!\n";
}



void testPrepareNextTurn(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // test checkmate is detected
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "F6") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E3", "E4") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("G7", "G5") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D1", "H5") == NO_ERROR);
  // test board is in checkmate
  assert(cb.getState() == CHECKMATE);
  assert(cb.submitMove("A7", "A5") == GAME_IS_OVER);
  
 
  // test stalemate is detected
  cb.resetBoard();
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A7", "A5") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D1", "H5") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A8", "A6") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H5", "A5") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H7", "H5") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H2", "H4") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A6", "H6") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A5", "C7") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "F6") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("C7", "D7") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E8", "F7") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D7", "B7") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D8", "D3") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("B7", "B8") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D3", "H7") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("B8", "C8") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "G6") == NO_ERROR);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("C8", "E6") == NO_ERROR);
  // check board is in stalemate
  assert(cb.getState() == STALEMATE);
  assert(cb.submitMove("H2", "h4") == GAME_IS_OVER);

  
  // restore cout
  cr.restoreCout();

std::cout << "   Tests for testPrepareNextTurn passed!\n";
}


void testGetSquare(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // restore cout
  cr.restoreCout();
  
  char square_str[3];
  square_str[SENTINEL_CHAR_INDEX] = '\0';

  for (char file = 'A'; file <= 'H'; file++)
    for (char rank = '1'; rank <= '8'; rank++){
      square_str[FILE_CHAR_INDEX] = file;
      square_str[RANK_CHAR_INDEX] = rank;
      assert(cb.getSquare(square_str) == cb.getSquare(rank - '1', file - 'A'));
    }
  
  std::cout << "   Tests for getSquare passed!\n";
}



void testPlayerCanMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // restore cout
  cr.restoreCout();
  
  // check both players can move
  assert(cb.playerCanMove(WHITE));
  assert(cb.playerCanMove(BLACK));

  // delete all pieces
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
      cb.getSquare(rank_i, file_i)->destroyPiece();

  // check neither player can move
  assert(!cb.playerCanMove(WHITE));
  assert(!cb.playerCanMove(BLACK));


  // add a white pawn
  cb.getSquare("C2")->setPiece(new Pawn(WHITE));
  // check white can move and not black
  assert(cb.playerCanMove(WHITE));
  assert(!cb.playerCanMove(BLACK));
 
  
  std::cout << "   Tests for playerCanMove passed!\n";
}
