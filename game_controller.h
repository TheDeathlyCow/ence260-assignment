/**
 * @file game_controller.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 15 October 2021
 * @brief Controls the game state and handles relevant functions
 * for each tick of the game.
 */
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// The program loop rate, in Hz.
#define PACER_RATE 500
// How fast the player should move, in cells / second
#define MOVEMENT_RATE 8

#include "maze.h"
#include "position.h"
#include "input.h"
#include "levels.h"
#include "move.h"
#include "menus.h"

/**
 * Enum that defines the current state of the game.
 */
typedef enum {
    STARTING,
    MENU,
    WAITING,
    MOVING,
    NEXT_LEVEL,
    VICTORY_SCREEN,
    GAME_OVER
} GameState_t;

/**
 * Initialises objects needed for the game controller.
 */
void game_controller_init(void);

/**
 * Handles 1 tick of the game.
 * @param level A pointer to the current level.
 * @param playerPosition A pointer to the player's current position.
 */
void game_controller_update(Level_t** level, Position_t* playerPosition);

#endif

