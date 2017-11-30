// -*- C++ -*-
#include "knight.h"
#include "ChessBoard.h"
#include "square.h"
#include "utils.h"
#include <iostream>


bool Knight::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int file_diff = from_square_p->fileDiff(to_square_p);
  
  // only 8 (x, y) integer solutions to x^2 + y^2 = 5 which correspond
  // to the 8 knight moves
  int moveMagnitudeSquared = getMoveMagnitudeSquared(rank_diff, file_diff);
  
  if (moveMagnitudeSquared != KNIGHT_MOVE_MAGNITUDE_SQUARED)
    return false;

  // save pointer to the piece of the square we are moving to
  Piece* to_square_piece_p = to_square_p->getPiece();

  // move pieces
  to_square_p->setPiece(this);
  from_square_p->setPiece(0);

  // Get pointer to chessboard 
  ChessBoard* chessboard_p = from_square_p->getChessBoard();
  // check if new position discovers a check
  bool king_in_check = chessboard_p->kingIsInCheck(color);

  if (move_piece){
    // delete captured piece
    delete to_square_piece_p;
    
  }else{
    // return pieces to their prior squares
    from_square_p->setPiece(to_square_p->getPiece());
    to_square_p->setPiece(to_square_piece_p);
  }

  // return true if king is not in check
  return (!king_in_check);;
}
 
