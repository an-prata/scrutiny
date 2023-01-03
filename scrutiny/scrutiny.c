/* 
 * Copyright (c) 2023 Evan Overman (https://an-prata.it). Licensed under the MIT License.
 * See LICENSE file in repository root for complete license text.
 */

#ifndef SCRUTINY_C
#define SCRUTINY_C

#ifndef SCRUTINY_H
#define SCRUTINY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* 
 * Defined for convinience and code clarity, beyond that this definition
 * serves no purpose.
 */
#define SCRUTINY_UNIT_TEST

/* 
 * This collection of macros serves only to simplify assert calls by
 * automatically adding the __FILE__, __LINE__, and __func__ macros as
 * arguments to the function call for easier debugging.
 */

#define scrutiny_assert_pass() scrutiny_report_assert_pass(__FILE__, __func__)
#define scrutiny_assert_fail() scrutiny_report_assert_fail(__FILE__, __func__, __LINE__)
#define scrutiny_assert_true(expression) scrutiny_report_assert_true(expression, __FILE__, __func__, __LINE__)
#define scrutiny_assert_false(expression) scrutiny_report_assert_false(expression, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_char(expected, actual) scrutiny_report_assert_equal_char(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_unsigned_char(expected, actual) scrutiny_report_assert_equal_unsigned_char(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_short(expected, actual) scrutiny_report_assert_equal_short(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int(expected, actual) scrutiny_report_assert_equal_int(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_long(expected, actual) scrutiny_report_assert_equal_long(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_long_long(expected, actual) scrutiny_report_assert_equal_long_long(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_unsigned_short(expected, actual) scrutiny_report_assert_equal_unsigned_short(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_unsigned_int(expected, actual) scrutiny_report_assert_equal_unsigned_int(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_unsigned_long(expected, actual) scrutiny_report_assert_equal_unsigned_long(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_unsigned_long_long(expected, actual) scrutiny_report_assert_equal_unsigned_long_long(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_float(expected, actual) scrutiny_report_assert_equal_float(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_double(expected, actual) scrutiny_report_assert_equal_double(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_long_double(expected, actual) scrutiny_report_assert_equal_long_double(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int8_t(expected, actual) scrutiny_report_assert_equal_int8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int16_t(expected, actual) scrutiny_report_assert_equal_int16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int32_t(expected, actual) scrutiny_report_assert_equal_int32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int64_t(expected, actual) scrutiny_report_assert_equal_int64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_fast8_t(expected, actual) scrutiny_report_assert_equal_int_fast8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_fast16_t(expected, actual) scrutiny_report_assert_equal_int_fast16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_fast32_t(expected, actual) scrutiny_report_assert_equal_int_fast32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_fast64_t(expected, actual) scrutiny_report_assert_equal_int_fast64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_least8_t(expected, actual) scrutiny_report_assert_equal_int_least8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_least16_t(expected, actual) scrutiny_report_assert_equal_int_least16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_least32_t(expected, actual) scrutiny_report_assert_equal_int_least32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_int_least64_t(expected, actual) scrutiny_report_assert_equal_int_least64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint8_t(expected, actual) scrutiny_report_assert_equal_uint8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint16_t(expected, actual) scrutiny_report_assert_equal_uint16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint32_t(expected, actual) scrutiny_report_assert_equal_uint32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint64_t(expected, actual) scrutiny_report_assert_equal_uint64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_fast8_t(expected, actual) scrutiny_report_assert_equal_uint_fast8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_fast16_t(expected, actual) scrutiny_report_assert_equal_uint_fast16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_fast32_t(expected, actual) scrutiny_report_assert_equal_uint_fast32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_fast64_t(expected, actual) scrutiny_report_assert_equal_uint_fast64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_least8_t(expected, actual) scrutiny_report_assert_equal_uint_least8_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_least16_t(expected, actual) scrutiny_report_assert_equal_uint_least16_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_least32_t(expected, actual) scrutiny_report_assert_equal_uint_least32_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_uint_least64_t(expected, actual) scrutiny_report_assert_equal_uint_least64_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_intptr_t(expected, actual) scrutiny_report_assert_equal_intptr_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_intmax_t(expected, actual) scrutiny_report_assert_equal_intmax_t(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_ptr(expected, actual) scrutiny_report_assert_equal_ptr(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_ptr_data(expected, actual, struct_size) scrutiny_report_assert_equal_ptr_data(expected, actual, struct_size, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_array(expected, actual, sizeof_type, array_length) scrutiny_report_assert_equal_array(expected, actual, sizeof_type, array_length, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_string(expected, actual) scrutiny_report_assert_equal_string(expected, actual, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal_non_terminated_string(expected, actual, size) scrutiny_report_assert_equal_non_terminated_string(expected, actual, size, __FILE__, __func__, __LINE__)

typedef void (*scrutiny_unit_test_t)(void);

/**
 * Runs all given test functions and prints the results.
 *
 * @param scrutiny_unit_tests An array of functions taking void parameters and
 *                            returning void. The last element of this array
 *                            should be a NULL pointer to terminate the array.
 */
