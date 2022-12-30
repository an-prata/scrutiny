/* 
 * Copyright (c) 2022 Evan Overman (https://an-prata.it). Licensed under the MIT License.
 * See LICENSE file in repository root for complete license text.
 */

#ifndef SCRUTINY_H
#define SCRUTINY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define scrutiny_test extern

/* 
 * This collection of macros serves only to simplify assert calls by
 * automatically adding the __FILE__, __LINE__, and __func__ macros as
 * arguments to the function call for easier debugging.
 */

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

int main(); /* Just reserves the main function, no test suite should contain a main function. */

enum scrutiny_assert_result_e
{
    SCRUTINY_ASSERT_FAILURE = 0,
    SCRUTINY_ASSERT_SUCCESS = 1,
    SCRUTINY_ASSERT_ERROR = -1
};

typedef enum scrutiny_assert_result_e scrutiny_assert_result_t;

/*
 * The following functions, while not intended to be used directly, will not
 * be a problem if used directly. In most cases the macros above should be used
 * but if many asserts are run in a loop it may be useful to replace one of the
 * arguments with a custom string in case the default report is not enough.
 */

void scrutiny_report_assert_true(bool expression, const char* file, const char* function, size_t line);
void scrutiny_report_assert_false(bool expression, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_char(char expected, char actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_unsigned_char(unsigned char expected, unsigned char actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_short(short expected, short actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int(int expected, int actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_long(long expected, long actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_long_long(long long expected, long long actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_unsigned_short(unsigned short expected, unsigned short actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_unsigned_int(unsigned int expected, unsigned int actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_unsigned_long(unsigned long expected, unsigned long actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_float(float expected, float actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_double(double expected, double actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_long_double(long double expected, long double actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int8_t(int8_t expected, int8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int16_t(int16_t expected, int16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int32_t(int32_t expected, int32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int64_t(int64_t expected, int64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_least8_t(int_least8_t expected, int_least8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_least16_t(int_least16_t expected, int_least16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_least32_t(int_least32_t expected, int_least32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_int_least64_t(int_least64_t expected, int_least64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint8_t(uint8_t expected, uint8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint16_t(uint16_t expected, uint16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint32_t(uint32_t expected, uint32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint64_t(uint64_t expected, uint64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_intptr_t(intptr_t expected, intptr_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_intmax_t(intmax_t expected, intmax_t actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_ptr(void* expected, void* actual, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_ptr_data(void* expected, void* actual, size_t struct_size, const char* file, const char* function, size_t line);
void scrutiny_report_assert_equal_array(void* expected, void* actual, size_t sizeof_type, size_t array_length, const char* file, const char* function, size_t line);

/*
 * These functions will not produce a report, I would not recommend using them. 
 * They are used internally by scrutiny and are available with the definition 
 * of the SCRUTINY_NON_REPORTING_ASSERT macro. Unlike their reporting 
 * counter-parts however, these functions will return an enum showing the 
 * success/failure of the assert.
 */

#ifdef SCRUTINY_NON_REPORTING_ASSERT
#ifndef SCRUTINY_NO_WARN_NON_REPORTING_ASSERT /* Define to disable warning on non-reporting asserts. */
#warning "Using non reporting assert functions, avoid this if possible."
#endif // SCRUTINY_NO_WARN_NON_REPORTING_ASSERT
scrutiny_assert_result_t inline scrutiny_no_report_assert_true(bool expression);
scrutiny_assert_result_t inline scrutiny_no_report_assert_false(bool expression);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_char(char expected, char actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_unsigned_char(unsigned char expected, unsigned char actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_short(short expected, short actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int(int expected, int actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_long(long expected, long actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_long_long(long long expected, long long actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_unsigned_short(unsigned short expected, unsigned short actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_unsigned_int(unsigned int expected, unsigned int actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_unsigned_long(unsigned long expected, unsigned long actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_unsigned_long_long(unsigned long long expected, unsigned long long actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_float(float expected, float actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_double(double expected, double actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_long_double(long double expected, long double actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int8_t(int8_t expected, int8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int16_t(int16_t expected, int16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int32_t(int32_t expected, int32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int64_t(int64_t expected, int64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_fast8_t(int_fast8_t expected, int_fast8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_fast16_t(int_fast16_t expected, int_fast16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_fast32_t(int_fast32_t expected, int_fast32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_fast64_t(int_fast64_t expected, int_fast64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_least8_t(int_least8_t expected, int_least8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_least16_t(int_least16_t expected, int_least16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_least32_t(int_least32_t expected, int_least32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_int_least64_t(int_least64_t expected, int_least64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint8_t(uint8_t expected, uint8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint16_t(uint16_t expected, uint16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint32_t(uint32_t expected, uint32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint64_t(uint64_t expected, uint64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_fast8_t(uint_fast8_t expected, uint_fast8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_fast16_t(uint_fast16_t expected, uint_fast16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_fast32_t(uint_fast32_t expected, uint_fast32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_fast64_t(uint_fast64_t expected, uint_fast64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_least8_t(uint_least8_t expected, uint_least8_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_least16_t(uint_least16_t expected, uint_least16_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_least32_t(uint_least32_t expected, uint_least32_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_uint_least64_t(uint_least64_t expected, uint_least64_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_intptr_t(intptr_t expected, intptr_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_intmax_t(intmax_t expected, intmax_t actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_ptr(void* expected, void* actual);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_ptr_data(void* expected, void* actual, size_t struct_size);
scrutiny_assert_result_t inline scrutiny_no_report_assert_equal_array(void* expected, void* actual, size_t sizeof_type, size_t array_length);
#endif // SCRUTINY_NON_REPORTING_ASSERT

#endif // SCRUTINY_H

