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
ctest_return_t testRgbCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100, 200};
    struct Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    CTAssertEqual(test, 0, rgb->r, "%d is not equal to %d", 0, rgb->r);
    CTAssertEqual(test, 100, rgb->g, "%d is not equal to %d", 100, rgb->g);
    CTAssertEqual(test, 200, rgb->b, "%d is not equal to %d", 200, rgb->b);
    
    free(rgb);
}

// Test fail Rgb Creation
ctest_return_t testFailRgbCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100};
    struct Rgb *rgb = makeRGB(uc, sizeof(uc));
    
    CTAssertNull(test, rgb, "rgb is not NULL");
    free(rgb);
}

ctest_return_t testCreationRgbFromPointerArr(ctest_t *test, void *arg) {
    uint8_t *uc = malloc(sizeof(uint8_t) * 3);
    uc[0] = 100;
    uc[1] = 152;
    uc[2] = 200;
    
    struct Rgb *rgb = makeRGB(uc, 3);
    CTAssertEqual(test, 100, rgb->r, "%d is not equal to %d", 100, rgb->r);
    CTAssertEqual(test, 152, rgb->g, "%d is not equal to %d", 152, rgb->g);
    CTAssertEqual(test, 200, rgb->b, "%d is not equal to %d", 100, rgb->b);
    
    free(rgb);
    free(uc);
}

// Wrap Rgb Creation Test
ctcase_t *wrapRgbCreationTest() {
    // Create test case
    ctcase_t *rgbCase = ctcase("Rgb creation test case");
    
    // Create test
    ctest_t   *rgbCreation = ctest("Create RGB from UINT_8T Array", testRgbCreation, NULL);
    ctest_t   *rgbFailure  = ctest("Create RGB from UINT_8T Array", testFailRgbCreation, NULL);
    ctest_t   *rgbFromArr  = ctest("Create RGB from UINT_8T Array", testCreationRgbFromPointerArr, NULL);
    
    ctctestadd(rgbCase, rgbCreation);
    ctctestadd(rgbCase, rgbFailure);
    ctctestadd(rgbCase, rgbFromArr);
    
    return rgbCase;
}
