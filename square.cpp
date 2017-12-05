// -*- C++ -*-
#include "square.h"
#include "ChessBoard.h"
#include "piece.h"
#include "utils.h"

// initialize static variable
int Square::num_squares = 0;


void Square::init(ChessBoard* chessboard_p, int rank_i, int file_i){
  this->chessboard_p = chessboard_p;
  this->rank_i = rank_i;
  this->file_i = file_i;
  this->piece_p = 0; // set to null
  num_squares++;
}


Square::~Square(){
  // frees memory allocated to the piece at piece_p if it has one
  destroyPiece();
  num_squares--;
}


const int Square::rankDiff(Square* to_square_p) const{
  return to_square_p->rank_i - rank_i;
}


const int Square::fileDiff(Square* to_square_p) const{
  return to_square_p->file_i - file_i;
}


bool Square::getPath(Square* to_square_p, Square** path, PieceType type){
  int rank_diff = rankDiff(to_square_p);
  int file_diff = fileDiff(to_square_p);
  Dimension moveDimension = getMoveDimension(rank_diff, file_diff);
  // set raw_path pointers to null for getPointerIndex function requirement
  Square* raw_path[8] = {};
  
  if (moveDimension == HORIZONTAL && type != BISHOP)
    getRank(raw_path);
  
  else if (moveDimension == VERTICAL && type != BISHOP)
    getFile(raw_path);
  
  else if (moveDimension == DIAGONAL && type != ROOK)
    getDiagonal(to_square_p, raw_path);
  
  else
    // no path
    return false; 

  // get indices of this & to_square_p in raw_path
  int current_i = getPointerIndex(raw_path, this);
  int end_i = getPointerIndex(raw_path, to_square_p);
  
  // we now want to increment or decrement current_i to move it towards
  // end_i, we call this increment or decrement step
  int step = (current_i < end_i)? 1: -1;

  // copy pointers of squares on the path [this, to_square_p] into path
  // longest path is guaranteed <= 8 & guaranteed to fit into path.
  for (; current_i != (end_i + step); current_i += step){
    *path = raw_path[current_i];
    path++;
  }
  
  return true;
}


void Square::getRank(Square** rank){
  // does not use this square's file index
  for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
    rank[file_i] = chessboard_p->getSquare(this->rank_i, file_i);
}


void Square::getFile(Square** file){
  // does not use this square's rank index
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    file[rank_i] = chessboard_p->getSquare(rank_i, this->file_i);
}


void Square::getDiagonal(Square* to_square_p, Square** diagonal){
  // find whether this square and the square at to_square_p lie on the 
  // rank increasing or rank decreasing diagonal. Move vector components 
  // signs determine which diagonal s.t.: (+,+) || (-,-) -> rank increasing
  // diagonal and (+,-) || (-,+) -> rank decreasing diagonal.
  bool rank_increasing = rankDiff(to_square_p)*fileDiff(to_square_p) > 0;

  // start at this square's indices
  int current_rank_i = rank_i, current_file_i = file_i;
  
  // we are always copying diagonals in increasing file index order, but
  // the rank index order changes depending on the diagonal we seek to copy.
  // if we want the rank increasing diagonal & we start to the first element
  // of the diagonal, we want to increase rank index by 1 on each step along
  // with the always positive file index increase to get to the next square
  int rank_step = (rank_increasing)? 1 : -1;

  // rank increasing diagonal in increasing file index order starts at 
  // rank >= MIN_INDEX, while rank decreasing diagonal starts at
  // rank <= MAX_INDEX.
  int start_rank_i_limit = (rank_increasing)? MIN_INDEX: MAX_INDEX;

  // first the indices of the first square on the correct diagonal. notice
  // that both diagonal start at file_index >= MIN_INDEX
  while (current_rank_i != start_rank_i_limit && current_file_i != MIN_INDEX){
    current_rank_i -= rank_step;
    current_file_i--;
  }

  
  int current_diagonal_i= 0;
  Square* current_square;
  // now copy diagonal squares into diagonal.
  while (validIndex(current_rank_i) && validIndex(current_file_i)){
    current_square = chessboard_p->getSquare(current_rank_i, current_file_i);
    diagonal[current_diagonal_i] = current_square;
    current_diagonal_i++;
    // step current rank index to the next square's rank index
    current_rank_i += rank_step;
    current_file_i++;
  }
}



Square* Square::getSquareBelow(const Color color) const{
  // if color is white, the square "below" this one is one rank lower
  // if color is black, the square "below" is actually one rank higher
  int rank_offset = (color == WHITE)? -1 : 1;
  return chessboard_p->getSquare(rank_i + rank_offset, file_i);
}


void Square::destroyPiece(){
  // safe to call on null pointers so no logic check needed
  delete piece_p;
  // set to null
  piece_p = 0; 
 
}


Error Square::movePiece(Square* to_square_p){
  // default call to canMove does not move pieces, simply checks
  // whether move is possible and legal
  Error move = piece_p->canMove(this, to_square_p);
  if (move == NO_ERROR){
    if (movePutsKingInCheck(to_square_p))
      return KING_IS_IN_CHECK;
    else
      piece_p->canMove(this, to_square_p, true);
  }
  return move;
}


bool Square::movePutsKingInCheck(Square* to_square_p){
  // gather player information
  Color player_color = piece_p->getColor();
  bool moving_piece_is_king = chessboard_p->
    getKingSquareP(player_color) == this;

  // save the piece pointer of the square we are moving to
  Piece* to_square_piece_p = to_square_p->piece_p;
  
  // if we are moving the king, we must update our chessboard's kings
  // square pointers.
  if (moving_piece_is_king)
    chessboard_p->setKingSquareP(player_color, to_square_p);

  // manually move the piece
  to_square_p->piece_p = piece_p;
  // set this square's pointer to null since piece has moved
  piece_p = 0; 

  bool kingIsInCheck = chessboard_p->kingIsInCheck(player_color);

  // return the pieces to their squares
  piece_p = to_square_p->piece_p;
  to_square_p->piece_p = to_square_piece_p;

  // if we moved the king earlier, we must restore the chessboard's kings
  // square pointers 
  if (moving_piece_is_king)
    chessboard_p->setKingSquareP(player_color, this);
  
  return kingIsInCheck;
}


bool Square::pieceCanMove(){
  Square* to_square_p;
  
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++){
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      to_square_p = chessboard_p->getSquare(rank_i, file_i);
      
      // check if this square's piece can move to the current to_square_p
      // without putting its king in check.
      if (piece_p->canMove(this, to_square_p) == NO_ERROR &&
	  !movePutsKingInCheck(to_square_p))
	return true;
    }
  }
  return false;
}


bool Square::isUnderAttack(Color player_color){
  bool this_square_has_a_piece = hasPiece();
  Square* from_square_p;
  
  // assume square is not under attack until proven otherwise
  bool is_under_attack = false;
  
  if (!this_square_has_a_piece)
    // set a dummy piece here to check if under attack
    setPiece(new Piece(player_color, DUMMY));

  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){

      from_square_p = chessboard_p->getSquare(rank_i, file_i);
      
      if (from_square_p->hasPiece())
	if (from_square_p->getPiece()->getColor() != player_color)
	  // here we don't check if this piece moving would induce a
	  // a check on its king because we only care about threat
	  if (from_square_p->getPiece()->canMove(from_square_p, this) == NO_ERROR)
	    is_under_attack = true;
    }
  
  if (!this_square_has_a_piece)
    // delete dummy piece
    destroyPiece();
  
  return is_under_attack;
}
