// -*- C++ -*-
#include "knight.h"
#include "square.h"
#include "utils.h"
#include <iostream>


bool Knight::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not moving to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
      return false;

  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);
  
  // only 8 (x, y) integer solutions to x^2 + y^2 = 5 which correspond
  // to the 8 knight moves
  int moveMagnitudeSquared = getMoveMagnitudeSquared(rank_diff, file_diff);
  
  if (moveMagnitudeSquared != KNIGHT_MOVE_MAGNITUDE_SQUARED)
    return false;

  if (move_piece){
    to_square_p->destroyPiece();
    to_square_p->setPiece(this);
    from_square_p->setPiece(0);
  }
  
  return true;

}
