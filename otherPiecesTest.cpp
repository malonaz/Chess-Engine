#include "otherPiecesTest.h"
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


void testKnight(){
  std::cout << " Starting tests for Knight\n";

  testKnightCanMove();
  testKingCanMove();
  testKingCanCastle();
  testPawnCanMove();
  
  std::cout << " finished tests for Knight\n\n";
  
}


void testKing(){
  std::cout << " Starting tests for King\n";


  std::cout << " finished tests for King\n\n";
  
}


void testPawn(){
  std::cout << " Starting tests for Pawn\n";


  std::cout << " finished tests for Pawn\n\n";
  
}


void testKnightCanMove(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // restore cout
  cr.restoreCout();

  Square *from_square_p, *to_square_p;
  // tries to move knight onto piece of same color
  from_square_p = cb.getSquare("B1");
  to_square_p = cb.getSquare("D2");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == TAKES_PIECE_OF_SAME_COLOR);

  // try to move knight vertically
  to_square_p = cb.getSquare("B4");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == INVALID);

  // now move to valid square
  to_square_p = cb.getSquare("C3");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == VALID);
  
  std::cout << "   Tests for knight's canMove passed!\n";

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
	 == INVALID);

  // now moves to a valid square
  // first move pawn above king
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  to_square_p = cb.getSquare("E7");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == VALID);
  
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
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("G1", "F3") == VALID);
  assert(cb.submitMove("B8", "C6") == VALID);
  // try to castle illegally here
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == PATH_OBSTRUCTED);
  assert(cb.submitMove("F1", "C4") == VALID);
  assert(cb.submitMove("F8", "C5") == VALID);
  
  
  // white king can castle
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == VALID);

  // sets rook on H1 to moved
  cb.getSquare("H1")->getPiece()->setToMoved();

  // cannot castle now
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == INVALID);

  // now delete rook on H1 and check if you can castle
  delete cb.getSquare("H1")->getPiece();
  cb.getSquare("H1")->setPiece(0);

  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == INVALID);

  // now add a black rook on H1 and try to castle
  cb.getSquare("H1")->setPiece(new Piece(BLACK, ROOK));

  // king cannot castle while in check!
  assert(white_king->canCastle(cb.getSquare("E1"), cb.getSquare("G1"), KING_SIDE)
	 == DISCOVERS_CHECK);
  
  // delete rook on h1 and move knight on g8 and black king can castle
  delete cb.getSquare("H1")->getPiece();
  cb.getSquare("H1")->setPiece(0);

  assert(cb.submitMove("B1", "C3") == VALID);
  assert(cb.submitMove("G8", "F6") == VALID);
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("G8"), KING_SIDE)
  	 == VALID);

  // black king cannot castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == PATH_OBSTRUCTED);
  // remove pieces obstructing the path
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("D7", "D6") == VALID);
  assert(cb.submitMove("A3", "A4") == VALID);
  assert(cb.submitMove("D8", "E7") == VALID);
  assert(cb.submitMove("B2", "B3") == VALID);
  assert(cb.submitMove("C8", "D7") == VALID);
  assert(cb.submitMove("H2", "H3") == VALID);

  // black king can castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == VALID);

  // add a black knight on A6 which threatens the rook's path but no the king - legal
  cb.getSquare("A6")->setPiece(new Knight(WHITE));
  // black king can castle queenside
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == VALID);

  // add a black knight on B6, which threatens the destination square of the king
  cb.getSquare("B6")->setPiece(new Knight(WHITE));
  // check king cannot castle queenside without putting itself on check but
  // the canCastle does not check the destination square. this is done higher up
  // hence my call to submitMove below and not canCastle!
  assert(cb.submitMove("E8", "C8") == DISCOVERS_CHECK);
  
  // add a black knight on C6, threatening the path of the king
  delete cb.getSquare("C6")->getPiece();
  cb.getSquare("C6")->setPiece(new Knight(WHITE));
  // check king cannot castle queen side
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("C8"), QUEEN_SIDE)
  	 == DISCOVERS_CHECK);
  
  // set king to moved and king cannot castle
  black_king->setToMoved();
  assert(black_king->canCastle(cb.getSquare("E8"), cb.getSquare("G8"), KING_SIDE)
  	 == INVALID);
  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for king's canCastle passed!\n";
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
    assert(moving_piece_p->canMove(from_square_p, to_square_p) == VALID);

    // check black pawn can move up two squares
    from_square_p = cb.getSquare(black_pawn_rank, file_i);
    to_square_p = cb.getSquare(black_pawn_rank - 2, file_i);
    moving_piece_p = from_square_p->getPiece();
    assert(moving_piece_p->canMove(from_square_p, to_square_p) == VALID);
  }

  // now set pawn on B2 to moved
  from_square_p = cb.getSquare("B2");
  to_square_p = cb.getSquare("B4");
  moving_piece_p = from_square_p->getPiece();
  moving_piece_p->setToMoved();
  // check pawn cannot move up two squares
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == INVALID);


  // test pawn cannot move diagonally to empty square
  to_square_p = cb.getSquare("C3");
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == INVALID);

  // test pawn cannot take a piece by moving vertically
  to_square_p = cb.getSquare("B3");
  to_square_p->setPiece(new Piece(BLACK, DUMMY));
  // check pawn cannot take by moving up one
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == PATH_OBSTRUCTED);
  // check pawn can take diagonally
  from_square_p = cb.getSquare("A2");
  assert(moving_piece_p->canMove(from_square_p, to_square_p)
	 == VALID);

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

  std::cout << "   Tests for pawn's canMove passed!\n";
}
