// -*- C++ -*-
#include "piece.h"
#include <iostream>

int Piece::num_pieces = 0;


Piece::Piece(Color color, char repr)
  :color(color), has_moved(false), repr(repr){
  num_pieces++;
}

