/**
 * @file ucfk_assertions.h
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief Provides macro-based assertions for unit testing the UCFK4.
 */
#ifndef UCFK_TESTS_H
#define UCFK_TESTS_H

#include "system.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern uint32_t testsRun;
extern uint32_t testsFailed;
extern size_t expectedSize;
extern size_t actualSize;

#define TEST_ASSERT_TRUE(condition)                                               \
    testsRun++;                                                                   \
    if (!condition) {                                                             \
        printf("FAIL %s:%d: Expected TRUE but got FALSE.\n", __func__, __LINE__); \
        testsFailed++;                                                            \
    }

#define TEST_ASSERT_FALSE(condition)                                              \
    testsRun++;                                                                   \
    if (condition) {                                                              \
        printf("FAIL %s:%d: Expected FALSE but got TRUE.\n", __func__, __LINE__); \
        testsFailed++;                                                            \
    }

#define TEST_ASSERT_EQUALS(expected, actual)                                                        \
    testsRun++;                                                                                     \
    if (expected != actual) {                                                                       \
        testsFailed++;                                                                              \
        printf("FAIL %s:%d: Expected " #expected " to equal " #actual ", but they are NOT equal."); \
    }

#define TEST_ASSERT_NOT_EQUALS(expected, actual)                                                    \
    testsRun++;                                                                                     \
    if (expected == actual) {                                                                       \
        testsFailed++;                                                                              \
        printf("FAIL %s:%d: Expected " #expected " to NOT equal " #actual ", but they are equal."); \
    }

#define TEST_ASSERT_ARRAY_EQUALS(expected, actual)                                                                                \
    testsRun++;                                                                                                                   \
    expectedSize = ARRAY_SIZE(expected);                                                                                          \
    actualSize = ARRAY_SIZE(actual);                                                                                              \
    if (expectedSize != actualSize) {                                                                                             \
        testsFailed++;                                                                                                            \
        printf("FAIL %s:%d: Expected array to be of size %zu, but got %zu.\n", __func__, __LINE__, expectedSize, actualSize);     \
    } else {                                                                                                                      \
        for (size_t i = 0; i < expectedSize; i++) {                                                                               \
            if (expected[i] != actual[i]) {                                                                                       \
                printf("FAIL %s:%d: Expected arrays to be equal but they first differ at element %zu.\n", __func__, __LINE__, i); \
                testsFailed++;                                                                                                    \
                break;                                                                                                            \
            }                                                                                                                     \
        }                                                                                                                         \
    }

typedef void (*test_t)(void);

void assertions_runTests(test_t tests[], size_t n);

void assertions_printResults(void);

#endif