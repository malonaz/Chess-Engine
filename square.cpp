// -*- C++ -*-
#include "square.h"
#include "chessboard.h"
#include "piece.h"
#include "utils.h"
#include <iostream>

int Square::num_squares = 0;

Square::Square(ChessBoard* chessboard, int file, int rank)
  :chessboard(chessboard),file(file), rank(rank), piece_ptr(0){
  num_squares++;
}


Square::~Square(){
  num_squares--;
  destroyPiece();
}

const int Square::filesTo(Square* sqr_dest_ptr) const{
  return sqr_dest_ptr->file - file;
}

const int Square::ranksTo(Square* sqr_dest_ptr) const{
  return sqr_dest_ptr->rank - rank;
}

int getPointerIndex(Square** pointers, Square* pointer){
  int index = 0;
  for (; pointers[index] != pointer; index++);
  return index;
}

bool Square::getPath(Square* sqr_dest_ptr, Square** path, bool no_diagonal){
  int rank_shift = ranksTo(sqr_dest_ptr);
  int file_shift = filesTo(sqr_dest_ptr);
  int moveDimension = getMoveDimension(rank_shift, file_shift);
  Square* raw_path[8]= {};
  
  if (moveDimension == HORIZONTAL)
    getRow(raw_path);
  else if (moveDimension == VERTICAL)
    getColumn(raw_path);
  else if (moveDimension == DIAGONAL && !no_diagonal)
    return false; // must implement;
  else 
    return false;

  int current_index = getPointerIndex(raw_path, this);
  int end_index = getPointerIndex(raw_path, sqr_dest_ptr);
  int increment = (current_index < end_index)? 1: -1; 
  for (int i = 0; current_index <= end_index; current_index += increment, i++)
    path[i] = raw_path[current_index];
  
  return true;
}

void Square::getRow(Square** row){
  chessboard->getRow(rank, row);
}

void Square::getColumn(Square** column){
  chessboard->getColumn(file, column);
}

void Square::setPiece(Piece* piece_ptr){
  destroyPiece();
  this->piece_ptr = piece_ptr;
}

void Square::destroyPiece(){
  if (!isEmpty()){
    delete piece_ptr;
    piece_ptr = 0; // set to NULL
  }
}

bool Square::movePiece(Square* sqr_dest_ptr){
  // make sure you are not moving a piece on top of another of same color
  if (!sqr_dest_ptr-> isEmpty() &&
      sqr_dest_ptr->getPiece()->isWhite() == getPiece()->isWhite())
    return false;
  
  if (piece_ptr->move(this, sqr_dest_ptr)){
    piece_ptr->setToMoved();
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


