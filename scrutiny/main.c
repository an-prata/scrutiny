#include "scrutiny.h"
#include <string.h>

#define A_SIZE 8
#define B_SIZE 7

SCRUTINY_UNIT_TEST add_test(void)
{
    int a = 3;
    int b = 5;
    int expected = 8;

    scrutiny_assert_equal_int(a + b, expected);
}

SCRUTINY_UNIT_TEST int_array_test(void)
{
    uint8_t a[B_SIZE] = { 2, 6, 1, 27, 86, 3, 3 };
    uint8_t b[B_SIZE] = { 2, 6, 1, 27, 86, 3, 3 };

    for (size_t i = 0; i < B_SIZE; i++)
        scrutiny_assert_equal_uint8_t(a[i], b[i]);
}

SCRUTINY_UNIT_TEST void_ptr_data_test(void)
{
    const size_t size = 8;

    char* a = malloc(size);
    char* b = malloc(size);

    memset(a, ' ', size);
    memset(b, ' ', size);

    // b[7] = 'c';

    scrutiny_assert_equal_ptr_data(a, b, size);
}

SCRUTINY_UNIT_TEST bool_test(void)
{
    scrutiny_assert_true(1 == 1);
    scrutiny_assert_false(1 == 2);
    // scrutiny_assert_true(1 != 1);
    // scrutiny_assert_false(1 != 2);
    scrutiny_assert_fail();
}

SCRUTINY_UNIT_TEST string_test(void)
{
    char* str0 = "yeetus";
    char* str1 = "yeetus";

    scrutiny_assert_equal_string(str0, str1);
    scrutiny_assert_equal_non_terminated_string(str0, str1, 6);
}

SCRUTINY_BENCHMARK loop_thousand(void)
{
    size_t total;

    scrutiny_benchamrk_start();
    {
        for (size_t i = 0; i < 1000000; i++)
            total += total + i;
    }
    scrutiny_benchmark_finish();
}

int main()
{
    // scrutiny_unit_test_t scrutiny_unit_tests[] = 
    // {
    //     add_test,
    //     int_array_test,
    //     void_ptr_data_test,
    //     bool_test,
    //     string_test,
    //     NULL
    // };

    // scrutiny_run_tests(scrutiny_unit_tests);
    // scrutiny_output_test_results_parsable(fopen("out.txt", "w"));


    scrutiny_benchmark_t scrutiny_benchmarks[] =
    {
        loop_thousand,
        NULL
    };

    scrutiny_run_benchmarks_n_times(scrutiny_benchmarks, 64);
    scrutiny_output_benchmark_results(stdout);
}

