// -*- C++ -*-
#include "rook.h"
#include "square.h"
#include "utils.h"
#include <iostream>

bool Rook::move(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  int rank_shift = sqr_source_ptr->ranksTo(sqr_dest_ptr);
  int file_shift = sqr_source_ptr->filesTo(sqr_dest_ptr);

  Square* path[8];
  
  if (getMoveDimension(rank_shift, file_shift) == HORIZONTAL)
    sqr_source_ptr->getRow(path);
  else if (getMoveDimension(rank_shift, file_shift) == VERTICAL)
    sqr_source_ptr->getColumn(path);
  else 
    return false;

  
  
}
  
