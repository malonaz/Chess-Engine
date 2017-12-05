#include "squareTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "utils.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>
#include <cmath>


void testSquare(){
  std::cout << " Starting tests for Square\n";

  testStaticNumSquares();
  testSquareDestructor();
  testGetSquareBelow();
  testRankFileDiff();
  testMovePutsKingInCheck();
  testGetPath();
  testGetRankGetFile();
  testGetDiagonal();
  testIsUnderAttack();
  testPieceCanMove();
  std::cout << " finished tests for Square\n\n";
  
}


void testStaticNumSquares(){

  Square* square_ps[100];
  for (int i = 0; i < 100; i++){
    assert (Square::num_squares == i);
    square_ps[i] = new Square();
  }
    
  for (int i = 99; i >= 0; i--){
    delete square_ps[i];
    assert (Square::num_squares == i);
  }
  
  std::cout << "   Tests for static member num_squares passed!\n";
}

void testSquareDestructor(){
  assert(Piece::num_pieces == 0);
  // create dummy piece 
  Piece* piece_p = new Piece(WHITE, DUMMY);
 
  // create square
  Square* square_p = new Square();
  square_p->setPiece(piece_p);

  // static num_piece should be at one now
  assert(Piece::num_pieces == 1);

  // delete square
  delete square_p;
  // static num_piece should be at 0 now
  assert(Piece::num_pieces == 0);

  std::cout << "   Tests for Square destructor passed!\n";
}

void testGetSquareBelow(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // restore cout
  cr.restoreCout();
  
  Square* current_square_p;
  Square* square_below_p;

  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      current_square_p = cb.getSquare(rank_i, file_i);
      // no square below rank 0 for white
      if (rank_i != MIN_INDEX){
	square_below_p = current_square_p->getSquareBelow(WHITE);
	assert(square_below_p->getRankIndex() == current_square_p->getRankIndex() - 1);
	assert(square_below_p->getFileIndex() == current_square_p->getFileIndex());
      }

      //no square below rank 7 for black
      if (rank_i != MAX_INDEX){
	square_below_p = current_square_p->getSquareBelow(BLACK);
	assert(square_below_p->getRankIndex() == current_square_p->getRankIndex() + 1);
	assert(square_below_p->getFileIndex() == current_square_p->getFileIndex());
      }
    }

  std::cout << "   Tests for getSquareBelow passed!\n";
}

void testGetPath(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // restore cout
  cr.restoreCout();
  
  Square* path[8];
  Square* from_square_p;
  Square* to_square_p;
  int rank_diff, file_diff;
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
      for (int rank_i2 = MIN_INDEX; rank_i2 <= MAX_INDEX; rank_i2++)
	for (int file_i2 = MIN_INDEX; file_i2 <= MAX_INDEX; file_i2++){
	  from_square_p = cb.getSquare(rank_i, file_i);
	  to_square_p = cb.getSquare(rank_i2, file_i2);
	  rank_diff = from_square_p->rankDiff(to_square_p);
	  file_diff = from_square_p->fileDiff(to_square_p);
	  Dimension dim = getMoveDimension(rank_diff, file_diff);
	  
	  if (dim == INCORRECT || dim == NO_CHANGE)
	    assert(from_square_p->getPath(to_square_p, path, QUEEN) == false);
	  
	  else{
	    assert(from_square_p->getPath(to_square_p, path, QUEEN) == true);
	    assert(path[0] == from_square_p);
	    int abs_file_diff = std::abs(file_diff);
	    int abs_rank_diff = std::abs(rank_diff);
	    if (dim == VERTICAL)
	      assert(path[abs_rank_diff] == to_square_p);
	    else
	      assert(path[abs_file_diff] == to_square_p);
	      
	  }
	}
									
  std::cout << "   Tests for getPath passed!\n";

}

