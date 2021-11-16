/**
 * @file run_tests.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Runs the unit tests.
 */
#include "ucfk_assertions.h"
#include "bitmap_tests.h"
#include "maze_tests.h"
#include "position_tests.h"

void tests_runTests(void)
{
    test_bitmap_set();
    test_bitmap_get();
    test_maze_isWall_small();
}

int main(void)
{
    test_t tests[] = {
        test_bitmap_set,
        test_bitmap_get,
        test_maze_isWall_small,
        test_maze_isWall_large,
        test_maze_can_move_all_sides_valid,
        test_maze_can_move_north_invalid,
        test_maze_can_move_west_invalid,
        test_maze_can_move_east_invalid,
        test_maze_can_move_south_invalid,
        test_maze_cannot_move,
        test_maze_can_move_between_rooms,
        test_makes_wall_on_cell_leave,
        test_position_adds_correctly,
        test_equal_positions_are_equal,
        test_unequal_positions_are_not_equal,
        test_relative_pos_origin_room,
        test_relative_pos_outer_room
    };
    assertions_runTests(tests, 17);
    assertions_printResults();
    
    return 0;
}