void scrutiny_run_tests(scrutiny_unit_test_t* scrutiny_unit_tests);

/*
 * The following functions, while not intended to be used directly, will not
 * be a problem if used directly. In most cases the macros above should be used
 * but if many asserts are run in a loop it may be useful to replace one of the
 * arguments with a custom string in case the default report is not enough.
 */

void scrutiny_report_assert_pass(const char* file, const char* function); /* Automatically asserts case passing. */
void scrutiny_report_assert_fail(const char* file, const char* function, size_t line); /* Automatically asserts case failure. */
void scrutiny_report_assert_true(bool expression, const char* file, const char* function, size_t line); /* Checks if the boolean expression is true. */
void scrutiny_report_assert_false(bool expression, const char* file, const char* function, size_t line); /* Checks if the boolean expression is false. */
void scrutiny_report_assert_equal_char(char expected, char actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_short(short expected, short actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int(int expected, int actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_long(long expected, long actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_long_long(long long expected, long long actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_float(float expected, float actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_double(double expected, double actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_long_double(long double expected, long double actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line); /* Checks if expected is equivilant to actual. */
void scrutiny_report_assert_equal_ptr(void* expected, void* actual, const char* file, const char* function, size_t line); /* Checks if the expected pointer and actual pointer are the same. */
void scrutiny_report_assert_equal_ptr_data(void* expected, void* actual, size_t struct_size, const char* file, const char* function, size_t line); /* Checks if the data at the pointer expected is the same as actual. */
void scrutiny_report_assert_equal_array(void* expected, void* actual, size_t sizeof_type, size_t array_length, const char* file, const char* function, size_t line); /* Checks if the expected array and actual array are equal. */
void scrutiny_report_assert_equal_string(char* expected, char* actual, const char* file, const char* function, size_t line); /* Checks if the two strings are equal. */
void scrutiny_report_assert_equal_non_terminated_string(char* expected, char* actual, size_t size, const char* file, const char* function, size_t line); /* Checks if the two strings are equal. */

#endif // SCRUTINY_H

/* ----------------------------------------------------------------------------
 * This will be the imaginary line between the header and source "files".
 * Everything above is intended to be used as documentation, everything below
 * should probably not be used externally.
 * ------------------------------------------------------------------------- */

#define SCRUTINY_TEXT_NORMAL "\033[0m"
#define SCRUTINY_TEXT_BOLD "\033[1m"
#define SCRUTINY_TEXT_ITALIC "\033[3m"
#define SCRUTINY_TEXT_GREEN "\033[0;32m"
#define SCRUTINY_TEXT_BLUE "\033[0;44m"
#define SCRUTINY_TEXT_RED "\033[0;31m"

static size_t failed_cases = 0;
static size_t passed_cases = 0;
static size_t failed_tests_length = 0;
static size_t passed_tests_length = 0;
static const char** failed_tests;
static const char** passed_tests;
static size_t test_files_length = 0;
static const char** test_files;

static bool compare_null_terminated_strings(const char* str0, const char* str1)
{
    for (size_t i = 0;; i++)
    {
        if (str0[i] == '\0' && str1[i] == '\0')
            return true;
        if (str0[i] == '\0' && str1[i] == '\0')
            return false;
        if (str0[i] != str1[i])
            return false;
    }
}

static void succeeded_test_expand_and_add(const char* succeeded_test)
{
    passed_cases++;
    
    for (size_t i = 0; i < passed_tests_length; i++)
        if (compare_null_terminated_strings(passed_tests[i], succeeded_test))
            return;

    /* If the test function has failed previously dont add it to the succeeded list. */
    for (size_t i = 0; i < failed_tests_length; i++)
        if (compare_null_terminated_strings(failed_tests[i], succeeded_test))
            return;
    
    passed_tests_length++;
    passed_tests = realloc(passed_tests, passed_tests_length * sizeof(char*));
    passed_tests[passed_tests_length - 1] = succeeded_test;
}

static void succeeded_test_contract_and_remove(const char* test)
{
    for (size_t i = 0; i < passed_tests_length; i++)
    {
        if (compare_null_terminated_strings(passed_tests[i], test))
        {
            if (i != passed_tests_length - 1)
                passed_tests[i] = passed_tests[passed_tests_length - 1];

            passed_tests_length--;
            return;
        }
    }
}

static void failed_test_expand_and_add(const char* failed_test)
{
    failed_cases++;
    
    for (size_t i = 0; i < failed_tests_length; i++)
        if (compare_null_terminated_strings(failed_tests[i], failed_test))
            return;

    failed_tests_length++;
    failed_tests = realloc(failed_tests, failed_tests_length * sizeof(char*));
    failed_tests[failed_tests_length - 1] = failed_test;
}

static void test_file_expand_and_add(const char* test_file)
{
    for (size_t i = 0; i < test_files_length; i++)
        if (compare_null_terminated_strings(test_files[i], test_file))
            return;

    test_files_length++;
    test_files = realloc(test_files, test_files_length * sizeof(char*));
    test_files[test_files_length - 1] = test_file;
}

static void failed_test_print_failure(const char* expected, const char* actual, const char* file, const char* function, size_t line, const char* assert)
{
    printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, assert, line);
    printf("\tExpected:  %s\n", expected);
    printf("\tActual:    %s\n", actual);
}

static void failed_test_print_failure_unsigned_integer(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line, const char* assert)
{
    printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, assert, line);
    printf("\tExpected:  %zu\n", expected);
    printf("\tActual:    %zu\n", actual);
}

static void failed_test_print_failure_signed_integer(int64_t expected, int64_t actual, const char* file, const char* function, size_t line, const char* assert)
{
    printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, assert, line);
    printf("\tExpected:  %zi\n", expected);
    printf("\tActual:    %zi\n", actual);
}

void scrutiny_run_tests(scrutiny_unit_test_t* scrutiny_unit_tests)
{
    size_t tests_count;
    for (tests_count = 0; scrutiny_unit_tests[tests_count] != NULL; tests_count++);
    printf("Running %zu scrutiny unit tests...\n", tests_count);
    
    for (size_t test = 0; test < tests_count; test++)
        scrutiny_unit_tests[test]();

    long double percent_passed = ((long double)passed_tests_length / (long double)tests_count) * 100.0;
    long double percent_failed = ((long double)failed_tests_length / (long double)tests_count) * 100.0;
    long double percent_cases_passed = ((long double)passed_cases / (long double)(passed_cases + failed_cases)) * 100.0;
    long double percent_cases_failed = ((long double)failed_cases / (long double)(passed_cases + failed_cases)) * 100.0;

    printf("\nScrutiny ran %zu test cases, from %zu tests, in %zu files.\n", failed_cases + passed_cases, failed_tests_length + passed_tests_length, test_files_length);

    if (passed_cases > 0)
    {
        printf("\n(" SCRUTINY_TEXT_GREEN "" SCRUTINY_TEXT_NORMAL ") %zu of %zu tests passed (%2.1Lf%%).", passed_tests_length, tests_count, percent_passed);
        printf("\t(" SCRUTINY_TEXT_GREEN "" SCRUTINY_TEXT_NORMAL ") %zu of %zu test cases passed (%2.1Lf%%).\n", passed_cases, passed_cases + failed_cases, percent_cases_passed);
    }

    if (failed_cases> 0)
    {
        printf("(" SCRUTINY_TEXT_RED "x" SCRUTINY_TEXT_NORMAL ") %zu of %zu tests failed (%2.1Lf%%).", failed_tests_length, tests_count, percent_failed);
        printf("\t(" SCRUTINY_TEXT_RED "x" SCRUTINY_TEXT_NORMAL ") %zu of %zu test cases failed (%2.1Lf%%).\n", failed_cases, failed_cases + passed_cases, percent_cases_failed);
    }
}

void scrutiny_report_assert_pass(const char* file, const char* function)
{
    test_file_expand_and_add(file);
    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_fail(const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);
    succeeded_test_contract_and_remove(function);
    failed_test_expand_and_add(function);
    printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
}

void scrutiny_report_assert_true(bool expression, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (!expression)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_false(bool expression, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expression)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_char(char expected, char actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_short(short expected, short actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int(int expected, int actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_long(long expected, long actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_long_long(long long expected, long long actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_float(float expected, float actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_double(double expected, double actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_long_double(long double expected, long double actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_ptr(void* expected, void* actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (expected != actual)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure_unsigned_integer((uint64_t)expected, (uint64_t)actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_ptr_data(void* expected, void* actual, size_t struct_size, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    uint8_t* expected_bytes = (uint8_t*)expected;
    uint8_t* actual_bytes = (uint8_t*)actual;

    for (size_t i = 0; i < struct_size; i++)
    {
        if (expected_bytes[i] != actual_bytes[i])
        {
            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
            printf("\tExpected:  %u at byte %zu\n", expected_bytes[i], i);
            printf("\tActual:    %u\n", actual_bytes[i]);
            return;
        }
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_array(void* expected, void* actual, size_t sizeof_type, size_t array_length, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    uint8_t* expected_bytes = (uint8_t*)expected;
    uint8_t* actual_bytes = (uint8_t*)actual;

    for (size_t byte = 0; byte < sizeof_type * array_length; byte++)
    {
        if (expected_bytes[byte] != actual_bytes[byte])
        {
            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
            printf("\tDifference at index: %zu\n", byte / sizeof_type);
            return;
        }
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_string(char* expected, char* actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (!compare_null_terminated_strings(expected, actual))
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_equal_non_terminated_string(char* expected, char* actual, size_t size, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    for (size_t i = 0; i < size; i++)
    {
        if (expected[i] != actual[i])
        {
            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n", file, function, __func__, line);
            printf("\tExpected:  %c at index %zu\n", expected[i], i);
            printf("\tActual:    %c\n", actual[i]);
            return;
        }
    }

    succeeded_test_expand_and_add(function);
}

#endif // SCRUTINY_C

