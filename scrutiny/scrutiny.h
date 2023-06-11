// Copyright (c) 2023 Evan Overman (https://an-prata.it). Licensed under the MIT License.
// See LICENSE file in repository root for complete license text.

#ifndef SCRUTINY_H
#define SCRUTINY_H

#include <stdbool.h>

#define SCRUTINY_UNIT_TEST(name) void name(scrutiny_test_run_t* _scrutiny_test_run)

#define scrutiny_assert(a) \
_scrutiny_assert(a, __FILE__, __func__, __LINE__)
#define scrutiny_assert_equal(a, b) \
_scrutiny_assert_equal(a, b, __FILE__, __func__, __LINE__)
#define scrutiny_assert_not_equal(a, b) \
_scrutiny_assert_not_equal(a, b, __FILE__, __func__, __LINE__)
#define scrutiny_assert_greater_than(a, b) \
_scrutiny_assert_greater_than(a, b, __FILE__, __func__, __LINE__)
#define scrutiny_assert_less_than(a, b) \
_scrutiny_assert_less_than(a, b, __FILE__, __func__, __LINE__)
#define scrutiny_assert_greater_than_or_equal(a, b) \
_scrutiny_assert_greater_than_or_equal(a, b, "scrutiny_assert_greater_than_or_equal", __FILE__, __func__, __LINE__)
#define scrutiny_assert_less_thanor_equal(a, b) \
_scrutiny_assert_less_than_or_equal(a, b, "scrutiny_assert_less_thanor_equal", __FILE__, __func__, __LINE__)
#define scrutiny_assert_no_less_than(a, b) \
_scrutiny_assert_greater_than_or_equal(a, b, "scrutiny_assert_no_less_than", __FILE__, __func__, __LINE__)
#define scrutiny_assert_no_greater_than(a, b) \
_scrutiny_assert_less_than_or_equal(a, b, "scrutiny_assert_no_greater_than", __FILE__, __func__, __LINE__)

#define _scrutiny_assert(a, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a), "scrutiny_assert", #a, file, func, line)) \
	return
#define _scrutiny_assert_equal(a, b, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) == (b), "scrutiny_assert_equal", #a ", " #b, file, func, line)) \
	return
#define _scrutiny_assert_not_equal(a, b, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) != (b), "scrutiny_assert_not_equal", #a ", " #b, file, func, line)) \
	return
#define _scrutiny_assert_greater_than(a, b, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) > (b), "scrutiny_assert_greater_than", #a ", " #b, file, func, line)) \
	return
#define _scrutiny_assert_less_than(a, b, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) < (b), "scrutiny_assert_less_than", #a ", " #b, file, func, line)) \
	return
#define _scrutiny_assert_greater_than_or_equal(a, b, assert, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) >= (b), assert, #a ", " #b, file, func, line)) \
	return
#define _scrutiny_assert_less_than_or_equal(a, b, assert, file, func, line) \
if (!_scrutiny_record_assert(_scrutiny_test_run, (a) <= (b), assert, #a ", " #b, file, func, line)) \
	return

typedef enum {
	SCRUTINY_SUCCESS = true,
	SCRUTINY_FAILURE = false,
} scrutiny_test_result_t;

typedef struct {
	const char* previous_function;
	scrutiny_test_result_t current_test_result;
	unsigned long asserts_passed;
	unsigned long asserts_failed;
	unsigned long tests_passed;
	unsigned long tests_failed;
} scrutiny_test_run_t;

typedef void (*scrutiny_test_t)(scrutiny_test_run_t*);

/*
 * This function expected that `tests` points to a NULL terminated array of
 * `scrutiny_test_t` function pointers.
 */
void scrutiny_run_tests(scrutiny_test_t* tests);
void scrutiny_run_tests_with_stats(scrutiny_test_t* tests);

bool _scrutiny_record_assert(scrutiny_test_run_t* test_run, bool succeeded, const char* assert, const char* condition, const char* file, const char* function, unsigned long line);

#endif // SCRUTINY_H

