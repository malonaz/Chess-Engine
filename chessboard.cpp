// -*- C++ -*-
#include "chessboard.h"
#include "square.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "utils.h"

#include <iostream>

#define WHITE 1
#define BLACK 0

void ChessBoard::destroySquares(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){ 
      delete square_ptrs[rank][file];
    }
}

void ChessBoard::init(){ // try to pass class to generic set piece ...
  white_to_play = true;
  int file, rank;
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      square_ptrs[rank][file] = new Square(this, file, rank);

  // set Pawns
  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    square_ptrs[WHITE_RANK2][file]->setPiece(new Pawn(WHITE));
    square_ptrs[BLACK_RANK2][file]->setPiece(new Pawn(BLACK));
  }

  // set Knights
  square_ptrs[WHITE_RANK1][KNIGHT1_FILE]->setPiece(new Knight(WHITE));
  square_ptrs[WHITE_RANK1][KNIGHT2_FILE]->setPiece(new Knight(WHITE));
  square_ptrs[BLACK_RANK1][KNIGHT1_FILE]->setPiece(new Knight(BLACK));
  square_ptrs[BLACK_RANK1][KNIGHT2_FILE]->setPiece(new Knight(BLACK));

  // set Rooks
  square_ptrs[WHITE_RANK1][ROOK1_FILE]->setPiece(new Rook(WHITE));
  square_ptrs[WHITE_RANK1][ROOK2_FILE]->setPiece(new Rook(WHITE));
  square_ptrs[BLACK_RANK1][ROOK1_FILE]->setPiece(new Rook(BLACK));
  square_ptrs[BLACK_RANK1][ROOK2_FILE]->setPiece(new Rook(BLACK));

  // set Bishops
  square_ptrs[WHITE_RANK1][BISHOP1_FILE]->setPiece(new Bishop(WHITE));
  square_ptrs[WHITE_RANK1][BISHOP2_FILE]->setPiece(new Bishop(WHITE));
  square_ptrs[BLACK_RANK1][BISHOP1_FILE]->setPiece(new Bishop(BLACK));
  square_ptrs[BLACK_RANK1][BISHOP2_FILE]->setPiece(new Bishop(BLACK));

  // set Queens & Kings
  square_ptrs[WHITE_RANK1][QUEEN_FILE]->setPiece(new Queen(WHITE));
  square_ptrs[WHITE_RANK1][KING_FILE]->setPiece(new King(WHITE));
  square_ptrs[BLACK_RANK1][QUEEN_FILE]->setPiece(new Queen(BLACK));
  square_ptrs[BLACK_RANK1][KING_FILE]->setPiece(new King(BLACK));
  
}

void ChessBoard::resetBoard(){
  destroySquares();
  init();
}


void ChessBoard::submitMove(const char* source_sqr_str,
			   const char* dest_sqr_str){
  if (!isValidSquare(source_sqr_str) || !isValidSquare(dest_sqr_str))
    return;

  Square* source_sqr = getSquare(source_sqr_str);
  Square* dest_sqr = getSquare(dest_sqr_str);

  // make sure it is the correct color to play
  if (source_sqr->isEmpty() ||
      source_sqr->getPiece()->isWhite() != white_to_play)
    return;
  
  if (source_sqr->movePiece(dest_sqr))
    prepareNextTurn();
  else
    std::cout << "invalid move: " << source_sqr_str <<  " to " << dest_sqr_str << std::endl;
      
}

void ChessBoard::prepareNextTurn(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
      if (!square_ptrs[rank][file]->isEmpty())
	if (square_ptrs[rank][file]->getPiece()->isWhite() != white_to_play)
	  square_ptrs[rank][file]->getPiece()->update();

  white_to_play = !white_to_play;
}
Square* ChessBoard::getSquare(const char* sqr_str)const{
  int rank, file;
  rank = parseRank(sqr_str);
  file = parseFile(sqr_str);
  return square_ptrs[rank][file];
}

void ChessBoard::getRow(int rank, Square** row){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    *(row + file) = square_ptrs[rank][file];
}


void ChessBoard::getColumn(int file, Square** column){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    *(column + rank) = square_ptrs[rank][file];
}


void ChessBoard::getDiagonal(int rank, int file, Square** diagonal,
			     bool rank_increasing){
  int current_rank = rank, current_file = file;
  int rank_increment = (rank_increasing)? 1 : -1;
    
  while (current_rank != MIN_INDEX && current_file != MIN_INDEX){
    current_rank -= rank_increment;
    current_file--;
  }
  
  int diagonal_index = 0;
  while (current_rank != MAX_INDEX && current_file != MAX_INDEX){
    diagonal[diagonal_index] = square_ptrs[current_rank][current_file];
    diagonal_index++;
    current_rank += rank_increment;
    current_file++;
  }
    
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
  std::cout << std::endl;
}


void ChessBoard::printObjects(){
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
}
