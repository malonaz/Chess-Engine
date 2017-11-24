// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "square.h"
#include "piece.h"

#define MIN_INDEX 0
#define MAX_INDEX 7

/**
 * Chessboard. This class represents a chessboard,
 * as an array of pointers to squares, and 
 * a boolean variable to keep track of which player's
 * turn is it next.
 */
class Chessboard{
private:
  Square* square_ptrs[8][8];
  bool white_turn;
public:
  /**
   *  Constructor which:
   *  - initializes white_turn to true;
   *  - creates 64 Square objects on the heap
   *    and assigns their pointers to the square_ptrs array.
   */
  Chessboard();

  /**
   * Destructor which:
   *  - deletes all 64 square objects on the heap,
   */
  ~Chessboard();

  /**
   * Reader method which given a rank and a file,
   * returns the approprite square pointer;
   */
  Square* getSquare(int rank, int file) const {return square_ptrs[rank][file];}

  
  /**
   * Reader debugging method which prints the chessboard
   * to the standard output stream.
   */
  void printBoard();

};

#endif
