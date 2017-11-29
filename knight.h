// -*- C++ -*-
#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

// definitions
#define KNIGHT_MOVE_MAGNITUDE_SQUARED 5

// forward declarations
class Square;

/**
 * Knight. This derived class represents a chess knight.
 */
class Knight: public Piece{

public:

  /**
   * Constructor. Passes color and type to superclass constructor, then
   * intializes en_passant to false.
   */
  Knight(const Color color): Piece(color, KNIGHT){}

  
  void update(){}
  
  
  /**
   * Observer. Returns true if this Knight can move from the Square at 
   * from_square_p to the Square at to_square_p legally as per chess rules.
   */
  bool canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);

};




#endif
