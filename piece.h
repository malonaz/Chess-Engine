// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

#include "square.h"

#define NO_MOVEMENT 0

enum Color{white, black};

class Piece{
protected:
  const Color color;
  bool has_moved;
  Square* square;
  Piece(Color color): color(color), has_moved(false){}
  
public:
  virtual ~Piece(){}
  virtual bool legalMove(Square square_destination) = 0; // makes this an abstract class 
  // virtual void moveTo(Square destination);
  void setSquare(Square *square){this->square = square;}
};

#endif
