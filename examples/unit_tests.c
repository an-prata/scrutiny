#include "../scrutiny/scrutiny.h"

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

SCRUTINY_UNIT_TEST not_equal_test(void)
{
    /*
     * Scrutiny can make equality assertion on arrays as well if given the
     * length to compare to.
     */
    
    int arr1[] = { 1, 2, 3 };
    int arr2[] = { 1, 4, 9 };

    /*
     * We've seen alot of equality assertions, so how about we assert that the
     * expected value is not equal to the actual value.
     */

    scrutiny_assert_not_equal_array(arr1, arr2, sizeof(int), 3);
}

/*
 * For this next bit we need to create a struct and custom comparison.
 */

struct _MyStruct {
    int value;
    bool unequal;
};

typedef struct _MyStruct MyStruct;

Scrutiny_ComparisonResult compare_my_struct(MyStruct* left, MyStruct* right) {
    if (left->unequal || right->unequal) {
        return SCRUTINY_UNEQUAL;
    }

    if (left->value > right->value) {
        return SCRUTINY_GREATOR_THAN;
    }

    if (left->value < right->value) {
        return SCRUTINY_LESS_THAN;
    }

    return SCRUTINY_EQUAL;
}

SCRUTINY_UNIT_TEST custom_compare_test() {
    MyStruct a = { .value = 3, .unequal = false };
    MyStruct b = { .value = 0, .unequal = false };

    scrutiny_assert_greator_than_struct(&a, &b, (Scrutiny_CompareFunction)compare_my_struct);

    a.unequal = true;

    scrutiny_assert_not_equal_struct(&a, &b, (Scrutiny_CompareFunction)compare_my_struct);
}

int main()
{
    Scrutiny_UnitTest scrutiny_unit_tests[] = 
    {
        add_test,        /* Pointer to our unit test. */
        increment_test,  /* Another test. */
        not_equal_test, 
        NULL             /* End the list. */
    };

    /* Runs all tests until terminating NULL pointer. */
    scrutiny_run_tests(scrutiny_unit_tests);

    /* Outputs test results to standard out. */
    scrutiny_output_test_results(stdout);

    /* Outputs easily parsable test results to a file. */
    scrutiny_output_test_results_parsable(fopen("out.txt", "w"));
}