void testRankFileDiff(){
  // dummy chessboard_pointer for square initialization
  ChessBoard* chessboard_p = 0;

  Square* base_square_p = new Square();
  base_square_p->init(chessboard_p, 0, 5);

  Square* current_square_p;
  
  for (int i = 0; i < 100; i++){
    current_square_p = new Square();
    current_square_p->init(chessboard_p, i, i + 5);
    assert(current_square_p->rankDiff(base_square_p) == -i);
    assert(base_square_p->rankDiff(current_square_p) == i);
    assert(current_square_p->fileDiff(base_square_p) == -i);
    assert(base_square_p->fileDiff(current_square_p) == i);
    // free memory
    delete current_square_p;
  }
  // free base square
  delete base_square_p;
  std::cout << "   Tests for RankDiff passed!\n";
  std::cout << "   Tests for FileDiff passed!\n";
}


void testGetRankGetFile(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // restore cout
  cr.restoreCout();

  Square* rank[8];
  Square* file[8];
  Square* current_square_p;
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++){
      current_square_p = cb.getSquare(rank_i, file_i);
      current_square_p->getRank(rank);
      current_square_p->getFile(file);
      for (int i = MIN_INDEX; i <= MAX_INDEX; i++){
	assert(rank[i]->getRankIndex() == rank_i);
	assert(rank[i]->getFileIndex() == i);
	assert(file[i]->getRankIndex() == i);
	assert(file[i]->getFileIndex() == file_i);
      }
    }
  std::cout << "   Tests for getRank passed!\n";
  std::cout << "   Tests for getFile passed!\n";
}


void testGetDiagonal(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;
  
  ChessBoard cb;

  // restore cout
  cr.restoreCout();

  Square* diagonal[8];
  Square* from_square_p;
  Square* to_square_p;
  // rank increasing diagonals
  // test 1 
  from_square_p = cb.getSquare(6, 0);
  to_square_p = cb.getSquare(7, 1);

  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);

  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[0] == from_square_p); // same order as before
  assert(diagonal[1] == to_square_p);

  // test 2
  from_square_p = cb.getSquare(0, 6);
  to_square_p = cb.getSquare(1, 7);

  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);

  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);


  // test 3
  from_square_p = cb.getSquare(1,1);
  to_square_p = cb.getSquare(6,6);
  
  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[1] == from_square_p);
  assert(diagonal[6] == to_square_p);
  
  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[1] == from_square_p);
  assert(diagonal[6] == to_square_p);
  
  // rank decreasing diagonals
  // test 1 
  from_square_p = cb.getSquare(7, 6);
  to_square_p = cb.getSquare(6, 7);

  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);

  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[0] == from_square_p); // same order as before
  assert(diagonal[1] == to_square_p);

  // test 2
  from_square_p = cb.getSquare(1, 0);
  to_square_p = cb.getSquare(0, 1);

  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);

  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[0] == from_square_p);
  assert(diagonal[1] == to_square_p);


  // test 3
  from_square_p = cb.getSquare(6,1);
  to_square_p = cb.getSquare(1,6);
  
  from_square_p->getDiagonal(to_square_p, diagonal);
  assert(diagonal[1] == from_square_p);
  assert(diagonal[6] == to_square_p);
  
  to_square_p->getDiagonal(from_square_p, diagonal);
  assert(diagonal[1] == from_square_p);
  assert(diagonal[6] == to_square_p);
  
  std::cout << "   Tests for getDiagonal passed!\n";
}


