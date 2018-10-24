//
//  ARgb_test.c
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include <math.h>
#include "helper.h"
#include "rgb.h"
#include "xyz.h"
#include "argb.h"

ctest_return_t testARgbCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    ARgb *ARgb = getARgbFromXyz(xyz);
    
    // These test are a bit falsy as i didn't find any converter of XYZ -> Adobe RGB so take it with grain of salt
    CTAssertEqual(test, 19.6f, roundDigit(ARgb->r * 100, 100), "Expect R to be equal to %f but got %f", 19.6f, roundDigit(ARgb->r * 100, 100));
    CTAssertEqual(test, 3.89f, roundDigit(ARgb->g * 100, 100), "Expect G to be equal to %f but got %f", 3.89f, roundDigit(ARgb->g * 100, 100));
    CTAssertEqual(test, 37.25f, roundDigit(ARgb->b * 100, 100), "Expect B to be equal to %f but got %f", 37.25f, roundDigit(ARgb->b * 100, 100));
    
    free(ARgb);
}

ctest_return_t testARgbEmpty(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    ARgb *ARgb = getARgbFromXyz(xyz);
    
    CTAssertEqual(test, 0.0f, ARgb->r, "Expect R to be equal to 0.0 but got %f", ARgb->r);
    CTAssertEqual(test, 0.0f, ARgb->g, "Expect G to be equal to 0.0 but got %f", ARgb->g);
    CTAssertEqual(test, 0.0f, ARgb->b, "Expect B to be equal to 0.0 but got %f", ARgb->b);
    
    free(ARgb);
}

ctest_return_t testMaxARgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    ARgb *ARgb = getARgbFromXyz(xyz);
    
    // Value are equal to 0.999... so round it to 1.0f
    CTAssertEqual(test, 1.0f, roundf(ARgb->r), "Expect R to be equal to %f but got %f", 1.0f, ARgb->r);
    CTAssertEqual(test, 1.0f, roundf(ARgb->g), "Expect G to be equal to %f but got %f", 1.0f, ARgb->g);
    CTAssertEqual(test, 1.0f, roundf(ARgb->b), "Expect B to be equal to %f but got %f", 1.0f, ARgb->b);
    
    free(ARgb);
}

ctest_return_t testNullARgb(ctest_t *test, void *arg) {
    ARgb *ARgb = getARgbFromXyz(NULL);
    CTAssertNull(test, ARgb, "Expect ARgb to be NULL");
    
    free(ARgb);
}

ctcase_t *wrapARgbCreationTest() {
    ctcase_t *ARgbCase = ctcase("Adobe RGB test case");
    
    ctest_t *testARgb      = ctest("Creation of an Adobe RGB from Rgb struct", testARgbCreation, NULL);
    ctest_t *testARgbNull  = ctest("Creation of an NULL Adobe RGB", testNullARgb, NULL);
    ctest_t *testEmptyARgb = ctest("Creation of an Adobe RGB from Rgb black color", testARgbEmpty, NULL);
    ctest_t *testARgbMax   = ctest("Creation of an Adobe RGB from Rgb with with white color", testMaxARgb, NULL);
    
    ctctestadd(ARgbCase, testARgb);
    ctctestadd(ARgbCase, testARgbNull);
    ctctestadd(ARgbCase, testEmptyARgb);
    ctctestadd(ARgbCase, testARgbMax);
    
    return ARgbCase;
}
