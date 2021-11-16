/**
 * @file maze_tests.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Unit tests for the maze module.
 */
#include "maze_tests.h"

void test_maze_isWall_small(void)
{
    Bitmap_t maps[] = {{1, 0, 0, 0, 0}};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };
    Position_t origin = {0, 0};
    Position_t g = {1, 1};

    TEST_ASSERT_TRUE(maze_isWall(&maze, &origin));
    TEST_ASSERT_FALSE(maze_isWall(&maze, &g));
}

void test_maze_isWall_large(void)
{
    Bitmap_t maps[] = {
        {0xff, 0xff, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0xff, 0xff, 0xff}
    };
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };
    Position_t pos = {10, 10};

    TEST_ASSERT_TRUE(maze_isWall(&maze, &pos));
}

void test_maze_can_move_all_sides_valid(void)
{
    Bitmap_t maps[] = {{
        0b1111101,
        0b1000000,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {1, 1};

    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_maze_can_move_north_invalid(void)
{
    Bitmap_t maps[] = {{
        0b1111101,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {1, 1};

    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_maze_can_move_west_invalid(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b1000000,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {1, 1};

    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_maze_can_move_east_invalid(void)
{
    Bitmap_t maps[] = {{
        0b1111101,
        0b1000000,
        0b1000011,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {1, 1};

    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_maze_can_move_south_invalid(void)
{
    Bitmap_t maps[] = {{
        0b1111101,
        0b1000100,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {1, 1};
    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_maze_cannot_move(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b1000101,
        0b1000011,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };
    Position_t pos = {1, 1};
    TEST_ASSERT_FALSE(maze_canMove(&maze, &pos));
}

void test_maze_can_move_between_rooms(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b0000001,
        0b1000001,
        0b1000001,
        0b1111111
    },{
        0b1111111,
        0b1000010,
        0b1000001,
        0b1000001,
        0b1111111
    },{
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111
    },{
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 2,
        .goalPosition = {2, 2},
        .playerStartPosition = {0, 0}
    };

    Position_t pos = {7, 1};

    TEST_ASSERT_TRUE(maze_canMove(&maze, &pos));
}

void test_makes_wall_on_cell_leave(void)
{
    Bitmap_t maps[] = {{
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1111111
    }};
    Maze_t maze = {
        .rooms = maps,
        .size = 1,
        .goalPosition = {1, 1},
        .playerStartPosition = {0, 0}
    };
    Position_t pos = {1, 1};
    maze_onLeaveCell(&maze, &pos);
    TEST_ASSERT_TRUE(maze_isWall(&maze, &pos));
}