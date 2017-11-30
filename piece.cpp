// -*- C++ -*-
#include "piece.h"
#include "square.h"


// initializes static variable
int Piece::num_pieces = 0;


Piece::Piece(const Color color, const PieceType type)
  :color(color), has_moved(false), type(type){
  num_pieces++;
}


bool Piece::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){  
  Square* path[8];
  
  if (!from_square_p->getPath(to_square_p, path, type))
    // there is no such path for this piece
     return false;
  
  for (int i = 1; path[i] != to_square_p; i++)
    if (path[i]->hasPiece())
      // this piece cannot go through another piece on its path
      return false;

  if (move_piece){
    // we move the pieces
    to_square_p->destroyPiece();
    to_square_p->setPiece(this);
    from_square_p->setPiece(0);
  }
  
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
