// -*- C++ -*-
#include "king.h"
#include "square.h"
#include "utils.h"
#include <cmath>

bool King::canMove(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  int abs_rank_shift = std::abs(sqr_source_ptr->ranksTo(sqr_dest_ptr));
  int abs_file_shift = std::abs(sqr_source_ptr->filesTo(sqr_dest_ptr));

  if (abs_rank_shift > KING_MAX_1D_SHIFT || abs_file_shift > KING_MAX_1D_SHIFT)
    return false;
  
  return true;

}




