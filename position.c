/** 
 * @file position.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 10 October 2021
 * @brief Handles positions on a maze and within a room. 
 */
#include "position.h"

/**
 * Compares two positions and returns if they are equal.
 * @param a First position
 * @param b Second position
 * @return Returns true if the row of a matches the row of b and the col of a
 * matches the col of b.
 */
bool position_equals(const Position_t a, const Position_t b)
{
    return a.row == b.row && a.col == b.col;
}

/**
 * Adds two positions together, and returns the result.
 * @param a First position
 * @param b Second position
 * @return The position containing the sum of 
 * the rows and cols of two positions. 
 */
Position_t position_add(const Position_t a, const Position_t b)
{
    Position_t result = {
        .row = a.row + b.row,
        .col = a.col + b.col
    };
    return result;
}

/**
 * Converts the given aboslute maze position to a position
 * relative to the room of the position.
 * @param pos The current absolute position.
 * @return Returns a position relative to a room.
 */
Position_t position_getRelativePos(const Position_t* pos)
{
    Position_t relativePos = {
        .row = pos->row % LEDMAT_ROWS_NUM,
        .col = pos->col % LEDMAT_COLS_NUM
    };

    return relativePos;
}