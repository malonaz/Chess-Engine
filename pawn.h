// -*- C++ -*-
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#define PAWN_LATERAL_MOVEMENT 1
#define PAWN_FORWARD_MOVEMENT 1
#define PAWN_MAX_FIRST_FORWARD_MOVEMENT 2

class Pawn: public Piece{



public:
  Pawn(Color color): Piece(color){}
  ~Pawn(){}
  bool legalMove(Square square_destination);
};



#endif
