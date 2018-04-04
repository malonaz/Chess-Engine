#include "knightTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "utils.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>
#include <cmath>


void testKnight(){
  std::cout << " Starting tests for Knight\n";

  testKnightCanMove();
  
  std::cout << " finished tests for Knight\n\n";
  
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
	 == INVALID_MOVE);

  // now move to valid square
  to_square_p = cb.getSquare("C3");
  assert(from_square_p->getPiece()->canMove(from_square_p, to_square_p)
	 == NO_ERROR);
  
  std::cout << "   Tests for knight's canMove passed!\n";

}

