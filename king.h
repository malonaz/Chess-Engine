// -*- C++ -*-
#ifndef KING_H
#define KING_H

#include "piece.h"
#include "utils.h"

// definitions
#define KING_MAX_1D_MOVE 1
#define KING_CASTLE_MOVE 2

enum Castle{QUEEN_SIDE, KING_SIDE};

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
   * Mutator. Checks if this King can move from the Square at from_square_p
   * to the Square at to_square_p legally as per chess rules. Returns an 
   * Error describing the move (see utils.h for more info). if move_piece is
   * true and king is castling, this method will move the appropriate rook
   * to its castled position. note: if king is castling, this method will 
   * return a KING_IS_IN_CHECK error if the squares the king must travel 
   * through to get to its castled position are under threat.
   */
  Error moveIsLegal(Square* from_square_p, Square* to_square_p, bool move_piece = false);
  

  /** 
   * Mutator. Checks if  King can castle by moving to the square at 
   * to_square_p. Returns an Error describing the move (see utils.h 
   * for more info). If move_piece is true and castling attempt is 
   * legal, this method moves the appropriate rook to its castled 
   * position. note: this method returns false if the king has to
   * travel through threatened squares to get to its castled position.
   */
  Error canCastle(Square* from_square_p, Square* to_square_p, Castle castle, bool move_piece = false);
  
};

#endif
