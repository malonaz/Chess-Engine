// -*- C++ -*-
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

// forward declarations
class Square;

/**
 * Queen. This derived class represents a chess queen.
 */
class Queen: public Piece{
public:

  /**
   * Constructor. Passes color and type to superclass constructor.
   */
  Queen(const Color color): Piece(color, QUEEN){}
  
  void update(){}
};




#endif
