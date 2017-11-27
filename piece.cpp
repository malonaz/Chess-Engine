// -*- C++ -*-
#include "piece.h"
#include "square.h"
#include <iostream>

int Piece::num_pieces = 0;

Piece::Piece(const bool white, const int id)
  :white(white), has_moved(false), id(id){
  num_pieces++;
}


bool Piece::move(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  Square* path[8];
  if (!sqr_source_ptr->getPath(sqr_dest_ptr, path, id))
    return false;


  for (int i = 1; path[i] != sqr_dest_ptr; i++)
    if (!path[i]->isEmpty())
      return false;
  
  return true;
  
}
  
