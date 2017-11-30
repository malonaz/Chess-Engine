// -*- C++ -*-
#include "king.h"
#include "ChessBoard.h"
#include "square.h"
#include "utils.h"
#include <cmath>
#include <iostream>

bool King::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not moving to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
      return false;

  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);

  // assumes king cannot move until proven otherwise
  bool can_move = false;


  if (std::abs(rank_diff) <= KING_MAX_1D_MOVE &&
      std::abs(file_diff) <= KING_MAX_1D_MOVE)
    // regular king move
    can_move = true;

  
  if (rank_diff == NO_CHANGE && file_diff == QUEEN_SIDE)
    if (canCastle(from_square_p, to_square_p, QUEEN_SIDE, move_piece))
      // king is castling queen side
      can_move = true;
    
  if (rank_diff == NO_CHANGE && file_diff == KING_SIDE)
    if (canCastle(from_square_p, to_square_p, KING_SIDE, move_piece))
      // king is castling king side
      can_move = true;
  
  
  if (move_piece){
    // move pieces
    to_square_p->destroyPiece();
    to_square_p->setPiece(this);
    from_square_p->setPiece(0);
  }
  
  return can_move;
}



bool King::canCastle(Square* from_square_p, Square* to_square_p, Castle castle, bool move_piece){
  // a king that has moved, loses its castling privileges. This takes
  // care of checking king is in the right square. If it has not moved
  // it must be in the e file & its color's first rank.
  if (has_moved)
    return false;

  // king cannot castle while in check
  if (from_square_p->isUnderAttack(color)) 
    return false;

  
  Square* rank[8];
  from_square_p->getRank(rank);

  // king castles with rook in 1st file when castling queen side
  // king castes with rook in 8th file when castling king side
  int rook_square_file_i = (castle == QUEEN_SIDE)? MIN_INDEX: MAX_INDEX;
  Square* rook_square_p = rank[rook_square_file_i];
  
  // get pointer to rook square after castling
  int rook_castle_file_i = (castle == QUEEN_SIDE)? KING_FILE -1: KING_FILE + 1;
  Square* rook_castle_square_p = rank[rook_castle_file_i];

  
  // there must be a piece on this square
  if (!rook_square_p->hasPiece()) 
    return false;
  
  Piece* rook_square_piece_p = rook_square_p->getPiece();

  // piece must be a rook of the same color as the king that has not moved.
  if (rook_square_piece_p->getType() != ROOK || 
      rook_square_piece_p->getColor() != color ||
      rook_square_piece_p->hasMoved()) 
    return false;
  
  Square* path[8];
  // get path from the king to the rook it is castling with
  from_square_p->getPath(rook_square_p, path, type);

  // iterate through the squares in between king and rook.
  for (int i = 1; path[i] != rook_square_p; i++){
    // there cannot be a piece on that path
    if (path[i]->hasPiece()) 
      return false; 

    // this pathway is activated only for the squares that the king will
    // move through and the square it stops on.
    if (i <= 2 && path[i]->isUnderAttack(color))
      // these squares cannot be under attack
      return false; 
  }
  
  if (move_piece){
    // move rook to new castle square and set old square's pointer to null
    // we know square rook is moving to is empty
    rook_castle_square_p->setPiece(rook_square_piece_p);
    rook_square_p->setPiece(0);
  }
    
  return true;

}


