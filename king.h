// -*- C++ -*-
#ifndef KING_H
#define KING_H

#include "piece.h"

// definitions

// forward declarations
class Square;

/**
 * King. This derived class represents a chess king.
 */
class King: public Piece{
public:
  /**
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the knight char representation
   */
  King(const bool white): Piece(white, KING){}

  /**
   * Destructor. Empty
   */
  ~King(){}

  void update(){}
};




#endif
