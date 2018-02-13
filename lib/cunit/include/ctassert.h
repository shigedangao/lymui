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

/*!
 * @define _CTFailure(test, ...)
 * Generates a failure unconditionally (for internal usage, use CFail(...) instead in your code).
 */

#define _CTFailure(test, expr1Str, assertionStr, expr2Str, ...) _cfail(test, expr1Str, assertionStr, expr2Str, __FILE__, __LINE__, "" __VA_ARGS__);

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
 
@discussion This function is for internal usage. If you want to generate a failure unconditionally, please use the defined macro CTFail(test, ...)
 */

void _cfail(ctest_t *test, const char *expr1, const char *assertion, const char *expr2, const char *filename, unsigned long lineNumber, const char * format, ...);

#endif /* ctassert_h */
