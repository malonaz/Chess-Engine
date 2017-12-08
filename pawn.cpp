// -*- C++ -*-
#include "pawn.h"
#include "ChessBoard.h"
#include "square.h"
#include <cmath>
#include <iostream>


/**
 * Internal helper function. Returns true if the given components of a
 * move's vector corresponds to a two squares pawn push.
 */
bool twoSquarePawnPush(int rank_diff, int file_diff){
  if (rank_diff != PAWN_MAX_FIRST_FORWARD_MOVE || file_diff != NO_CHANGE)
    return false;
  
  return true;
}


/**
 * Internal helper function. Returns true if the given components of a
 * move's vector correspond to a simple pawn push.
 */
bool simplePawnPush(int rank_diff, int file_diff){
   if (rank_diff != PAWN_FORWARD_MOVE || file_diff != NO_CHANGE)
     return false;
   
   return true;  
}
 

/*
 * Internal helper function. Returns true if the given components of a
 * move's vector correspond to a pawn take.
 */
bool pawnTakes(int rank_diff, int file_diff){
   if (rank_diff != PAWN_FORWARD_MOVE || file_diff != PAWN_LATERAL_MOVE)
     return false;
   
   return true;
}


Error Pawn::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not moving to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
      return TAKES_PIECE_OF_SAME_COLOR;
  
  // get component of move's vector. notice we don't care about the sign
  // of the file diff component.
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int abs_file_diff = std::abs(from_square_p->fileDiff(to_square_p));

  // If piece is black, a rank_diff of 1 corresponds to a forward move of 1
  rank_diff *= (color == WHITE)? 1: -1;

  // match move vector against correct ones. No multiple matches possible
  bool pawn_takes = pawnTakes(rank_diff, abs_file_diff);
  bool simple_pawn_push = simplePawnPush(rank_diff, abs_file_diff);
  bool two_square_pawn_push = twoSquarePawnPush(rank_diff, abs_file_diff);
  
  // gather information about destination square
  bool to_square_has_piece  = to_square_p->hasPiece();
  
  // there cannot be a piece on the square a simple pawn push moves to    
  if (simple_pawn_push){
    if (!to_square_has_piece)
      return NO_ERROR;
  }
  
  // if pawn takes regularly, there must be a piece on to_square_p
  if (pawn_takes && to_square_has_piece)
    return NO_ERROR;

  // notice that we pass @param move_piece to canEnPassant.
  if (pawn_takes && !to_square_has_piece)
    return canEnPassant(from_square_p, to_square_p, move_piece);

  // there cannot be a piece on the square a two square pawn push moves to
  if (two_square_pawn_push && !to_square_has_piece & !has_moved){
    // get square below the square at to_square_p
    Square* square_below_p = to_square_p->getSquareBelow(color); 
    
    if (square_below_p->hasPiece())
      // pawn cannot move through a piece !
      return PATH_OBSTRUCTED;

    if (move_piece)
      // this pawn can be taken en passant next turn
      en_passant = true;  
    
    return NO_ERROR;
  }

  return INVALID_MOVE;
}


Error Pawn::canEnPassant(Square* from_square_p, Square* to_square_p, bool move_piece){
  // get square below the square at to_square_p
  Square* en_passant_square_p = to_square_p->getSquareBelow(color); 

  // en passant square must contain a piece
  if (!en_passant_square_p->hasPiece())
    return INVALID_MOVE;

  // get piece
  Piece* piece_below_p = en_passant_square_p->getPiece();
  Pawn* en_passant_pawn_p;

  // piece must be an opponent's pawn
  if (piece_below_p->getColor() == color ||
      piece_below_p->getType() != type)
    return INVALID_MOVE;

  // recast piece as a pawn
  en_passant_pawn_p = static_cast<Pawn*>(piece_below_p);

  // pawn must have moved past this pawn's ability to take it on the
  // previous turn. If so, it's en passant attribute is true
  if (!en_passant_pawn_p->en_passant)
    return INVALID_MOVE;

  // checks if taking en passant discovers a check on its king
  // null en_passant_square's piece pointer
  en_passant_square_p->setPiece(0);
  // check if move puts king in check
  bool king_is_in_check = from_square_p->movePutsKingInCheck(to_square_p);
  // return the en passant piece to its square
  en_passant_square_p->setPiece(piece_below_p);
  
  if (king_is_in_check)
    return KING_IS_IN_CHECK;
  
  if (move_piece)
    // delete en passant pawn
    en_passant_square_p->destroyPiece();
  
  return NO_ERROR;
}

