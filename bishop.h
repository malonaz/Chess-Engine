// -*- C++ -*-
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

// definitions

// forward declarations
class Square;

/**
 * Bishop. This derived class represents a chess bishop.
 */
class Bishop: public Piece{
public:
  /**
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the knight char representation
   */
  Bishop(const Color color): Piece(color, BISHOP){}

  /**
   * Destructor. Empty
   */
  ~Bishop(){}


  void update(){}
  
};




#endif
