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
   * Constructor. Creates 64 Squares and 32 Pieces and sets them up on 
   * the board. These Squares and Pieces are allocated memory which the 
   * desctructor will free. 
   */
  ChessBoard(){init();}

  
  /**
   * Destructor. Frees memory allocated to Squares. Square's destructor 
   * frees memory allocated to its Piece if it has one.
   */
  ~ChessBoard(){destroySquares();}

  /**
   * Mutator. Creates 64 chessboard Squares and copes their pointers to the
   * square_ptrs array. Creates 32 Pieces and sets them on the appropriate
   * squares as chess rules dicate it. Copies Kings pointers to 
   * kings_square_ptrs. Sets the color to play next to white.
   */
  void init();

  /**
   * Mutator. Frees memory allocated to ChessBoard Squares.
   */
  void destroySquares();


  /**
   * Mutator. Frees memory allocated to Squares and Pieces, then calls init.
   */
  void resetBoard();
  
  
  /**
   * Mutator. If both inputs are valid (see utils.h) and from_square has
   * a piece, moves the piece to to_square if it is possible and legal
   * according to the rules of chess.
   */
  void submitMove(const char* from_square,
		  const char* to_square);

  /**
   * Mutator. Requires rank array size >= 8. Copies pointers to Squares 
   * with given rank_index into rank, in increasing file index order.
   */
  void getRow(int rank_index, Square** rank);


  /**
   * Mutator. Requires file array size >= 8. Copies pointers to Squares 
   * with given file_index into file, in increasing file index order.
   */
  void getColumn(int file_index, Square** file);



  /**
   * Mutator. Requires diagonal array size >= 8. Looks at rank index 
   * increasing Copies pointers to 
   * Squares on the diagonal that contains Square with given rank_index and
   * file index, in increasing file index order.
   */
  
  /**
   * Method which, given a file, a rank and an array of 8 square pointers:
   *   - looks at the rank increasing diagonal (/) if rank_increasing is true
   *     otherwise looks at the rank decreasing diagonal (\)
   *   - copies all pointers to squares in the appropriate diagonal that contains 
   *     the square with given rank and file, in increasing file order.
   */
  void getDiagonal(int rank, int file, Square** diagonal,
		   bool rank_increasing);

  /**
   * Reader method which given a rank and a file,
   * returns the approprite square pointer;
   */
  Square* getSquare(const char* sqr_str)const;

  void prepareNextTurn();


  bool kingIsInCheck(Color color);

  bool noPieceCanMove(Color color);
  /**
   * Reader debugging method which prints the chessboard
   * to the standard output stream.
   */
  void printBoard();

  void printObjects();

};

#endif
