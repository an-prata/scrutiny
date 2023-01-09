#include "../../scrutiny/scrutiny.h"

/* This macro expands to void. */
SCRUTINY_UNIT_TEST add_test(void)
{
    int a = 3;
    int b = 5;

    /* Assert that a does not equal b. */
    scrutiny_assert_false(a == b);

    /* Asserts only document the failiure, they wont terminate execution. */

    /* 
     * Assert that a + b is 8, scrutiny allows you to make more than one
     * assertion in the same test, each assert is a "test case" and each given
     * function is a "unit test". Scrutiny reports both in output.
     */
    scrutiny_assert_equal_int(a + b, 8);
}

SCRUTINY_UNIT_TEST increment_test(void)
{
    size_t limit = 128;

    /* Because scrutiny allows for multiple asserts, you can run them in a loop. */
    for (size_t i = 0; i < limit; i++)
        scrutiny_assert_false(limit == i);
}

int main()
{
    scrutiny_unit_test_t scrutiny_unit_tests[] = 
    {
        add_test,        /* Pointer to our unit test. */
        increment_test,  /* Another test. */
        NULL             /* End the list. */
    };

    /* Runs all tests until terminating NULL pointer. */
    scrutiny_run_tests(scrutiny_unit_tests);

    /* Outputs test results to standard out. */
    scrutiny_output_test_results(stdout);

    /* Outputs easily parsable test results to a file. */
    scrutiny_output_test_results_parsable(fopen("out.txt", "w"));
}

