// -*- C++ -*-
#include "chessboard.h"
#include "pawn.h"

#include <iostream>
Chessboard::Chessboard()
  :white_turn(true){
  int file, rank;
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      square_ptrs[rank][file] = new Square(file, rank);

  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    square_ptrs[1][file]->setPiece(new Pawn(white));
    square_ptrs[6][file]->setPiece(new Pawn(black));
  }
}

Chessboard::~Chessboard(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank; rank <= MAX_INDEX; rank++){ 
      delete square_ptrs[rank][file];
    }
}


void Chessboard::printBoard(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      Square* current_sqr = square_ptrs[rank][file];
      if (current_sqr->isEmpty())
	std::cout << ' ';
      else
	std::cout << current_sqr->getPiece()->getRepr();
    }
    std::cout << std::endl;
  }
}
