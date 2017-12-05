#include "ChessBoardTest.h"
#include "squareTest.h"
#include "pieceTest.h"
#include "utilsTest.h"
#include <iostream>

using namespace std;


int main(){

  std::cout << "Starting tests for Chess\n\n";
  testChessBoard();
  testSquare();
  testPiece();
  testUtils();
  return 0;
}
