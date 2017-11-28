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


void ChessBoard::destroySquares(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){ 
      delete square_ptrs[rank][file];
    }
}

void ChessBoard::init(){ // try to pass class to generic set piece ...
  color_to_play = WHITE;
  int file, rank;

  std::cout << "A New chess game is started!" << std::endl;
  
  // create Squares
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      square_ptrs[rank][file] = new Square(this, file, rank);
  
  // create and set Pawns
  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    square_ptrs[WHITE_RANK2][file]->setPiece(new Pawn(WHITE));
    square_ptrs[BLACK_RANK2][file]->setPiece(new Pawn(BLACK));
  }

  // create and set Knights
  square_ptrs[WHITE_RANK1][KNIGHT1_FILE]->setPiece(new Knight(WHITE));
  square_ptrs[WHITE_RANK1][KNIGHT2_FILE]->setPiece(new Knight(WHITE));
  square_ptrs[BLACK_RANK1][KNIGHT1_FILE]->setPiece(new Knight(BLACK));
  square_ptrs[BLACK_RANK1][KNIGHT2_FILE]->setPiece(new Knight(BLACK));

  // create and set Rooks
  square_ptrs[WHITE_RANK1][ROOK1_FILE]->setPiece(new Rook(WHITE));
  square_ptrs[WHITE_RANK1][ROOK2_FILE]->setPiece(new Rook(WHITE));
  square_ptrs[BLACK_RANK1][ROOK1_FILE]->setPiece(new Rook(BLACK));
  square_ptrs[BLACK_RANK1][ROOK2_FILE]->setPiece(new Rook(BLACK));

  // create and set Bishops
  square_ptrs[WHITE_RANK1][BISHOP1_FILE]->setPiece(new Bishop(WHITE));
  square_ptrs[WHITE_RANK1][BISHOP2_FILE]->setPiece(new Bishop(WHITE));
  square_ptrs[BLACK_RANK1][BISHOP1_FILE]->setPiece(new Bishop(BLACK));
  square_ptrs[BLACK_RANK1][BISHOP2_FILE]->setPiece(new Bishop(BLACK));

  // create and set Queens & Kings
  square_ptrs[WHITE_RANK1][QUEEN_FILE]->setPiece(new Queen(WHITE));
  square_ptrs[WHITE_RANK1][KING_FILE]->setPiece(new King(WHITE));
  square_ptrs[BLACK_RANK1][QUEEN_FILE]->setPiece(new Queen(BLACK));
  square_ptrs[BLACK_RANK1][KING_FILE]->setPiece(new King(BLACK));

  kings_square_ptrs[WHITE] = square_ptrs[WHITE_RANK1][KING_FILE];
  kings_square_ptrs[BLACK] = square_ptrs[BLACK_RANK1][KING_FILE];
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
  Piece* piece_ptr = source_sqr->getPiece();
  
  // make sure it is the correct color to play
  if (source_sqr->isEmpty()){
    std::cout << "There is no piece at position " << source_sqr_str << "!" << std::endl;
    return;
  }

  if (piece_ptr->getColor() != color_to_play){
    std::cout << "It is not " << piece_ptr->getColor() << "'s turn to move!" << std::endl; 
    return;
  }

  std::cout << piece_ptr->getColor() << "'s " << piece_ptr->getType();
  if (source_sqr->movePiece(dest_sqr)){
    if (piece_ptr->getType() == KING)
      kings_square_ptrs[piece_ptr->getColor()] = dest_sqr;
    prepareNextTurn();
    std::cout << " moves from " << source_sqr_str << " to " << dest_sqr_str;
  }else{
    std::cout << " cannot move to " << dest_sqr_str << "!";
  }
  std::cout << std::endl;
}

void ChessBoard::prepareNextTurn(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
      if (!square_ptrs[rank][file]->isEmpty())
	if (square_ptrs[rank][file]->getPiece()->getColor() != color_to_play)
	  square_ptrs[rank][file]->getPiece()->update();

  color_to_play = (color_to_play == WHITE)? BLACK: WHITE;
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
  int start_rank_limit = (rank_increasing)? MIN_INDEX: MAX_INDEX;
  
  while (current_rank != start_rank_limit && current_file != MIN_INDEX){
    current_rank -= rank_increment;
    current_file--;
  }
  
  int diagonal_index = 0;
  while (validIndex(current_rank) && validIndex(current_file)){
    diagonal[diagonal_index] = square_ptrs[current_rank][current_file];
    diagonal_index++;
    current_rank += rank_increment;
    current_file++;
  }
    
}

bool ChessBoard::kingIsInCheck(Color color){
  Square* current_square;
  Piece* current_piece;
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      current_square = square_ptrs[rank][file];
      if (current_square->isEmpty())
	continue;
      
      current_piece = current_square->getPiece();
      if (current_piece->getColor() == color)
	continue;
      
      if (current_piece->canMove(current_square, kings_square_ptrs[color]))
	return true;	
    }
  return false;
}
				 


void ChessBoard::printBoard(){
  for (int rank = MAX_INDEX; rank >= MIN_INDEX; rank--){
    std::cout << HORIZONTAL_BAR  << std::endl;
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      std::cout << VERTICAL_BAR;
      Square* current_sqr = square_ptrs[rank][file];
      if (current_sqr->isEmpty())
	std::cout << ' ';
      else
	std::cout << current_sqr->getPiece();
    }
    
    std::cout << VERTICAL_BAR <<  std::endl;
  }
  std::cout << HORIZONTAL_BAR << std::endl;
}


void ChessBoard::printObjects(){
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
}
