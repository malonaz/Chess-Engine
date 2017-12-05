#include "utilsTest.h"
#include "utils.h"
#include "ChessBoard.h"
#include "square.h"
#include <iostream>
#include <cstring>
#include <assert.h>




void testUtils(){
  std::cout << " Starting tests for utils\n";
  
  testIsValidSquare();
  testGetMoveDimension();
  testGetPointerIndex();
  testIsInBetween();
  
  std::cout << " finished tests for utils\n\n";
}


void testIsValidSquare(){
  // iterate through ascii characters
  for (int rank = 0; rank < 256; rank++)
    for (int file = 0; file < 256; file++){
      std::string square_string;
      square_string += file;
      square_string += rank;
      const char* c_square_string = square_string.c_str();
      if (char(rank) >= '1' && char(rank) <= '8' &&
	  char(file) >= 'A' && char(file) <= 'H')
	// it is a legal square
	assert(isValidSquare(c_square_string));
      else
	assert(!isValidSquare(c_square_string));
    }

  // test various wrong size inputs
  assert(!isValidSquare(""));
  assert(!isValidSquare(" "));
  assert(!isValidSquare("1A"));
  assert(!isValidSquare("3"));
  assert(!isValidSquare("A "));
  assert(!isValidSquare("A22 "));
  assert(!isValidSquare("BB"));
  assert(!isValidSquare("A3 "));    
        
  std::cout << "   Tests for IsValidSquare passed!" << std::endl;

}





void testGetMoveDimension(){
  // test no diff 
  assert(getMoveDimension(0,0) == NO_CHANGE);
  
  // test diagonal in each of the 4 quadrants
  assert(getMoveDimension(1,1) == DIAGONAL);
  assert(getMoveDimension(-1,1) == DIAGONAL);
  assert(getMoveDimension(1,-1) == DIAGONAL);
  assert(getMoveDimension(-1,-1) == DIAGONAL);

  //test horizontal in 2 directions
  assert(getMoveDimension(0,1) == HORIZONTAL);
  assert(getMoveDimension(0,-1) == HORIZONTAL);

  // test vertical in 2 directions
  assert(getMoveDimension(1,0) == VERTICAL);
  assert(getMoveDimension(-1,0) == VERTICAL);

  // test incorrect in 4 quadrants
  assert(getMoveDimension(1,2) == INCORRECT);
  assert(getMoveDimension(-2,1) == INCORRECT);
  assert(getMoveDimension(1,-2) == INCORRECT);
  assert(getMoveDimension(-2,-1) == INCORRECT);

std::cout << "   Tests for GetMoveDimension passed!" << std::endl;
}



void testGetPointerIndex(){
  // dummy chessboard_pointer for square initialization
  ChessBoard* chessboard_p = 0;
  Square* squares[64];
  int index = 0;
  for (int rank = MIN_INDEX; rank <= MAX_INDEX; rank++)
    for (int file = MIN_INDEX; file <= MAX_INDEX; file++){
      squares[index] = new Square();
      squares[index]->init(chessboard_p, rank, file);
      index++;
    }

  for (int index = 0; index < 64; index++)
    assert(getPointerIndex(squares, squares[index]) == index);
  

  for (int index = 0; index < 64; index++)
    // free memory
    delete squares[index];
  
  std::cout << "   Tests for getPointerIndex passed!" << std::endl;
}



void testIsInBetween(){
  int left = -10;
  int right = 40;
  for (int i = -10 + 1; i < 40; i++){
    assert(isInBetween(i, left, right));
    assert(isInBetween(i, right, left));
  }

  // test edges
  assert(!isInBetween(left, left, right));
  assert(!isInBetween(left, right, left));
  assert(!isInBetween(right, left, right));
  assert(!isInBetween(left, right, left));

  // test no number in between
  left = 0;
  right = 1;
  for (int i = -10 + 1; i < 40; i++){
    assert(!isInBetween(i, left, right));
    assert(!isInBetween(i, right, left));
  }

  // test tricky boundary
  left = -1;
  right = 1;
  assert(isInBetween(0, left, right));

  std::cout << "   Tests for IsInBetween passed!" << std::endl;

}

