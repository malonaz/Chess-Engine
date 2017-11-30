// -*- C++ -*-
#include "pawn.h"
#include "square.h"
#include "utils.h"
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

bool Pawn::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int abs_file_diff = std::abs(from_square_p->fileDiff(to_square_p));
  rank_diff *= (color == WHITE)? 1: -1; // switch to black perspective
  bool to_square_has_piece  = to_square_p->hasPiece();

  bool pawn_takes = pawnTakes(rank_diff, abs_file_diff);
  bool simple_pawn_push = simplePawnPush(rank_diff, abs_file_diff);
  bool two_square_pawn_push = twoSquarePawnPush(rank_diff, abs_file_diff);

  bool can_move = false;
  
  if (simple_pawn_push && !to_square_has_piece)
    can_move = true;
  
  if (pawn_takes && to_square_has_piece)
    can_move = true;
 
  if (pawn_takes && !to_square_has_piece && canEnPassant(to_square_p, move_piece))
    can_move = true;

  if (two_square_pawn_push && !to_square_has_piece){
    Square* square_below = to_square_p->getSquareBelow(color); 

    if (square_below->hasPiece()) // cannot move past a piece
      return false;

    if (move_piece)
      en_passant = true; // this pawn can be taken en passant next turn
    
    can_move = true;
  }

  if (can_move && move_piece){
    to_square_p->destroyPiece();
    to_square_p->setPiece(this);
    from_square_p->setPiece(0);
  }

  return can_move;
}


bool Pawn::canEnPassant(Square* to_square_p, bool destroy_piece){
  int en_passant_rank_offset = (color)? -1: 1;
  Square* en_passant_file[8], *en_passant_square;
  Piece* en_passant_piece;
  Pawn* en_passant_pawn;
  int en_passant_rank_i = to_square_p->getRankIndex() + en_passant_rank_offset;

  to_square_p->getFile(en_passant_file);
  
  en_passant_square = en_passant_file[en_passant_rank_i]; // must be valid rank index
  
  if (!en_passant_square->hasPiece())
    return false;

  en_passant_piece = en_passant_square->getPiece();
  if (en_passant_piece->getColor() == color ||
      en_passant_piece->getType() != PAWN)
    return false;
  
  en_passant_pawn = static_cast<Pawn*>(en_passant_piece);
  
  if (!en_passant_pawn->en_passant)
    return false;

  if (destroy_piece)
    en_passant_square->destroyPiece();
  
  return true;
}
