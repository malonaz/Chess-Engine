#ifndef SQUARE_TEST_H
#define SQUARE_TEST_H


/**
 * Tests Square class.
 */
void testSquare();


/**
 * test the rankDiff and fileDiff methods
 */
void testRankFileDiff();


/**
 * Tests movePutsKingInCheck method by pinning each type of black piece
 * and white piece, attempting to move the pinned piece and checking 
 * whether this results in a discovered check. Checks castling and 
 * en passant potential discovered checks as well.
 */
void testMovePutsKingInCheck();



#endif
