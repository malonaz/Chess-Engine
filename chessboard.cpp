// -*- C++ -*-
#include "chessboard.h"


Chessboard::Chessboard()
  :white_turn(true){
  for (int file = 0; file < 8; file++)
    for (int rank = 0; rank <8; rank++)
      squares[rank][file] = new Square(file, rank);

  
  
}



Chessboard::~Chessboard(){
  for (int file = 0; file < 8; file++)
    for (int rank; rank < 8; rank++)
      delete squares[rank][file];
    
}

