// -*- C++ -*-
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

// definitions

// forward declarations
class Square;

/**
 * Queen. This derived class represents a chess queen.
 */
class Queen: public Piece{
public:
  /**
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the knight char representation
   */
  Queen(const bool white): Piece(white, QUEEN){}

  /**
   * Destructor. Empty
   */
  ~Queen(){}
  
  void update(){}
};




#endif
