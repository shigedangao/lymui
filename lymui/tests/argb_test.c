//
//  argb_test.c
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

ctest_return_t testArgbCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    struct aRgb *argb = getARgbFromXyz(xyz);
    
    // These test are a bit falsy as i didn't find any converter of XYZ -> Adobe RGB so take it with grain of salt
    CTAssertEqual(test, 19.6f, roundDigit(argb->r * 100, 100), "Expect R to be equal to %f but got %f", 19.6f, roundDigit(argb->r * 100, 100));
    CTAssertEqual(test, 3.89f, roundDigit(argb->g * 100, 100), "Expect G to be equal to %f but got %f", 3.89f, roundDigit(argb->g * 100, 100));
    CTAssertEqual(test, 37.25f, roundDigit(argb->b * 100, 100), "Expect B to be equal to %f but got %f", 37.25f, roundDigit(argb->b * 100, 100));
    
    free(argb);
}

ctest_return_t testArgbEmpty(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    struct Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    struct aRgb *argb = getARgbFromXyz(xyz);
    
    CTAssertEqual(test, 0.0f, argb->r, "Expect R to be equal to 0.0 but got %f", argb->r);
    CTAssertEqual(test, 0.0f, argb->g, "Expect G to be equal to 0.0 but got %f", argb->g);
    CTAssertEqual(test, 0.0f, argb->b, "Expect B to be equal to 0.0 but got %f", argb->b);
    
    free(argb);
}

ctest_return_t testMaxArgb(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz   = generateXyzFromRgb(rgb, adobeRgb);
    struct aRgb *argb = getARgbFromXyz(xyz);
    
    // Value are equal to 0.999... so round it to 1.0f
    CTAssertEqual(test, 1.0f, roundf(argb->r), "Expect R to be equal to %f but got %f", 1.0f, argb->r);
    CTAssertEqual(test, 1.0f, roundf(argb->g), "Expect G to be equal to %f but got %f", 1.0f, argb->g);
    CTAssertEqual(test, 1.0f, roundf(argb->b), "Expect B to be equal to %f but got %f", 1.0f, argb->b);
    
    free(argb);
}

ctest_return_t testNullArgb(ctest_t *test, void *arg) {
    struct aRgb *argb = getARgbFromXyz(NULL);
    CTAssertNull(test, argb, "Expect argb to be NULL");
    
    free(argb);
}

ctcase_t *wrapARgbCreationTest() {
    ctcase_t *aRgbCase = ctcase("Adobe RGB test case");
    
    ctest_t *testArgb      = ctest("Creation of an Adobe RGB struct from Rgb struct", testArgbCreation, NULL);
    ctest_t *testArgbNull  = ctest("Creation of an NULL Adobe RGB", testNullArgb, NULL);
    ctest_t *testEmptyArgb = ctest("Creation of an Adobe RGB struct from Rgb struct black color", testArgbEmpty, NULL);
    ctest_t *testArgbMax   = ctest("Creation of an Adobe RGB struct from Rgb struct with with white color", testMaxArgb, NULL);
    
    ctctestadd(aRgbCase, testArgb);
    ctctestadd(aRgbCase, testArgbNull);
    ctctestadd(aRgbCase, testEmptyArgb);
    ctctestadd(aRgbCase, testArgbMax);
    
    return aRgbCase;
}
