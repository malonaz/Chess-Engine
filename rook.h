// -*- C++ -*-
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

// definitions

// forward declarations
class Square;

/**
 * Rook. This derived class represents a chess rook.
 */
class Rook: public Piece{
public:
  /**
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the knight char representation
   */
  Rook(const Color color): Piece(color, ROOK){}

  /**
   * Destructor. Empty
   */
  ~Rook(){}


  void update(){}

  
};




#endif
