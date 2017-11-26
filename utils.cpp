#include "utils.h"


// definitions


bool isValidSquare(const char* square_string){
  int rank = square_string[RANK_CHAR_INDEX] - LOWEST_RANK_CHAR;
  if (!validIndex(rank))
    return false;
  // step by step prevents segmentation error.
  int file = square_string[FILE_CHAR_INDEX] - LOWEST_FILE_CHAR;
  if (!validIndex(file))
    return false;

  if (square_string[SENTINEL_CHAR_INDEX] != '\0')
    return false;
  
  return true;
}

const int parseRank(const char* square_string){
  return square_string[RANK_CHAR_INDEX] - '1';
}

const int parseFile(const char* square_string){
  return square_string[FILE_CHAR_INDEX] - 'A';
}

bool validIndex(int index){
  if (index < MIN_INDEX || index > MAX_INDEX)
    return false;
  return true;
}
