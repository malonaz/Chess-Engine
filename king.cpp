// -*- C++ -*-
#include "king.h"
#include "ChessBoard.h"
#include "square.h"

#include <cmath>

Error King::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not moving to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
    return TAKES_PIECE_OF_SAME_COLOR;

  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);

  if (std::abs(rank_diff) <= KING_MAX_1D_MOVE &&
      std::abs(file_diff) <= KING_MAX_1D_MOVE)
    // regular king move
    return NO_ERROR;

  
  if (rank_diff == NO_CHANGE && file_diff == -KING_CASTLE_MOVE)
    return canCastle(from_square_p, to_square_p, QUEEN_SIDE, move_piece); 
    
  if (rank_diff == NO_CHANGE && file_diff == +KING_CASTLE_MOVE)
    return canCastle(from_square_p, to_square_p, KING_SIDE, move_piece);
  
  return INVALID_MOVE;
}



Error King::canCastle(Square* from_square_p, Square* to_square_p, Castle castle, bool move_piece){
  // a king that has moved, loses its castling privileges. This takes
  // care of checking king is in the right square. If it has not moved
  // it must be in the e file & its color's first rank.
  if (has_moved)
    return INVALID_MOVE;

  // king cannot castle while in check
  if (from_square_p->isUnderAttack(color)) 
    return KING_IS_IN_CHECK;
  
  Square* rank[SQUARES_PER_SIDE];
  // get the squares in the same rank as the king
  from_square_p->getRank(rank);

  // king castles with rook in 1st file when castling queen side
  // king castes with rook in 8th file when castling king side
  int rook_square_file_i = (castle == QUEEN_SIDE)? MIN_INDEX: MAX_INDEX;
  Square* rook_square_p = rank[rook_square_file_i];
  
  // there must be a piece on this square
  if (!rook_square_p->hasPiece()) 
    return INVALID_MOVE;

  Piece* rook_square_piece_p = rook_square_p->getPiece();

  // piece must be a rook that has not moved of the same color as the
  // king. If the rook_square_piece has not moved, it must be the rook
  // of the correct color!
  if (rook_square_piece_p->hasMoved())
    return INVALID_MOVE;
  
  Square* path[SQUARES_PER_SIDE];
  // get path from the king to the rook it is castling with
  from_square_p->getPath(rook_square_p, path, type);

  // iterate through the squares in between king and rook.
  for (int i = 1; path[i] != rook_square_p; i++){
    // there cannot be a piece on that path
    if (path[i]->hasPiece()) 
      return PATH_OBSTRUCTED;
    
    // this pathway is activated only for the square the king travels
    // through on its way to castle.
    if (i < KING_CASTLE_MOVE && path[i]->isUnderAttack(color))
      // that square cannot be under attack
      return KING_IS_IN_CHECK; 
  }
  
  if (move_piece){
    // get pointer to rook's post-castling square
    int rook_castle_file_i = (castle == QUEEN_SIDE)? KING_FILE -1: KING_FILE + 1;
    Square* rook_castle_square_p = rank[rook_castle_file_i];
    
    // move rook to its post_castling square which we know is empty
    rook_castle_square_p->setPiece(rook_square_piece_p);
    
    // set old square's pointer to null
    rook_square_p->setPiece(0);
  }
    
  return NO_ERROR;

}


