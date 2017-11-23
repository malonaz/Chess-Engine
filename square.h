// -*- C++ -*-
#ifndef SQUARE_H
#define SQUARE_H

// Forward declaration
class Piece;
	  

class Square{
private:
  const int file;
  const int rank;
  Piece* piece;
  bool is_free;
  
public:
  Square(int file, int rank);
  ~Square(){}
  void setPiece(Piece* piece){this->piece = piece;}
  bool isFree() {return is_free;}
  Piece* getPiece(){return piece;}
  int filesTo(Square square_destination);
  int ranksTo(Square square_destination);
};


#endif
