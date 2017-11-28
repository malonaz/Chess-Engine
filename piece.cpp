// -*- C++ -*-
#include "piece.h"
#include "square.h"

int Piece::num_pieces = 0;

Piece::Piece(const Color color, const PieceType type)
  :color(color), has_moved(false), type(type){
  num_pieces++;
}


bool Piece::canMove(Square* from_square_p, Square* to_square_p){  
  Square* path[8];
  if (!from_square_p->getPath(to_square_p, path, type))
     return false;
  
  for (int i = 1; path[i] != to_square_p; i++)
    if (path[i]->hasPiece())
      return false;

  return true;
}


std::ostream& operator<<(std::ostream& stream, Color color){
  if (color == WHITE)
    stream << "White's";
  else
    stream << "Black's";
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Piece* piece_p){
  if (piece_p->color == WHITE)
    stream << "White 's ";
  else
    stream << "Black 's ";
  
  switch(piece_p->type){
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
    stream << "Knight";
    break;
  }
  return stream;
}


