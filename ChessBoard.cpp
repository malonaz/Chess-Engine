// -*- C++ -*-
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "utils.h"

#include <iostream>

void ChessBoard::init(){
  // initialize members
  color_to_play = WHITE;
  state = PLAYING_GAME;

  // output new game start to std stream
  std::cout << "A new chess game is started!" << std::endl;


  int file, rank;
  // create Squares
  for (file = MIN_INDEX; file <= MAX_INDEX; file++)
    for (rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
      square_ps[rank][file] = new Square(this, rank, file);
  
  // create and set Pawns
  for (file = MIN_INDEX; file <= MAX_INDEX; file++){
    square_ps[WHITE_RANK2][file]->setPiece(new Pawn(WHITE));
    square_ps[BLACK_RANK2][file]->setPiece(new Pawn(BLACK));
  }

  // create and set Knights
  square_ps[WHITE_RANK1][KNIGHT1_FILE]->setPiece(new Knight(WHITE));
  square_ps[WHITE_RANK1][KNIGHT2_FILE]->setPiece(new Knight(WHITE));
  square_ps[BLACK_RANK1][KNIGHT1_FILE]->setPiece(new Knight(BLACK));
  square_ps[BLACK_RANK1][KNIGHT2_FILE]->setPiece(new Knight(BLACK));

  // create and set Rooks
  square_ps[WHITE_RANK1][ROOK1_FILE]->setPiece(new Piece(WHITE, ROOK));
  square_ps[WHITE_RANK1][ROOK2_FILE]->setPiece(new Piece(WHITE, ROOK));
  square_ps[BLACK_RANK1][ROOK1_FILE]->setPiece(new Piece(BLACK, ROOK));
  square_ps[BLACK_RANK1][ROOK2_FILE]->setPiece(new Piece(BLACK, ROOK));

  // create and set Bishops
  square_ps[WHITE_RANK1][BISHOP1_FILE]->setPiece(new Piece(WHITE, BISHOP));
  square_ps[WHITE_RANK1][BISHOP2_FILE]->setPiece(new Piece(WHITE, BISHOP));
  square_ps[BLACK_RANK1][BISHOP1_FILE]->setPiece(new Piece(BLACK, BISHOP));
  square_ps[BLACK_RANK1][BISHOP2_FILE]->setPiece(new Piece(BLACK, BISHOP));

  // create and set Queens & Kings
  square_ps[WHITE_RANK1][QUEEN_FILE]->setPiece(new Piece(WHITE, QUEEN));
  square_ps[WHITE_RANK1][KING_FILE]->setPiece(new King(WHITE));
  square_ps[BLACK_RANK1][QUEEN_FILE]->setPiece(new Piece(BLACK, QUEEN));
  square_ps[BLACK_RANK1][KING_FILE]->setPiece(new King(BLACK));

  // copie pointers to kings into kings_square_ps
  kings_square_ps[WHITE] = square_ps[WHITE_RANK1][KING_FILE];
  kings_square_ps[BLACK] = square_ps[BLACK_RANK1][KING_FILE];
}


void ChessBoard::destroySquares(){
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
    for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++){
      // square destructor handle deallocating Pieces memory
      delete square_ps[rank_i][file_i];
      // nulls pointers
      square_ps[rank_i][file_i] = 0;
    }
}


void ChessBoard::resetBoard(){
  // deallocates memory to squares and pieces, then recreates them
  destroySquares();
  init();
}


