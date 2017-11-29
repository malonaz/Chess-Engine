// -*- C++ -*-
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

// definitions
#define PAWN_LATERAL_MOVE 1
#define PAWN_FORWARD_MOVE 1
#define PAWN_MAX_FIRST_FORWARD_MOVE 2

// forward declarations
class Square;


/**
 * Pawn. This derived class represents a chess pawn. 
 */
class Pawn: public Piece{

private:
  bool en_passant; // true if this pawn can be taken en passant
public:

  
  /**
   * Constructor. Passes color and type to superclass constructor, then
   * intializes en_passant to false.
   */
  Pawn(const Color  color): Piece(color, PAWN), en_passant(false){}


  void update(){en_passant = false;}

  
   /**
   * Observer. Returns true if this Pawn can move from the Square at 
   * from_square_p to the Square at to_square_p legally as per chess rules.
   */
  bool canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);
  

  /**
   * Mutator. Returns true if this pawn can taken en passant while moving
   * to the square at to_square_p and calls destroy on the piece taken on
   * passant if destroy_piece is true.
   */
  bool canEnPassant(Square* to_square_p, bool destroy_piece = false);

  
};




#endif
