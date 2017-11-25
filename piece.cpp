// -*- C++ -*-
#include "piece.h"
#include <iostream>

int Piece::num_pieces = 0;


Piece::Piece(const Color color, const int id)
  :color(color), has_moved(false), id(id){
  num_pieces++;
}

