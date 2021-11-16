/**
 * @file levels.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Implements a system for storing and retrieving the levels
 * of the game.
 */
#include "levels.h"

#define LEVEL_ONE_SIZE 1
#define LEVEL_TWO_SIZE 2
#define LEVEL_THREE_SIZE 2

/**
 * Creates and gets the level 1 maze.
 * 
 * @return Returns a dynamically allocated pointer to the level 1 maze.
 */
static Maze_t* levels_getMaze1(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b1000101,
        0b1010101,
        0b1010001,
        0b1111111
    }};

    Bitmap_t* lvl1_maps = calloc(LEVEL_ONE_SIZE * LEVEL_ONE_SIZE, sizeof(Bitmap_t));

    memcpy(lvl1_maps, maps, LEVEL_ONE_SIZE * LEVEL_ONE_SIZE * sizeof(Bitmap_t));

    Maze_t levelOneMaze = {
        .size = LEVEL_ONE_SIZE,
        .rooms = lvl1_maps,
        .goalPosition = {5, 3},
        .playerStartPosition = {1, 1}
    };

    Maze_t* mazePtr = calloc(1, sizeof(Maze_t));
    *mazePtr = levelOneMaze;
    return mazePtr;
}

/**
 * Creates and gets the level 2 maze.
 * 
 * @return Returns a dynamically allocated pointer to the level 2 maze.
 */
static Maze_t* levels_getMaze2(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b0000001,
        0b1111101,
        0b0000101,
        0b0000101
    },{
        0b1111111,
        0b1000000,
        0b1000000,
        0b1000000,
        0b1100000
    },{
        0b1000001,
        0b1000111,
        0b0000001,
        0b0000001,
        0b1111111
    },{
        0b1100001,
        0b1000001,
        0b1010000,
        0b1011000,
        0b1111111
    }};

    Bitmap_t* lvl2_maps = calloc(LEVEL_TWO_SIZE * LEVEL_TWO_SIZE, sizeof(Bitmap_t));

    memcpy(lvl2_maps, maps, LEVEL_TWO_SIZE * LEVEL_TWO_SIZE * sizeof(Bitmap_t));

    Maze_t levelTwoMaze = {
        .size = LEVEL_TWO_SIZE,
        .rooms = lvl2_maps,
        .goalPosition = {12, 8},
        .playerStartPosition = {1, 1}
    };

    Maze_t* mazePtr = calloc(1, sizeof(Maze_t));
    *mazePtr = levelTwoMaze;
    return mazePtr;
}

/**
 * Creates and gets the level 3 maze.
 * 
 * @return Returns a dynamically allocated pointer to the level 3 maze.
 */
static Maze_t* levels_getMaze3(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b0000001,
        0b0100001,
        0b0100001,
        0b0000001
    },{
        0b1111111,
        0b1000000,
        0b1100000,
        0b1001111,
        0b1000000
    },{
        0b1000001,
        0b1100001,
        0b0000101,
        0b0001001,
        0b1111111
    },{ 
        0b1000000,
        0b1011111,
        0b1000000,
        0b1001000,
        0b1111111
    }};

    Bitmap_t* lvl3_maps = calloc(LEVEL_THREE_SIZE * LEVEL_THREE_SIZE, sizeof(Bitmap_t));

    memcpy(lvl3_maps, maps, LEVEL_THREE_SIZE * LEVEL_THREE_SIZE * sizeof(Bitmap_t));

    Maze_t levelTwoMaze = {
        .size = LEVEL_THREE_SIZE,
        .rooms = lvl3_maps,
        .goalPosition = {3, 3},
        .playerStartPosition = {2, 2}
    };

    Maze_t* mazePtr = calloc(1, sizeof(Maze_t));
    *mazePtr = levelTwoMaze;
    return mazePtr;
}

/**
 * Dynamically allocates pointers to each level of the game, 
 * and puts them into a linked list.
 * @return A dynamically-allocated pointer to the head of the new list.
 */
Level_t* levels_init(void)
{
    Level_t* level1 = calloc(1, sizeof(Level_t));
    Level_t* level2 = calloc(1, sizeof(Level_t));
    Level_t* level3 = calloc(1, sizeof(Level_t));
    level1->maze = levels_getMaze1();
    level1->nextLevel = level2;
    
    level2->maze = levels_getMaze2();
    level2->nextLevel = level3;
    
    level3->maze = levels_getMaze3();
    level3->nextLevel = NULL;

    return level1;
}

/**
 * Sets the current level to the next level, and frees the current level.
 * 
 * @param level The current level.
 */
void levels_nextLevel(Level_t** level)
{   
    if (*level != NULL) {
        Level_t* next = (*level)->nextLevel;
        free((*level)->maze->rooms);
        free((*level)->maze);
        free(*level);
        *level = next;
    }
}