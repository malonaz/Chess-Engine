// -*- C++ -*-
#ifndef SQUARE_H
#define SQUARE_H

// forward declarations
class Piece;
class ChessBoard;


/**
 * Square. This class represents a square
 * on a chessboard as:
 *   - a pointer to the chessboard it belongs to
 *   - file int in range [0,7]:
 *     file 'a' corresponds to 0, 'b' to 1 etc.
 *   - rank int in range [0,7]:
 *     rank 1 corresponds to 1, 1 to 2 etc.
 *   - if square is empty, piece_ptr points to a Piece
 *     otherwise, points to NULL
 */
class Square{

private:
  ChessBoard* chessboard;
  const int file;
  const int rank;
  Piece* piece_ptr;

public:
  // keeps track of number of squares. used for debugging
  static int num_squares;

  
  /**
   * Constructor which:
   *    - initializes chessboard_ptr
   *    - initializes constants file and rank
   *    - sets piece_ptr to NULL.
   *    - increments num_squares
   */
  Square(ChessBoard* chessboard, int file, int rank);

  /**
   * Destructor which:
   *   - deletes piece_ptr if this square has a piece
   *   - decrements num_squares
   */
  ~Square();

  
  /**
   * Internal helper method which, given a valid destination Square pointer:
   *   - returns the difference between the destination square's file
   *     and this square's file
   */
  const int filesTo(Square* sqr_dest_ptr) const;

  /**
   * Internal helper method which, given a valid destinatin Square pointer:
   *   - returns the difference between the destination square's rank
   *     and this square's rank
   */
  const int ranksTo(Square* sqr_dest_ptr) const;

  /**
   * Observer method which returns rank
   */
  int getRank(){return rank;}

  /**
   * Observer method which returns file
   */
  int getFile(){return file;}
  
  /**
   * Method which given a pointer to a destination Square and an array
   * of 8 NULL Square pointers (longest path <= 8)
   *   - returns false if there is no horizontal, vertical or diagonal
   *     path from this square to the destination square
   *   - otherwise, copies pointers to all squares in that path to the 
   *     path array, starting with this square and ending with the 
   *     destination square, then returns true
   */
  bool getPath(Square* sqr_dest_ptr, Square** path, int piece_ID);

  /**
   * Method which given an array of 8 Square pointers, copies all
   * pointers to the Squares in the same row as this square into it.
   */
  void getRow(Square** row);

  /**
   * Method which given an array of 8 Square pointers, copies all
   * pointers to the Squares in the same column as this square into it.
   */
  void getColumn(Square** column);

  
  void getDiagonal(Square* sqr_dst_ptr, Square** diagonal);

  // PIECE RELATED METHODS //
  
  /**
   *  Method which returns true if this square has no piece
   */
  bool isEmpty() const;


  /**
   * Reader method which returns a pointer to this square's piece
   */
  Piece* getPiece() const {return piece_ptr;}
  
  /** 
   * Mutator method which given a piece pointer:
   *  - deletes this square's current piece if it has one
   *  - sets its piece pointer to the given piece pointer
   */ 
  void setPiece(Piece* piece_ptr);

  /**
   * Mutator method which delete this square's piece if it has one
   * and sets its pointer to NULL
   */
  void destroyPiece();

  /**
   * Mutator method which given a pointer to a valid destination square
   *   - if this square has a piece, which can legally move to the
   *     the destination square:
   *      > delete the destination square's piece if it has one
   *      > moves this square's piece to the destination square
   *      > sets this square's piece pointer to NULL
   *      > updates the moved piece to indicate it has moved
   */
  bool movePiece(Square* sqr_dest_ptr);
  
};


#endif
