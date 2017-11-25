// -*- C++ -*-
#include "chessboard.h"
#include "pawn.h"
#include "utils.h"

#include <iostream>


void ChessBoard::destroySquares(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){ 
      delete square_ptrs[rank][file];
    }
}

void ChessBoard::init(){
  color_to_play = white;
  int file, rank;
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      square_ptrs[rank][file] = new Square(file, rank);
  
  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    square_ptrs[1][file]->setPiece(new Pawn(white));
    square_ptrs[6][file]->setPiece(new Pawn(black));
  }
}

void ChessBoard::resetBoard(){
  destroySquares();
  init();
}
    


void ChessBoard::submitMove(const char* source_sqr_str,
			   const char* dest_sqr_str){
  if (!isValidSquare(source_sqr_str) ||
      !isValidSquare(dest_sqr_str))
    return;

  Square* source_sqr = getSquare(source_sqr_str);
  Square* dest_sqr = getSquare(dest_sqr_str);

  if (source_sqr->isEmpty() ||
      !(source_sqr->getPiece()->getColor() == color_to_play))
    return;

  if (source_sqr->movePiece(dest_sqr))
    changeColorToPlay();
      
}

void ChessBoard::changeColorToPlay(){
  if (color_to_play == white)
    color_to_play = black;
  else
    color_to_play = white;
}
Square* ChessBoard::getSquare(const char* sqr_str)const{
  int rank, file;
  rank = getRank(sqr_str);
  file = getFile(sqr_str);
  return square_ptrs[rank][file];
}

void ChessBoard::printBoard(){
  for (int rank = MAX_INDEX; rank >= MIN_INDEX; rank--){
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      Square* current_sqr = square_ptrs[rank][file];
      if (current_sqr->isEmpty())
	std::cout << ' ';
      else
	std::cout << current_sqr->getPiece()->getID();
    }
    std::cout << std::endl;
  }
}


void ChessBoard::printObjects(){
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
}