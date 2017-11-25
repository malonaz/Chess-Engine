// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

// forward declaration
class Square;

#define NO_MOVE 0
#define PAWN 1

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
 *  - a constant character representing the type of piece it is 
 */
class Piece{
protected:
  const Color color;
  bool has_moved;
  const int id;

public:
    static int num_pieces;
  
  /**
   * Constructor which, given a color and a character representation,
   * instantiates both of these constant fields.
   */
  Piece(const Color color, const int id);

  /**
   * Virtual destructor so derived destructor is called when
   * manipulating a derived Piece object.
   */
  virtual ~Piece(){num_pieces--;}

  /**
   * Pure virtual observer method, which all 
   * derived pieces will need to implement
   */
  virtual bool move(Square* sqr_source_ptr,
			   Square* sqr_dest_ptr)const = 0;


  /**
   * Observer method which sets has_moved to true
   */
  void setToMoved(){has_moved = true;};

  
  /**
   * Observer method, which returns the character 
   * representation of this piece
   */
  const int getID()const{return id;}

  /**
   * Observer method, which returns the color 
   * of this piece
   */
  const Color getColor() const{return color;}

};

#endif