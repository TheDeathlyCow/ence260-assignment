/** 
 * @file bitmap.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 10 October 2021
 * @brief Handles bitmaps for LED matrix drawing.
 */
#ifndef BITMAP_H
#define BITMAP_H

#include "pio.h"
#include "position.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * In essence, an array of 5 bytes that correspond to
 * the columns of the LED matrix. In this definition,
 * 1 corresponds to ON and 0 corresponds to OFF. The 
 * first bit is ignored.
 * 
 * For example, the following definition of a Bitmap_t
 * will display a smiley face:
 * @code
 * Bitmap_t bitmap = {
 *      0b0100000,
 *      0b1000110,
 *      0b1010000,
 *      0b1000110,
 *      0b0100000
 * };
 * @endcode
 */
typedef uint8_t Bitmap_t[5];

/** Initialise led matrix for drawing */
void bitmap_init(void);

/**
 * Displays the next row of the given map.
 * @param map The map to display.
 */
void bitmap_display(const Bitmap_t* map);

/**
 * Row and col of the map to the value.
 * @param map The map to be modified.
 * @param pos The position of the value.
 * @param value The value to set - must be 1 or 0.
 */
void bitmap_set(Bitmap_t* map, Position_t pos, bool value);

/**
 * Returns the state of the bitmap at the row and col.
 * @param map The map to check.
 * @param pos The position to check.
 * @return Returns 1 or 0.
 */
bool bitmap_get(const Bitmap_t* map, Position_t pos);

#endif