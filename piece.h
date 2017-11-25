// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

// forward declaration
class Square;

#define NO_MOVEMENT 0

// used to represent the color of pieces
enum Color{white, black};


/**
 * Piece. This abstract superclass represents the shared
 * attributes of all chess pieces:
 * pawn, knights, bishops, rooks, queens and kings.
 * A piece is characterized by:
 *  - a color (black or white)
 *  - has_moved which indicates whether this piece has moved
 *    squares since the beginning of a chess game.
 *  - a Square ptr pointing to the square this piece is on
 *  - a constant character representing the type of piece it is 
 */
class Piece{
protected:
  const Color color;
  bool has_moved;
  Square* square_ptr;
  const char repr;

public:
    static int num_pieces;
  
  /**
   * Constructor which, given a color and a character representation,
   * instantiates both of these constant fields.
   */
  Piece(Color color, char repr);


  /**
   * Virtual destructor so derived destructor is called when
   * manipulating a derived Piece object.
   */
  virtual ~Piece(){num_pieces--;}

  /**
   * Pure virtual observer method, which all 
   * derived pieces will need to implement
   */
  virtual bool isLegalMove(Square* sqr_dest_ptr)const = 0;

  /**
   * Mutator method which:
   *   - sets this square_ptr to given square_ptr
   */
  void setSquare(Square* square_ptr){this->square_ptr = square_ptr;}
  
  /**
   * Observer method, which returns the character 
   * representation of this piece
   */
  const char getRepr()const{return repr;}

  /**
   * Observer method, which returns the color 
   * of this piece
   */
  const Color getColor() const{return color;}

};

#endif
