#include <iostream>
#include "chessboard.h"

using namespace std;

#include "chessboard.h"

int main() {


  
    cout << "===========================" << endl;
    cout << "Testing the Chess Engine" << endl;
    cout << "===========================" << endl;
    cout << endl;
 
    ChessBoard cb;
    cout << endl;
    
    cb.submitMove("D7", "D6");
    cout << endl;
    
    cb.submitMove("D4", "H6");
    cout << endl;

    cb.printBoard();
    
    cb.submitMove("D2", "D4");
    cout << endl;
    //

    cb.submitMove("E7", "E6");
    cb.submitMove("D4", "D5");
    cb.submitMove("C7", "C5");
    cb.submitMove("D5", "C6");
    cb.submitMove("B8", "C6");
    cb.submitMove("B1", "C3");
    cb.submitMove("G8", "F6");
    cb.submitMove("A1", "B1");
    cb.submitMove("G7", "G6");
    cb.submitMove("C1", "F4");
    cb.submitMove("F8" ,"G7");
    cb.submitMove("G1", "F3");
    cb.submitMove("D7", "D5");
    cb.submitMove("G2", "G3");
    cb.submitMove("C8", "D7");
    cb.submitMove("F1", "G2");
    cb.submitMove("A8", "B8");
    cb.submitMove("D1", "D5");
    cb.printBoard();
    cb.printObjects();
    return 0;


    cb.submitMove("A8", "C8");
    
    cb.submitMove("D1", "D7");
    cb.submitMove("F6", "D7");
    cb.submitMove("C1", "E3");
    cb.submitMove("G7", "G6");
    cb.submitMove("A1", "B1");
    cb.submitMove("H8", "E7");
        //
    
    cb.submitMove("F8", "B4");
    cout << endl;

    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cout << endl;

    cb.submitMove("E2", "E4");
    cb.submitMove("E7", "E6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << endl;

    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << endl;

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << endl;

    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << endl;

    cb.submitMove("C1", "A3");
    cb.submitMove("B8", "D7");
    cout << endl;

    cb.submitMove("D1", "E2");
    cb.submitMove("D5", "E4");
    cout << endl;

    cb.submitMove("D3", "E4");
    cb.submitMove("G8", "F6");
    cout << endl;

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << endl;

    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << endl;

    cb.submitMove("D3", "G6");
    cout << endl;

    return 0;
}
