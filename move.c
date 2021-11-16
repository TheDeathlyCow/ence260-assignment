/**
 * @file move.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief Implements movement.
 */
#include "move.h"

static Position_t neighbour_vectors[] = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {0, 0}, {0, 0}
};

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
bool move_onNavswitchEvent(Maze_t* maze, Position_t* playerPosition, NavswitchInput_t direction)
{
    Position_t nextPosition = position_add(*playerPosition, neighbour_vectors[direction]);

    if (!maze_isWall(maze, &nextPosition)) {
        maze_onLeaveCell(maze, playerPosition);
        *playerPosition = position_add(*playerPosition, neighbour_vectors[direction]);
        nextPosition = position_add(*playerPosition, neighbour_vectors[direction]);
        return false;
    } else {
        return true;
    }
}