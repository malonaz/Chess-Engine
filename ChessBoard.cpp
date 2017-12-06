// -*- C++ -*-
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "utils.h"

#include <iostream>



ChessBoard::ChessBoard(){  
  
  // initiate Squares
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
    for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
      squares[rank_i][file_i].init(this, rank_i, file_i);

  init();

}


void ChessBoard::init(){
  // initialize members
  color_to_play = WHITE;
  state = PLAYING_GAME;

  // output new game start to std stream
  std::cout << "A new chess game is started!" << std::endl;
   
  // create and set Pawns
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
    squares[WHITE_RANK2][file_i].setPiece(new Pawn(WHITE));
    squares[BLACK_RANK2][file_i].setPiece(new Pawn(BLACK));
  }

  // create and set Knights
  squares[WHITE_RANK1][KNIGHT1_FILE].setPiece(new Knight(WHITE));
  squares[WHITE_RANK1][KNIGHT2_FILE].setPiece(new Knight(WHITE));
  squares[BLACK_RANK1][KNIGHT1_FILE].setPiece(new Knight(BLACK));
  squares[BLACK_RANK1][KNIGHT2_FILE].setPiece(new Knight(BLACK));

  // create and set Rooks
  squares[WHITE_RANK1][ROOK1_FILE].setPiece(new Piece(WHITE, ROOK));
  squares[WHITE_RANK1][ROOK2_FILE].setPiece(new Piece(WHITE, ROOK));
  squares[BLACK_RANK1][ROOK1_FILE].setPiece(new Piece(BLACK, ROOK));
  squares[BLACK_RANK1][ROOK2_FILE].setPiece(new Piece(BLACK, ROOK));

  // create and set Bishops
  squares[WHITE_RANK1][BISHOP1_FILE].setPiece(new Piece(WHITE, BISHOP));
  squares[WHITE_RANK1][BISHOP2_FILE].setPiece(new Piece(WHITE, BISHOP));
  squares[BLACK_RANK1][BISHOP1_FILE].setPiece(new Piece(BLACK, BISHOP));
  squares[BLACK_RANK1][BISHOP2_FILE].setPiece(new Piece(BLACK, BISHOP));

  // create and set Queens & Kings
  squares[WHITE_RANK1][QUEEN_FILE].setPiece(new Piece(WHITE, QUEEN));
  squares[WHITE_RANK1][KING_FILE].setPiece(new King(WHITE));
  squares[BLACK_RANK1][QUEEN_FILE].setPiece(new Piece(BLACK, QUEEN));
  squares[BLACK_RANK1][KING_FILE].setPiece(new King(BLACK));

  // copie pointers to kings into kings_square_ps
  kings_square_ps[WHITE] = &squares[WHITE_RANK1][KING_FILE];
  kings_square_ps[BLACK] = &squares[BLACK_RANK1][KING_FILE];
}


void ChessBoard::freePieces(){
  // delete pieces and null piece pointers
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
    for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
      squares[rank_i][file_i].destroyPiece();
}


void ChessBoard::resetBoard(){
  // delete pieces, then call init to create new pieces and set them
  // on the appropriate squares.
  freePieces();
  init();
}


Error ChessBoard::submitMove(const char* from_square, const char* to_square){
  if (state != PLAYING_GAME){
    std::cout << "Game is over!\n";
    return GAME_IS_OVER;
  }
  
  // inputs must correspond to valid squares
  if (!isValidSquare(from_square) || !isValidSquare(to_square))
    return INVALID_SQUARE;
  
  // parse Squares from inputs and get the from square's piece pointer
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

  Error error = from_square_p->movePiece(to_square_p);
  if (error == NO_ERROR){
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
    
    // process turn
    prepareNextTurn();
    
  }else{    
  // move is illegal or impossible. output to std stream
  std::cout << " cannot move to " << to_square << std::endl;
  }
  
  return error;
}


void ChessBoard::prepareNextTurn(){
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
      if (squares[rank_i][file_i].hasPiece())
	if (squares[rank_i][file_i].getPiece()->getColor() != color_to_play)
	  squares[rank_i][file_i].getPiece()->update();

  // change color to play next
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


Square* ChessBoard::getSquare(const char* sqr_str) {
  // parsing functions are located in utils
  int rank_i = parseRank(sqr_str);
  int file_i = parseFile(sqr_str);
  return &squares[rank_i][file_i];
}


Square* ChessBoard::getSquare(int rank_i, int file_i) {
  return &squares[rank_i][file_i];
}


void ChessBoard::setKingSquareP(Color king_color, Square* king_square_p){
  kings_square_ps[king_color] = king_square_p;
}


bool ChessBoard::kingIsInCheck(Color color){
  return kings_square_ps[color]->isUnderAttack(color);
}


bool ChessBoard::playerCanMove(Color color){
  Square* current_square;
  
  // iterate through all squares of the chessboard
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++){
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      
      current_square = &squares[rank_i][file_i];

      // check square if current_square has a piece of the given color
      if (current_square->hasPiece())
	if (current_square->getPiece()->getColor() == color)
	  // check piece can move
	  if (current_square->pieceCanMove())
	    return true;
	
    }
  }

  // no piece of the given color can move
  return false;
}


void ChessBoard::printBoard() {
  for (int rank_i = MAX_INDEX; rank_i >= MIN_INDEX; rank_i--){
    std::cout << HORIZONTAL_BAR  << std::endl;

    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      std::cout << VERTICAL_BAR;

      Square* current_sqr = &squares[rank_i][file_i];
      
      if (!current_sqr->hasPiece())
	std::cout << ' ';
      else
	// see utils for square pointer << operator overload
	std::cout << current_sqr->getPiece();
    }
    std::cout << VERTICAL_BAR <<  std::endl;
  }
  std::cout << HORIZONTAL_BAR;
  // print number of Squares and Pieces
  printObjects();
  std::cout << "\n\n\n";
}

void ChessBoard::printObjects()const{
  std::cout << "\nNumber of Squares: " << Square::num_squares << '\n';
  std::cout << "Number of Pieces: " << Piece::num_pieces << '\n';
}
