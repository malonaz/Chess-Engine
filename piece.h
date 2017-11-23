// -*- C++ -*-
#ifndef PIECE_H
#define PIECE_H

#include "square.h"

enum Color{white, black};

class Piece{
protected:
  const Color color;
  Square* square;
  Piece(Color color): color(color){}
  
public:
  virtual ~Piece() = 0;
  virtual bool legalMove(Square destination); 
  virtual void moveTo(Square destination);
};


#endif
