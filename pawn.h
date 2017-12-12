// -*- C++ -*-
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "utils.h"

// definitions
#define PAWN_LATERAL_MOVE 1
#define PAWN_FORWARD_MOVE 1
#define PAWN_MAX_FIRST_FORWARD_MOVE 2

#define KING_NOT_FOUND -1

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

  void setEnPassantToFalse(){en_passant = false;}

  
  /**
   * Mutator. Checks if this Pawn can move from the Square at from_square_p
   * to the Square at to_square_p legally as per chess rules. Returns an Error
   * describing the move (see utils.h for more info). if move_piece is true, 
   * this method will modify pieces and objects as needed to complete moves
   * such as an enPassant take or a two-square pawn push that makes the pawn
   * vulnerable to enPassant takes. note: if a move is correct en_passant 
   * move, this method will return an KING_IS_IN_CHECK error if doing so would
   * place the king in check for scenarios that would not be detected by the
   * movePutsKingInCheck method.
   */
  Error moveIsLegal(Square* from_square_p, Square* to_square_p, bool move_piece = false);
  

  /**
   * Mutator. Checks if this pawn can move enPassant and returns an error 
   * describing the move. Note: this method will return a KING_IS_IN_CHECK
   * error if the en passant take puts the king in check. if move_piece is
   * true and the move is valid, this method will delete the en_passant piece.
   */
  Error canEnPassant(Square* from_square_p, Square* to_square_p, bool move_piece);


  /**
   * Observer. Returns true if removing the piece at en_passant_square
   * discovers a check on its king. This method checks the only scenario
   * that would not be discovered by the movePutsKingInCheck method.
   * Please read my readme.txt file for more info!
   */
  bool enPassantDiscoversCheck(Square* en_passant_square_p)const;
  
};




#endif
