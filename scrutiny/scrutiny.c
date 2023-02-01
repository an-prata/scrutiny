/* 
 * Copyright (c) 2023 Evan Overman (https://an-prata.it). Licensed under the MIT License.
 * See LICENSE file in repository root for complete license text.
 */

#include "scrutiny.h"
#include <string.h>

#define SCRUTINY_TEXT_NORMAL "\033[0m"
#define SCRUTINY_TEXT_BOLD "\033[1m"
#define SCRUTINY_TEXT_ITALIC "\033[3m"
#define SCRUTINY_TEXT_GREEN "\033[0;32m"
#define SCRUTINY_TEXT_BLUE "\033[0;44m"
#define SCRUTINY_TEXT_RED "\033[0;31m"

#define assert_unsigned_generic(operator, expected, actual, file, function, line) test_file_expand_and_add(file); \
    if (!(expected operator actual)) \
    { \
        succeeded_test_contract_and_remove(function); \
        failed_test_expand_and_add(function); \
        failed_test_print_failure_unsigned_integer(expected, actual, file, function, line, __func__); \
        return; \
    }\
    succeeded_test_expand_and_add(function)

#define assert_signed_generic(operator, expected, actual, file, function, line) test_file_expand_and_add(file); \
    if (!(expected operator actual)) \
    { \
        succeeded_test_contract_and_remove(function); \
        failed_test_expand_and_add(function); \
        failed_test_print_failure_signed_integer(expected, actual, file, function, line, __func__); \
        return; \
    }\
    succeeded_test_expand_and_add(function)

#define assert_floating_generic(operator, expected, actual, file, function, line) test_file_expand_and_add(file); \
    if (!(expected operator actual)) \
    { \
        succeeded_test_contract_and_remove(function); \
        failed_test_expand_and_add(function); \
        failed_test_print_failure_floating(expected, actual, file, function, line, __func__); \
        return; \
    }\
    succeeded_test_expand_and_add(function)

typedef struct in_progress_average_s in_progress_average_t;

struct in_progress_average_s
{
    size_t divisor;
    clock_t running_total;
};

static scrutiny_test_results_t* test_results = NULL;
static scrutiny_benchmark_results_t* benchmark_results = NULL;

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
    if (test_results == NULL)
        return;

    test_results->passed_cases++;
    
    for (size_t i = 0; i < test_results->passed_tests; i++)
        if (compare_null_terminated_strings(test_results->passed_test_names[i], succeeded_test))
            return;

    /* If the test function has failed previously dont add it to the succeeded list. */
    for (size_t i = 0; i < test_results->failed_tests; i++)
        if (compare_null_terminated_strings(test_results->failed_test_names[i], succeeded_test))
            return;
    
    test_results->passed_tests++;
    test_results->passed_test_names = reallocarray(test_results->passed_test_names, test_results->passed_tests, sizeof(char*));
    test_results->passed_test_names[test_results->passed_tests - 1] = succeeded_test;
}

static void succeeded_test_contract_and_remove(const char* test)
{
    if (test_results == NULL)
        return;

    for (size_t i = 0; i < test_results->passed_tests; i++)
    {
        if (compare_null_terminated_strings(test_results->passed_test_names[i], test))
        {
            if (i != test_results->passed_tests - 1)
                test_results->passed_test_names[i] = test_results->passed_test_names[test_results->passed_tests - 1];

            test_results->passed_tests--;
            return;
        }
    }
}

static void failed_test_expand_and_add(const char* failed_test)
{
    if (test_results == NULL)
        return;
    
    test_results->failed_cases++;
    
    for (size_t i = 0; i < test_results->failed_tests; i++)
        if (compare_null_terminated_strings(test_results->failed_test_names[i], failed_test))
            return;

    test_results->failed_tests++;
    test_results->failed_test_names = reallocarray(test_results->failed_test_names, test_results->failed_tests, sizeof(char*));
    test_results->failed_test_names[test_results->failed_tests - 1] = failed_test;
}

