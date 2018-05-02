//
//  rgb_test.c
//  lymui
//
//  Created by Marc on 14/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "test_header.h"
#include <stdlib.h>
#include <stdint.h>
#include <cunit.h>
#include "rgb.h"

// For instance the test are done in the main file
// Test Rgb Creation
ctest_return_t testRgbCreationFromArr(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100, 200};
    struct Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    CTAssertEqual(test, 0, rgb->r, "Expect R to be equal to %i but got %i", 0, rgb->r);
    CTAssertEqual(test, 100, rgb->g, "Expect G to be equal to %i but got %i", 100, rgb->g);
    CTAssertEqual(test, 200, rgb->b, "Expect B to be equal to %i but got %i", 200, rgb->b);
    
    free(rgb);
}

// Test fail Rgb Creation
ctest_return_t testFailRgbCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100};
    struct Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    CTAssertNull(test, rgb, "Expect RGB to be NULL");
    free(rgb);
}

ctest_return_t testCreationRgbFromPtrArr(ctest_t *test, void *arg) {
    uint8_t *uc = malloc(sizeof(uint8_t) * 3);
    uc[0] = 100;
    uc[1] = 152;
    uc[2] = 200;
    
    struct Rgb *rgb = makeRGB(uc, 3);
    CTAssertEqual(test, 100, rgb->r, "Expect R to be equal to %i but got %i", 100, rgb->r);
    CTAssertEqual(test, 152, rgb->g, "Expect G to be equal to %i but got %i", 152, rgb->g);
    CTAssertEqual(test, 200, rgb->b, "Expect B to be equal to %i but got %i", 100, rgb->b);
    
    free(rgb);
}

// Wrap Rgb Creation Test
ctcase_t *wrapRgbCreationTest() {
    // Create test case
    ctcase_t *rgbCase = ctcase("Rgb creation test case");
    
    // Create test
    ctest_t   *testRgbCreation = ctest("Creation of a RGB from a null uint8_t array", testRgbCreationFromArr, NULL);
    ctest_t   *testRgbFailure  = ctest("Creation of a NULL RGB from a NULL uint8_t array", testFailRgbCreation, NULL);
    ctest_t   *testRgbFromArr  = ctest("Creation of a RGB from uint8_t array", testCreationRgbFromPtrArr, NULL);
    
    ctctestadd(rgbCase, testRgbCreation);
    ctctestadd(rgbCase, testRgbFailure);
    ctctestadd(rgbCase, testRgbFromArr);
    
    return rgbCase;
}
