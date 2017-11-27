// -*- C++ -*-
#include "pawn.h"
#include "square.h"
#include "utils.h"
#include <cmath>
#include <iostream>



/**
 * internal helper function that returns true if this move 
 * is a 2 squares pawn push
 */
bool twoSquaresPush(int ranks_to_dest, int files_to_dest){
  if (ranks_to_dest != PAWN_MAX_FIRST_FORWARD_MOVE ||
      files_to_dest != NONE)
    return false;
  
  return true;
}

/**
 * internal helper function that returns true if this move 
 * is a simple pawn push
 */
bool simplePawnPush(int ranks_to_dest, int files_to_dest){
   if (ranks_to_dest != PAWN_FORWARD_MOVE ||
       files_to_dest != NONE)
     return false;
   return true;  
}
 

/*
 * internal helper function that returns true if this move is 
 * a pawn take
 */
bool pawnTakes(int ranks_to_dest, int files_to_dest){
   if (ranks_to_dest != PAWN_FORWARD_MOVE ||
       files_to_dest != PAWN_LATERAL_MOVE)
     return false;
   return true;
}

bool Pawn::move(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  int ranks_to_dest = sqr_source_ptr->ranksTo(sqr_dest_ptr);
  int files_to_dest = std::abs(sqr_source_ptr->filesTo(sqr_dest_ptr));
  ranks_to_dest *= (color)? 1: -1; // switch to black perspective
  bool dest_sqr_empty  = sqr_dest_ptr->isEmpty();
  
  if (twoSquaresPush(ranks_to_dest, files_to_dest))
    if (dest_sqr_empty){
      en_passant = true;
      return true;
    }

  if (simplePawnPush(ranks_to_dest, files_to_dest))
    if (dest_sqr_empty)
      return true;

  if (pawnTakes(ranks_to_dest, files_to_dest)){
    if (!dest_sqr_empty) // no need to check for colors. this is done higher up
      return true;

    if (dest_sqr_empty && canEnPassant(sqr_dest_ptr))
      return true;
  }
  return false;
}
 
bool Pawn::canEnPassant(Square* sqr_dest_ptr){
  int en_passant_offset = (color)? -1: 1;
  Square* column[8];
  Pawn* pawn;
  sqr_dest_ptr->getColumn(column);
  // must be a valid index since we're moving one square back after a pawn take
  Square* en_passant_sqr = column[sqr_dest_ptr->getRank() + en_passant_offset];
  if (en_passant_sqr->isEmpty() ||
      en_passant_sqr->getPiece()->getType() != PAWN)
    return false;

  pawn = static_cast<Pawn*>(en_passant_sqr->getPiece());
  if (!(pawn->en_passant))
    return false;
  
  en_passant_sqr->destroyPiece();
  return true;
}
