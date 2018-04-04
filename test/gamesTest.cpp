#include "gamesTest.h"
#include "ChessBoard.h"
#include "utils.h"
#include "coutRedirect.h"

#include <iostream>
#include <assert.h>


void testGames(){

  std::cout << " Starting tests for games\n";

  testGame1();
  
  std::cout << " finished tests for games\n\n";

}


void testGame1(){
  // redirecting cout to suppress new game started msg
  CoutRedirect cr;

  ChessBoard cb;

  assert(cb.submitMove("E2", "E4") == NO_ERROR);
  assert(cb.submitMove("B8", "C6") == NO_ERROR);
  assert(cb.submitMove("D2", "D4") == NO_ERROR);
  assert(cb.submitMove("E7", "E5") == NO_ERROR);
  assert(cb.submitMove("G1", "F3") == NO_ERROR);
  assert(cb.submitMove("E5", "D4") == NO_ERROR);
  assert(cb.submitMove("F3", "D4") == NO_ERROR);
  assert(cb.submitMove("G8", "F6") == NO_ERROR);
  assert(cb.submitMove("B1", "C3") == NO_ERROR);
  assert(cb.submitMove("F8", "B4") == NO_ERROR);
  assert(cb.submitMove("D4", "C6") == NO_ERROR);
  assert(cb.submitMove("B7", "C6") == NO_ERROR);
  assert(cb.submitMove("F1", "D3") == NO_ERROR);
  assert(cb.submitMove("D7", "D5") == NO_ERROR);
  assert(cb.submitMove("E4", "D5") == NO_ERROR);
  assert(cb.submitMove("F6", "D5") == NO_ERROR);
  assert(cb.submitMove("E1", "G1") == NO_ERROR);
  assert(cb.submitMove("D5", "C3") == NO_ERROR);
  assert(cb.submitMove("B2", "C3") == NO_ERROR);
  assert(cb.submitMove("B4", "C3") == NO_ERROR);
  assert(cb.submitMove("C1", "A3") == NO_ERROR);
  assert(cb.submitMove("C3", "A1") == NO_ERROR);
  assert(cb.submitMove("D1", "A1") == NO_ERROR);
  assert(cb.submitMove("D8", "G5") == NO_ERROR);
  assert(cb.submitMove("A1", "C3") == NO_ERROR);
  assert(cb.submitMove("C8", "D7") == NO_ERROR);
  assert(cb.submitMove("F1", "E1") == NO_ERROR);
  assert(cb.submitMove("E8", "D8") == NO_ERROR);
  // opponent resigned here. let's see how game could have continued!
  assert(cb.submitMove("F2", "F4") == NO_ERROR);
  assert(cb.submitMove("G5", "F6") == NO_ERROR);
  assert(cb.submitMove("C3", "F6") == NO_ERROR);
  assert(cb.submitMove("G7", "F6") == NO_ERROR);
  assert(cb.submitMove("A3", "E7") == NO_ERROR);
  assert(cb.submitMove("D8", "E8") == NO_ERROR);
  assert(cb.submitMove("E7", "F6") == NO_ERROR);
  assert(cb.submitMove("D7", "E6") == NO_ERROR);
  assert(cb.submitMove("F6", "H8") == NO_ERROR);
  assert(cb.submitMove("A8", "D8") == NO_ERROR);
  assert(cb.submitMove("F4", "F5") == NO_ERROR);
  assert(cb.submitMove("A7", "A6") == NO_ERROR);
  assert(cb.submitMove("F5", "E6") == NO_ERROR);
  assert(cb.submitMove("A6", "A5") == NO_ERROR);
  assert(cb.submitMove("E6", "F7") == NO_ERROR);
  assert(cb.submitMove("E8", "D7") == NO_ERROR);
  assert(cb.submitMove("H8", "D4") == NO_ERROR);
  assert(cb.submitMove("A5", "A4") == NO_ERROR);
  assert(cb.submitMove("D4", "C5") == NO_ERROR);
  assert(cb.submitMove("A4", "A3") == NO_ERROR);
  assert(cb.submitMove("D3", "F5") == NO_ERROR);
  // check state is checkmate
  assert(cb.getState() == CHECKMATE);
  // check submission of additional move returns GAME OVER
  assert(cb.submitMove("E8", "A8") == GAME_IS_OVER);
      
  // restore cout
  cr.restoreCout();


  std::cout << "   Tests for Game 1 passed!\n";
}
