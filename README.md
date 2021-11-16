# Amazeing Mazes
ENCE260 Embedded Systems Ass and Beilang Fan (George).

## Setup and Compilation steps

### Main Game

1) Ensure that you have the UCFK4 API downloaded from [Richard Clare's GitLab](https://eng-git.canterbury.ac.nz/rmc84/ence260-ucfk4) (unless you are Richard Clare, I guess).
2) Plug the UC Funkit Version 4 into a USB port.
3) Clone this repository into the assignment/ subdirectory in the Funkit API folder, so that game.c is located in assignment/group_229.
4) Open a terminal window and change directory into assignment/group_229.
5) Run the command `make` to compile.
6) Run the command `make program` to load the game onto the Funkit.

### Running Tests

1) Ensure that you have the UCFK4 API downloaded from [Richard Clare's GitLab](https://eng-git.canterbury.ac.nz/rmc84/ence260-ucfk4) (unless you are Richard Clare, I guess).
2) Ensure you have the gcc compiler installed.
3) Clone this repository into the assignment/ subdirectory in the Funkit API folder, so that game.c is located in assignment/group_229.
4) Open a terminal window and change directory into assignment/group_229.
5) Run the command `make -f Makefile.test` to compile.
6) Run the command `./run_tests.out` to run all of the tests.
7) IMPORTANT: For some reason, `drivers/test/system.h` redefines `bool`. When attempting to compile the tests, this will cause errors. To avoid this, simply comment out the `typedef uint8_t bool;` and add `#include <stdbool.c>`. 

# How to play

When you first load this program onto your microcontroller, you will be shown a welcome message. Simply press `BUTTON1` to begin the game. For any subsequent message screens, the blue LED being on indicates the game is waiting for you to press `BUTTON1` to continue.

## Objective

The objective of the game is to get your player (indicated by the LED flashing at about 1 Hz) to a goal position (indicated by an LED flashing at about 4 Hz). The `navswitch` is used to control which direction you would like the player to go. Once a player begins moving in a direction, they will keep moving in that direction until they hit a wall or the edge of the map; you cannot change the direction of the player until they stop. When a player leaves a cell, that cell becomes a wall and cannot be entered again. Therefore, it is possible for you to become permanently stuck. If this happens, the game will end and you will be shown a game over message. If you reach the goal position, then you will be sent to the next level screen. Simply press `BUTTON1` to continue. When you complete all of the levels, you will be shown a game complete message. 

## Controls
* Go to next state (while in menu): `BUTTON1`
* Move north (while not moving and in game): `NAVSWITCH_NORTH` 
* Move south (while not moving and in game): `NAVSWITCH_SOUTH` 
* Move east (while not moving and in game): `NAVSWITCH_EAST` 
* Move west (while not moving and in game): `NAVSWITCH_WEST` 
------------------------------------------------------------------------