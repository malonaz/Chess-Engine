// -*- C++ -*-
#include "king.h"
#include "square.h"
#include "utils.h"
#include <cmath>


bool King::canMove(Square* from_square_p, Square* to_square_p){
  int abs_rank_diff = std::abs(from_square_p->rankDiff(to_square_p));
  int abs_file_diff = std::abs(from_square_p->fileDiff(to_square_p));

  if (abs_rank_diff > KING_MAX_1D_DIFF || abs_file_diff > KING_MAX_1D_DIFF)
    return false;
  
  return true;
}




