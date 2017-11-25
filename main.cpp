#include <iostream>
#include "chessboard.h"
#include "utils.h"

int main(){
  Chessboard cb;
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
  cb.printBoard();
  cb.submitMove("B2","B4");
  cb.submitMove("C2","C4");
  cb.printBoard();
  cb.~Chessboard();
  std::cout << "Number of Squares: " << Square::num_squares << std::endl;
  std::cout << "Number of Pieces: " << Piece::num_pieces << std::endl;
  return 0;
}
