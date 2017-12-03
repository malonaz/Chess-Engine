#include "squareTest.h"
#include "ChessBoard.h"
#include "square.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>


void testSquare(){
  std::cout << " Starting tests for Square\n";


  testRankFileDiff();
  testMovePutsKingInCheck();
  testGetRankGetFile();
  
  std::cout << " finished tests for Square\n\n";
  
}


void testRankFileDiff(){
  // dummy chessboard_pointer for square initialization
  ChessBoard* chessboard_p = 0;

  Square* base_square_p = new Square(chessboard_p, 0, 5);

  Square* current_square_p;
  
  for (int i = 0; i < 100; i++){
    current_square_p = new Square(chessboard_p, i, i + 5);
    assert(current_square_p->rankDiff(base_square_p) == -i);
    assert(base_square_p->rankDiff(current_square_p) == i);
    assert(current_square_p->fileDiff(base_square_p) == -i);
    assert(base_square_p->fileDiff(current_square_p) == i);
    // free memory
    delete current_square_p;
  }
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
  for (int rank_i = MIN_INDEX; rank_i < MAX_INDEX; rank_i++)
    for (int file_i = MIN_INDEX; file_i < MAX_INDEX; file_i++){
      current_square_p = cb.getSquare(rank_i, file_i);
      current_square_p->getRank(rank);
      current_square_p->getFile(file);
      for (int i = MIN_INDEX; i < MAX_INDEX; i++){
	assert(rank[i]->getRankIndex() == rank_i);
	assert(rank[i]->getFileIndex() == i);
	assert(file[i]->getRankIndex() == i);
	assert(file[i]->getFileIndex() == file_i);
      }
    }
  std::cout << "   Tests for getRank passed!\n";
  std::cout << "   Tests for getFile passed!\n";
}







