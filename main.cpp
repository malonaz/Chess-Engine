#include <iostream>
#include "chessboard.h"

int main(){
  Chessboard cb;
  cb.printBoard();
  cb.getSquare(1,2)->movePiece(cb.getSquare(3,2));
  cb.printBoard();
  return 0;
}
