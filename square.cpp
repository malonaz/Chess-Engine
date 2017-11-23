// -*- C++ -*-
#include "square.h"


Square::Square(int file, int rank)
  :file(file), rank(rank){}

int Square::filesTo(Square square_destination){
  return square_destination.file - file;
}


int Square::ranksTo(Square square_destination){
  return square_destination.rank - rank;
}
