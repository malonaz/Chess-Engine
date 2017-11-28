// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "piece.h"

// GUI
#define HORIZONTAL_BAR " ---------------------------------"
#define VERTICAL_BAR " | "


// definitions
#define SQUARES_PER_SIDE 8
#define NUMBER_OF_COLORS 2
#define NUMBER_OF_PIECES_PER_COLOR 8

// ranks
#define WHITE_RANK1 0
#define WHITE_RANK2 1
#define BLACK_RANK1 7
#define BLACK_RANK2 6

// files
#define ROOK1_FILE   0
#define KNIGHT1_FILE 1
#define BISHOP1_FILE 2
#define QUEEN_FILE   3
#define KING_FILE    4
#define BISHOP2_FILE 5
#define KNIGHT2_FILE 6
#define ROOK2_FILE   7


// forward declaration
class square;

/**
 * Chessboard. This class represents a chessboard as:
 *   - 8 rows of 8 pointers to Squares
 *   - a boolean variable to keep track of turns 
 *   - an array of 2 pointers to square which hold the two Kings
 */
class ChessBoard{
  
private:
  Square* square_ptrs[SQUARES_PER_SIDE][SQUARES_PER_SIDE];
  Square* kings_square_ptrs[NUMBER_OF_COLORS];
  Color color_to_play;
  
public:
  /**
   * Constructor. Calls init method.
   */			 
  ChessBoard(){init();}
  

  /**
   * Destructor. Calls destroySquares method.
   */
  ~ChessBoard(){destroySquares();}
  

  /**
   * Mutator. Creates 64 chessboard Squares and copies their pointers into
   * square_ptrs array. Creates 32 Pieces and sets them on the appropriate
   * squares as standard chess rules would have it. Copies Kings pointers
   * to kings_square_ptrs. Sets the color to play next to white.
   */
  void init();
  

  /**
   * Mutator. Frees memory allocated to all 64 ChessBoard Squares.
   */
  void destroySquares();
  

  /**
   * Mutator. calls destroySquares then init.
   */
  void resetBoard();

  
  /**
   * Mutator. Requires both inputs be valid (see utils.h) and from_square
   * has a piece. Moves the piece to to_square if it is possible and legal
   * according to the rules of chess.
   */
  void submitMove(const char* from_square, const char* to_square);

  
  /**
   * Observer. Requires input be a valid (see utils.h) chess square coordinate.
   * returns a pointer to the square at the given coordinates.
   */
  Square* getSquare(const char* sqr_coordinates)const;


  /**
   * Observer. Requires valid rank and file index in range [0,7], returns
   * pointer to square at the the given indices.
   */
  Square* getSquare(int i_rank, int i_file)const{return square_ptrs[i_rank][i_file];}

  /**
   * Mutator. Changes the color to play next. Checks if next player is in
   * stalemate, checkmate or check. Writes information to std output stream.
   */
  void prepareNextTurn();


  /**
   * Observer. returns true if king is in check.
   */
  bool kingIsInCheck(Color color);

  
  /**
   * Observer. Returns true if player of given color cannot move any piece.
   */
  bool cannotMove(Color color)const;

  
  /**
   * Observer. Prints board state to std output stream.
   */
  void printBoard()const;

  
  /**
   * Observer. Prints number of Squares and Pieces to the board.
   */
  void printObjects()const;

};

#endif