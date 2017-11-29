// -*- C++ -*-
#include "square.h"
#include "ChessBoard.h"
#include "utils.h"
#include "knight.h"
#include <iostream>


int Square::num_squares = 0;


Square::Square(ChessBoard* chessboard_p, int rank_i, int file_i)
  :chessboard_p(chessboard_p), rank_i(rank_i), file_i(file_i), piece_p(0){
  num_squares++;
}


Square::~Square(){
  destroyPiece();
  num_squares--;
}


const int Square::rankDiff(Square* dest_p) const{
  return dest_p->rank_i - rank_i;
}


const int Square::fileDiff(Square* dest_p) const{
  return dest_p->file_i - file_i;
}


int getPointerIndex(Square** pointers, Square* pointer){
  int index = 0;
  for (; pointers[index] != pointer; index++);
  return index;
}


// ???????????????????????????????????????
bool Square::getPath(Square* dest_p, Square** path, PieceType type){ // remove pieceType...
  int rank_diff = rankDiff(dest_p);
  int file_diff = fileDiff(dest_p);
  int moveDimension = getMoveDimension(rank_diff, file_diff);
  Square* raw_path[8] = {}; // set to null for getPointerIndex function
  
  if (moveDimension == HORIZONTAL && type != BISHOP)
    getRank(raw_path);
  
  else if (moveDimension == VERTICAL && type != BISHOP)
    getFile(raw_path);
  
  else if (moveDimension == DIAGONAL && type != ROOK)
    getDiagonal(dest_p, raw_path);
  
  else 
    return false; // no path

  // get indices of this & dest_p in raw_path
  int current_i = getPointerIndex(raw_path, this);
  int end_i = getPointerIndex(raw_path, dest_p);
  int incr = (current_i < end_i)? 1: -1;
  
  for (int i = 0; current_i != end_i + incr; current_i += incr, i++)
    path[i] = raw_path[current_i];
  
  return true;
}


void Square::getRank(Square** rank){
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
    rank[file_i] = chessboard_p->getSquare(rank_i, file_i);
}


void Square::getFile(Square** file){
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    file[rank_i] = chessboard_p->getSquare(rank_i, file_i);
}


Square* Square::getSquareBelow(const Color color) const{
  int rank_offset = (color == WHITE)? -1 : 1;
  return chessboard_p->getSquare(rank_i + rank_offset, file_i);
}


void Square::getDiagonal(Square* dest_p, Square** diagonal){
  bool rank_increasing = rankDiff(dest_p)*fileDiff(dest_p) > 0;

  int current_rank_i = rank_i, current_file_i = file_i;
  int rank_increment = (rank_increasing)? 1 : -1;
  int start_rank_i_limit = (rank_increasing)? MIN_INDEX: MAX_INDEX;
  
  while (current_rank_i != start_rank_i_limit && current_file_i != MIN_INDEX){
    current_rank_i -= rank_increment;
    current_file_i--;
  }
  
  int diagonal_i= 0;
  while (validIndex(current_rank_i) && validIndex(current_file_i)){
    diagonal[diagonal_i] = chessboard_p->getSquare(current_rank_i, current_file_i);
    diagonal_i++;
    current_rank_i += rank_increment;
    current_file_i++;
  }
}

void Square::setPiece(Piece* piece_p){
  this->piece_p = piece_p;
}

void Square::destroyPiece(){
  if (hasPiece()){
    delete piece_p;
    piece_p = 0; // set to NULL
  }
}

bool Square::movePiece(Square* dest_p){
  if (piece_p->canMove(this, dest_p))
    return piece_p->canMove(this, dest_p, true); // true because we want to move pieces
  return false;
}

bool Square::movePutsKingInCheck(Square* dest_p){
  Color player_color = piece_p->getColor();
  Piece* taken_piece_p = dest_p->piece_p;
  bool piece_is_king = chessboard_p->getKingSquareP(player_color) == this;
  
  if (piece_is_king)
    chessboard_p->setKingSquareP(dest_p);
  
  dest_p->piece_p = piece_p;
  piece_p = 0; // set to NULL

  
  bool kingIsInCheck = chessboard_p->kingIsInCheck(player_color);
  
  piece_p = dest_p->piece_p;
  dest_p->piece_p = taken_piece_p;

  if (piece_is_king)
    chessboard_p->setKingSquareP(this);
  
  return kingIsInCheck;
}

bool Square::hasPiece()const{
  if (piece_p == 0)
    return false;
  return true;
}


bool Square::pieceCanMove(){
  Square* dest_p;
  
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++){
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      dest_p = chessboard_p->getSquare(rank_i, file_i);
  
      if (piece_p->canMove(this, dest_p) && !movePutsKingInCheck(dest_p)){

	return true;
      }
    }
  }
  return false;
}


bool Square::isUnderAttack(Color player_color){
  bool this_square_has_a_piece = hasPiece();
  Square* current_square;
  
  if (!this_square_has_a_piece) // set a dummy piece here to check if under attack
    setPiece(new Knight(player_color));

  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){

      current_square = chessboard_p->getSquare(rank_i, file_i);

      if (current_square->hasPiece())
	if (current_square->getPiece()->getColor() != player_color)
	  if (current_square->getPiece()->
	      canMove(current_square, this)){
	    if (!this_square_has_a_piece)
	      destroyPiece();
	    return true;
	  }
    }
  
  if (!this_square_has_a_piece)
    destroyPiece();
  
  return false;
}
