/**
 * @file maze_tests.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Unit tests for the maze module.
 */
#ifndef MAZE_TESTS_H
#define MAZE_TESTS_H

#include "ucfk_assertions.h"
#include "../bitmap.h"
#include "../position.h"
#include "../maze.h"

void test_maze_isWall_small(void);

void test_maze_isWall_large(void);

void test_maze_can_move_all_sides_valid(void);

void test_maze_can_move_north_invalid(void);

void test_maze_can_move_west_invalid(void);

void test_maze_can_move_east_invalid(void);

void test_maze_can_move_south_invalid(void);

void test_maze_cannot_move(void);

void test_maze_can_move_between_rooms(void);

void test_makes_wall_on_cell_leave(void);

#endif

