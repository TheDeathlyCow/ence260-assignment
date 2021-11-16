/**
 * @file game.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief A simple puzzle/maze game with multiple rooms and a fun movement
 * mechanic.
 */
#include "game_controller.h"
#include "levels.h"
#include "button.h"
#include "maze.h"
#include "position.h"
#include "pacer.h"
#include "system.h"
#include <stdbool.h>


/**
 * Initialises the game and then enters an infinite loop.
 */
int main(void)
{
    system_init();
    pacer_init(PACER_RATE); 
    game_controller_init();

    Level_t* level = levels_init();
    Position_t playerPosition = level->maze->playerStartPosition;
    

    while (true) {
        pacer_wait();
        game_controller_update(&level, &playerPosition);
    }
}
