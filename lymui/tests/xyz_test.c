//
//  xyz_test.c
//  lymui
//
//  Created by Marc on 13/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "rgb.h"
#include "xyz.h"
#include "helper.h"

ctest_return_t testXyzRgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertEqual(test, 3.49f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to %f but got %f", 3.49f, roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.72f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to %f but got %f", 1.72f, roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 10.97f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to %f but got %f", 10.97f, roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t testXyzAdobeRgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    // Though this test are kinda falsy as i didn't find any XYZ converter with the adobe RGB format online... so take it with grain of salt
    CTAssertEqual(test, 3.76f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to %f but got %f", 3.76f, roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.73f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to %f but got %f", 1.73f, roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 11.38f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to %f but got %f", 11.38f, roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t testXyzSrgbDark(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz * xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertEqual(test, 0.0f, xyz->x, "Expect X to be equal to 0 but got %f", xyz->x);
    CTAssertEqual(test, 0.0f, xyz->y, "Expect Y to be equal to 0 but got %f", xyz->y);
    CTAssertEqual(test, 0.0f, xyz->z, "Expect Z to be equal to 0 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzArgbDark(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz * xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    CTAssertEqual(test, 0.0f, xyz->x, "Expect X to be equal to 0 but got %f", xyz->x);
    CTAssertEqual(test, 0.0f, xyz->y, "Expect Y to be equal to 0 but got %f", xyz->y);
    CTAssertEqual(test, 0.0f, xyz->z, "Expect Z to be equal to 0 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzSRgbBright(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz * xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertDecimalEqual(test, 0.9502f, xyz->x, 0.01f, "Expect X to be equal to 0.9502 but got %f", xyz->x);
    CTAssertDecimalEqual(test, 0.9997, xyz->y, 0.01f, "Expect X to be equal to 0.9997 but got %f", xyz->y);
    CTAssertDecimalEqual(test, 1.0f, xyz->z, 0.01f, "Expect X to be equal to 1.0 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzArgbBright(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz * xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    CTAssertDecimalEqual(test, 0.9502f, xyz->x, 0.01f, "Expect X to be equal to 0.9502 but got %f", xyz->x);
    CTAssertDecimalEqual(test, 0.9998, xyz->y, 0.01f, "Expect X to be equal to 0.9998 but got %f", xyz->y);
    CTAssertDecimalEqual(test, 1.0887f, xyz->z, 0.01f, "Expect X to be equal to 1.0887 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzRgbNull(ctest_t *test, void *arg) {
    Xyz *xyz = generateXyzFromRgb(NULL, srgb);
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}

ctcase_t *wrapXyzCreationTest() {
    ctcase_t *xyzCase = ctcase("Xyz test case");
    
    // xyz rgb case
    ctest_t *testRgbCase    = ctest("Creation of an Xyz with RGB case", testXyzRgb, NULL);
    ctest_t *testAdobeCase  = ctest("Creation of an Xyz with Adobe value", testXyzRgbNull, NULL);
    ctest_t *testNRgbCase   = ctest("Creation of an NULL Xyz value with RGB case", testXyzAdobeRgb, NULL);
    ctest_t *testDarkSrgb   = ctest("Creation of a dark Xyz value with RGB case", testXyzSrgbDark, NULL);
    ctest_t *testDarkArgb   = ctest("Creation of a dark Xyz value with ARGB case", testXyzArgbDark, NULL);
    ctest_t *testBrightSrgb = ctest("Creation of a bright Xyz value with SRGB case", testXyzSRgbBright, NULL);
    ctest_t *testBrightArgb = ctest("Creation of a bright Xyz value with ARGB case", testXyzArgbBright, NULL);
    
    // add cases
    ctctestadd(xyzCase, testRgbCase);
    ctctestadd(xyzCase, testNRgbCase);
    ctctestadd(xyzCase, testAdobeCase);
    ctctestadd(xyzCase, testDarkSrgb);
    ctctestadd(xyzCase, testDarkArgb);
    ctctestadd(xyzCase, testBrightSrgb);
    ctctestadd(xyzCase, testBrightArgb);
    
    return xyzCase;
}

