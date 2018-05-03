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
    CTAssertEqual(test, 0.0f, cymk->c, "Expect C to be equal to %f but got %f", 0.0f, cymk->c);
    CTAssertEqual(test, 8.0f, roundf(cymk->m * 10), "Expect Y to be equal to %f but got %f", 8.0f, cymk->m);
    CTAssertEqual(test, 6.0f, round(cymk->y * 10), "Expect M to be equal to %f but got %f", 0.6f, cymk->y);
    CTAssertEqual(test, 0.0, cymk->k, "Expect K to be equal to %f but got %f", 0.0f, cymk->k);
    
    free(cymk);
}

ctest_return_t testCymkNullCreation(ctest_t *test, void *arg) {
    struct Cymk *cymk = getCymkFromRgb(NULL);
    CTAssertNull(test, cymk, "Expected CYMK to be NULL");
    
    free(cymk);
}

ctest_return_t testCymkToRgb(ctest_t *test, void *arg) {
    struct Cymk *cymk = malloc(sizeof(struct Cymk));
    cymk->c = 0.0f;
    cymk->y = 0.0f;
    cymk->m = 0.0f;
    cymk->k = 1.0f;
    
    struct Rgb *color = getRawRGBValueFromCymk(cymk);
    
    CTAssertEqual(test, 0, color->r, "Expect R to be equal to %i but got %i", 0, color->r);
    CTAssertEqual(test, 0, color->g, "Expect G to be equal to %i but got %i", 0, color->g);
    CTAssertEqual(test, 0, color->b, "Expect B to be equal to %i but got %i", 0, color->b);

    free(cymk);
    free(color);
}

ctest_return_t testCymkToUintNull(ctest_t *test, void *arg) {
    struct Rgb *colors = getRawRGBValueFromCymk(NULL);
    
    CTAssertNull(test, colors, "Expected RGB to be NULL");
    free(colors);
}

ctcase_t *wrapCymkCreationTest() {
    // Create case
    ctcase_t *cymkCase = ctcase("Cymk test case");
    
    // Create test
    ctest_t *testCymk     = ctest("Creation of a Cymk From RGB", testCymkCreation, NULL);
    ctest_t *testCymkNull = ctest("Creation of a NULL Cymk from a RGB NULL", testCymkNullCreation, NULL);
    ctest_t *testRgbCymk  = ctest("Creation of a RGB from a CYMK", testCymkToRgb, NULL);
    ctest_t *testRgbNull  = ctest("Creation of a NULL RGB from a NULL Cymk", testCymkToUintNull, NULL);

    
    // add test to cases
    ctctestadd(cymkCase, testCymk);
    ctctestadd(cymkCase, testCymkNull);
    ctctestadd(cymkCase, testRgbCymk);
    ctctestadd(cymkCase, testRgbNull);
    
    return cymkCase;
}
