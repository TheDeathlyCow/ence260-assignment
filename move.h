/**
 * @file move.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief Implements movement.
 */
#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "maze.h"
#include "input.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * Called when the navswitch is pressed, and moves the player one
 * cell in the given direction, and sets the cell they exited to be a wall.
 * 
 * @param maze The current maze.
 * @param playerPosition The current position of the player.
 * @param direction The direction the player is moving in.
 * @return Returns true when the player cannot move in the given direction
 * (ie, the next cell is a wall or out of bounds).
 */
bool move_onNavswitchEvent(Maze_t* maze, Position_t* playerPosition, NavswitchInput_t direction);

#endif