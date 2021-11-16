/** 
 * @file bitmap.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 10 October 2021
 * @brief Handles bitmaps for LED matrix drawing.
 */
#include "bitmap.h"

static const pio_t rows[LEDMAT_ROWS_NUM] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t cols[LEDMAT_COLS_NUM] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/**
 * Turns all of the pins on the LED matrix off by 
 * setting them to HIGH.
 */
static void reset_ledmat(void)
{
    for (size_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }

    for (size_t i = 0; i < LEDMAT_COLS_NUM; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}

/**
 * Displays a single column of a bitmap on the LED matrix. 
 */
static void display_column(uint8_t columnPattern, uint8_t currentColumn)
{
    static uint8_t previousCol = LEDMAT_COLS_NUM - 1;
    pio_config_set(cols[previousCol], PIO_OUTPUT_HIGH);

    for (size_t rowNum = 0; rowNum < LEDMAT_ROWS_NUM; rowNum++) {
        if ((columnPattern >> rowNum) & 1) {
            pio_output_low(rows[rowNum]);
        } else {
            pio_output_high(rows[rowNum]);
        }
    }

    pio_config_set(cols[currentColumn], PIO_OUTPUT_LOW);
    previousCol = currentColumn;
}

/** Initialise led matrix for drawing */
void bitmap_init(void)
{
    reset_ledmat();
}

/**
 * Displays the next row of the given map.
 * @param map The map to display.
 */
void bitmap_display(const Bitmap_t* map)
{
    static uint8_t currentColumn = 0;
    display_column((*map)[currentColumn], currentColumn);
    
    currentColumn ++;
    currentColumn %= LEDMAT_COLS_NUM;
}

/**
 * Row and col of the map to the value.
 * @param map The map to be modified.
 * @param pos The position of the value.
 * @param value The value to set - must be 1 or 0.
 */
void bitmap_set(Bitmap_t* map, Position_t pos, bool value)
{
    if (value) {
        (*map)[pos.col] |= BIT(pos.row);
    } else {
        (*map)[pos.col] &= ~BIT(pos.row);
    }
}

/**
 * Returns the state of the bitmap at the row and col.
 * @param map The map to check.
 * @param pos The position to check.
 * @return Returns 1 or 0.
 */
bool bitmap_get(const Bitmap_t* map, Position_t pos)
{   
    return ((*map)[pos.col] >> pos.row) & 1;
}