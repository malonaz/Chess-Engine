// -*- C++ -*-
#include "knight.h"
#include "square.h"
#include "utils.h"
#include <iostream>


bool Knight::canMove(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  int rank_shift = sqr_source_ptr->ranksTo(sqr_dest_ptr);
  int file_shift = sqr_source_ptr->filesTo(sqr_dest_ptr);

  int moveMagnitudeSquared = getMoveMagnitudeSquared(rank_shift, file_shift);
  
  if (moveMagnitudeSquared != KNIGHT_MOVE_MAGNITUDE_SQUARED)
    return false;
  
  return true;

}
