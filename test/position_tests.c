/**
 * @file position_tests.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Unit tests for the position module.
 */
#include "position_tests.h"

void test_position_adds_correctly(void)
{
    Position_t a = {1, 1};
    Position_t b = {2, 3};

    Position_t result = position_add(a, b);
    Position_t expected = {3, 4};
    TEST_ASSERT_TRUE(position_equals(expected, result));
}

void test_equal_positions_are_equal(void)
{
    Position_t a = {1, 1};
    Position_t b = {1, 1};
    TEST_ASSERT_TRUE(position_equals(a, b));
}

void test_unequal_positions_are_not_equal(void)
{
    Position_t a = {2, 1};
    Position_t b = {1, 1};
    TEST_ASSERT_FALSE(position_equals(a, b));
}

void test_relative_pos_origin_room(void)
{
    Position_t a = {1, 1};
    Position_t relative = position_getRelativePos(&a);
    TEST_ASSERT_TRUE(position_equals(a, relative));
}

void test_relative_pos_outer_room(void)
{
    Position_t a = {8, 6};
    Position_t expected = {1, 1};
    Position_t relative = position_getRelativePos(&a);
    TEST_ASSERT_TRUE(position_equals(expected, relative));
}