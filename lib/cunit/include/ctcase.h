//
//  ctcase.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctcase_h
#define ctcase_h

#include "ctest.h"

/*!
 * @brief The object for defining a test case.
 */

typedef struct ctcase_t {
    /// Name of the test case
    const char *name;
    /// Internal usage
    void *_internal;
}ctcase_t;

/*!
 * @discussion Creates a test case
 * @param name the name of the test case
 * @return a test case
 */

ctcase_t *ctcase(const char *name);

/*!
 * @discussion Adds a standard test to the case
 * @param tcase the test case
 * @param test the standard test to add
 */

void ctctestadd(ctcase_t *tcase, ctest_t *test);

/*!
 * @discussion Adds a performance test to the case
 * @param tcase the test case
 * @param test the performance test to add
 * @param time the expected time for the performance test 
 */

void ctcperfadd(ctcase_t *tcase, ctest_t *test, double time);

/*!
 * @discussion Frees the memory used by the test case
 * @param tcase the test case
 */

void ctcfree(ctcase_t *tcase);

#endif /* ctcase_h */
