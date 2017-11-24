// -*- C++ -*-
#include "square.h"
#include <iostream>

Square::Square(int file, int rank)
  :file(file), rank(rank){}


Square::~Square(){
  destroyPiece();
}

const int Square::filesTo(Square* sqr_dest_ptr) const{
  return sqr_dest_ptr->file - file;
}


const int Square::ranksTo(Square* sqr_dest_ptr) const{
  return sqr_dest_ptr->rank - rank;
}

void Square::setPiece(Piece* piece_ptr){
  this->piece_ptr = piece_ptr;
  piece_ptr->setSquare(this);
}


void Square::destroyPiece(){
  if (!isEmpty()){
    delete piece_ptr;
    piece_ptr = 0; // set to NULL
  }
}

bool Square::movePiece(Square* sqr_dest_ptr){
  if (!isEmpty() && piece_ptr->isLegalMove(sqr_dest_ptr)){
    sqr_dest_ptr->destroyPiece();
    sqr_dest_ptr->setPiece(piece_ptr);
    piece_ptr = 0; // set to NULL
    return true;
  }
  return false;
}


bool Square::isEmpty()const{
  if (piece_ptr == 0)
    return true;
  return false;
}
