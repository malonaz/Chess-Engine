#include "utils.h"
#include "square.h"
#include <cmath>

// definitions

bool isValidSquare(const char* square_string){

  int file = parseFile(square_string);
  if (!validIndex(file))
    return false;
  // step by step prevents segmentation error.

  int rank = parseRank(square_string);
  if (!validIndex(rank))
    return false;

  // check string ends here
  if (square_string[SENTINEL_CHAR_INDEX] != '\0')
    return false;
  
  return true;
}

const int parseRank(const char* square_string){
  return square_string[RANK_CHAR_INDEX] - LOWEST_RANK_CHAR;
}

const int parseFile(const char* square_string){
  return square_string[FILE_CHAR_INDEX] - LOWEST_FILE_CHAR;
}



bool validIndex(int index){
  if (index < MIN_INDEX || index > MAX_INDEX)
    return false;
  return true;
}


int getMoveDimension(int rank_shift, int file_shift){
  int abs_rank_shift = std::abs(rank_shift);
  int abs_file_shift = std::abs(file_shift);

  if (rank_shift == NO_CHANGE){
    if (file_shift == NO_CHANGE)
      return NO_CHANGE;
    else
      return HORIZONTAL;
  }else{
    if (file_shift == NO_CHANGE)
      return VERTICAL;
    if (abs_rank_shift == abs_file_shift)
      return DIAGONAL;
  }
  return INCORRECT;
}


int getMoveMagnitudeSquared(int rank_shift, int file_shift){
  return rank_shift*rank_shift + file_shift*file_shift;
}


int getPointerIndex(Square** pointers, Square* pointer){
  int index = 0;
  for (; pointers[index] != pointer; index++);
  return index;
}
