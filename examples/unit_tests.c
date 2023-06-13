#include <stdlib.h>

// This macro makes scrutiny's assertions not abort the program on failure and 
// instead return from the current function.
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
}