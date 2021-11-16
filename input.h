/**
 * @file input.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 16 October 2021
 * @brief Handles input from the microcontroller. 
 * 
 * Provides functions to easily check which event was just triggered from the input.
 */
#ifndef INPUT_H
#define INPUT_H

#include "navswitch.h"
#include "position.h"
#include "button.h"
#include <stdbool.h>

/**
 * All possible statesof the navswitch.
 */
typedef enum {
    NAVSTATE_NORTH,
    NAVSTATE_SOUTH,
    NAVSTATE_EAST,
    NAVSTATE_WEST,
    NAVSTATE_PUSHED,
    NAVSTATE_UNPUSHED
} NavswitchInput_t;

/**
 * Updates all of the input ports.
 */
void input_update(void);

/**
 * Returns the push event on the navswitch, if any. 
 * @return If the state of the navswitch has changed, returns what
 * state the navswitch changed to. Otherwise, returns UNPUSHED.
 */
int input_getNavswitchPushEvent(void);

#endif