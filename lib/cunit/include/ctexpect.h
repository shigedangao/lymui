//
//  ctexpect.h
//  cunit
//
//  Created by itzseven on 14/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef ctexpect_h
#define ctexpect_h

#include <stdbool.h>

/*!
 * @brief The object for defining an expectation.
 * @discussion Use an expectation to test the behavior of your code asynchronously
 */

typedef struct ctexpect_t {
    /// Description for the expectation
    const char *desc;
    /// If set to @c true, the test will fail if you fulfill the expectation
    bool inverted;
    /// Number of times you have to call @c fulfill function to completely fulfill the expectation
    unsigned int expectedFulfillmentCount;
    /// If set to @c true, the test will fail if the number of fulfillment exceed @c expectedFulfillmentCount
    bool assertForOverFulfill;
    /// Internal usage
    void *_internal;
}ctexpect_t;

/*!
 * @discussion Fulfills the expectation
 * @param texpect the test expectation
 */

void fulfill(ctexpect_t *texpect);
void ctefree(ctexpect_t *texpect);

#endif /* ctexpect_h */
