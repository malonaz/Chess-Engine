// -*- C++ -*-
#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

// forward declarations
class ChessBoard;



/**
 * Square. This class represents a square on a chessboard as:
 *   - a pointer to the chessboard it belongs to
 *   - a file index in range [0, 7] s.t file 0 maps to 'a' & 7 to 'h''
 *   - a rank index in range [0 ,7] s.t rank 0 maps to 1  & 7 to 8
 *   - a pointer to the Piece currently on this square or to NULL
 *     if this square does not have a piece
 */
class Square{

private:
  ChessBoard* chessboard_p;
  const int file_i;
  const int rank_i;
  Piece* piece_p;

public:
  // keeps track of number of squares. used for testing & debugging
  static int num_squares;

  
  /**
   * Constructor. Initializes chessboard_p to point to the chessboard this
   * Square belongs to. Initializes file_i & rank_i. sets piece_p to NULL.
   * Increments num_squares.
   */
  Square(ChessBoard* chessboard, int file_i, int rank_i);

  
  /**
   * Destructor which:
   *   - deletes piece_ptr if this square has a piece
   *   - decrements num_squares
   */
  ~Square();

  
  /**
   * Observer. Returns the difference between the file indices of the 
   * Square at the given pointer and this Square.
   */
  const int filesTo(Square* dest_p) const;

  
  /**
   * Observer. Returns the difference between the index indices of the 
   * Square at the given pointer and this Square.
   */
  const int ranksTo(Square* sqr_dest_p) const;

  
  /**
   * Observer. Returns this Square's rank index
   */
  int getRankIndex(){return rank_i;}


  /**
   * Observer. Returns this Square's file index.
   */
  int getFileIndex(){return file_i;}

  
  /**
   * Mutator. Requires path array size >= 8. Copies all squares on the 
   * diagonal, horizontal or vertical path starting at this Square 
   * & ending with the Square at the given pointer, into the given
   * path array, then returns true. Returns false if there is no such path.
   */
  bool getPath(Square* dest_p, Square** path, PieceType type);


  /**
   * Mutator. Requires rank array size >= 8. Copies pointers to Squares 
   * in this Square's rank into rank, in increasing file index order.
   */
  void getRank(Square** rank);

  /**
   * Mutator. Requires file array size >= 8. Copies pointers to Squares
   * in this Square's file into file, in increasing rank index order.
   */
  void getFile(Square** file);


  /**
   * Mutator. Requires diagonal array size >= 8. Copies pointers to Squares
   * in the chessboard diagonal that contains both this square and the one
   * at the given pointer, in increasing file order.
   */
  void getDiagonal(Square* dest_p, Square** diagonal);

  
  /**
   *  Observer. Returns true if this square has a piece.
   */
  bool hasPiece() const;


  /**
   * Observer. Returns a pointer to this square's piece.
   */
  Piece* getPiece() const {return piece_p;}

  
  /**
   * Mutator. calls destroyPiece method then sets its piece pointer 
   * equal to the given piece pointer.
   */ 
  void setPiece(Piece* piece_p);

  
  /**
   * Mutator. Frees memory allocated to this square's piece if it has one
   * then sets its pointer to NULL.
   */
  void destroyPiece();
  

  /**
   * Mutator. Requires this Square has a piece, which is of the color that
   * is play next. If moving the piece from this square to the square at
   * given pointer is legal as per chess rules, this method calls 
   * the destination Square's destroy method on it,  moves this 
   * square's piece to it, updates the moved piece to indicate it has moved, 
   * then sets this square's piece pointer to NULL. Returns true if piece 
   * what moved. Returns false otherwise.
   */
  bool movePiece(Square* dest_p);


  /**
   * Mutator. Requires this Square to have a piece. Returns true if moving
   * this Square's piece to the Square at the given pointer would put the 
   * king of the player in check, as per chess rules. This method will undo
   *  any mutation it induces.
   */
  Bool movePutsKingInCheck(Square* dest_p);


  /**
   * Mutator. Requires this Square to have a piece. Returns true if this 
   * Square's piece can move to a square.
   */
  bool pieceCanMove();
};


#endif
