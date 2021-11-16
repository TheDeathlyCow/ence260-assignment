/**
 * @file position_tests.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 19 October 2021
 * @brief Unit tests for the position module.
 */
#ifndef POSITION_TESTS_H
#define POSITION_TESTS_H

#include "ucfk_assertions.h"
#include "../position.h"


void test_position_adds_correctly(void);

void test_equal_positions_are_equal(void);

void test_unequal_positions_are_not_equal(void);

void test_relative_pos_origin_room(void);

void test_relative_pos_outer_room(void);


#endif