void testIsUnderAttack(){
  // redirecting cout
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // delete all pieces
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
      cb.getSquare(rank_i, file_i)->destroyPiece();

  // add a white bishop on D6, cb destructor will free it
  cb.getSquare("D4")->setPiece(new Piece(WHITE, BISHOP));
  
  Square* square_ps[8];
  // get rank increasing diagonal
  cb.getSquare("D4")->getDiagonal(cb.getSquare("E5"), square_ps);
  
  // all squares in the diagonals threated by bishop should be under attack
  for (int file_i = MIN_INDEX; file_i < MAX_INDEX; file_i++){
    if (square_ps[file_i] != cb.getSquare("D4"))
      assert(square_ps[file_i]->isUnderAttack(BLACK));
    else
      assert(!square_ps[file_i]->isUnderAttack(BLACK));
    
    // there are no black pieces so no black piece can threaten these squares
    assert(!square_ps[file_i]->isUnderAttack(WHITE));
  }
  
  // get other diagonal
  cb.getSquare("D4")->getDiagonal(cb.getSquare("E3"), square_ps);
  for (int file_i = MIN_INDEX; file_i < MAX_INDEX; file_i++){
    if (square_ps[file_i] != cb.getSquare("D4"))
      assert(square_ps[file_i]->isUnderAttack(BLACK));
    else
      assert(!square_ps[file_i]->isUnderAttack(BLACK));

    // there are no black pieces so no black piece can threaten these squares
    assert(!square_ps[file_i]->isUnderAttack(WHITE));
  }

  // now place a white rook on E5
  cb.getSquare("E5")->setPiece(new Piece(WHITE, ROOK));
  
  // get rank increasing diagonal
  cb.getSquare("D4")->getDiagonal(cb.getSquare("E5"), square_ps);

  // all squares from A1 to C3 are under attack, but white rook shields the rest
  for (int file_i = MIN_INDEX; file_i < MAX_INDEX; file_i++){
    if (square_ps[file_i]->getFileIndex() < cb.getSquare("D4")->getFileIndex())
      assert(square_ps[file_i]->isUnderAttack(BLACK));
    else
      assert(!square_ps[file_i]->isUnderAttack(BLACK));

    // there are no black pieces so no black piece can threaten these squares
    assert(!square_ps[file_i]->isUnderAttack(WHITE));
  }

  // corner a case. a pawn can move to the square directly above him but does not
  // threaten in as it threatens diagonally not vertically

  // place a black pawn on C7 and get rank "above" C7 (black perspective)
  cb.getSquare("C7")->setPiece(new Pawn(BLACK));
  cb.getSquare("C6")->getRank(square_ps);

  // check all all squares are not under attack except square B6 and D6
  for (int file_i = MIN_INDEX; file_i < MAX_INDEX; file_i++){
    if (square_ps[file_i] == cb.getSquare("B6") ||
	square_ps[file_i] == cb.getSquare("D6"))
      assert(square_ps[file_i]->isUnderAttack(WHITE));
    else
      assert(!square_ps[file_i]->isUnderAttack(WHITE));  
  }
  
  // add a black king on A1 and check A2, B2 and B1 are under attack
  cb.getSquare("A1")->setPiece(new King(BLACK));
  assert(cb.getSquare("A2")->isUnderAttack(WHITE));
  assert(cb.getSquare("B2")->isUnderAttack(WHITE));
  assert(cb.getSquare("B1")->isUnderAttack(WHITE));
  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for isUnderAttack passed!\n";
}


