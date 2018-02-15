//
//  cymk_test.c
//  lymui
//
//  Created by Marc on 15/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cunit.h>
#include "test_header.h"
#include "rgb.h"
#include "cymk.h"

ctest_return_t testCymkCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {255, 55, 102};
    struct Rgb *rgb = makeRGB(uc, 3);
    struct Cymk *cymk = getCymkFromRgb(rgb);
    
    // Check the value of the cymk
    CTAssertEqual(test, 0.0f, cymk->c, "Expected value for C %f, value: %f", 0.0f, cymk->c);
    CTAssertEqual(test, 8.0f, roundf(cymk->m * 10), "Expected value for M %f, value: %f", cymk->m);
    CTAssertEqual(test, 6.0f, round(cymk->y * 10), "Expected value for Y %f, value: %f", 0.6f, cymk->y);
    CTAssertEqual(test, 0.0, cymk->k, "Expected value for K %f, value: %f", 0.0f, cymk->k);
    
    free(cymk);
}

ctcase_t *wrapCymkCreationTest() {
    // Create case
    ctcase_t *cymkCase = ctcase("Cymk test case");
    
    // Create test
    ctest_t *cymkCreation = ctest("Create Cymk From RGB struct", testCymkCreation, NULL);
    
    // add test to cases
    ctctestadd(cymkCase, cymkCreation);
    return cymkCase;
}
