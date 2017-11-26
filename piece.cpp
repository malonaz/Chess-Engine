// -*- C++ -*-
#include "piece.h"
#include <iostream>

int Piece::num_pieces = 0;


Piece::Piece(const bool is_white, const int id)
  :is_white(is_white), has_moved(false), id(id){
  num_pieces++;
}

