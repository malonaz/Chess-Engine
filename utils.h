#ifndef UTILS_H
#define UTILS_H

// forward declaration
class Square;


// definitions
#define MIN_INDEX 0
#define MAX_INDEX 7

#define FILE_CHAR_INDEX 0
#define RANK_CHAR_INDEX 1
#define SENTINEL_CHAR_INDEX 2

#define LOWEST_FILE_CHAR 'A'
#define LOWEST_RANK_CHAR '1'

// dimensions
#define INCORRECT -1
#define NO_CHANGE 0
#define DIAGONAL 1
#define HORIZONTAL 2
#define VERTICAL 3

// error codes
enum Error{ VALID, INVALID_SQUARE, EMPTY_SQUARE, WRONG_COLOR, DISCOVERS_CHECK, TAKES_PIECE_OF_SAME_COLOR, PATH_OBSTRUCTED, PIECE_DOES_NOT_MOVE_THIS_WAY};

bool isValidSquare(const char* square_string);

const int parseRank(const char* square_string);

const int parseFile(const char* square_string);

bool validIndex(int index);

int getMoveDimension(int rank_shift, int file_shift);

int getMoveMagnitudeSquared(int rank_shift, int file_shift);


int getPointerIndex(Square** pointers, Square* pointer);


bool isInBetween(int num, int a, int b);


#endif