Error ChessBoard::submitMove(const char* from_square, const char* to_square){
  if (state != PLAYING_GAME){
    std::cout << "Game is over!\n";
    return GAME_IS_OVER;
  }
  
  // check inputs correspond to valid squares
  if (!isValidSquare(from_square) || !isValidSquare(to_square))
    return INVALID_SQUARE;
  
  // parse squares
  Square* from_square_p = getSquare(from_square); 
  Square* to_square_p = getSquare(to_square);
  Piece* moving_piece_p = from_square_p->getPiece();

  // check piece present
  if (!from_square_p->hasPiece()){
    std::cout << "There is no piece at position " << from_square << "!\n";
    return EMPTY_SQUARE;
  }
  
  // check piece moving is of the color to play 
  if (moving_piece_p->getColor() != color_to_play){ 
    std::cout << "It is not " << moving_piece_p->getColor();
    std::cout << "'s turn to move!\n";
    return MOVE_OUT_OF_TURN;
  }

  // get destination square piece information
  bool to_square_has_piece = to_square_p->hasPiece();
  PieceType captured_piece_type;
  Color captured_piece_color;
  
  if (to_square_has_piece){
    captured_piece_type = to_square_p->getPiece()->getType();
    captured_piece_color = to_square_p->getPiece()->getColor();
  }

  // output move info to std stream
  std::cout << color_to_play  << "'s " << moving_piece_p->getType();

  Error move = from_square_p->movePiece(to_square_p);
  if (move == NO_ERROR){
    // move succeeded
    
    // update king square pointer if needed
    if (moving_piece_p->getType() == KING) 
      kings_square_ps[color_to_play] = to_square_p;

    // output successful move to std stream
    std::cout << " moves from " << from_square << " to " << to_square;

    // check if a piece was captured
    if (to_square_has_piece){
      // output capture to std output stream
      std::cout << " taking " << captured_piece_color << "'s ";
      std::cout << captured_piece_type;
    }
    
    prepareNextTurn();
    
  }else{    
  // move is illegal or impossible. output to std stream
  std::cout << " cannot move to " << to_square << std::endl;
  }
  
  return move;

}


void ChessBoard::prepareNextTurn(){
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++)
      if (square_ps[rank][file]->hasPiece())
	if (square_ps[rank][file]->getPiece()->getColor() != color_to_play)
	  square_ps[rank][file]->getPiece()->update();

  color_to_play = (color_to_play == WHITE)? BLACK: WHITE;

  bool player_can_move = playerCanMove(color_to_play);
  
  if (kingIsInCheck(color_to_play)){
    std::cout << std::endl << color_to_play << " is in check";
	
    if (!player_can_move){
	std::cout << "mate";
	// update game state
	state = CHECKMATE;
    }
  }else{
    if (!playerCanMove(color_to_play)){
      std::cout <<  "\nstalemate";
      // update game state
      state = STALEMATE;
    }
  }
  
  std::cout << std::endl;
}


Square* ChessBoard::getSquare(const char* sqr_str) const{
  int rank, file;
  // parsing functions are located in utils
  rank = parseRank(sqr_str);
  file = parseFile(sqr_str);
  return square_ps[rank][file];
}


Square* ChessBoard::getSquare(int rank_i, int file_i) const{
  return square_ps[rank_i][file_i];
}


void ChessBoard::setKingSquareP(Color king_color, Square* king_square_p){
  kings_square_ps[king_color] = king_square_p;
}


bool ChessBoard::kingIsInCheck(Color color){
  return kings_square_ps[color]->isUnderAttack(color);
}


bool ChessBoard::playerCanMove(Color color) const{
  Square* current_square;
  
  // iterate through all squares of the chessboard
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++){
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      
      current_square = square_ps[rank_i][file_i];

      // check square if current_square has a piece of the 
      // given color that can move
      if (current_square->hasPiece())
	if (current_square->getPiece()->getColor() == color)
	  if (current_square->pieceCanMove())
	    return true;
	
    }
  }

  // no piece of the given color can move
  return false;
}


void ChessBoard::printBoard() const{
  for (int rank_i = MAX_INDEX; rank_i >= MIN_INDEX; rank_i--){
    std::cout << HORIZONTAL_BAR  << std::endl;

    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      std::cout << VERTICAL_BAR;

      Square* current_sqr = square_ps[rank_i][file_i];
      
      if (!current_sqr->hasPiece())
	std::cout << ' ';
      else
	std::cout << current_sqr->getPiece();
    }
    std::cout << VERTICAL_BAR <<  std::endl;
  }
  std::cout << HORIZONTAL_BAR;
  printObjects();
  std::cout << "\n\n\n";
}

void ChessBoard::printObjects()const{
  std::cout << "\nNumber of Squares: " << Square::num_squares << '\n';
  std::cout << "Number of Pieces: " << Piece::num_pieces << '\n';
}
