#include "scrutiny.h"
#include <string.h>

#define A_SIZE 8
#define B_SIZE 7

SCRUTINY_UNIT_TEST void add_test(void)
{
    int a = 3;
    int b = 5;
    int expected = 8;

    scrutiny_assert_equal_int(a + b, expected);
}

SCRUTINY_UNIT_TEST void int_array_test(void)
{
    uint8_t a[B_SIZE] = { 2, 6, 1, 27, 86, 3, 3 };
    uint8_t b[B_SIZE] = { 2, 6, 1, 28, 1, 3, 3 };

    for (size_t i = 0; i < B_SIZE; i++)
        scrutiny_assert_equal_uint8_t(a[i], b[i]);
}

SCRUTINY_UNIT_TEST void void_ptr_data_test(void)
{
    const size_t size = 8;

    char* a = malloc(size);
    char* b = malloc(size);

    memset(a, ' ', size);
    memset(b, ' ', size);

    b[7] = 'c';

    scrutiny_assert_equal_ptr_data(a, b, size);
}

SCRUTINY_UNIT_TEST void bool_test(void)
{
    scrutiny_assert_true(1 == 1);
    scrutiny_assert_false(1 == 2);
    scrutiny_assert_true(1 != 1);
    scrutiny_assert_false(1 != 2);
}

SCRUTINY_UNIT_TEST void string_test(void)
{
    char* str0 = "yeetus";
    char* str1 = "yeetus";

    scrutiny_assert_equal_string(str0, str1);
    scrutiny_assert_equal_non_terminated_string(str0, str1, 6);
}

int main()
{
    scrutiny_unit_test scrutiny_unit_tests[] = 
    {
        add_test,
        int_array_test,
        void_ptr_data_test,
        bool_test,
        string_test,
        NULL
    };

    scrutiny_run_tests(scrutiny_unit_tests);
}

