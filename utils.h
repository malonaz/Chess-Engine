#ifndef UTILS_H
#define UTILS_H

// forward declaration
class Square;


/**
 * Definitions used to parse a chessboard square string.
 */
#define MIN_INDEX 0
#define MAX_INDEX 7

#define FILE_CHAR_INDEX 0
#define RANK_CHAR_INDEX 1
#define SENTINEL_CHAR_INDEX 2

#define LOWEST_FILE_CHAR 'A'
#define LOWEST_RANK_CHAR '1'


/**
 * Definitions used to describe dimensions of moves 
 */
enum Dimension{NO_CHANGE, DIAGONAL, HORIZONTAL, VERTICAL, INCORRECT};

/**
 * Error. Enum used to describe move results
 */
enum Error{ NO_ERROR, INVALID_MOVE, INVALID_SQUARE, EMPTY_SQUARE, MOVE_OUT_OF_TURN,
	    KING_IS_IN_CHECK, TAKES_PIECE_OF_SAME_COLOR, PATH_OBSTRUCTED,
	    GAME_IS_OVER};


/**
 * Function which returns true if square string describes a square such
 * that its first char is in the range ['A', 'H'], second char is in the
 * range ['1', '8'] and third char is the '\0' sentinel.
 */
bool isValidSquare(const char* square_string);


/**
 * Require a valid square string input. Function which extracts rank 
 * number from its square string input and returns it as an integer 
 * such that rank 1 returns 0 & rank 8 returns 7.
 */
const int parseRank(const char* square_string);


/**
 * Require a valid square string input. Function which extracts file 
 * number from its square string input and returns it as an integer 
 * such that file 'A' returns 0 & file 'H' returns 7.
 */
const int parseFile(const char* square_string);

/**
 * Returns true if given index lies in range [0, 7].
 */
bool validIndex(int index);

/**
 * Returns dimension (see definitions above) of the move vector with
 * the given rank_diff and file_diff component.
 */
Dimension getMoveDimension(int rank_diff, int file_diff);

/**
 * Returns the square of the move vector with the given rank_diff and 
 * file_diff component.
 */
int getMoveMagnitudeSquared(int rank_diff, int file_diff);

/**
 * Requires that the given pointer is in the given array of pointers.
 * Returns the index of pointer in the pointers array.
 */
int getPointerIndex(Square** pointers, Square* pointer);


/**
 * Returns true if num is in range (a, b).
 */
bool isInBetween(int num, int a, int b);


#endif
