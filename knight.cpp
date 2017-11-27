// -*- C++ -*-
#include "knight.h"
#include "square.h"
#include "utils.h"
#include <iostream>


bool isLegalKnightMove(int ranks, int files){
  if (ranks*ranks + files*files !=
      KNIGHT_MOVE_HYPOTHENUS_SQUARED)
    return false;
  return true;
}

bool Knight::move(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  int ranks_to_dest = sqr_source_ptr->ranksTo(sqr_dest_ptr);
  int files_to_dest = sqr_source_ptr->filesTo(sqr_dest_ptr);

  if (isLegalKnightMove(ranks_to_dest, files_to_dest))
    return true;
  
  return false;
}
  
