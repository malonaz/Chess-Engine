#ifndef SQUARE_TEST_H
#define SQUARE_TEST_H


/**
 * Tests Square class.
 */
void testSquare();


/**
 * Test the rankDiff and fileDiff methods
 */
void testRankFileDiff();

/**
 * Test the getRank & getFile method
 */
void testGetRankGetFile();

/**
 * Tests movePutsKingInCheck method by pinning each type of black piece
 * and white piece, attempting to move the pinned piece and checking 
 * whether this results in a discovered check. Checks castling and 
 * en passant potential discovered checks as well.
 */
void testMovePutsKingInCheck();



#endif
