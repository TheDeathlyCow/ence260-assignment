/**
 * @file maze.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Handles maze logic, including rendering, the position of walls,
 * and whether or not the player can move. 
 */
#include "maze.h"

#define NUM_NEIGHBOURS 4

#define PLAYER_DRAW_FREQ 2
#define GOAL_DRAW_FREQ 8

static Position_t neighbour_vectors[] = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {0, 0}, {0, 0}
};

/**
 * Returns a pointer to the room of the given position within the maze. 
 * @param maze The maze to retrieve from.
 * @param pos The position that is within the returned room. 
 * @return Returns a pointer to the room (a bitmap) that the position is contained in.
 * If the position is out of bounds, returns NULL.
 */
static Bitmap_t* maze_getRoomOfPosition(const Maze_t* maze, const Position_t* pos)
{
    uint8_t roomRow = pos->row / LEDMAT_ROWS_NUM;
    uint8_t roomCol = pos->col / LEDMAT_COLS_NUM;

    if (roomRow > (LEDMAT_ROWS_NUM * maze->size) || roomCol > (LEDMAT_COLS_NUM * maze->size)) {
        return NULL;
    }

    return &maze->rooms[roomRow + maze->size * roomCol];
}

/**
 * Determines if two positions are in the same room.
 * @param pos1 The first position.
 * @param pos1 The second position.
 * @return Returns true if the two positions are in the same room.
 */
static bool maze_inSameRoom(const Position_t* pos1, const Position_t* pos2)
{
    Position_t pos1Room = {
        .row = pos1->row / LEDMAT_ROWS_NUM,
        .col = pos1->col / LEDMAT_COLS_NUM
    };

    Position_t pos2Room = {
        .row = pos2->row / LEDMAT_ROWS_NUM,
        .col = pos2->col / LEDMAT_COLS_NUM
    };

    return position_equals(pos1Room, pos2Room);
}

/**
 * Draws the maze to the LED matrix, with the player's position at the given
 * pacer rate.
 * @param maze Maze to draw.
 * @param playerPosition The current position of the player.
 * @param pacerRate The pacer rate.
 */
void maze_draw(const Maze_t* maze, const Position_t* playerPosition, const uint16_t pacerRate)
{
    static uint16_t ticks = 0;
    static bool playerOn = true;
    static bool goalOn = true;
    Bitmap_t* playerRoom = maze_getRoomOfPosition(maze, playerPosition);
    Bitmap_t* displayedRoom = calloc(1, sizeof(Bitmap_t));
    memcpy(displayedRoom, playerRoom, sizeof(Bitmap_t));
    Position_t roomPos = position_getRelativePos(playerPosition);
    if (ticks % (pacerRate / PLAYER_DRAW_FREQ) == 0) {
        playerOn = !playerOn;
    }

    Position_t goalPos = position_getRelativePos(&(maze->goalPosition));
    if (ticks % (pacerRate / GOAL_DRAW_FREQ) == 0) {
        goalOn = !goalOn;
    }

    if (maze_inSameRoom(playerPosition, &(maze->goalPosition))) {
        bitmap_set(displayedRoom, goalPos, goalOn);
    }
    bitmap_set(displayedRoom, roomPos, playerOn);

    ticks++;
    ticks %= pacerRate;
    bitmap_display(displayedRoom);

    free(displayedRoom);
}

/**
 * Determines if the player is at the maze's goal position.
 * @param maze The maze to look in.
 * @param playerPosition The current position of the player.
 * @return Returns true if the player is at the goal position.
 */
bool maze_atGoal(const Maze_t* maze, const Position_t* playerPosition)
{
    return position_equals(maze->goalPosition, *playerPosition);
}

/**
 * Called when a player exits a cell, and sets that cell in the maze to
 * be a wall.
 * @param maze The maze of the cell, will be modified.
 * @param cellPosition The cell the player left.
 */
void maze_onLeaveCell(Maze_t* maze, const Position_t* cellPosition)
{
    Bitmap_t* oldRoom = maze_getRoomOfPosition(maze, cellPosition);
    Position_t roomPos = position_getRelativePos(cellPosition);
    bitmap_set(oldRoom, roomPos, 1);
}

/**
 * Determines if the cell at the given position in the maze is a wall.
 * @param maze The maze to check the cell of.
 * @param position The position to check.
 * @return Returns true if the given position is a wall (in essence, returns
 * the state of a given cell).
 */
bool maze_isWall(const Maze_t* maze, const Position_t* position)
{
    if (!(position->row < (maze->size * LEDMAT_ROWS_NUM) - 1
            && position->col < (maze->size * LEDMAT_COLS_NUM) - 1
            && position->row > 0
            && position->col > 0)) {
        return true;
    }

    Bitmap_t* room = maze_getRoomOfPosition(maze, position);
    Position_t roomPos = position_getRelativePos(position);
    return bitmap_get(room, roomPos);
}

/**
 * Determines if the player can move in any direction.
 * @param maze The maze the player is in.
 * @param playerPosition The current position of the player.
 * @return Returns true if any of the neighbouring cells are free, false
 * otherwise.
 */
bool maze_canMove(const Maze_t* maze, const Position_t* playerPosition)
{
    bool canMove = false;
    for (uint8_t i = 0; i < NUM_NEIGHBOURS; i++) {
        Position_t pos = position_add(*playerPosition, neighbour_vectors[i]);
        if (!maze_isWall(maze, &pos)) {
            canMove = true;
        }
    }
    return canMove;
}