static void test_file_expand_and_add(const char* test_file)
{
    if (test_results == NULL)
        return;

    for (size_t i = 0; i < test_results->files; i++)
        if (compare_null_terminated_strings(test_results->file_names[i], test_file))
            return;

    test_results->files++;
    test_results->file_names = reallocarray(test_results->file_names, test_results->files, sizeof(char*));
    test_results->file_names[test_results->files - 1] = test_file;
}

static void benchmark_run_expand_and_add(const char* name, const char* file, clock_t time)
{
    benchmark_results->benchmarks++;
    benchmark_results->benchmark_names = reallocarray(benchmark_results->benchmark_names, benchmark_results->benchmarks, sizeof(char*));
    benchmark_results->benchmark_times = reallocarray(benchmark_results->benchmark_times, benchmark_results->benchmarks, sizeof(char*));
    benchmark_results->file_names = reallocarray(benchmark_results->file_names, benchmark_results->benchmarks, sizeof(char*));
    benchmark_results->benchmark_names[benchmark_results->benchmarks - 1] = name;
    benchmark_results->benchmark_times[benchmark_results->benchmarks - 1] = time;
    benchmark_results->file_names[benchmark_results->benchmarks - 1] = file;
}

static void failed_test_print_failure(const char* expected, const char* actual, const char* file, const char* function, size_t line, const char* assert)
{
    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, assert, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, assert, line);

    printf("\tExpected:  %s\n", expected);
    printf("\tActual:    %s\n", actual);

    if (test_results == NULL)
        exit(EXIT_FAILURE);
}

static void failed_test_print_failure_unsigned_integer(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line, const char* assert)
{
    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, assert, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, assert, line);

    printf("\tExpected:  %zu\n", expected);
    printf("\tActual:    %zu\n", actual);

    if (test_results == NULL)
        exit(EXIT_FAILURE);
}

static void failed_test_print_failure_signed_integer(int64_t expected, int64_t actual, const char* file, const char* function, size_t line, const char* assert)
{
    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, assert, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, assert, line);

    printf("\tExpected:  %zi\n", expected);
    printf("\tActual:    %zi\n", actual);

    if (test_results == NULL)
        exit(EXIT_FAILURE);
}

static void failed_test_print_failure_floating(long double expected, long double actual, const char* file, const char* function, size_t line, const char* assert)
{
    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, assert, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, assert, line);

    printf("\tExpected:  %Lf\n", expected);
    printf("\tActual:    %Lf\n", actual);

    if (test_results == NULL)
        exit(EXIT_FAILURE);
}

void scrutiny_run_tests(scrutiny_unit_test_t* scrutiny_unit_tests)
{
    test_results = malloc(sizeof(scrutiny_test_results_t));
    memset(test_results, 0, sizeof(scrutiny_test_results_t));

    for (size_t test = 0; scrutiny_unit_tests[test] != NULL; test++)
        scrutiny_unit_tests[test]();
}

void scrutiny_run_benchmarks(scrutiny_benchmark_t* scrutiny_benchmarks)
{
    benchmark_results = malloc(sizeof(scrutiny_benchmark_results_t));
    memset(benchmark_results, 0, sizeof(scrutiny_benchmark_results_t));
    
    for (size_t benchmark = 0; scrutiny_benchmarks[benchmark] != NULL; benchmark++)
        scrutiny_benchmarks[benchmark]();
}

void scrutiny_run_benchmarks_n_times(scrutiny_benchmark_t* scrutiny_benchmarks, size_t n)
{
    benchmark_results = malloc(sizeof(scrutiny_benchmark_results_t));
    memset(benchmark_results, 0, sizeof(scrutiny_benchmark_results_t));
    
    for (size_t benchmark = 0; scrutiny_benchmarks[benchmark] != NULL; benchmark++)
        for (size_t i = 0; i < n; i++)
            scrutiny_benchmarks[benchmark]();
}

scrutiny_test_results_t* scrutiny_get_test_results(void)
{
    return test_results;
}

scrutiny_benchmark_results_t* scrutiny_get_benchmark_results(void)
{
    return benchmark_results;
}

