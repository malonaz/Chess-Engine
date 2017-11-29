// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

#include <iostream>

// colors
enum Color {BLACK, WHITE};
std::ostream& operator<<(std::ostream& stream, Color color);
  
// pieces
enum PieceType {PAWN, KNIGHT, ROOK, BISHOP, QUEEN, KING};
std::ostream& operator<<(std::ostream& stream, PieceType type);


// forward declaration
class Square;


/**
 * Piece. This abstract class represents the shared a chess piece. A
 * chess piece is represented by a color, a type and a boolean variable
 * indicating whether this piece has moved squares since its creation.
 */
class Piece{
  
protected:
  const Color color;
  bool has_moved; 
  const PieceType type;

public:
    static int num_pieces;
  
  /**
   * Constructor. Initializes a piece's color and type.
   */
  Piece(const Color color, const PieceType type);

  
  /**
   * Destructor. Virtual so that derived class destructors are called
   * when manipulating Piece objects. Decrements num_pieces.
   */
  virtual ~Piece(){num_pieces--;}

  
  /**
   * Observer. Returns true if the move from the Square at from_square_p
   * to the Square at to_square_p is legal as per chess rules.
   */
  virtual bool canMove(Square* from_square_p, Square* to_square_p, bool move_piece = false);


  // ?????????????????????????????????????
  virtual void update() = 0;

  
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
   * Observer. Returns true if this piece has not been moved since setting the baord
   */
  bool hasMoved()const{return has_moved;}


  friend std::ostream& operator<<(std::ostream& stream, Piece* piece_p);
  

};

#endif
