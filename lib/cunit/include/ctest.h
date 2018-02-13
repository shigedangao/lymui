//
//  ctest.h
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef ctest_h
#define ctest_h

#include "ctexpect.h"

struct ctest_t;

typedef void ctest_return_t;
typedef void ctopt_return_t;

typedef ctest_return_t (*ctinv_ptr_t)(struct ctest_t *test, void *arg);
typedef ctopt_return_t (*ctoptinv_ptr_t)(void *arg);

/*!
 * @brief The object for defining a test.
 */

typedef struct ctest_t {
    /// Name of the test
    const char *name;
    /// Invocation of the test
    ctinv_ptr_t inv;
    /// Argument of the test
    void *arg;
    /// Setup function
    ctoptinv_ptr_t setup;
    /// Tear down function
    ctoptinv_ptr_t tdown;
    /// Internal usage
    void *_internal;
}ctest_t;

/*!
 * @discussion Creates a test
 * @param name the name of the test
 * @param inv the pointer of the function to call
 * @param arg the argument to pass to your function
 * @return a test
 */

ctest_t *ctest(const char *name, ctinv_ptr_t inv, void *arg);

/*!
 * @discussion Creates an expectation
 * @param test the test responsible of the expectation
 * @param desc the expectation description
 * @return an expectation
 */

ctexpect_t *ctexpect(ctest_t *test, const char *desc);

/*!
 * @discussion Waits for all expectations related to the test
 * @param test the test responsible of the expectations
 * @param timeout the amount of time to wait before checking expectation's fulfillment state
 */
void ctexpectwait(ctest_t *test, unsigned int timeout);

/*!
 * @discussion Frees the memory used by the test
 * @param test the test
 */

void ctfree(ctest_t *test);

#endif /* ctest_h */
