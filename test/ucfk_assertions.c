/**
 * @file ucfk_assertions.c
 * @author Michael Alpenfels (mwa172)
 * @author Beilang Fan (bfa37)
 * @date 17 October 2021
 * @brief Provides macro-based assertions for unit testing the UCFK4.
 */
#include "ucfk_assertions.h"

uint32_t testsRun = 0;
uint32_t testsFailed = 0;
size_t expectedSize = 0;
size_t actualSize = 0;

void assertions_runTests(test_t tests[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        tests[i]();
    }
}

void assertions_printResults(void)
{
    if (testsFailed == 0) {
        printf("OK\n");
    } else {
        printf("*** %d TEST%s FAILED ***\n", testsFailed, testsFailed != 1 ? "S" : "");
    }
    printf("--- %d / %d tests passed ---\n", testsRun - testsFailed, testsRun);
}

