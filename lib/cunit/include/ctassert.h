//
//  ctassert.h
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctassert_h
#define ctassert_h

#include "ctest.h"
#include <string.h>
#include <math.h>

/*!
 * @define _CTFailure(test, ...)
 * Generates a failure unconditionally (for internal usage, use CFail(...) instead in your code).
 */

#define _CTFailure(test, expr1Str, assertionStr, expr2Str, ...) _ctfail(test, expr1Str, assertionStr, expr2Str, __FILE__, __LINE__, "" __VA_ARGS__);

/*!
 * @define CTFail(test, ...)
 * Generates a failure unconditionally.
 * @param test The test
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTFail(test, ...) _CTFailure(test, "", "", "", __VA_ARGS__);

/*!
 * @define CTAssertEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) != (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertEqual(test, expression1, expression2, ...) if ((expression1) != (expression2)) { _CTFailure(test, #expression1, "is not equal to", #expression2, __VA_ARGS__) }

/*!
 * @define CTAssertNotEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) == (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotEqual(test, expression1, expression2, ...) if ((expression1) == (expression2)) { _CTFailure(test, #expression1, "is equal to", #expression2, __VA_ARGS__) }

/*!
 * @define CTAssertStringEqual(test, str1, str2, ...)
 * Generates a failure when str1 is not equal to str2.
 * @param test The test
 * @param str1 A string.
 * @param str2 A string.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertStringEqual(test, str1, str2, ...) if (strcmp(str1, str2) != 0) { _CTFailure(test, #str1, "string is not equal to string", #str2, __VA_ARGS__) }

/*!
 * @define CTAssertStringNotEqual(test, str1, str2, ...)
 * Generates a failure when str1 is equal to str2.
 * @param test The test
 * @param str1 A string.
 * @param str2 A string.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertStringNotEqual(test, str1, str2, ...) if (strcmp(str1, str2) == 0) { _CTFailure(test, #str1, "string is equal to string", #str2, __VA_ARGS__) }

/*!
 * @define CTAssertDecimalEqual(test, dec1, dec2, precision, ...)
 * Generates a failure when dec1 is not equal to dec2.
 * @param test The test
 * @param dec1 A decimal value.
 * @param dec2 A decimal value.
 * @param precision The precision used for the comparison.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertDecimalEqual(test, dec1, dec2, precision, ...) if (fabs(dec1 - dec2) > precision) { _CTFailure(test, #dec1, "is not equal to", #dec2, __VA_ARGS__) }

/*!
 * @define CTAssertDecimalNotEqual(test, dec1, dec2, precision, ...)
 * Generates a failure when dec1 is equal to dec2.
 * @param test The test
 * @param dec1 A decimal value.
 * @param dec2 A decimal value.
 * @param precision The precision used for the comparison.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertDecimalNotEqual(test, dec1, dec2, precision, ...) if (fabs(dec1 - dec2) <= precision) { _CTFailure(test, #dec1, "is equal to", #dec2, __VA_ARGS__) }

/*!
 * @define CTAssertArrayEqual(test, arr1, arr2, asize, atsize, aeltcmp_fct, ...)
 * Generates a failure when arr1 is not equal to arr2.
 * @param test The test
 * @param arr1 An array.
 * @param arr2 An array.
 * @param asize The size of the array.
 * @param atsize The size of the array element.
 * @param aeltcmp_fct The function to use for comparing two array elements.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertArrayEqual(test, arr1, arr2, asize, atsize, aeltcmp_fct, ...) if (_ctarraycmp(arr1, arr2, asize, atsize, aeltcmp_fct) != 0) { _CTFailure(test, #arr1, "array is not equal to array", #arr2, __VA_ARGS__) }

/*!
 * @define CTAssertArrayNotEqual(test, arr1, arr2, asize, atsize, aeltcmp_fct, ...)
 * Generates a failure when arr1 is equal to arr2.
 * @param test The test
 * @param arr1 An array.
 * @param arr2 An array.
 * @param asize The size of the array.
 * @param atsize The size of the array element.
 * @param aeltcmp_fct The function to use for comparing two array elements.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertArrayNotEqual(test, arr1, arr2, asize, atsize, aeltcmp_fct, ...) if (_ctarraycmp(arr1, arr2, asize, atsize, aeltcmp_fct) == 0) { _CTFailure(test, #arr1, "array is equal to array", #arr2, __VA_ARGS__) }

/*!
 * @define CTAssertTrue(expression, ...)
 * Generates a failure when ((\a expression) != true).
 * @param test The test
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertTrue(test, expression, ...) if (!(expression)) { _CTFailure(test, #expression, "is not true", "", __VA_ARGS__) }

/*!
 * @define CTAssertFalse(expression, ...)
 * Generates a failure when ((\a expression) != false).
 * @param test The test
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertFalse(test, expression, ...) if ((expression)) { _CTFailure(test, #expression, "is not false", "", __VA_ARGS__) }

/*!
 * @define CTAssertNull(expression, ...)
 * Generates a failure when ((\a expression) != NULL).
 * @param test The test
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNull(test, expression, ...) if ((expression) != NULL) { _CTFailure(test, #expression, "is not null", "", __VA_ARGS__) }

/*!
 * @define CTAssertNotNull(expression, ...)
 * Generates a failure when ((\a expression) == NULL).
 * @param test The test
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotNull(test, expression, ...) if ((expression) == NULL) { _CTFailure(test, #expression, "is null", "", __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) <= (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThan(test, expression1, expression2, ...) if ((expression1) <= (expression2)) { _CTFailure(test, #expression1, "is not greater than", #expression2, __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) < (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThanOrEqual(test, expression1, expression2, ...) if ((expression1) < (expression2)) { _CTFailure(test, #expression1, "is not greater than or equal to", #expression2, __VA_ARGS__) }

/*!
 * @define CTAssertLessThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) >= (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThan(test, expression1, expression2, ...) if ((expression1) >= (expression2)) { _CTFailure(test, #expression1, "is not lesser than", #expression2, __VA_ARGS__) }

/*!
 * @define CTAssertLessThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) > (\a expression2)).
 * @param test The test
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThanOrEqual(test, expression1, expression2, ...) if ((expression1) > (expression2)) { _CTFailure(test, #expression1, "is not less or equal to", #expression2, __VA_ARGS__) }

/*!
 @function   _cfail
 @abstract   Generates a failure unconditionally.
 
@discussion This function is for internal usage. If you want to generate a failure unconditionally, please use the defined macro CTFail
 */

void _ctfail(ctest_t *test, const char *expr1, const char *assertion, const char *expr2, const char *filename, unsigned long lineNumber, const char * format, ...);

/*!
 @function   _ctarraycmp
 @abstract   Compares two arrays.
 
 @discussion This function is for internal usage. If you want to test array equality, please use the defined macros CTAssertArrayEqual and CTAssertArrayNotEqual
 */

int _ctarraycmp(void *arr1, void *arr2, size_t asize, size_t atsize, int (* _aeltcmp)(const void *, const void *));

#endif /* ctassert_h */
