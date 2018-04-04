#include "test.h"
#include "ChessBoard.h"
#include <iostream>

using namespace std;


void test(){

  testPins();
  testCastling();
}



void testCastling(){
  cout << "===========================" << endl;
  cout << "     Testing Castling" << endl;
  cout << "===========================" << endl;
  cout << endl;
  
  ChessBoard cb;
  cout << endl;
  
  // testing white Queenside castle
  cb.submitMove("B1", "C3");
  cb.submitMove("B8", "C6");
  cb.submitMove("B2", "B3");
  cb.submitMove("D7", "D6");
  cb.submitMove("C1", "B2");
  cb.submitMove("C8", "F5");
  cb.submitMove("E2", "E3");
  cb.submitMove("G8", "F6");
  cb.submitMove("D1", "F3");
  cb.submitMove("G7", "G6");
  cb.submitMove("E1", "C1");

  cb.printBoard();
  

  // testing white Queenside castle fails
  cb.resetBoard();
  cb.submitMove("B1", "C3");
  cb.submitMove("B8", "C6");
  cb.submitMove("B2", "B3");
  cb.submitMove("D7", "D6");
  cb.submitMove("C1", "B2");
  cb.submitMove("C8", "G4");
  cb.submitMove("E2", "E4");
  cb.submitMove("G8", "F6");
  cb.submitMove("D2", "D4");
  cb.submitMove("G7", "G6");
  cb.submitMove("D1", "D3");
  cb.submitMove("A7", "A5");
  cb.submitMove("E1", "C1");
  
  cb.printBoard();
  
  
  //testing white Kingside castle
  
}
