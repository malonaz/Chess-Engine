// -*- C++ -*-
#include "ChessBoard.h"
#include "square.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "utils.h"

#include <iostream>

void ChessBoard::init(){
  color_to_play = WHITE;
  int file, rank;

  std::cout << "A new chess game is started!" << std::endl;
  
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

  // copie pointers to kings into kings_square_ptrs
  kings_square_ptrs[WHITE] = square_ptrs[WHITE_RANK1][KING_FILE];
  kings_square_ptrs[BLACK] = square_ptrs[BLACK_RANK1][KING_FILE];
}


void ChessBoard::destroySquares(){
  for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++){ 
      delete square_ptrs[rank][file]; 
    }
}


void ChessBoard::resetBoard(){
  destroySquares();
  init();
}


void ChessBoard::submitMove(const char* from_square, const char* to_square){
  if (!isValidSquare(from_square) || !isValidSquare(to_square))
    return;

  Square* from_square_p = getSquare(from_square);
  Square* to_square_p = getSquare(to_square);
  Piece* piece_p = from_square_p->getPiece();
  
  if (from_square_p->isEmpty()){
    std::cout << "There is no piece at position " << from_square << "!\n";
    return;
  }

  if (piece_p->getColor() != color_to_play){
    std::cout << "It is not " << piece_p->getColor() << "'s turn to move!\n";
    return;
  }
  
  bool to_square_empty = to_square_p->isEmpty();
  PieceType to_square_piece_type;
  Color to_square_piece_color;
  if (!to_square_empty){
    to_square_piece_type = to_square_p->getPiece()->getType();
    to_square_piece_color = to_square_p->getPiece()->getColor();
  }

  std::cout << piece_p;
  
  if (from_square_p->movePiece(to_square_p)){
    if (piece_p->getType() == KING)
      kings_square_ptrs[piece_p->getColor()] = to_square_p;

    if (piece_p->getType() == PAWN){
      Pawn* pawn = static_cast<Pawn*>(piece_p);
      if (pawn->canEnPassant(to_square_p, true))
	std::cout << " taking en passant ";
    }
    std::cout << " moves from " << from_square << " to " << to_square;

    if (!to_square_empty)
      std::cout << " taking " << to_square_piece_color << "'s " << to_square_piece_type;
    prepareNextTurn();
    std::cout << std::endl;
    return;
  }
  std::cout << " cannot move to " << to_square << "!\n";
}


void ChessBoard::prepareNextTurn(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
      if (!square_ptrs[rank][file]->isEmpty())
	if (square_ptrs[rank][file]->getPiece()->getColor() != color_to_play)
	  square_ptrs[rank][file]->getPiece()->update();

  color_to_play = (color_to_play == WHITE)? BLACK: WHITE;
  
  if (kingIsInCheck(color_to_play)){
    std::cout << std::endl << color_to_play << " is in check";
    if (cannotMove(color_to_play))
	std::cout << "mate";
  }  
}


Square* ChessBoard::getSquare(const char* sqr_str)const{
  int rank, file;
  rank = parseRank(sqr_str);
  file = parseFile(sqr_str);
  return square_ptrs[rank][file];
}


Square* ChessBoard::getSquare(int i_rank, int i_file)const{
  return square_ptrs[i_rank][i_file];
}


bool ChessBoard::kingIsInCheck(Color color){
  Square* current_square;
  
  for (int i_rank = MIN_INDEX; i_rank <= MAX_INDEX; i_rank++)
    for (int i_file = MIN_INDEX; i_file <= MAX_INDEX; i_file++){

      current_square = square_ptrs[i_rank][i_file];

      if (!current_square->isEmpty())
	if (current_square->getPiece()->getColor() != color)
	  if (current_square->getPiece()->
	      canMove(current_square, kings_square_ptrs[color]))
	    return true;
    }
  return false;
}


bool ChessBoard::cannotMove(Color color)const{
  Square* current_square;
  
  for (int i_rank = MIN_INDEX; i_rank <= MAX_INDEX; i_rank++)
    for (int i_file = MIN_INDEX; i_file <= MIN_INDEX; i_file++){

      current_square = square_ptrs[i_rank][i_file];
      
      if (!current_square->isEmpty())
	if (current_square->getPiece()->getColor() == color)
	  if (current_square->pieceCanMove())
	    return false;
    }
  return true;
}


void ChessBoard::printBoard()const{
  for (int i_rank = MAX_INDEX; i_rank >= MIN_INDEX; i_rank--){
    std::cout << HORIZONTAL_BAR  << std::endl;

    for (int i_file = MIN_INDEX; i_file <= MAX_INDEX; i_file++){
      std::cout << VERTICAL_BAR;
      
      Square* current_sqr = square_ptrs[i_rank][i_file];
      if (current_sqr->isEmpty())
	std::cout << ' ';
      else
	std::cout << current_sqr->getPiece();
    }
    std::cout << VERTICAL_BAR <<  std::endl;
  }
  std::cout << HORIZONTAL_BAR << std::endl;
}


void ChessBoard::printObjects()const{
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
}
