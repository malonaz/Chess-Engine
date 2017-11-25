#include "utils.h"


bool isValidSquare(const char* square_string){
  
  if (square_string[FILE_CHAR_INDEX] < 'A'||
      square_string[FILE_CHAR_INDEX] > 'H')
    return false;

  if (square_string[RANK_CHAR_INDEX] < '1'||
      square_string[RANK_CHAR_INDEX] > '8')
    return false;

  if (square_string[SENTINEL_CHAR_INDEX] != '\0')
    return false;
  return true;
}

const int getRank(const char* square_string){
  return square_string[RANK_CHAR_INDEX] - '1';
}

const int getFile(const char* square_string){
  return square_string[FILE_CHAR_INDEX] - 'A';
}