scrutiny_error_t scrutiny_output_test_results(file_t* out_file)
{
    if (out_file == NULL)
        return SCRUTINY_ERROR_INVALID_ARGUMENT;

    long double percent_passed = ((long double)test_results->passed_tests / (long double)(test_results->passed_tests + test_results->failed_tests)) * 100.0;
    long double percent_failed = ((long double)test_results->failed_tests / (long double)(test_results->passed_tests + test_results->failed_tests)) * 100.0;
    long double percent_cases_passed = ((long double)test_results->passed_cases / (long double)(test_results->passed_cases + test_results->failed_cases)) * 100.0;
    long double percent_cases_failed = ((long double)test_results->failed_cases / (long double)(test_results->passed_cases + test_results->failed_cases)) * 100.0;

    fprintf(out_file, "\nScrutiny ran %zu test cases, from %zu tests, in %zu files.\n\n", test_results->failed_cases + test_results->passed_cases, test_results->passed_tests + test_results->failed_tests, test_results->files);

    if (test_results->failed_tests > 0)
        fprintf(out_file, "Failed tests:\n");

    for (size_t i = 0; i < test_results->failed_tests; i++)
        fprintf(out_file, SCRUTINY_TEXT_ITALIC "\t%s\n" SCRUTINY_TEXT_NORMAL, test_results->failed_test_names[i]);

    if (test_results->passed_cases > 0)
    {
        fprintf(out_file, "\n(" SCRUTINY_TEXT_GREEN "" SCRUTINY_TEXT_NORMAL ") %zu of %zu tests passed (%2.1Lf%%).", test_results->passed_tests, test_results->passed_tests + test_results->failed_tests, percent_passed);
        fprintf(out_file, "\t(" SCRUTINY_TEXT_GREEN "" SCRUTINY_TEXT_NORMAL ") %zu of %zu test cases passed (%2.1Lf%%).\n", test_results->passed_cases, test_results->passed_cases + test_results->failed_cases, percent_cases_passed);
    }

    if (test_results->failed_cases > 0)
    {
        fprintf(out_file, "(" SCRUTINY_TEXT_RED "x" SCRUTINY_TEXT_NORMAL ") %zu of %zu tests failed (%2.1Lf%%).", test_results->failed_tests, test_results->passed_tests + test_results->passed_tests, percent_failed);
        fprintf(out_file, "\t(" SCRUTINY_TEXT_RED "x" SCRUTINY_TEXT_NORMAL ") %zu of %zu test cases failed (%2.1Lf%%).\n", test_results->failed_cases, test_results->passed_cases + test_results->failed_cases, percent_cases_failed);
    }

    fflush(out_file);

    if (ferror(out_file))
        return SCRUTINY_ERROR_COULDNT_WRITE_TO_FILE;
    
    return SCRUTINY_ERROR_NONE;
}

scrutiny_error_t scrutiny_output_benchmark_results(file_t* out_file)
{
    if (out_file == NULL)
        return SCRUTINY_ERROR_INVALID_ARGUMENT;

    size_t unique_benchmarks = 0;
    in_progress_average_t* average_times = NULL;
    const char** unique_benchmarks_names = NULL;

    for (size_t benchmark = 0; benchmark < benchmark_results->benchmarks; benchmark++)
    {
        bool unique = true;
        size_t index_non_unique;

        for (index_non_unique = 0; index_non_unique < unique_benchmarks; index_non_unique++)
        {
            if (compare_null_terminated_strings(benchmark_results->benchmark_names[benchmark], unique_benchmarks_names[index_non_unique]))
            {
                unique = false;
                break;
            }
        }

        if (unique)
        {
            unique_benchmarks++;
            unique_benchmarks_names = reallocarray(unique_benchmarks_names, unique_benchmarks, sizeof(char*));
            average_times = reallocarray(average_times, unique_benchmarks, sizeof(in_progress_average_t));
            unique_benchmarks_names[unique_benchmarks - 1] = benchmark_results->benchmark_names[benchmark];
            average_times[unique_benchmarks - 1].running_total = benchmark_results->benchmark_times[benchmark];
            average_times[unique_benchmarks - 1].divisor = 1;
            continue;
        }

        average_times[index_non_unique].running_total += benchmark_results->benchmark_times[benchmark];
        average_times[index_non_unique].divisor++;
    }

    fprintf(out_file, "Scrutiny ran %zu unique benchmarks for a total of %zu benchmark runs.\n\n", unique_benchmarks, benchmark_results->benchmarks);

    for (size_t i = 0; i < unique_benchmarks; i++)
    {
        clock_t average_time = average_times[i].running_total / average_times[i].divisor;
        long double average_seconds = (long double)average_time / (long double)CLOCKS_PER_SEC;

        if (average_seconds < 0.1)
            fprintf(out_file, SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL ": %.1Lf ms (%.1Lf per/s)\n", unique_benchmarks_names[i], average_seconds * 1000, 1.0L / average_seconds);
        else
            fprintf(out_file, SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL ": %.3Lf s (%.1Lf per/s)\n", unique_benchmarks_names[i], average_seconds, 1.0L / average_seconds);
    }

    if (ferror(out_file))
        return SCRUTINY_ERROR_COULDNT_WRITE_TO_FILE; 

    return SCRUTINY_ERROR_NONE;
}

