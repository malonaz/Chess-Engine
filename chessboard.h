// -*- C++ -*-
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "square.h"
#include "piece.h"

#define MIN_INDEX 0
#define MAX_INDEX 7

class Chessboard{
private:
  Square* squares[8][8];
  bool white_turn;
public:
  Chessboard();
  ~Chessboard();
};

#endif
