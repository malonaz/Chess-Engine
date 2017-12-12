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
  int rank_i;
  int file_i;
  Piece* piece_p;

 public:
  
  // keeps track of number of square objects. used for testing & debugging
  static int num_squares;

  /**
   * Constructor. Increments num of squares
   */
  Square(){num_squares++;}
  
  /**
   * Mutator. Initializes chessboard_p to point to the chessboard this
   * Square belongs to. Initializes file_i & rank_i. sets piece_p to NULL.
   */
  void init(ChessBoard* chessboard_p, int rank_i, int file_i);

  
  /**
   * Destructor. Calls destroyPiece, then decrements static num_squares
   */
  ~Square();


  /**
   * Observer. Returns the difference between the index indices of the 
   * Square at the given pointer and this Square.
   */
  const int rankDiff(Square* sqr_to_square_p) const;
  

  /**
   * Observer. Returns the difference between the file indices of the 
   * Square at the given pointer and this Square.
   */
  const int fileDiff(Square* to_square_p) const;

  
  /**
   * Observer. Returns this Square's rank index
   */
  int getRankIndex()const{return rank_i;}

  
  /**
   * Observer. Returns this Square's file index.
   */
  int getFileIndex()const{return file_i;}


  /**
   * Mutator. Requires path array size >= 8. Makes sure that the dimensions
   * of the path requested correspond to the type of the piece moving. 
   * Copies pointers to all the squares on the diagonal, horizontal 
   * or vertical path the squares starting at this Square & ending with 
   * the Square at the given pointer, into the given path array, then 
   * returns true. Returns false if there is no such path.
   */
  bool getPath(Square* to_square_p, Square** path, PieceType type);

  
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
   * Mutator. Requires diagonal array size >= 8 & this != to_square_p. 
   * Copies pointers to Squares in the chessboard diagonal that contains 
   * both this square and the one at the given pointer, in increasing 
   * file index order.
   */
  void getDiagonal(Square* to_square_p, Square** diagonal);


  /**
   * Observer. Requires this square to have 0 < rank index < 7. Returns a 
   * pointer to the Square below this Square, from the perspective of the 
   * player with the given color.
   */
  Square* getSquareBelow(const Color color) const;

  
  /**
   *  Observer. Returns true if this square has a piece.
   */
  bool hasPiece() const{ return piece_p != 0;}
  

  /**
   * Observer. Returns this square's piece pointer. Caller should call
   * hasPiece method before to make sure this square has a piece.
   */
  Piece* getPiece() const {return piece_p;}

  
  /**
   * Mutator. Caller must make sure that if called while this square has
   * a piece, its pointer is saved or its allocated memory freed prior the
   * to the call to avoid a memory leak. Sets this square's piece pointer
   * equal to the given pointer.
   */ 
  void setPiece(Piece* piece_p){this->piece_p = piece_p;}

  
  /**
   * Mutator. Frees memory allocated to this square's piece if it has one
   * then sets its pointer to null.
   */
  void destroyPiece();

  
  /**
   * Mutator. Requires this Square has a piece. If moving the piece from 
   * this square to the square at given pointer is legal as per chess 
   * rules, this method moves this square's piece to it, updates the moved 
   * piece to indicate it has moved, then sets this square's piece pointer 
   * to NULL. If to_square has a piece, the piece will be deleted off the heap.  
   * Returns an Error describing the outcome of this move attempts.
   * (see utils.h for Error descriptions)
   */
  Error movePiece(Square* to_square_p);

  
  /**
   * Mutator. Requires this Square to have a piece. Returns true if moving
   * this Square's piece to the Square at the given pointer would put the 
   * player's king in check, as per chess rules. This method will undo
   * any mutation it induces.
   */
  bool movePutsKingInCheck(Square* to_square_p);

  
  /**
   * Mutator. Requires this Square to have a piece. Returns true if this 
   * Square's piece can move to a square.
   */
  bool pieceCanMove();

  
  /**
   * Observer. Returns true if opponent of given player_color is attacking
   * this square.
   */
  bool isUnderAttack(Color player_color);
  
};


#endif
