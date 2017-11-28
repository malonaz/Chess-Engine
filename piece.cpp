// -*- C++ -*-
#include "piece.h"
#include "square.h"

int Piece::num_pieces = 0;

Piece::Piece(const Color color, const PieceType type)
  :color(color), has_moved(false), type(type){
  num_pieces++;
}


bool Piece::canMove(Square* sqr_source_ptr, Square* sqr_dest_ptr){  
  Square* path[8];
  
  if (!sqr_source_ptr->getPath(sqr_dest_ptr, path, type))
     return false;
  
  for (int i = 1; path[i] != sqr_dest_ptr; i++)
    if (!path[i]->isEmpty())
      return false;
  
  return true;
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
    stream << "Knight";
    break;
  }
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Piece* piece_ptr){
  if (piece_ptr->getColor() == BLACK)
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
  }

  if (piece_ptr->getColor() == BLACK)
    stream << "\e[0m";
  return stream;
}

