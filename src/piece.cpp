// -*- C++ -*-
#include "piece.h"
#include "ChessBoard.h"
#include "square.h"
#include "utils.h"

// initializes static variable
int Piece::num_pieces = 0;

Piece::Piece(const Color color, const PieceType type)
  :color(color), has_moved(false), type(type){
  num_pieces++;
}


Error Piece::moveIsLegal(Square* from_square_p, Square* to_square_p, bool move_piece){
  // create square array for getPath method
  Square* path[SQUARES_PER_SIDE];
  if (!from_square_p->getPath(to_square_p, path, type))
    // there is no such path for this piece
    return INVALID_MOVE;
  
  for (int i = 1; path[i] != to_square_p; i++)
    if (path[i]->hasPiece())
      // this piece cannot go through another piece on its path
      return PATH_OBSTRUCTED;

  return NO_ERROR;
}

Error Piece::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not movint to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
    return TAKES_PIECE_OF_SAME_COLOR;
  
  // check if move is legal
  return moveIsLegal(from_square_p, to_square_p, move_piece);

}


void Piece::move(Square* from_square_p, Square* to_square_p){
  // calls canMove function with move_piece = true
  // see canMove documentation in piece.h
  canMove(from_square_p, to_square_p, true);

  // move piece
  to_square_p->destroyPiece();
  to_square_p->setPiece(this);
  from_square_p->setPiece(0);
}


bool Piece::squareOccupiedByFriendlyPiece(Square* square_p)const{
  if (square_p->hasPiece() && square_p->getPiece()->color == color)
    return true;
  return false;
}


std::ostream& operator<<(std::ostream& stream, Color color){
  if (color == WHITE)
    stream << "White";
  else
    stream << "Black";
  return stream;
}


std::ostream& operator<<(std::ostream& stream, PieceType type){
  switch(type){
  case PAWN:
    stream << "Pawn";
    break;
  case KNIGHT:
    stream << "Knight";
    break;
  case ROOK:
    stream << "Rook";
    break;
  case BISHOP:
    stream << "Bishop";
    break;
  case QUEEN:
    stream << "Queen";
    break;
  case KING:
    stream << "King";
    break;
  default:
    break;
  }
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Piece* piece_ptr){
  if (piece_ptr->getColor() == BLACK)
    // start bold font
    stream << "\e[1m";
  switch(piece_ptr->getType()){
  case PAWN:
    stream << 'P';
    break;
  case KNIGHT:
    stream << 'N';
    break;
  case ROOK:
    stream << 'R';
    break;
  case BISHOP:
    stream << 'B';
    break;
  case QUEEN:
    stream << 'Q';
    break;
  case KING:
    stream << 'K';
    break;
  default:
    break;
  }

  if (piece_ptr->getColor() == BLACK)
    // end bold font
    stream << "\e[0m";
  
  return stream;
}

