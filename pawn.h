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
  bool en_passant;
public:
  /**
   * Constructor which, given a color,
   * calls its superclass constructor with
   * the given color and the pawn char representation
   */
  Pawn(const Color  color): Piece(color, PAWN), en_passant(false){}

  /**
   * Destructor. Empty
   */
  ~Pawn(){}


  void update(){en_passant = false;}

  
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
  bool canMove(Square* sqr_source_ptr, Square* sqr_dest_ptr);

  bool canEnPassant(Square* sqr_dest_ptr, bool destroy_piece = false);

  
};




#endif
