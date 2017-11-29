// -*- C++ -*-
#ifndef KING_H
#define KING_H

#include "piece.h"

// definitions
#define KING_MAX_1D_MOVE 1

enum Castle{QUEEN_SIDE = -2, KING_SIDE = 2};

// forward declarations
class Square;

/**
 * King. This derived class represents a chess king.
 */
class King: public Piece{
public:

  /**
   * Constructor. Passes color and type to superclass constructor.
   */
  King(const Color color): Piece(color, KING){}
  

  /**
   * Observer. Returns true if this King can move from the Square at 
   * from_square_p to the Square at to_square_p legally as per chess rules.
   */
  bool canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);
  

  /** 
   * Observer.  Method which returns true this King can castle by moving to
   * the square at to_square_p;
   */
  bool canCastle(Square* from_square_p, Square* to_square_p, Castle castle, bool move_piece = false);


  void update(){}


  
  
};




#endif
