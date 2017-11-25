#ifndef UTILS_H
#define UTILS_H

#define FILE_CHAR_INDEX 0
#define RANK_CHAR_INDEX 1
#define SENTINEL_CHAR_INDEX 2


bool isValidSquare(const char* square_string);

const int getRank(const char* square_string);

const int getFile(const char* square_string);

#endif
