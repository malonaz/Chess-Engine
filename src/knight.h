// -*- C++ -*-
#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "utils.h"

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

  
  /**
   * Mutator. Checks if this Knight can move from the Square at from_square_p 
   * to the Square at to_square_p legally as per chess rules. Returns an error 
   * describing the move (see utils.h for more info). Here move_piece has no
   * effect.
   */
  Error moveIsLegal(Square* from_square_p, Square* to_square_p, bool move_piece = false);

};

#endif
