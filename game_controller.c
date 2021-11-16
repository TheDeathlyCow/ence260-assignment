/**
 * @file game_controller.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 15 October 2021
 * @brief Controls the game state and handles relevant functions
 * for each tick of the game.
 */
#include "game_controller.h"

/**
 * Moves the game to the next level, and returns the game state.
 * @param level A pointer to a pointer to the current level, will be modified.
 * @param playerPosition A pointer to the player's current position.
 * @return Returns the game state after moving to the next level, which will either be
 * NEXT_LEVEL or VICTORY_SCREEN.
 */
static GameState_t gotoNextLevel(Level_t** level, Position_t* playerPosition)
{
    levels_nextLevel(level);
    if (*level != NULL) {
        *playerPosition = ((*level)->maze)->playerStartPosition;
        menus_setText(MENU_NEXT_LEVEL_TEXT);
        return NEXT_LEVEL;
    } else {
        menus_setText(MENU_GAME_COMPLETE_TEXT);
        return VICTORY_SCREEN;
    }
}

/**
 * Handles one tick for the WAITING state.
 * @param level A pointer to a pointer to the current level. May be modified.
 * @param playerPosition A pointer to the player's position. May be modified.
 * @param navswitchState The input from the navswitch. Will NOT be modified.
 * @return Returns the game state after this tick.
 */
static GameState_t waiting_update(Level_t** level, Position_t* playerPosition, const NavswitchInput_t navswitchState)
{
    GameState_t postState = WAITING;
    if (maze_atGoal((*level)->maze, playerPosition)) {
        postState = gotoNextLevel(level, playerPosition);
    } else if (!maze_canMove((*level)->maze, playerPosition)) {
        menus_setText(MENU_GAME_OVER_TEXT);
        postState = GAME_OVER;
    } else if (navswitchState != NAVSTATE_UNPUSHED && navswitchState != NAVSTATE_PUSHED) {
        postState = MOVING;
    }
    return postState;
}

/**
 * Handles one tick for the MOVING state.
 * @param level A pointer to the current level. May be modified.
 * @param playerPosition A pointer to the player's position. May be modified.
 * @param direction The direction in which the player will be travelling. Will NOT be modified.
 * @return Returns the game state after this tick.
 */
static GameState_t moving_update(Level_t** level, Position_t* playerPosition, const NavswitchInput_t direction)
{
    static uint16_t ticks = 0;
    static const uint16_t ticksPerMoveUpdate = PACER_RATE / MOVEMENT_RATE;
    if (maze_atGoal((*level)->maze, playerPosition)) {
        return gotoNextLevel(level, playerPosition);
    } else if (ticks % ticksPerMoveUpdate == 0 && direction != NAVSTATE_PUSHED && direction != NAVSTATE_UNPUSHED) {
        if (move_onNavswitchEvent((*level)->maze, playerPosition, direction)) {
            return WAITING;
        }
    }
    ticks++;
    ticks %= PACER_RATE;
    return MOVING;
}

/**
 * Initialises objects needed for the game controller.
 */
void game_controller_init(void)
{
    bitmap_init();
    menus_init(PACER_RATE);
}

/**
 * Handles 1 tick of the game.
 * @param level A pointer to a pointer to the current level.
 * @param playerPosition A pointer to the player's current position.
 */
void game_controller_update(Level_t** level, Position_t* playerPosition)
{
    static GameState_t gameState = STARTING;
    static NavswitchInput_t navswitchState = NAVSTATE_UNPUSHED;
    input_update();
    switch (gameState) {
    case STARTING:
        gameState = MENU;
        break;
    case WAITING:
        navswitchState = input_getNavswitchPushEvent();
        gameState = waiting_update(level, playerPosition, navswitchState);
        maze_draw((*level)->maze, playerPosition, PACER_RATE);
        break;
    case MOVING:
        gameState = moving_update(level, playerPosition, navswitchState);
        maze_draw((*level)->maze, playerPosition, PACER_RATE);
        break;
    case MENU:
    case NEXT_LEVEL:
        gameState = menus_update() ? WAITING : gameState;
        break;
    case GAME_OVER:
    case VICTORY_SCREEN:
        menus_update();
        break;
    default:
        break;
    }
}