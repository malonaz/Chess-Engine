// -*- C++ -*-
#include "pawn.h"
#include <iostream>

bool Pawn::isLegalMove(Square* sqr_dest_ptr) const{
  int ranks_to_dest = square_ptr->ranksTo(sqr_dest_ptr);
  int files_to_dest = square_ptr->filesTo(sqr_dest_ptr);
  
  if (color == black)
    ranks_to_dest *= -1; // switch to black's perspective   
  std::cout << "isLegalMove -> has moved: " << has_moved << std::endl;
  
  // case 1: initial move
  if (!has_moved &&
      ranks_to_dest == PAWN_MAX_FIRST_FORWARD_MOVEMENT &&
      files_to_dest == NO_MOVEMENT &&
      sqr_dest_ptr->isEmpty()){
    std::cout << "case 1: initial move" << std::endl;
    return true;
  }
  
  if (ranks_to_dest == PAWN_FORWARD_MOVEMENT){
    // case 2: simple forward move
    if (files_to_dest == NO_MOVEMENT &&
	sqr_dest_ptr->isEmpty()){
          std::cout << "case 2: forward move" << std::endl;
      return true;
    }

   
    if (files_to_dest == PAWN_LATERAL_MOVEMENT)
      // case 3: pawn takes
      if (!sqr_dest_ptr->isEmpty() &&
	  this->color != sqr_dest_ptr->getPiece()->getColor()){
	std::cout << "case 3: pawn takes" << std::endl;
	return true;
      }
    
      // MUST IMPLEMENT: case 4: check en-passant
      //if (sqr_dest_ptr->isEmpty())
  }
  
  return false;
}
