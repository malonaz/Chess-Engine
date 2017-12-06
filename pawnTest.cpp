#include "pawnTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "pawn.h"
#include "utils.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>
#include <cmath>


void testPawn(){
  std::cout << " Starting tests for Pawn\n";

  testPawnCanMove();
  testCanEnPassant();

  std::cout << " finished tests for Pawn\n\n";
  
}


void testPawnCanMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // check that all pawns can initially move by two squares
  
  int white_pawn_rank = 1; 
  int black_pawn_rank = 6;
  Square *from_square_p, *to_square_p;
  Piece *moving_piece_p;
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
    // check white pawn can move up two squares
    from_square_p = cb.getSquare(white_pawn_rank, file_i);
    to_square_p = cb.getSquare(white_pawn_rank + 2, file_i);
    moving_piece_p = from_square_p->getPiece();
    assert(moving_piece_p->canMove(from_square_p, to_square_p) == NO_ERROR);

    // check black pawn can move up two squares
    from_square_p = cb.getSquare(black_pawn_rank, file_i);
    to_square_p = cb.getSquare(black_pawn_rank - 2, file_i);
    moving_piece_p = from_square_p->getPiece();
    assert(moving_piece_p->canMove(from_square_p, to_square_p) == NO_ERROR);
  }

  // now set pawn on B2 to moved
  from_square_p = cb.getSquare("B2");
  to_square_p = cb.getSquare("B4");
  moving_piece_p = from_square_p->getPiece();
  moving_piece_p->setToMoved();
  // check pawn cannot move up two squares
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // test pawn cannot move diagonally to empty square
  to_square_p = cb.getSquare("C3");
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);

  // test pawn cannot take a piece by moving vertically
  to_square_p = cb.getSquare("B3");
  to_square_p->setPiece(new Piece(BLACK, DUMMY));
  // check pawn cannot take by moving up one
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == INVALID_MOVE);
  // check pawn can take diagonally
  from_square_p = cb.getSquare("A2");
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == NO_ERROR);


  // check pawns cannot take their own piece
  from_square_p = cb.getSquare("B7");
  to_square_p = cb.getSquare("C6");
  to_square_p->setPiece(new Piece(BLACK, DUMMY));
  moving_piece_p = from_square_p->getPiece();
  // check pawn cannot take a friendly piece
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == TAKES_PIECE_OF_SAME_COLOR);

  // restore cout
  cr.restoreCout();

  // pieces created will be deleted when chessboard goes out of scope
  
  std::cout << "   Tests for pawn's canMove passed!\n";
}

void testCanEnPassant(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // let's get to a valid pawn en passant take
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("A7", "A6") == NO_ERROR);
  assert(cb.submitMove("E4", "E5") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  // attempt to take en passant
  assert(cb.submitMove("E5", "D6") == NO_ERROR);

  // let's get to an en passant take that discovers a check
  // that would be picked up by putsKingInCheck
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("C7", "C5") == NO_ERROR);
  assert(cb.submitMove("E4", "E5") == NO_ERROR);
  assert(cb.submitMove("D8", "B6") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("B6", "E6") == NO_ERROR);  
  assert(cb.submitMove("H2", "H3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  // check that submitMove returns putsKingInCheck
  assert(cb.submitMove("E5", "D6") == KING_IS_IN_CHECK); 
  // but canMove should return true as we do monitor for that kind
  // of check in the pawn's canMove method. this is implemented at a
  // a lower level
  assert(cb.getSquare("E5")->getPiece()->
	 canMove(cb.getSquare("E5"), cb.getSquare("D6"))
	 == NO_ERROR);

  // let's get to a position that would not be picked up by putsKingInCheck
  // but will get caught by pawn's canMove method. see readme.txt for more info
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("C7", "C6") == NO_ERROR);
  assert(cb.submitMove("E1", "E2") == NO_ERROR);
  assert(cb.submitMove("D8", "B6") == NO_ERROR);
  assert(cb.submitMove("E2", "F3") == NO_ERROR);
  assert(cb.submitMove("B6", "C5") == NO_ERROR);
  assert(cb.submitMove("F3", "F4") == NO_ERROR);
  assert(cb.submitMove("B7", "B6") == NO_ERROR);
  assert(cb.submitMove("E4", "E5") == NO_ERROR);
  assert(cb.submitMove("C8", "B7") == NO_ERROR);  
  assert(cb.submitMove("F4", "F5") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  // check that movePutsKingInCheck does not pick this up
  assert(!cb.getSquare("E5")->movePutsKingInCheck(cb.getSquare("D6")));
  // now check that canMove returns KING_IS_IN_CHECK
  assert(cb.getSquare("E5")->getPiece()->
	 canMove(cb.getSquare("E5"), cb.getSquare("D6"))
	 == KING_IS_IN_CHECK);
  
  

  
  // restore cout
  cr.restoreCout();
  std::cout << "   Tests for canEnPassant passed!\n";
}
