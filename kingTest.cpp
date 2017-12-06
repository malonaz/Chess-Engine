#include "kingTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "king.h"
#include "knight.h"
#include "utils.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>
#include <cmath>



void testKing(){
  std::cout << " Starting tests for King\n";

  testKingCanMove();
  testKingCanCastle();

  std::cout << " finished tests for King\n\n";
  
}




void testKingCanMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  Square *from_square_p, *to_square_p;
  // tries to move king onto piece of same color
  from_square_p = cb.getSquare("E8");
  to_square_p = cb.getSquare("D8");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == TAKES_PIECE_OF_SAME_COLOR);
  
  // tries to move king up two squares
  to_square_p = cb.getSquare("E6");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // now moves to a valid square
  // first move pawn above king
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  to_square_p = cb.getSquare("E7");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);
  
  // restore cout
  cr.restoreCout();

  std::cout << "   Tests for king's canMove passed!\n";
}



void testKingCanCastle(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  King* white_king = static_cast<King*> (cb.getKingSquareP(WHITE)->getPiece());
  King* black_king = static_cast<King*> (cb.getKingSquareP(BLACK)->getPiece());
  // first let's setup a position
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("G1", "F3") == NO_ERROR);
  assert(cb.submitMove("B8", "C6") == NO_ERROR);
  // try to castle illegally here
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == PATH_OBSTRUCTED);
  assert(cb.submitMove("F1", "C4") == NO_ERROR);
  assert(cb.submitMove("F8", "C5") == NO_ERROR);
  
  
  // white king can castle
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == NO_ERROR);

  // sets rook on H1 to moved
  cb.getSquare("H1")->getPiece()->setToMoved();

  // cannot castle now
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == INVALID_MOVE);

  // now delete rook on H1 and check if you can castle
  delete cb.getSquare("H1")->getPiece();
  cb.getSquare("H1")->setPiece(0);

  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == INVALID_MOVE);

  // now add a black rook on H1 and try to castle
  cb.getSquare("H1")->setPiece(new Piece(BLACK, ROOK));

  // king cannot castle while in check!
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == KING_IS_IN_CHECK);
  
  // delete rook on h1 and move knight on g8 and black king can castle
  delete cb.getSquare("H1")->getPiece();
  cb.getSquare("H1")->setPiece(0);

  assert(cb.submitMove("B1", "C3") == NO_ERROR);
  assert(cb.submitMove("G8", "F6") == NO_ERROR);
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("G8"), KING_SIDE)
  	 == NO_ERROR);

  // black king cannot castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == PATH_OBSTRUCTED);
  // remove pieces obstructing the path
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("D7", "D6") == NO_ERROR);
  assert(cb.submitMove("A3", "A4") == NO_ERROR);
  assert(cb.submitMove("D8", "E7") == NO_ERROR);
  assert(cb.submitMove("B2", "B3") == NO_ERROR);
  assert(cb.submitMove("C8", "D7") == NO_ERROR);
  assert(cb.submitMove("H2", "H3") == NO_ERROR);

  // black king can castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == NO_ERROR);

  // add a black knight on A6 which threatens the rook's path but no the king - legal
  cb.getSquare("A6")->setPiece(new Knight(WHITE));
  // black king can castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == NO_ERROR);

  // add a black knight on B6, which threatens the destination square of the king
  cb.getSquare("B6")->setPiece(new Knight(WHITE));
  // check king cannot castle queenside without putting itself on check but
  // the canCastle does not check the destination square. this is done higher up
  // hence my call to submitMove below and not canCastle!
  assert(cb.submitMove("E8", "C8") == KING_IS_IN_CHECK);
  
  // add a black knight on C6, threatening the path of the king
  delete cb.getSquare("C6")->getPiece();
  cb.getSquare("C6")->setPiece(new Knight(WHITE));
  // check king cannot castle queen side
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == KING_IS_IN_CHECK);
  
  // set king to moved and king cannot castle
  black_king->setToMoved();
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("G8"), KING_SIDE)
  	 == INVALID_MOVE);
  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for king's canCastle passed!\n";
}

