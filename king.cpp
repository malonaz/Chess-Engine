// -*- C++ -*-
#include "king.h"
#include "square.h"
#include "utils.h"
#include <cmath>


bool King::canMove(Square* from_square_p, Square* to_square_p){
  int rank_diff = std::abs(from_square_p->rankDiff(to_square_p));
  int file_diff = std::abs(from_square_p->fileDiff(to_square_p));
  
  if (to_square_p->hasPiece())
    return false;

  if (std::abs(rank_diff) <= KING_MAX_1D_MOVE &&
      std::abs(file_diff) <= KING_MAX_1D_MOVE)
    return true;

  /*
  if (!has_moved && rank_diff == NO_CHANGE && file_diff == QUEEN_SIDE)
    if (canCastle(from_square_p, QUEEN_SIDE))
      return true;
		
  if (rank_diff == NO_CHANGE && file_diff == KING_SIDE)
    if (canCastle(from_square_p, KING_SIDE))
      return true;
  */
      
  return false;
}



bool King::canCastle(Square* from_square_p, Castle castle){
  Square* rank[8];
  from_square_p->getRank(rank);
  
  int rook_square_file_i = (castle == QUEEN_SIDE)? MIN_INDEX: MAX_INDEX;
  Square* rook_square_p = rank[rook_square_file_i];
  
  Square* path[8];
  from_square_p->getPath(rook_square_p, path, type);

  for (int i = 1; path[i] != rook_square_p; i++)
    if (path[i]->hasPiece())
      return false;

  return true;

}