void testPieceCanMove(){
  // redirecting cout
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // delete all pieces
  for (int rank_i = MIN_INDEX; rank_i <= MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i <= MAX_INDEX; file_i++)
      cb.getSquare(rank_i, file_i)->destroyPiece();
  
  // add white pawns on B2 & B3
  cb.getSquare("B2")->setPiece(new Pawn(WHITE));
  cb.getSquare("B3")->setPiece(new Pawn(WHITE));
  
  // check pawn B2 cannot move but pawn B3 can
  assert(!cb.getSquare("B2")->pieceCanMove());
  assert(cb.getSquare("B3")->pieceCanMove());

  // put a bishop on square D5 and add same color piece on E6, E4, C4 & C6
  cb.getSquare("D5")->setPiece(new Piece(BLACK, BISHOP));
  cb.getSquare("E6")->setPiece(new Piece(BLACK, ROOK));
  cb.getSquare("E4")->setPiece(new Piece(BLACK, ROOK));
  cb.getSquare("C4")->setPiece(new Piece(BLACK, ROOK));
  cb.getSquare("C6")->setPiece(new Piece(BLACK, ROOK));

  // bishop cannot move but the rooks can
  assert(!cb.getSquare("D5")->pieceCanMove());
  assert(cb.getSquare("E6")->pieceCanMove());
  assert(cb.getSquare("E4")->pieceCanMove());
  assert(cb.getSquare("C4")->pieceCanMove());
  assert(cb.getSquare("C6")->pieceCanMove());
    
  // put a black king on H1, a black knight on G1 and a white queen on G3
  cb.getSquare("H1")->setPiece(new King(BLACK));
  cb.getSquare("G1")->setPiece(new Knight(BLACK));
  cb.getSquare("G3")->setPiece(new Piece(WHITE, QUEEN));
  // update chessboard king pointer
  cb.setKingSquareP(BLACK, cb.getSquare("H1"));

  // king cannot move without placing itself in check
  assert(!cb.getSquare("H1")->pieceCanMove());
  assert(cb.getSquare("G1")->pieceCanMove());
  assert(cb.getSquare("G3")->pieceCanMove());

  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for PieceCanMove passed!\n";

}

