// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "square.h"

// GUI
#define HORIZONTAL_BAR " ---------------------------------"
#define VERTICAL_BAR " | "


// definitions
#define SQUARES_PER_SIDE 8
#define NUMBER_OF_COLORS 2

// ranks
#define WHITE_RANK1 0
#define WHITE_RANK2 1
#define BLACK_RANK1 7
#define BLACK_RANK2 6

enum File{ROOK1_FILE, KNIGHT1_FILE, BISHOP1_FILE, QUEEN_FILE,
	  KING_FILE, BISHOP2_FILE, KNIGHT2_FILE,ROOK2_FILE};

enum State{PLAYING_GAME, CHECKMATE, STALEMATE};


/**
 * Chessboard. This class represents a chessboard as:
 *   - 8 rows of Squares
 *   - an array of 2 pointers to the squares which hold Kings
 *   - a binary Color variable to keep track of turns 
 *   - a variable indicating the game's state
 */
class ChessBoard{
  
private:
  Square squares[SQUARES_PER_SIDE][SQUARES_PER_SIDE];
  Square* kings_square_ps[NUMBER_OF_COLORS];
  Color color_to_play;
  State state;
  
public:
  
  /**
   * Constructor. Initiates Squares, then calls Chessboard's init method
   */			 
  ChessBoard();

  
  /**
   * Destructor. Calls destroySquares method.
   */
  ~ChessBoard(){destroySquares();}
  

  /**
   * Mutator. Creates 64 chessboard Squares and copies their pointers into
   * square_ps array. Creates 32 Pieces and sets them on the appropriate
   * squares as standard chess rules would have it. Copies Kings pointers
   * to kings_square_ps. Sets the color to play next to white.
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
   * Mutator. Requires both inputs be valid (see utils.h). If there is a piece
   * at from_square, moves it to_square if it is possible and legal
   * according to the rules of chess.
   */
  Error submitMove(const char* from_square, const char* to_square);


  /**
   * Mutator. Changes the color to play next. Checks if next player is in
   * stalemate, checkmate or check. Writes information to std output stream.
   */
  void prepareNextTurn();

  
  /**
   * Observer. Requires input be a valid (see utils.h) chess square coordinate.
   * returns a pointer to the square at the given coordinates.
   */
  Square* getSquare(const char* sqr_coordinates);


  /**
   * Observer. Requires valid rank and file index in range [0,7], returns
   * pointer to square at the the given indices.
   */
  Square* getSquare(int rank_i, int file_i);
  

  /**
   * Observer. Returns the pointer to the square the king of the given color
   * is currently on.
   */
  Square* getKingSquareP(Color color)const{return kings_square_ps[color];}

  
  /**
   * Mutator. Updates the chessboard's pointer to the square where the
   * king of given color is.
   */
  void setKingSquareP(Color king_color, Square* king_square_p);
  
  
  /**
   * Observer. returns true if king is in check.
   */
  bool kingIsInCheck(Color color);

  
  /**
   * Observer. Returns true if player of given color can move a piece.
   */
  bool playerCanMove(Color color);

  
  /**
   * Observer. Prints board state to std output stream.
   */
  void printBoard();

  
  /**
   * Observer. Prints number of Squares and Pieces to the board.
   */
  void printObjects()const;



  /**
   * Observer. Returns this board's state
   */
  State getState(){return state;}
};

#endif
