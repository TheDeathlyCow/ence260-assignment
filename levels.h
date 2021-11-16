/**
 * @file levels.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 15 October 2021
 * @brief Implements a system for storing and retrieving the levels
 * of the game.
 */
#ifndef LEVELS_H
#define LEVELS_H

#include "maze.h"
#include "bitmap.h"
#include "position.h"
#include <stdlib.h>
#include <string.h>

/**
 * A linked list struct for levels.
 */
typedef struct Level_s {
    Maze_t* maze;
    struct Level_s* nextLevel;
} Level_t;

/**
 * Dynamically allocates pointers to each level of the game, 
 * and puts them into a linked list.
 * @return A dynamically-allocated pointer to the head of the new list.
 */
Level_t* levels_init(void);

/**
 * Sets the current level to the next level, and frees the current level.
 * 
 * @param level The current level.
 */
void levels_nextLevel(Level_t** head);

#endif