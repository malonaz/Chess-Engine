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
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the knight char representation
   */
  Knight(const bool white): Piece(white, KNIGHT){}

  /**
   * Destructor. Empty
   */
  ~Knight(){}

  void update(){}
  
  /**
   * Implements superclass pure virtual method.
   * This method checks that the move to sqr_dest_ptr
   * is one of four moves a pawn can make:
   *   1) initial move forward 2 ranks
   *   2) simple move forward 1 rank
   *   3) pawn takes
   *   4) en passant take
   * returns true if one of those cases is true
   * false otherwise
   */
  bool move(Square* sqr_source_ptr, Square* sqr_dest_ptr);

};




#endif
