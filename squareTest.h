#ifndef SQUARE_TEST_H
#define SQUARE_TEST_H


/**
 * Tests Square class.
 */
void testSquare();



/**
 * Tests static member num squares.
 */
void testStaticNumSquares();

/**
 * Tests square destructor.
 */ 
void testSquareDestructor();

/**
 * Test getSquareBelow method.
 */
void testGetSquareBelow();


/**
 * Tests GetPath method. all cases.
 */
void testGetPath();

/**
 * Tests the rankDiff and fileDiff methods. all cases.
 */
void testRankFileDiff();

/**
 * Tests the getRank & getFile method. all cases.
 */
void testGetRankGetFile();

/**
 * Tests movePutsKingInCheck method by pinning each type of black piece
 * and white piece, attempting to move the pinned piece and checking 
 * whether this results in a discovered check. Checks castling and 
 * en passant potential discovered checks as well.
 */
void testMovePutsKingInCheck();


/**
 * Tests the getDiagonal method. tests following cases:
 * - A7-B8 diagonal && B8-A7 diagonals
 * - A1-H8 diagonal
 * - A8-H1 diagonal
 */
void testGetDiagonal();


#endif
