// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

#include "utils.h"
#include <ostream>


// colors
enum Color {BLACK, WHITE};
  
// piece types
enum PieceType {PAWN, KNIGHT, ROOK, BISHOP, QUEEN, KING, DUMMY};

/* overloads Color's << operator */
std::ostream& operator<<(std::ostream& stream, Color color);

/* overloads PieceType's operator */
std::ostream& operator<<(std::ostream& stream, PieceType type);

// forward declaration
class Square;


/**
 * Piece. This abstract class represents a chess piece. A
 * chess piece is represented by a color, a type and a boolean variable
 * indicating whether this piece has moved since its creation.
 */
class Piece{
  
protected:
  const Color color;
  bool has_moved; 
  const PieceType type;

public:
    static int num_pieces;
  
  /**
   * Constructor. Initializes a piece's color, type & has_moved to false
   */
  Piece(const Color color, const PieceType type);

  
  /**
   * Destructor. Virtual but not needed as derived classes do not have
   * destructors. Decrements num_pieces.
   */
  virtual ~Piece(){num_pieces--;}

   
  /**
   * Mutator. Virtual so that derived classes implementation is called
   * when manipulating Piece objects. Checks if move from square at 
   * from_square_p to square at to_square_p is legal and possible. Does not 
   * check for king checks in base class implementation. Returns an Error
   * describing the move (see utils.h for more info). The move_piece boolean
   * variable is not used in the base class implementation but can be used by
   * derived classes s.t. if true, the method may modify squares other than the 
   * from_square and to_square for moves such as enPassant or castling!
   */
  virtual Error moveIsLegal(Square* from_square_p, Square* to_square_p, bool move_piece = false);

  /**
   * Observer. Method which checks that move from the square at to_square_p to 
   * square at to_square_p does not move a piece on top of a piece of the same color.
   * It then calls moveIsLegal virtual method.
   */
  Error canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);

  
  
  /**
   * Mutator. Moves this piece from the square at from_square_p to 
   * the square at to_square_p. Calls canMove with move_piece = true as
   * derived classes may need to move other pieces (en passant, castling).
   * note: this method deletes the piece at to_square_p if there is one
   */
  void move(Square* from_square_p, Square* to_square_p);

    
  /**
   * Mutator. Sets has_moved to true.
   */
  void setToMoved(){has_moved = true;};

  
  /**
   * Observer. Returns the type of this piece
   */
  const PieceType getType()const{return type;}

  
  /**
   * Observer. Returns the color of this piece
   */
  const Color getColor() const{return color;}


  /**
   * Observer. Returns true if this piece has not been moved since
   * the chessboard was initialized or reset.
   */
  bool hasMoved()const{return has_moved;}  

  
  /**
   * Observer. Returns true if the square at the given pointer has a piece
   * of the same color as this piece.
   */  
  bool squareOccupiedByFriendlyPiece(Square* square_p)const;

  
  /**
   * Friend. overloads operator for piece pointers. Used by printBoard()
   */
  friend std::ostream& operator<<(std::ostream& stream, Piece* piece_p);
  

};

#endif
