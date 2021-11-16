/**
 * @file bitmap_tests.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Unit tests for the bitmap module.
 */
#include "bitmap_tests.h"

static void test_bitmap_set_true(void)
{
    Bitmap_t map = {0,0,0,0,0};
    Position_t pos = {0, 0};
    bitmap_set(&map, pos, 1);

    Bitmap_t expectedMap = {
        1, 0, 0, 0, 0
    };
    
    TEST_ASSERT_ARRAY_EQUALS(expectedMap, map);
}

static void test_bitmap_set_false(void)
{
    Bitmap_t map = {1,0,0,0,0};
    Position_t pos = {0, 0};
    bitmap_set(&map, pos, 0);

    Bitmap_t expectedMap = {
        0, 0, 0, 0, 0
    };
    
    TEST_ASSERT_ARRAY_EQUALS(expectedMap, map);
}

static void test_bitmap_get_true(void)
{
    Bitmap_t map = {1,0,0,0,0};
    Position_t pos = {0, 0};
    TEST_ASSERT_TRUE(bitmap_get(&map, pos));
}

static void test_bitmap_get_false(void)
{
    Bitmap_t map = {0,0,0,0,0};
    Position_t pos = {0, 0};
    TEST_ASSERT_FALSE(bitmap_get(&map, pos));
}

void test_bitmap_set(void)
{
    test_bitmap_set_true();
    test_bitmap_set_false();
}

void test_bitmap_get(void)
{
    test_bitmap_get_true();
    test_bitmap_get_false();
}
