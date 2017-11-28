// -*- C++ -*-
#include "square.h"
#include "ChessBoard.h"
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

bool Square::getPath(Square* sqr_dest_ptr, Square** path, PieceType piece_type){
  int rank_shift = ranksTo(sqr_dest_ptr);
  int file_shift = filesTo(sqr_dest_ptr);
  int moveDimension = getMoveDimension(rank_shift, file_shift);
  Square* raw_path[8]= {};
  
  if (moveDimension == HORIZONTAL && piece_type != BISHOP)
    getRow(raw_path);
  else if (moveDimension == VERTICAL && piece_type != BISHOP)
    getColumn(raw_path);
  else if (moveDimension == DIAGONAL && piece_type != ROOK)
    getDiagonal(sqr_dest_ptr, raw_path);
  else 
    return false;

  int current_index = getPointerIndex(raw_path, this);
  int end_index = getPointerIndex(raw_path, sqr_dest_ptr);
  int increment = (current_index < end_index)? 1: -1;
  for (int i = 0; current_index != end_index + increment; current_index += increment, i++)
    path[i] = raw_path[current_index];
  
  return true;
}

void Square::getRow(Square** rank_arr){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    rank_arr[file] = chessboard->getSquare(rank, file);
}

void Square::getColumn(Square** file_arr){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    file_arr[rank] = chessboard->getSquare(rank, file);
}

void Square::getDiagonal(Square* sqr_dest_ptr, Square** diagonal_arr){
  bool rank_increasing = ranksTo(sqr_dest_ptr)*filesTo(sqr_dest_ptr) > 0;

  int current_rank = rank, current_file = file;
  int rank_increment = (rank_increasing)? 1 : -1;
  int start_rank_limit = (rank_increasing)? MIN_INDEX: MAX_INDEX;
  
  while (current_rank != start_rank_limit && current_file != MIN_INDEX){
    current_rank -= rank_increment;
    current_file--;
  }
  
  int diagonal_arr_index = 0;
  while (validIndex(current_rank) && validIndex(current_file)){
    diagonal_arr[diagonal_arr_index] = chessboard->getSquare(current_rank, current_file);
    diagonal_arr_index++;
    current_rank += rank_increment;
    current_file++;
  }
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
      sqr_dest_ptr->getPiece()->getColor() == getPiece()->getColor())
    return false;
  
  if (piece_ptr->canMove(this, sqr_dest_ptr)){
    if (movePutsKingInCheck(sqr_dest_ptr))
      return false;
    
    piece_ptr->setToMoved();
    sqr_dest_ptr->setPiece(piece_ptr);
    piece_ptr = 0; // set to NULL
    return true;
  }
  
  return false;
}

bool Square::movePutsKingInCheck(Square* sqr_dest_ptr){
  Color player_color = piece_ptr->getColor();
  Piece* taken_piece_ptr = sqr_dest_ptr->piece_ptr;
  sqr_dest_ptr->piece_ptr = piece_ptr;
  piece_ptr = 0; // set to NULL

  bool kingIsInCheck = chessboard->kingIsInCheck(player_color);

  piece_ptr = sqr_dest_ptr->piece_ptr;
  sqr_dest_ptr->piece_ptr = taken_piece_ptr;

  
  return kingIsInCheck;
}

bool Square::isEmpty()const{
  if (piece_ptr == 0)
    return true;
  return false;
}


bool Square::pieceCanMove(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      Square* to_square = chessboard->getSquare(rank, file);
      if (piece_ptr->canMove(this, to_square) &&
	  !movePutsKingInCheck(to_square))
	return true;	   
    }
  }
  return false;
}
