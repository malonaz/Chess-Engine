// -*- C++ -*-
#include "king.h"
#include "square.h"
#include "utils.h"
#include <cmath>
#include <iostream>

bool King::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);

  bool can_move = false;
  if (std::abs(rank_diff) <= KING_MAX_1D_MOVE &&
      std::abs(file_diff) <= KING_MAX_1D_MOVE)
    can_move = true;

  
  if (rank_diff == NO_CHANGE && file_diff == QUEEN_SIDE)
    if (canCastle(from_square_p, to_square_p, QUEEN_SIDE))
      can_move = true;
		
  if (rank_diff == NO_CHANGE && file_diff == KING_SIDE)
    if (canCastle(from_square_p, to_square_p, KING_SIDE, move_piece))
      can_move = true;
  
  
  if (move_piece){
    to_square_p->destroyPiece();
    to_square_p->setPiece(this);
    from_square_p->setPiece(0);
  }
  
  return can_move;
}



bool King::canCastle(Square* from_square_p, Square* to_square_p, Castle castle, bool move_piece){
  if (has_moved) // king cannot have moved
    return false;
  
  if (from_square_p->isUnderAttack(color)) // king cannot be under check
    return false;

  Square* rank[8];
  from_square_p->getRank(rank);
  
  int rook_square_file_i = (castle == QUEEN_SIDE)? MIN_INDEX: MAX_INDEX;
  Square* rook_square_p = rank[rook_square_file_i];
  
  if (!rook_square_p->hasPiece()) // there must be a piece on this square
    return false;
  
  Piece* rook_square_piece_p = rook_square_p->getPiece();

  if (rook_square_piece_p->getType() != ROOK || // piece must be a rook 
      rook_square_piece_p->getColor() != color || // with same color
      rook_square_piece_p->hasMoved()) // that has not moved
    return false;
  						 
  Square* path[8];
  from_square_p->getPath(rook_square_p, path, type);
  
  for (int i = 1; path[i] != rook_square_p; i++){
    if (path[i]->hasPiece()) // there cannot be a piece on the path from 
      return false; // king to rook square

    if (i <= 2 && path[i]->isUnderAttack(color))
      return false; // no square the king passes through can be under attack
  }

  return true;

}


