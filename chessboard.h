// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "piece.h"

// definitions
#define SQUARES_PER_SIDE 8
// ranks
#define WHITE_RANK1 0
#define WHITE_RANK2 1
#define BLACK_RANK1 7
#define BLACK_RANK2 6

// files
#define KNIGHT1_FILE 1
#define KNIGHT2_FILE 6
#define ROOK1_FILE 0
#define ROOK2_FILE 7


// forward declarations
class square;

/**
 * Chessboard. This class represents a chessboard,
 * as an array of pointers to squares, and 
 * a boolean variable to keep track of which player's
 * turn is it next.
 */
class ChessBoard{
private:
  Square* square_ptrs[SQUARES_PER_SIDE][SQUARES_PER_SIDE];
  bool white_to_play;
  
public:
  /**
   *  Constructor which simply calls init method
   */
  ChessBoard(){init();}
  
  /**
   * Destructor which calls destroySquares
   */
  ~ChessBoard(){destroySquares();}

  /**
   * Method which:
   *  - initializes white_turn to true;
   *  - creates 64 Square objects on the heap
   *    and assigns their pointers to the square_ptrs array.
   */
  void init();

  /**
   * helper method which:
   *  - deletes all 64 square objects on the heap
   */
  void destroySquares();

  /*
   * Method which given two strings: 
   *  - if one of the string does not represents a square as 
   *    a letter in [A-H] and a number in [1-8], ???
   *  -  
   */
  void submitMove(const char* source_sqr_str,
		  const char* dest_sqr_str);
  /**
   * Method which:
   *  - calls destructor
   *  - calls init
   */
  void resetBoard();
    
  void getRow(int rank, Square** row);
  void getColumn(int file, Square** column);
  void getDiagonals(int rank, int file, Square*** diagonals);

  /**
   * Reader method which given a rank and a file,
   * returns the approprite square pointer;
   */
  Square* getSquare(const char* sqr_str)const;

  void prepareNextTurn();
  
  /**
   * Reader debugging method which prints the chessboard
   * to the standard output stream.
   */
  void printBoard();

  void printObjects();


};

#endif
