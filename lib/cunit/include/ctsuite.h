//
//  ctsuite.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctsuite_h
#define ctsuite_h

#include "ctcase.h"

/*!
 * @brief The object for defining a test suite.
 */

typedef struct ctsuite_t {
    /// Name of the test suite
    const char *name;
    /// The number of tests
    unsigned int count;
    /// The number of passed tests
    unsigned int passed;
    /// The number of failed tests
    unsigned int failed;
    /// Internal usage
    void *_internal;
}ctsuite_t;

/*!
 * @discussion Creates a test suite
 * @param name the name of the test suite
 * @return a test suite
 */

ctsuite_t *ctsuite(const char *name);

/*!
 * @discussion Adds a test case to the suite
 * @param tsuite the test suite
 * @param tcase the test case to add
 */

void ctscaseadd(ctsuite_t *tsuite, const ctcase_t *tcase);

/*!
 * @discussion Runs the test suite
 * @param tsuite the test suite
 */

void ctsrun(ctsuite_t *tsuite);

/*!
 * @discussion Frees the memory used by the test suite
 * @param tsuite the test suite
 */

void ctsfree(ctsuite_t *tsuite);

#endif /* ctsuite_h */
