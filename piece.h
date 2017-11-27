// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

//definitions 
#define PAWN 1
#define KNIGHT 2
#define ROOK 3

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
  const bool white;
  bool has_moved;
  const int id;

public:
    static int num_pieces;
  
  /**
   * Constructor which, given a color and a character representation,
   * instantiates both of these constant fields.
   */
  Piece(const bool white, const int id);

  /**
   * Virtual destructor so derived destructor is called when
   * manipulating a derived Piece object.
   */
  virtual ~Piece(){num_pieces--;}

  
  /**
   * Pure virtual observer method, which all 
   * derived pieces will need to implement
   */
  virtual bool move(Square* sqr_source_ptr, Square* sqr_dest_ptr) = 0;

  virtual void update() = 0;
  
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
  const bool isWhite() const{return white;}

};

#endif
