/**
 * @file menus.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief Provides functionality for menus. Essentially is a 
 * wrapper for tinygl.
 * 
 */
#include "menus.h"
#include <stdio.h>

#define MENU_TEXT_SPEED 15

/**
 * Initialises the menus.
 * @param rate The rate in Hz at which the menus are updated.
 */
void menus_init(const uint16_t rate)
{
    tinygl_init(rate);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MENU_TEXT_SPEED);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    button_init();
    led_init();
    led_set(LED1, 0);
    menus_setText(MENU_MAIN_TEXT);
}

/**
 * Sets the text of the menu.
 * @param text
 */
void menus_setText(char* text)
{
    tinygl_text(text);
}

/**
 * Updates the menu.
 * @return Returns true when the pushbutton is pressed.
 */
bool menus_update(void)
{
    tinygl_update();
    if (button_push_event_p(BUTTON1)) {
        led_set(LED1, 0);
        return true;
    } else {
        led_set(LED1, 1);
        return false;
    }
}