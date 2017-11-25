// -*- C++ -*-
#include "pawn.h"
#include <cmath>
#include <iostream>



/**
 * internal helper function that returns true if this move 
 * is a 2 squares pawn push
 */
bool twoSquaresPush(int ranks_to_dest, int files_to_dest){
  if (ranks_to_dest != PAWN_MAX_FIRST_FORWARD_MOVE ||
      files_to_dest != NO_MOVE)
    return false;
  
  return true;
}

/**
 * internal helper function that returns true if this move 
 * is a simple pawn push
 */
bool simplePawnPush(int ranks_to_dest, int files_to_dest){
   if (ranks_to_dest != PAWN_FORWARD_MOVE ||
       files_to_dest != NO_MOVE)
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

bool Pawn::move(Square* sqr_source_ptr, Square* sqr_dest_ptr) const{
  int ranks_to_dest = sqr_source_ptr->ranksTo(sqr_dest_ptr);
  int files_to_dest = std::abs(sqr_source_ptr->filesTo(sqr_dest_ptr));
  ranks_to_dest *= (color == black)? -1: 1; // switch to black perspective
  bool dest_sqr_empty  = sqr_dest_ptr->isEmpty();
  
  if (twoSquaresPush(ranks_to_dest, files_to_dest))
    if (dest_sqr_empty){
      
      return true;
    }

  if (simplePawnPush(ranks_to_dest, files_to_dest))
    if (dest_sqr_empty)
      return true;

  if (pawnTakes(ranks_to_dest, files_to_dest)){
    if (!dest_sqr_empty && color != sqr_dest_ptr->getPiece()->getColor())
      return true;
  
  }
   
  
  return false;
}

 

void Pawn::enableEnPassant(Square* sqr_dest_ptr){
}
