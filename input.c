/**
 * @file input.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Handles input from the microcontroller. 
 * 
 * Provides functions to easily check which event was just triggered from the input.
 */
#include "input.h"


/**
 * Updates all of the input ports.
 */
void input_update(void)
{
    navswitch_update();
    button_update();
}

/**
 * Returns the push event on the navswitch, if any. 
 * @return If the state of the navswitch has changed, returns what
 * state the navswitch changed to. Otherwise, returns UNPUSHED.
 */
int input_getNavswitchPushEvent(void)
{   
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        return NAVSTATE_NORTH;
    } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        return NAVSTATE_SOUTH;
    }else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        return NAVSTATE_EAST;
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        return NAVSTATE_WEST;
    } else if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        return NAVSTATE_PUSHED;
    } else {
        return NAVSTATE_UNPUSHED;
    }
}