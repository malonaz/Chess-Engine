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
 * Piece. This abstract superclass represents the shared
 * attributes of all chess pieces:
 * pawn, knights, bishops, rooks, queens and kings.
 * A piece is characterized by:
 *  - a color (black or white)
 *  - has_moved which indicates whether this piece has moved
 *    squares since the beginning of a chess game.
 *  - a constant character representing the type of piece it is 
 */
class Piece{
protected:
  const Color color;
  bool has_moved;
  const PieceType type;

public:
    static int num_pieces;
  
  /**
   * Constructor which, given a color and a character representation,
   * instantiates both of these constant fields.
   */
  Piece(const Color color, const PieceType type);

  /**
   * Virtual destructor so derived destructor is called when
   * manipulating a derived Piece object.
   */
  virtual ~Piece(){num_pieces--;}

  
  /**
   * Pure virtual observer method, which all 
   * derived pieces will need to implement
   */
  virtual bool canMove(Square* sqr_source_ptr, Square* sqr_dest_ptr);

  virtual void update() = 0;
  
  /**
   * Observer method which sets has_moved to true
   */
  void setToMoved(){has_moved = true;};
  
  /**
   * Observer method, which returns the character 
   * representation of this piece
   */
  const PieceType getType()const{return type;}

  /**
   * Observer method, which returns the color 
   * of this piece
   */
  const Color getColor() const{return color;}

  friend std::ostream& operator<<(std::ostream& stream, Piece* piece_ptr);
};

#endif
