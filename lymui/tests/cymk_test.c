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

ctest_return_t testCymkNullCreation(ctest_t *test, void *arg) {
    struct Cymk *cymk = getCymkFromRgb(NULL);
    CTAssertNull(test, cymk, "Expected CYMK to be NULL");
    
    free(cymk);
}

ctest_return_t testCymkToUint8Array(ctest_t *test, void *arg) {
    struct Cymk *cymk = malloc(sizeof(struct Cymk));
    cymk->c = 0.0f;
    cymk->y = 0.0f;
    cymk->m = 0.0f;
    cymk->k = 1.0f;
    
    uint8_t *colors = getRawRGBArrayValueFromCymk(cymk);
    
    CTAssertEqual(test, 0, colors[0], "Expected R to be 0, instead %ui", colors[0]);
    CTAssertEqual(test, 0, colors[1], "Expected G to be 0, instead %ui", colors[1]);
    CTAssertEqual(test, 0, colors[2], "Expected B to be 0, instead %ui", colors[2]);

    free(cymk);
    free(colors);
}

ctest_return_t testCymkToUintNull(ctest_t *test, void *arg) {
    uint8_t *colors = getRawRGBArrayValueFromCymk(NULL);
    
    CTAssertNull(test, colors, "Expected colors to be NULL");
    free(colors);
}

ctcase_t *wrapCymkCreationTest() {
    // Create case
    ctcase_t *cymkCase = ctcase("Cymk test case");
    
    // Create test
    ctest_t *cymkCreation = ctest("Create Cymk From RGB struct", testCymkCreation, NULL);
    ctest_t *cymkNull = ctest("Cymk should return NULL", testCymkNullCreation, NULL);
    ctest_t *colorsCymk = ctest("Cymk to UINT should return a valid colors array", testCymkToUint8Array, NULL);
    ctest_t *uintColorNull = ctest("Cymk should return NULL", testCymkToUintNull, NULL);

    
    // add test to cases
    ctctestadd(cymkCase, cymkCreation);
    ctctestadd(cymkCase, cymkNull);
    ctctestadd(cymkCase, colorsCymk);
    ctctestadd(cymkCase, uintColorNull);
    
    return cymkCase;
}