scrutiny_error_t scrutiny_output_test_results_parsable(file_t* out_file)
{
    if (out_file == NULL)
        return SCRUTINY_ERROR_INVALID_ARGUMENT;

    long double percent_passed = ((long double)test_results->passed_tests / (long double)(test_results->passed_tests + test_results->failed_tests)) * 100.0;
    long double percent_failed = ((long double)test_results->failed_tests / (long double)(test_results->passed_tests + test_results->failed_tests)) * 100.0;
    long double percent_cases_passed = ((long double)test_results->passed_cases / (long double)(test_results->passed_cases + test_results->failed_cases)) * 100.0;
    long double percent_cases_failed = ((long double)test_results->failed_cases / (long double)(test_results->passed_cases + test_results->failed_cases)) * 100.0;

    fprintf(out_file, "ran %zu cases, %zu tests, %zu files\n\n", test_results->failed_cases + test_results->passed_cases, test_results->failed_tests + test_results->passed_tests, test_results->files);

    fprintf(out_file, "cases:\n");
    fprintf(out_file, "%zu/%zu passed (%2.1Lf%%)\n", test_results->passed_cases, test_results->passed_cases + test_results->failed_cases, percent_cases_passed);
    fprintf(out_file, "%zu/%zu failed (%2.1Lf%%)\n\n", test_results->failed_cases, test_results->failed_cases + test_results->passed_cases, percent_cases_failed);

    fprintf(out_file, "tests:\n");
    fprintf(out_file, "%zu/%zu passed (%2.1Lf%%)\n", test_results->passed_tests, test_results->passed_tests+ test_results->failed_tests, percent_passed);
    fprintf(out_file, "%zu/%zu failed (%2.1Lf%%)\n\n", test_results->failed_tests, test_results->passed_tests+ test_results->failed_tests, percent_failed);

    fprintf(out_file, "failed tests:\n");

    for (size_t i = 0; i < test_results->failed_tests; i++)
        fprintf(out_file, "%s\n", test_results->failed_test_names[i]);

    fflush(out_file);

    if (ferror(out_file))
        return SCRUTINY_ERROR_COULDNT_WRITE_TO_FILE;
    
    return SCRUTINY_ERROR_NONE;
}

scrutiny_error_t scrutiny_output_benchmark_results_parsable(file_t* file)
{
    if (file == NULL)
        return SCRUTINY_ERROR_INVALID_ARGUMENT;

    for (size_t i = 0; i < benchmark_results->benchmarks; i++)
        fprintf(file, "%s:%Lf\n", benchmark_results->benchmark_names[i], (long double)benchmark_results->benchmark_times[i] / (long double)CLOCKS_PER_SEC);
    
    if (ferror(file))
        return SCRUTINY_ERROR_COULDNT_WRITE_TO_FILE;
    
    return SCRUTINY_ERROR_NONE;
}

void scrutiny_clear_results(void)
{
    if (test_results != NULL)
    {
        free(test_results->passed_test_names);
        free(test_results->failed_test_names);
        free(test_results->file_names);
        free(test_results);
    }

    if (benchmark_results != NULL)
    {
        free(benchmark_results->benchmark_names);
        free(benchmark_results->benchmark_times);
        free(benchmark_results->file_names);
        free(benchmark_results);
    }

    test_results = NULL;
    benchmark_results = NULL;
}

