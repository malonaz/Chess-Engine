#include "ChessBoardTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "utils.h"
#include "coutRedirect.h"

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
  assert(cb.submitMove("E7", "E5") == WRONG_COLOR);


  // restore cout
  cr.restoreCout();  
  std::cout << "   Tests for ChessBoard init passed!\n";
}



void testDestroySquares(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  ChessBoard cb;

  cb.destroySquares();

  // check number of pieces
  assert(Square::num_squares == 0);
  assert(Piece::num_pieces == 0);

  // restore cout
  cr.restoreCout();

  std::cout << "   Tests for destroySquares passed!\n";
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
  assert(cb.submitMove("A7", "A5") == WRONG_COLOR);
  assert(cb.submitMove("G8", "F6") == WRONG_COLOR);
  cb.submitMove("A2", "A4"); // move white piece
  assert(cb.submitMove("B1", "C3") == WRONG_COLOR);
  assert(cb.submitMove("H2", "H4") == WRONG_COLOR);

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
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "F6") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E3", "E4") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("G7", "G5") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D1", "H5") == VALID);
  // test board is in checkmate
  assert(cb.getState() == CHECKMATE);
  assert(cb.submitMove("A7", "A5") == GAME_IS_OVER);
  
 
  // test stalemate is detected
  cb.resetBoard();
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A7", "A5") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D1", "H5") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A8", "A6") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H5", "A5") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H7", "H5") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("H2", "H4") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A6", "H6") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("A5", "C7") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "F6") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("C7", "D7") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("E8", "F7") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D7", "B7") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D8", "D3") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("B7", "B8") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("D3", "H7") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("B8", "C8") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("F7", "G6") == VALID);
  assert(cb.getState() == PLAYING_GAME);
  assert(cb.submitMove("C8", "E6") == VALID);
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
