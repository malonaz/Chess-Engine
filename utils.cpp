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


Dimension getMoveDimension(int rank_diff, int file_diff){
  int abs_rank_diff = std::abs(rank_diff);
  int abs_file_diff = std::abs(file_diff);

  if (rank_diff == NO_CHANGE){
    if (file_diff == NO_CHANGE)
      return NO_CHANGE;
    
    else
      return HORIZONTAL;
    
  }else{
    if (file_diff == NO_CHANGE)
      return VERTICAL;
    
    if (abs_rank_diff == abs_file_diff)
      return DIAGONAL;
  }
  
  return INCORRECT;
}


int getMoveMagnitudeSquared(int rank_diff, int file_diff){
  return rank_diff*rank_diff + file_diff*file_diff;
}


int getPointerIndex(Square** pointers, Square* pointer){
  int index = 0;
  for (; pointers[index] != pointer; index++);
  return index;
}


