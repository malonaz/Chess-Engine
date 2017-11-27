// -*- C++ -*-
#include "piece.h"
#include <iostream>

int Piece::num_pieces = 0;

Piece::Piece(const bool white, const int id)
  :white(white), has_moved(false), id(id){
  num_pieces++;
}

