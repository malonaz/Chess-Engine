// -*- C++ -*-
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"


// forward declarations
class Square;

/**
 * Rook. This derived class represents a chess rook.
 */
class Rook: public Piece{

public:

  /**
   * Constructor. Passes color and type to superclass constructor.
   */
  Rook(const Color color): Piece(color, ROOK){}

  void update(){}
  
};




#endif