void testMovePutsKingInCheck(){
  // redirecting cout
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // testing white pieces
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("E1", "E2") == NO_ERROR);
  assert(cb.submitMove("F8", "C5") == NO_ERROR);
  assert(cb.submitMove("E2", "E3") == KING_IS_IN_CHECK); // Black king steps into check
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E6") == NO_ERROR);
  assert(cb.submitMove("D1", "E2") == NO_ERROR);
  assert(cb.submitMove("D8", "F6") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("F6", "E5") == NO_ERROR);
  assert(cb.submitMove("H2", "H3") == NO_ERROR);
  assert(cb.submitMove("E5", "E4") == NO_ERROR);
  assert(cb.submitMove("E2", "F3") == KING_IS_IN_CHECK); // White Queen is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E6") == NO_ERROR);
  assert(cb.submitMove("A2", "A4") == NO_ERROR);
  assert(cb.submitMove("D8", "F6") == NO_ERROR);
  assert(cb.submitMove("A1", "A3") == NO_ERROR);
  assert(cb.submitMove("F6", "E5") == NO_ERROR);
  assert(cb.submitMove("A3", "E3") == NO_ERROR);
  assert(cb.submitMove("E5", "E4") == NO_ERROR);
  assert(cb.submitMove("E3", "A3") == KING_IS_IN_CHECK); // White Rook is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E6") == NO_ERROR);
  assert(cb.submitMove("F1", "E2") == NO_ERROR);
  assert(cb.submitMove("D8", "F6") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("F6", "E5") == NO_ERROR);
  assert(cb.submitMove("H2", "H3") == NO_ERROR);
  assert(cb.submitMove("E5", "E4") == NO_ERROR);
  assert(cb.submitMove("E2", "F3") == KING_IS_IN_CHECK); // White Bishop is pinned

  cb.resetBoard();
  assert(cb.submitMove("D2", "D4") == NO_ERROR);
  assert(cb.submitMove("E7", "E6") == NO_ERROR);
  assert(cb.submitMove("B1", "C3") == NO_ERROR);
  assert(cb.submitMove("F8", "B4") == NO_ERROR);
  assert(cb.submitMove("C3", "D5") == KING_IS_IN_CHECK); // White Knight is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E6") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("D8", "F6") == NO_ERROR);
  assert(cb.submitMove("H2", "H3") == NO_ERROR);
  assert(cb.submitMove("F6", "E5") == NO_ERROR);
  assert(cb.submitMove("A3", "A4") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("E4", "D5") == KING_IS_IN_CHECK); // White Pawn is pinned

  // testing black pieces
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("F1", "C4") == NO_ERROR);
  assert(cb.submitMove("E8", "E7") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR); 
  assert(cb.submitMove("E7", "E6") == KING_IS_IN_CHECK); // Black King steps into check
  
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("D1", "H5") == NO_ERROR);
  assert(cb.submitMove("D8", "E7") == NO_ERROR);
  assert(cb.submitMove("H5", "E5") == NO_ERROR); 
  assert(cb.submitMove("E7", "D8") == KING_IS_IN_CHECK);// Black Queen is pinned

  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("H2", "H3") == NO_ERROR);
  assert(cb.submitMove("A7", "A5") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("A8", "A6") == NO_ERROR);
  assert(cb.submitMove("B2", "B3") == NO_ERROR);
  assert(cb.submitMove("A6", "C6") == NO_ERROR); 
  assert(cb.submitMove("F1", "B5") == NO_ERROR);
  assert(cb.submitMove("C6", "A6") == KING_IS_IN_CHECK);// Black Rook is pinned (diagonally)
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("D1", "H5") == NO_ERROR);
  assert(cb.submitMove("A7", "A5") == NO_ERROR);
  assert(cb.submitMove("H5", "D5") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("B2", "B3") == NO_ERROR);
  assert(cb.submitMove("D8", "F6") == NO_ERROR); 
  assert(cb.submitMove("B1", "C3") == NO_ERROR);
  assert(cb.submitMove("F8", "D6") == NO_ERROR);  
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("E8", "D8") == NO_ERROR); // King is moved here
  assert(cb.submitMove("A3", "A4") == NO_ERROR);
  assert(cb.submitMove("D6", "F8") == KING_IS_IN_CHECK);// Black Bishop is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("D1", "H5") == NO_ERROR);
  assert(cb.submitMove("A7", "A5") == NO_ERROR);
  assert(cb.submitMove("H5", "D5") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("B2", "B3") == NO_ERROR);
  assert(cb.submitMove("B8", "C6") == NO_ERROR); 
  assert(cb.submitMove("F1", "B5") == NO_ERROR); 
  assert(cb.submitMove("C6", "D4") == KING_IS_IN_CHECK); // Black Knight is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("D1", "E2") == NO_ERROR);
  assert(cb.submitMove("E8", "D7") == NO_ERROR);
  assert(cb.submitMove("E2", "D3") == NO_ERROR);
  assert(cb.submitMove("G8", "F6") == NO_ERROR);
  assert(cb.submitMove("E3", "E4") == NO_ERROR);
  assert(cb.submitMove("D5", "E4") == KING_IS_IN_CHECK); // Black Pawn is pinned
  
  // testing castling
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("G1", "F3") == NO_ERROR);
  assert(cb.submitMove("B7", "B6") == NO_ERROR);
  assert(cb.submitMove("F1", "A6") == NO_ERROR);
  assert(cb.submitMove("C8", "A6") == NO_ERROR);
  // square on white king's path to kingside castled position is under attack.
  assert(cb.submitMove("E1", "G1") == KING_IS_IN_CHECK);

  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("G1", "F3") == NO_ERROR);
  assert(cb.submitMove("D8", "G5") == NO_ERROR);
  assert(cb.submitMove("F1", "A6") == NO_ERROR);
  assert(cb.submitMove("G5", "E3") == NO_ERROR);
  // white king attempts to castle kingside  while in check
  assert(cb.submitMove("E1", "G1") == KING_IS_IN_CHECK);

  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("A2", "A3") == NO_ERROR);
  assert(cb.submitMove("C8", "G4") == NO_ERROR);
  assert(cb.submitMove("D1", "G4") == NO_ERROR);
  assert(cb.submitMove("D8", "D6") == NO_ERROR);
  assert(cb.submitMove("F1", "D3") == NO_ERROR);
  assert(cb.submitMove("B8", "C6") == NO_ERROR);
  assert(cb.submitMove("A3", "A4") == NO_ERROR);
  // queenside castle king position under thread
  assert(cb.submitMove("E8", "C8") == KING_IS_IN_CHECK);
  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for MovePutsKingInCheck passed!\n";
}
