#include "squareTest.h"
#include <iostream>

using namespace std;


void testSquare(){

  cout << "===========================" << endl;
  cout << "Testing MovePutsKingInCheck" << endl;
  cout << "===========================" << endl;
  cout << endl;

  
}



void testMovePutsKingInCheck(){
  
  cout << "===========================" << endl;
  cout << "Testing MovePutsKingInCheck" << endl;
  cout << "===========================" << endl;
  cout << endl;
  
  ChessBoard cb;
  cout << endl;
  
  // testing white pinned pieces
  cb.submitMove("D2", "D4");
  cb.submitMove("E7", "E6");
  cb.submitMove("B1", "C3");
  cb.submitMove("F8", "B4");
  cb.submitMove("C3", "D5"); // this knight is pinned
  cb.printBoard();
  
  
  cb.resetBoard();
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  cb.submitMove("F1", "E2");
  cb.submitMove("D8", "F6");
  cb.submitMove("A2", "A3");
  cb.submitMove("F6", "E5");
  cb.submitMove("H2", "H3");
  cb.submitMove("E5", "E4");
  cb.submitMove("E2", "F3"); // this bishop is pinned
  cb.printBoard();
  
  
  cb.resetBoard();
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  cb.submitMove("D1", "E2");
  cb.submitMove("D8", "F6");
  cb.submitMove("A2", "A3");
  cb.submitMove("F6", "E5");
  cb.submitMove("H2", "H3");
  cb.submitMove("E5", "E4");
  cb.submitMove("E2", "F3"); // this Queen is pinned
  cb.printBoard();
  
  
  cb.resetBoard();
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  cb.submitMove("A2", "A4");
  cb.submitMove("D8", "F6");
  cb.submitMove("A1", "A3");
  cb.submitMove("F6", "E5");
  cb.submitMove("A3", "E3");
  cb.submitMove("E5", "E4");
  cb.submitMove("E3", "A3"); // this Rook is pinned
  cb.printBoard();
  
  
  cb.resetBoard();
  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  cb.submitMove("A2", "A3");
  cb.submitMove("D8", "F6");
  cb.submitMove("H2", "H3");
  cb.submitMove("F6", "E5");
  cb.submitMove("A3", "A4");
  cb.submitMove("D7", "D5");
  cb.submitMove("E4", "D5"); // this pawn is pinned
  cb.printBoard();
  

  cout << endl << endl;
}
