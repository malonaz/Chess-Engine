#include "ChessBoardTest.h"
#include "squareTest.h"
#include "pieceTest.h"
#include "pawnTest.h"
#include "kingTest.h"
#include "knightTest.h"
#include "utilsTest.h"
#include <iostream>

using namespace std;


int main(){

  std::cout << "Starting tests for Chess\n\n";
  
  testChessBoard();
  testSquare();
  testPiece();
  testPawn();
  testKnight();
  testKing();
  testPawn();
  testUtils();

  std::cout << "Tests for Chess passed!\n\n";
  return 0;
}
