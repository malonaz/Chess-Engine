// -*- C++ -*-
#ifndef KING_H
#define KING_H

#include "piece.h"

// definitions
#define KING_MOVE_MAGNITUDE_SQUARED 1

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
  King(const Color color): Piece(color, KING){}

  /**
   * Destructor. Empty
   */
  ~King(){}
  
  bool move(Square* sqr_source_ptr, Square* sqr_dest_ptr);
  
  void update(){}

  
};




#endif
