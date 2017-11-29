// -*- C++ -*-
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

// forward declarations
class Square;

/**
 * Bishop. This derived class represents a chess bishop.
 */
class Bishop: public Piece{

public:

  /**
   * Constructor. Passes color and type to superclass constructor.
   */
  Bishop(const Color color): Piece(color, BISHOP){}

  void update(){}
  
};




#endif