void scrutiny_report_assert_pass(const char* file, const char* function)
{
    if (test_results == NULL)
        return;
    
    test_file_expand_and_add(file);
    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_fail(const char* file, const char* function, size_t line)
{
    if (test_results == NULL)
    {
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
        exit(EXIT_FAILURE);
    }

    test_file_expand_and_add(file);
    succeeded_test_contract_and_remove(function);
    failed_test_expand_and_add(function);

    printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
}

void scrutiny_report_assert_true(bool expression, const char* file, const char* function, size_t line)
{
    if (test_results == NULL && !expression)
    {
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
        exit(EXIT_FAILURE);
    }
    else if (test_results == NULL)
    {
        return;
    }

    test_file_expand_and_add(file);

    if (!expression)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_false(bool expression, const char* file, const char* function, size_t line)
{
    if (test_results == NULL && expression)
    {
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
        exit(EXIT_FAILURE);
    }
    else if (test_results == NULL)
    {
        return;
    }

    test_file_expand_and_add(file);

    if (expression)
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
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
            if (test_results == NULL)
            {
                printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
                printf("\tExpected:  %u at byte %zu\n", expected_bytes[i], i);
                printf("\tActual:    %u\n", actual_bytes[i]);
                exit(EXIT_FAILURE);
            }

            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
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
            if (test_results == NULL)
            {
                printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
                printf("\tDifference at index: %zu\n", byte / sizeof_type);
                exit(EXIT_FAILURE);
            }

            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
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
            if (test_results == NULL)
            {
                printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
                printf("\tExpected:  %c at index %zu\n", expected[i], i);
                printf("\tActual:    %c\n", actual[i]);
                exit(EXIT_FAILURE);
            }

            succeeded_test_contract_and_remove(function);
            failed_test_expand_and_add(function);
            printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
            printf("\tExpected:  %c at index %zu\n", expected[i], i);
            printf("\tActual:    %c\n", actual[i]);
            return;
        }
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_not_equal_ptr_data(void* expected, void* actual, size_t struct_size, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    uint8_t* expected_bytes = (uint8_t*)expected;
    uint8_t* actual_bytes = (uint8_t*)actual;

    for (size_t i = 0; i < struct_size; i++)
    {
        if (expected_bytes[i] != actual_bytes[i])
        {
            succeeded_test_expand_and_add(function);
            return;
        }
    }

    succeeded_test_contract_and_remove(function);
    failed_test_expand_and_add(function);

    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
}

void scrutiny_report_assert_not_equal_array(void* expected, void* actual, size_t sizeof_type, size_t array_length, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    uint8_t* expected_bytes = (uint8_t*)expected;
    uint8_t* actual_bytes = (uint8_t*)actual;

    for (size_t byte = 0; byte < sizeof_type * array_length; byte++)
    {
        if (expected_bytes[byte] != actual_bytes[byte])
        {
            succeeded_test_expand_and_add(function);
            return;
        }
    }

    succeeded_test_contract_and_remove(function);
    failed_test_expand_and_add(function);

    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
}

void scrutiny_report_assert_not_equal_string(char* expected, char* actual, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    if (compare_null_terminated_strings(expected, actual))
    {
        succeeded_test_contract_and_remove(function);
        failed_test_expand_and_add(function);
        failed_test_print_failure(expected, actual, file, function, line, __func__);
        return;
    }

    succeeded_test_expand_and_add(function);
}

void scrutiny_report_assert_not_equal_non_terminated_string(char* expected, char* actual, size_t size, const char* file, const char* function, size_t line)
{
    test_file_expand_and_add(file);

    for (size_t i = 0; i < size; i++)
    {
        if (expected[i] != actual[i])
        {
            succeeded_test_expand_and_add(function);
            return;
        }
    }

    succeeded_test_contract_and_remove(function);
    failed_test_expand_and_add(function);

    if (test_results == NULL)
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nASSERTION FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed in " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, __func__, function, line);
    else
        printf(SCRUTINY_TEXT_RED SCRUTINY_TEXT_BOLD "\nTEST FAILED" SCRUTINY_TEXT_NORMAL " (%s): " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " failed " SCRUTINY_TEXT_ITALIC "%s" SCRUTINY_TEXT_NORMAL " on line %zu\n\n", file, function, __func__, line);
}


void scrutiny_report_assert_equal_char(char expected, char actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_short(short expected, short actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int(int expected, int actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_long(long expected, long actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_long_long(long long expected, long long actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_float(float expected, float actual, const char* file, const char* function, size_t line) { assert_floating_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_double(double expected, double actual, const char* file, const char* function, size_t line) { assert_floating_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_long_double(long double expected, long double actual, const char* file, const char* function, size_t line) { assert_floating_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uintptr_t(uintptr_t expected, uintptr_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_uintmax_t(uintmax_t expected, uintmax_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_size_t(size_t expected, size_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_ssize_t(ssize_t expected, ssize_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_enum(enum_value_t expected, enum_value_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(==, expected, actual, file, function, line); }
void scrutiny_report_assert_equal_ptr(void* expected, void* actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(==, (uintptr_t)expected, (uintptr_t)actual, file, function, line); }

void scrutiny_report_assert_not_equal_char(char expected, char actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_short(short expected, short actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int(int expected, int actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_long(long expected, long actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_long_long(long long expected, long long actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_float(float expected, float actual, const char* file, const char* function, size_t line) { assert_floating_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_double(double expected, double actual, const char* file, const char* function, size_t line) { assert_floating_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_long_double(long double expected, long double actual, const char* file, const char* function, size_t line) { assert_floating_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uintptr_t(uintptr_t expected, uintptr_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_uintmax_t(uintmax_t expected, uintmax_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_size_t(size_t expected, size_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_ssize_t(ssize_t expected, ssize_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_enum(enum_value_t expected, enum_value_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(!=, expected, actual, file, function, line); }
void scrutiny_report_assert_not_equal_ptr(void* expected, void* actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(!=, (uintptr_t)expected, (uintptr_t)actual, file, function, line); }

void scrutiny_report_assert_greater_than_char(char expected, char actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_short(short expected, short actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int(int expected, int actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_long(long expected, long actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_long_long(long long expected, long long actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_float(float expected, float actual, const char* file, const char* function, size_t line) { assert_floating_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_double(double expected, double actual, const char* file, const char* function, size_t line) { assert_floating_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_long_double(long double expected, long double actual, const char* file, const char* function, size_t line) { assert_floating_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uintptr_t(uintptr_t expected, uintptr_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_uintmax_t(uintmax_t expected, uintmax_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_size_t(size_t expected, size_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_ssize_t(ssize_t expected, ssize_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_enum(enum_value_t expected, enum_value_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(>, expected, actual, file, function, line); }
void scrutiny_report_assert_greater_than_ptr(void* expected, void* actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(>, (uintptr_t)expected, (uintptr_t)actual, file, function, line); }

void scrutiny_report_assert_less_than_char(char expected, char actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_short(short expected, short actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int(int expected, int actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_long(long expected, long actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_long_long(long long expected, long long actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_float(float expected, float actual, const char* file, const char* function, size_t line) { assert_floating_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_double(double expected, double actual, const char* file, const char* function, size_t line) { assert_floating_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_long_double(long double expected, long double actual, const char* file, const char* function, size_t line) { assert_floating_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uintptr_t(uintptr_t expected, uintptr_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_uintmax_t(uintmax_t expected, uintmax_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_size_t(size_t expected, size_t actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_ssize_t(ssize_t expected, ssize_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_enum(enum_value_t expected, enum_value_t actual, const char* file, const char* function, size_t line) { assert_signed_generic(<, expected, actual, file, function, line); }
void scrutiny_report_assert_less_than_ptr(void* expected, void* actual, const char* file, const char* function, size_t line) { assert_unsigned_generic(<, (uintptr_t)expected, (uintptr_t)actual, file, function, line); }

void scrutiny_report_benchmark_time(clock_t time, const char* file, const char* function, size_t line)
{
    benchmark_run_expand_and_add(function, file, time);
}

