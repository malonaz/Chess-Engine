#include "pieceTest.h"
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

void testPiece(){
  std::cout << " Starting tests for Piece\n";

  testStaticNumPieces();
  testSquareOccupiedByFriendlyPiece();
  testCanMove();
  
  std::cout << " finished tests for Piece\n\n";
  
}


void testStaticNumPieces(){
  Piece* piece_ps[100];
  for (int i = 0; i < 100; i++){
    assert (Piece::num_pieces == i);
    piece_ps[i] = new Piece(WHITE, DUMMY);
  }
    
  for (int i = 99; i >= 0; i--){
    delete piece_ps[i];
    assert (Piece::num_pieces == i);
  }
  
  std::cout << "   Tests for static member num_pieces passed!\n";
}


void testSquareOccupiedByFriendlyPiece(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // restore cout
  cr.restoreCout();
  
  Square* from_square_p, *to_square_p;
  Piece* from_piece_p;
  Color from_piece_color;
  
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      from_square_p = cb.getSquare(rank_i, file_i);
      // get from piece information or continue if square has no piece
      if (!from_square_p->hasPiece())
	continue;

      from_piece_p = from_square_p->getPiece();
      from_piece_color = from_piece_p->getColor();


      for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
	for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
	  to_square_p = cb.getSquare(rank_i, file_i);

	  if (from_piece_p->squareOccupiedByFriendlyPiece(to_square_p)){
	    assert(to_square_p->hasPiece());
	    assert(to_square_p->getPiece()->getColor() == from_piece_color);
	  }
	  	  
	}
	  
    }
  
  
  std::cout << "   Tests for squareOccupiedByFriendlyPiece passed!\n";
}



void testCanMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  

  Square *from_square_p, *to_square_p;

  // QUEEN PIECE
  // tries to take own piece
  from_square_p = cb.getSquare("D1");
  to_square_p = cb.getSquare("C1");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == TAKES_PIECE_OF_SAME_COLOR);

  // test moving a piece in a way it's not allowed to move
  to_square_p = cb.getSquare("E4");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // test path obstructed
  // by own piece
  to_square_p = cb.getSquare("D4");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == PATH_OBSTRUCTED);
  // by enemy piece
  delete cb.getSquare("D2")->getPiece(); // free white pawn
  cb.getSquare("D2")->setPiece(new Piece(BLACK, DUMMY)); // add black dummy 
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == PATH_OBSTRUCTED);

  // test valid move
  cb.getSquare("D2")->setPiece(0); // remove piece
  to_square_p = cb.getSquare("D7");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);
  // move queen to D7
  cb.getSquare("D1")->getPiece()->move(from_square_p, to_square_p);
  from_square_p = to_square_p;
  to_square_p = cb.getSquare("E6");
  // can queen move diagonally from D7 to E6 
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);

  // ROOK PIECE
  // try to move diagonally
  from_square_p = cb.getSquare("A8");
  to_square_p = cb.getSquare("C6");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // delete pawn on A7
  delete cb.getSquare("A7")->getPiece();
  cb.getSquare("A7")->setPiece(0);
  // move piece vertically
  to_square_p = cb.getSquare("A4");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);

  // BISHOP PIECE
  // try to move vertically
  from_square_p = cb.getSquare("C1");
  to_square_p = cb.getSquare("C5");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // move piece diagonally
  // remember there is no piece on d2, so let's move to e3
  to_square_p = cb.getSquare("E3");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);

  // restore cout
  cr.restoreCout();
  std::cout << "   Tests for canMove passed!\n";
}
