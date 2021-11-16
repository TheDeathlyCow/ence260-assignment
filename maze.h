/**
 * @file maze.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Handles maze logic, including rendering, the position of walls,
 * and whether or not the player can move. 
 */
#ifndef MAZE_H
#define MAZE_H

#include "bitmap.h"
#include "position.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * A struct that contains a matrix of n x n rooms and
 * a goal position.
 */
typedef struct {
    uint8_t size;
    Bitmap_t* rooms;
    Position_t goalPosition;
    Position_t playerStartPosition;
} Maze_t;

/**
 * Draws the maze to the LED matrix, with the player's position at the given
 * pacer rate.
 * @param maze Maze to draw.
 * @param playerPosition The current position of the player.
 * @param pacerRate The pacer rate.
 */
void maze_draw(const Maze_t* maze, const Position_t* playerPosition, const uint16_t pacerRate);

/**
 * Determines if the player is at the maze's goal position.
 * @param maze The maze to look in.
 * @param playerPosition The current position of the player.
 * @return Returns true if the player is at the goal position.
 */
bool maze_atGoal(const Maze_t* maze, const Position_t* playerPosition);

/**
 * Called when a player exits a cell, and sets that cell in the maze to
 * be a wall.
 * @param maze The maze of the cell, will be modified.
 * @param cellPosition The cell the player left.
 */
void maze_onLeaveCell(Maze_t* maze, const Position_t* cellPosition);

/**
 * Determines if the cell at the given position in the maze is a wall.
 * @param maze The maze to check the cell of.
 * @param position The position to check.
 * @return Returns true if the given position is a wall (in essence, returns
 * the state of a given cell).
 */
bool maze_isWall(const Maze_t* maze, const Position_t* position);

/**
 * Determines if the player can move in any direction.
 * @param maze The maze the player is in.
 * @param playerPosition The current position of the player.
 * @return Returns true if any of the neighbouring cells are free, false
 * otherwise.
 */
bool maze_canMove(const Maze_t* maze, const Position_t* playerPosition);

#endif