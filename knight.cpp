// -*- C++ -*-
#include "knight.h"
#include "square.h"
#include "utils.h"
#include <iostream>


bool Knight::canMove(Square* from_square_p, Square* to_square_p){
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);

  // only 8 (x, y) integer solutions to x^2 + y^2 = 5 which correspond
  // to the 8 knight moves
  int moveMagnitudeSquared = getMoveMagnitudeSquared(rank_diff, file_diff);
  
  if (moveMagnitudeSquared != KNIGHT_MOVE_MAGNITUDE_SQUARED)
    return false;
  
  return true;

}
