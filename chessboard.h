// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "square.h"
#include "piece.h"

class Chessboard{
private:
  Square* squares[8][8];
  bool white_turn;
public:
  Chessboard();

  ~Chessboard();
};



#endif
