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
class ChessBoard{
private:
  Square* square_ptrs[8][8];
  Color color_to_play;
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

  
  /**
   * Method which:
   *  - calls destructor
   *  - calls init
   */
  void resetBoard();

  
  /**
   * Reader method which given a rank and a file,
   * returns the approprite square pointer;
   */
  Square* getSquare(const char* sqr_str)const;
  
  /*
   * Method which given two strings: 
   *  - if one of the string does not represents a square as 
   *    a letter in [A-H] and a number in [1-8], ???
   *  -  
   */
  void submitMove(const char* source_sqr_str,
		  const char* dest_sqr_str);


  void changeColorToPlay();
  
  /**
   * Reader debugging method which prints the chessboard
   * to the standard output stream.
   */
  void printBoard();

  void printObjects();
};

#endif