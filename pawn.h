// -*- C++ -*-
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "utils.h"

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
  // true if this pawn can be taken en passant
  bool en_passant;
  
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
  Error canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);
  

  /**
   * Mutator. Returns true if this pawn can taken en passant while moving
   * to the square at to_square_p and calls destroy on the piece taken on
   * passant if destroy_piece is true. note: this method returns false if
   * taking en passant would discover a check on its king.
   */
  bool canEnPassant(Square* to_square_p, bool move_piece = false);


  /**
   * Observer. Returns true if removing the piece at en_passant_square
   * would discover a check on its king. This method only checks 
   * one scenario. Please read my readme.txt file for more info!
   */
  bool enPassantDiscoversCheck(Square* en_passant_square_p)const;
  
};




#endif
