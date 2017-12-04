// -*- C++ -*-
#include "pawn.h"
#include "square.h"
#include <cmath>
#include <iostream>


/**
 * Internal helper function. Returns true if the given components of a
 * move's vector corresponds to a two squares pawn push.
 */
bool twoSquarePawnPush(int rank_diff, int file_diff){
  if (rank_diff != PAWN_MAX_FIRST_FORWARD_MOVE || file_diff != NO_CHANGE)
    return false;
  
  return true;
}


/**
 * Internal helper function. Returns true if the given components of a
 * move's vector correspond to a simple pawn push.
 */
bool simplePawnPush(int rank_diff, int file_diff){
   if (rank_diff != PAWN_FORWARD_MOVE || file_diff != NO_CHANGE)
     return false;
   
   return true;  
}
 

/*
 * Internal helper function. Returns true if the given components of a
 * move's vector correspond to a pawn take.
 */
bool pawnTakes(int rank_diff, int file_diff){
   if (rank_diff != PAWN_FORWARD_MOVE || file_diff != PAWN_LATERAL_MOVE)
     return false;
   
   return true;
}

Error Pawn::canMove(Square* from_square_p, Square* to_square_p, bool move_piece){
  // check we are not moving to a square occupied by a piece of the same color
  if (squareOccupiedByFriendlyPiece(to_square_p))
      return TAKES_PIECE_OF_SAME_COLOR;
  
  // get component of move's vector. notice we don't care about the sign
  // of the file diff component.
  int rank_diff = from_square_p->rankDiff(to_square_p);
  int abs_file_diff = std::abs(from_square_p->fileDiff(to_square_p));

  // If piece is black, a rank_diff of 1 corresponds to a forward move of 1
  rank_diff *= (color == WHITE)? 1: -1;

  // process move vector
  bool pawn_takes = pawnTakes(rank_diff, abs_file_diff);
  bool simple_pawn_push = simplePawnPush(rank_diff, abs_file_diff);
  bool two_square_pawn_push = twoSquarePawnPush(rank_diff, abs_file_diff);
  
  // gather information about destination square
  bool to_square_has_piece  = to_square_p->hasPiece();

  // assume piece cannot move this way until proven otherwise
  Error move = PIECE_DOES_NOT_MOVE_THIS_WAY;
  
  // there cannot be a piece on the square a simple pawn push moves to    
  if (simple_pawn_push){
    if (to_square_has_piece)
      return PATH_OBSTRUCTED;
    else
      move = VALID;
  }
  
  // if pawn takes regularly, there must be a piece on to_square_p
  if (pawn_takes && to_square_has_piece)
    move = VALID;

  // notice that we pass @param move_piece to canEnPassant.
  if (pawn_takes && !to_square_has_piece)
    move = canEnPassant(to_square_p, move_piece);

  // there cannot be a piece on the square a two square pawn push moves to
  if (two_square_pawn_push && !to_square_has_piece){
    // get square below the square at to_square_p
    Square* square_below = to_square_p->getSquareBelow(color); 
    
    if (square_below->hasPiece())
      // pawn cannot move through a piece !
      return PATH_OBSTRUCTED;

    if (move_piece)
      // this pawn can be taken en passant next turn
      en_passant = true;  
    
    move = VALID;
  }

  if (move == VALID && move_piece)
    movePiece(from_square_p, to_square_p);
  
  return move;
}


Error Pawn::canEnPassant(Square* to_square_p, bool move_piece){
  // get square below the square at to_square_p
  Square* en_passant_square_p = to_square_p->getSquareBelow(color); 

  // en passant square must contain a piece
  if (!en_passant_square_p->hasPiece())
    return PIECE_DOES_NOT_MOVE_THIS_WAY;

  // get piece
  Piece* en_passant_piece = en_passant_square_p->getPiece();
  Pawn* en_passant_pawn;

  // piece must be an opponent's pawn
  if (en_passant_piece->getColor() == color ||
      en_passant_piece->getType() == type)
    return PIECE_DOES_NOT_MOVE_THIS_WAY;

  // recast piece as a pawn
  en_passant_pawn = static_cast<Pawn*>(en_passant_piece);

  // pawn must have moved past this pawn's ability to take it on the
  // previous turn. If so, it's en passant attribute is true
  if (!en_passant_pawn->en_passant)
    return PIECE_DOES_NOT_MOVE_THIS_WAY;

  // checks if taking en passant discovers a check on its king
  if (enPassantDiscoversCheck(en_passant_square_p))
    return DISCOVERS_CHECK;
  
  if (move_piece)
    en_passant_square_p->destroyPiece();
  
  return VALID;
}


bool Pawn::enPassantDiscoversCheck(Square* en_passant_square_p)const{
  Square* rank[8];
  // get rank of en_passant_square
  en_passant_square_p->getRank(rank);

  bool enemy_queen_present = false, king_present = false;
  int enemy_queen_file_i, king_file_i;
  int en_passant_file_i = en_passant_square_p->getFileIndex();
  
  for ( int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){

    if (rank[file_i]->hasPiece()){
      
      if (rank[file_i]->getPiece()->getType() == QUEEN &&
	  rank[file_i]->getPiece()->getColor() != color){
	// found enemy queen
	enemy_queen_present = true;
	enemy_queen_file_i = file_i;
      }

      if (rank[file_i]->getPiece()->getType() == KING &&
	  rank[file_i]->getPiece()->getColor() == color){
	// found king
	king_present = true;
	king_file_i = file_i;
      }
    }
  }

  // no discovered check. please read readme.txt file for more info
  if (!enemy_queen_present  || !king_present)
    return false;
    
  // check if en_passant pawn is in between enemy queen and king
  if (!isInBetween(en_passant_file_i, enemy_queen_file_i, king_file_i))
    return false;

  // check that there are only two pieces between enemy queen and king
  int num_pieces_between_queen_and_king = 0;
  int file_i_step = (enemy_queen_file_i < king_file_i)? 1 : -1;
  int current_file_i = enemy_queen_file_i + file_i_step;
  for (; current_file_i != king_file_i; current_file_i += file_i_step)
    if (rank[current_file_i]->hasPiece())
      num_pieces_between_queen_and_king++;

  // if en_passant pawn is in between, then so must this pawn. if there
  // are any other piece, then removing both will not discover check
  if (num_pieces_between_queen_and_king != 2)
    return false;
  
  return true;
}
