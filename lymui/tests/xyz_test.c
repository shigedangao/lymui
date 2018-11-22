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
#include "errors.h"
#include "rgb.h"
#include "xyz.h"
#include "helper.h"

ctest_return_t testXyzRgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertDecimalEqual(test, 0.0349, xyz->x, 0.01, "Expect X to be equal to %f but got %f", 0.0349, xyz->x);
    CTAssertDecimalEqual(test, 0.0172, xyz->y, 0.01, "Expect Y to be equal to %f but got %f", 0.0172, xyz->y);
    CTAssertDecimalEqual(test, 0.1097, xyz->z, 0.01, "Expect Z to be equal to %f but got %f", 0.1097, xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzAdobeRgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    CTAssertDecimalEqual(test, 0.0376, xyz->x, 0.01, "Expect X to be equal to %f but got %f", 0.0376, xyz->x);
    CTAssertDecimalEqual(test, 0.0173, xyz->y, 0.01, "Expect Y to be equal to %f but got %f", 0.0173, xyz->y);
    CTAssertDecimalEqual(test, 0.1138, xyz->z, 0.01, "Expect Z to be equal to %f but got %f", 0.1138, xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzSrgbDark(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz * xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertEqual(test, 0.0, xyz->x, "Expect X to be equal to 0 but got %f", xyz->x);
    CTAssertEqual(test, 0.0, xyz->y, "Expect Y to be equal to 0 but got %f", xyz->y);
    CTAssertEqual(test, 0.0, xyz->z, "Expect Z to be equal to 0 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzArgbDark(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz * xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    CTAssertEqual(test, 0.0, xyz->x, "Expect X to be equal to 0 but got %f", xyz->x);
    CTAssertEqual(test, 0.0, xyz->y, "Expect Y to be equal to 0 but got %f", xyz->y);
    CTAssertEqual(test, 0.0, xyz->z, "Expect Z to be equal to 0 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzSRgbBright(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz * xyz = generateXyzFromRgb(rgb, srgb);
    
    CTAssertDecimalEqual(test, 0.9505, xyz->x, 0.01, "Expect X to be equal to 0.9502 but got %f", xyz->x);
    CTAssertDecimalEqual(test, 1.0, xyz->y, 0.01, "Expect X to be equal to 0.9997 but got %f", xyz->y);
    CTAssertDecimalEqual(test, 1.0887, xyz->z, 0.01, "Expect X to be equal to 1.0887 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzArgbBright(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz * xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    CTAssertDecimalEqual(test, 0.9502, xyz->x, 0.01, "Expect X to be equal to 0.9502 but got %f", xyz->x);
    CTAssertDecimalEqual(test, 0.9998, xyz->y, 0.01, "Expect .X to be equal to 0.9998 but got %f", xyz->y);
    CTAssertDecimalEqual(test, 1.0887, xyz->z, 0.01, "Expect X to be equal to 1.0887 but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzRgbNull(ctest_t *test, void *arg) {
    Xyz *xyz = generateXyzFromRgb(NULL, srgb);
    CTAssertEqual(test, xyz->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);

    free(xyz);
}

ctest_return_t testXyzToRgb(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz * xyz = generateXyzFromRgb(rgb, srgb);
    Rgb * iamtired = generateRgbFromXyz(xyz, srgb);
    
    CTAssertEqual(test, iamtired->r, 50, "Expect R to be equal to 50 but got %i", iamtired->r);
    CTAssertEqual(test, iamtired->g, 10, "Expect G to be equal to 10 but got %i", iamtired->g);
    CTAssertEqual(test, iamtired->b, 95, "Expect R to be equal to 95 but got %i", iamtired->b);

    free(iamtired);
}

ctest_return_t testXyzToARgb(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 98;
    
    Xyz * xyz = generateXyzFromRgb(rgb, adobeRgb);
    Rgb * iamtired = generateRgbFromXyz(xyz, adobeRgb);
    
    CTAssertEqual(test, iamtired->r, 5, "Expect R to be equal to 50 but got %i", iamtired->r);
    CTAssertEqual(test, iamtired->g, 10, "Expect G to be equal to 10 but got %i", iamtired->g);
    CTAssertEqual(test, iamtired->b, 98, "Expect B to be equal to 95 but got %i", iamtired->b);
    
    free(iamtired);
}

ctest_return_t testRgbXyzNull(ctest_t *test, void *arg) {
    Rgb *rgb = generateRgbFromXyz(NULL, srgb);
    CTAssertEqual(test, rgb->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);

    free(rgb);
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
    
    // xyz to rgb
    ctest_t *testXyzRgbCase  = ctest("Creation of an RGB from an XYZ srgb", testXyzToRgb, NULL);
    ctest_t *testXyzARgbCase = ctest("Creation of an RGB from an XYZ argb", testXyzToARgb, NULL);
    ctest_t *testXyzRgbNull  = ctest("Creation of an RGB with NULL value should return NULL", testRgbXyzNull, NULL);
    
    
    // add cases
    ctctestadd(xyzCase, testRgbCase);
    ctctestadd(xyzCase, testNRgbCase);
    ctctestadd(xyzCase, testAdobeCase);
    ctctestadd(xyzCase, testDarkSrgb);
    ctctestadd(xyzCase, testDarkArgb);
    ctctestadd(xyzCase, testBrightSrgb);
    ctctestadd(xyzCase, testBrightArgb);
    ctctestadd(xyzCase, testXyzRgbCase);
    ctctestadd(xyzCase, testXyzARgbCase);
    ctctestadd(xyzCase, testXyzRgbNull);
    
    return xyzCase;
}

