#include <stdlib.h>

// This macro makes scrutiny's assertions not abort the program on failure and 
// instead return from the current function, which makes unit testing easier.
#define SCRUTINY_DEBUG

#include "../scrutiny/scrutiny.h"

SCRUTINY_UNIT_TEST(addition_test) {
    int a = 2;
    int b = 3;

    scrutiny_assert_greater_than(b, a);
    scrutiny_assert_less_than(a, b);
    scrutiny_assert_no_greater_than(a, b);
    scrutiny_assert_equal(5, a + b);
}

// This test will fail.
SCRUTINY_UNIT_TEST(subtraction_test) {
    int a = 2;
    int b = 3;

    scrutiny_assert_equal(0, a - b);
}

int main() {
    scrutiny_test_t tests[] = {
        subtraction_test,
        addition_test,
        NULL
    };

    scrutiny_run_tests(tests);

    // Using this function will print some extra info at the end of the test run
    // for when you need that 100% passed dopamine. You cant use both in the
    // same run since they exit the program for you with a value inicative of
    // test success.
    // scrutiny_run_tests_with_stats(tests);
}