// -*- C++ -*-
#include "pawn.h"
#include <cmath>


bool Pawn::legalMove(Square square_destination){
  int ranks_to_dest = square->ranksTo(square_destination);
  int files_to_dest = square->filesTo(square_destination);

  // case 1: initial move
  if (!has_moved &&
      ranks_to_dest == PAWN_MAX_FIRST_FORWARD_MOVEMENT &&
      files_to_dest == NO_MOVEMENT &&
      square_destination.isFree())
    return true;
  
  if (ranks_to_dest == PAWN_FORWARD_MOVEMENT){
    // case 2: simple forward move
    if (files_to_dest == NO_MOVEMENT &&
	square_destination.isFree())
      return true;

   
    if (files_to_dest == PAWN_LATERAL_MOVEMENT)
      // case 3: pawn takes
      if (!square_destination.isFree())
	return true;
    
      // MUST IMPLEMENT: case 4: check en-passant
      //if (square_destination.isFree())
  }
  
  return false;
}
