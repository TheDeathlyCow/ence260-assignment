/**
 * @file menus.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Provides functionality for menus. Essentially is a 
 * wrapper for tinygl.
 * 
 */
#ifndef MENUS_H
#define MENUS_H

#include "button.h"
#include "led.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <stdbool.h>
#include <stdint.h>

#define MENU_MAIN_TEXT "Welcome to Amazeing Mazes!"
#define MENU_NEXT_LEVEL_TEXT "Level complete!"
#define MENU_GAME_COMPLETE_TEXT "Game complete!"
#define MENU_GAME_OVER_TEXT "Game over :("

/**
 * Initialises the menus.
 * @param rate The rate in Hz at which the menus are updated.
 */
void menus_init(const uint16_t rate);

/**
 * Sets the text of the menu.
 * @param text
 */
void menus_setText(char* text); 

/**
 * Updates the menu.
 * @return Returns true when the pushbutton is pressed.
 */
bool menus_update(void);

#endif