void testMovePutsKingInCheck(){
  // redirecting cout
  CoutRedirect cr;
  
  ChessBoard cb;
  
  // testing white pieces
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("E1", "E2") == VALID);
  assert(cb.submitMove("F8", "C5") == VALID);
  assert(cb.submitMove("E2", "E3") == DISCOVERS_CHECK); // Black king steps into check
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E6") == VALID);
  assert(cb.submitMove("D1", "E2") == VALID);
  assert(cb.submitMove("D8", "F6") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("F6", "E5") == VALID);
  assert(cb.submitMove("H2", "H3") == VALID);
  assert(cb.submitMove("E5", "E4") == VALID);
  assert(cb.submitMove("E2", "F3") == DISCOVERS_CHECK); // White Queen is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E6") == VALID);
  assert(cb.submitMove("A2", "A4") == VALID);
  assert(cb.submitMove("D8", "F6") == VALID);
  assert(cb.submitMove("A1", "A3") == VALID);
  assert(cb.submitMove("F6", "E5") == VALID);
  assert(cb.submitMove("A3", "E3") == VALID);
  assert(cb.submitMove("E5", "E4") == VALID);
  assert(cb.submitMove("E3", "A3") == DISCOVERS_CHECK); // White Rook is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E6") == VALID);
  assert(cb.submitMove("F1", "E2") == VALID);
  assert(cb.submitMove("D8", "F6") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("F6", "E5") == VALID);
  assert(cb.submitMove("H2", "H3") == VALID);
  assert(cb.submitMove("E5", "E4") == VALID);
  assert(cb.submitMove("E2", "F3") == DISCOVERS_CHECK); // White Bishop is pinned

  cb.resetBoard();
  assert(cb.submitMove("D2", "D4") == VALID);
  assert(cb.submitMove("E7", "E6") == VALID);
  assert(cb.submitMove("B1", "C3") == VALID);
  assert(cb.submitMove("F8", "B4") == VALID);
  assert(cb.submitMove("C3", "D5") == DISCOVERS_CHECK); // White Knight is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E6") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("D8", "F6") == VALID);
  assert(cb.submitMove("H2", "H3") == VALID);
  assert(cb.submitMove("F6", "E5") == VALID);
  assert(cb.submitMove("A3", "A4") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("E4", "D5") == DISCOVERS_CHECK); // White Pawn is pinned

  // testing black pieces
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("F1", "C4") == VALID);
  assert(cb.submitMove("E8", "E7") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID); 
  assert(cb.submitMove("E7", "E6") == DISCOVERS_CHECK); // Black King steps into check
  
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("D1", "H5") == VALID);
  assert(cb.submitMove("D8", "E7") == VALID);
  assert(cb.submitMove("H5", "E5") == VALID); 
  assert(cb.submitMove("E7", "D8") == DISCOVERS_CHECK);// Black Queen is pinned

  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("H2", "H3") == VALID);
  assert(cb.submitMove("A7", "A5") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("A8", "A6") == VALID);
  assert(cb.submitMove("B2", "B3") == VALID);
  assert(cb.submitMove("A6", "C6") == VALID); 
  assert(cb.submitMove("F1", "B5") == VALID);
  assert(cb.submitMove("C6", "A6") == DISCOVERS_CHECK);// Black Rook is pinned (diagonally)
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("D1", "H5") == VALID);
  assert(cb.submitMove("A7", "A5") == VALID);
  assert(cb.submitMove("H5", "D5") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("B2", "B3") == VALID);
  assert(cb.submitMove("D8", "F6") == VALID); 
  assert(cb.submitMove("B1", "C3") == VALID);
  assert(cb.submitMove("F8", "D6") == VALID);  
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("E8", "D8") == VALID); // King is moved here
  assert(cb.submitMove("A3", "A4") == VALID);
  assert(cb.submitMove("D6", "F8") == DISCOVERS_CHECK);// Black Bishop is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("D1", "H5") == VALID);
  assert(cb.submitMove("A7", "A5") == VALID);
  assert(cb.submitMove("H5", "D5") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("B2", "B3") == VALID);
  assert(cb.submitMove("B8", "C6") == VALID); 
  assert(cb.submitMove("F1", "B5") == VALID); 
  assert(cb.submitMove("C6", "D4") == DISCOVERS_CHECK); // Black Knight is pinned
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E3") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("D1", "E2") == VALID);
  assert(cb.submitMove("E8", "D7") == VALID);
  assert(cb.submitMove("E2", "D3") == VALID);
  assert(cb.submitMove("G8", "F6") == VALID);
  assert(cb.submitMove("E3", "E4") == VALID);
  assert(cb.submitMove("D5", "E4") == DISCOVERS_CHECK); // Black Pawn is pinned
  
  // testing castling
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("G1", "F3") == VALID);
  assert(cb.submitMove("B7", "B6") == VALID);
  assert(cb.submitMove("F1", "A6") == VALID);
  assert(cb.submitMove("C8", "A6") == VALID);
  // square on white king's path to kingside castled position is under attack.
  assert(cb.submitMove("E1", "G1") == DISCOVERS_CHECK);

  
  
  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("E7", "E5") == VALID);
  assert(cb.submitMove("G1", "F3") == VALID);
  assert(cb.submitMove("D8", "G5") == VALID);
  assert(cb.submitMove("F1", "A6") == VALID);
  assert(cb.submitMove("G5", "E3") == VALID);
  // white king attempts to castle kingside  while in check
  assert(cb.submitMove("E1", "G1") == DISCOVERS_CHECK);

  cb.resetBoard();
  assert(cb.submitMove("E2", "E4") == VALID);
  assert(cb.submitMove("D7", "D5") == VALID);
  assert(cb.submitMove("A2", "A3") == VALID);
  assert(cb.submitMove("C8", "G4") == VALID);
  assert(cb.submitMove("D1", "G4") == VALID);
  assert(cb.submitMove("D8", "D6") == VALID);
  assert(cb.submitMove("F1", "D3") == VALID);
  assert(cb.submitMove("B8", "C6") == VALID);
  assert(cb.submitMove("A3", "A4") == VALID);
  // queenside castle king position under thread
  assert(cb.submitMove("E8", "C8") == DISCOVERS_CHECK);
  
  // restore cout
  cr.restoreCout();
  
  std::cout << "   Tests for MovePutsKingInCheck passed!\n";
}
