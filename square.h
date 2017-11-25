// -*- C++ -*-
#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"


/**
 * Square. This class represents a square
 * on a chessboard as:
 *   - file int in range [0,7]:
 *     file 'a' corresponds to 0, 'b' to 1 etc.
 *   - rank int in range [0,7]:
 *     rank 1 corresponds to 1, 1 to 2 etc.
 *   - if square is empty, piece_ptr points to a Piece
 *     otherwise, points to the NULL pointer.
 */
class Square{
private:
  const int file;
  const int rank;
  Piece* piece_ptr;
  
public:
  static int num_squares;
  /**
   * Constructor which initializes constants file and rank
   * and sets piece_ptr to NULL.
   */
  Square(int file, int rank);

  /**
   * Destructor which deletes piece_ptr if is_free is false;
   */
  ~Square();

  
  /**
   * Internal helper method which, given a valid destination square ptr
   *   - returns the difference between the destination square's file
   *     and this square's file
   */
  const int filesTo(Square* sqr_dest_ptr) const;

  /**
   * Internal helper method which, given a valid destinatin square ptr
   *   - returns the difference between the destination square's rank
   *     and this square's rank
   */
  const int ranksTo(Square* sqr_dest_ptr) const;


  ///////////////////// PIECE RELATED METHODS
  /**
   *  Reader method.
   *    - returns true if is_free points to NULL (0)
   *    - else return false
   */
  bool isEmpty() const;


  /**
   * Reader method.
   *   - returns piece_ptr
   */
  Piece* getPiece() const {return piece_ptr;}
  
  /** 
   * Mutator method, which given a piece_ptr:
   *  - sets this piece_ptr to piece_ptr;
   *  - sets is_free to false;
   *  - set piece_ptr's square ptr to point to this
   */ 
  void setPiece(Piece* piece_ptr);

  /**
   * Mutator method:
   *   - if this square is not empty
   *     > delete the object piece_ptr points to
   *     > sets piece_ptr to NULL
   */
  void destroyPiece();

  /**
   * Mutator method, which give an valid destination square ptr:
   *   - if this square is not free and moving from this square
   *     to sqr_dest_ptr is valid for this square's piece:
   *      > if sqr_dest_ptr is not free,
   *        calls sqr_dest_ptr's destroyPiece method
   *      > set sqr_dest_ptr's piece_ptr to point to 
   *        this square's piece
   *      > sets piece_ptr to NULL
   */
  bool movePiece(Square* sqr_dest_ptr);

  
};


#endif
