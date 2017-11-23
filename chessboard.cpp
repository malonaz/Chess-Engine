// -*- C++ -*-
#include "chessboard.h"
#include "pawn.h"

Chessboard::Chessboard()
  :white_turn(true){
  int file, rank;
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      squares[rank][file] = new Square(file, rank);

  
  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    squares[MIN_INDEX][file]->setPiece(new Pawn(white));
    squares[MAX_INDEX][file]->setPiece(new Pawn(black));
  }
}

Chessboard::~Chessboard(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank; rank <= MAX_INDEX; rank++){
      delete squares[rank][file]->getPiece(); // eventually transfer this responsability to square destructor
      delete squares[rank][file];
    }
}
