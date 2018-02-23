//
//  hsl_test.c
//  lymui
//
//  Created by Marc on 22/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "hsl.h"

ctest_return_t testHslCreation(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {5, 10, 95};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    struct Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 237.0f, hsl->h, "Expect Hue to be equal to 237 but got %f", hsl->h);
    CTAssertEqual(test, 90.0f,  hsl->s, "Expect Saturation to be equal to 90.0 but got %f", hsl->s);
    CTAssertEqual(test, 19.6f,  hsl->l, "Expect Luminance to be equal to 19.61 but got %f", hsl->l);
}

ctest_return_t testHighSaturationHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {100, 150, 255};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    struct Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 221.0f, hsl->h, "Expect Hue to be equal to 237 but got %f", hsl->h);
    CTAssertEqual(test, 100.0f, hsl->s, "Expect Saturation to be equal to 100 but got %f", hsl->s);
    CTAssertEqual(test, 69.6f,  hsl->l, "Expect Luminance to be equal to 69.6 but got %f", hsl->l);
}

ctest_return_t testLowSaturationHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {5, 1, 9};
    struct Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    struct Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 270.0f, hsl->h, "Expect Hue to be equal to 270 but got %f", hsl->h);
    CTAssertEqual(test, 80.0f,  hsl->s, "Expect Saturation to be equal to 80.0 but got %f", hsl->s);
    CTAssertEqual(test, 2.0f,   hsl->l, "Expect Luminance to be equal to 2.0 but got %f", hsl->l);
}

ctest_return_t testRgbGrayCreationFromHsv(ctest_t *test, void *arg) {
    struct Hsl *hsl = malloc(sizeof(struct Hsl));
    hsl->h = 0;
    hsl->s = 0;
    hsl->l = 59;
    
    struct Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 150, rgb->r, "Expect r to be equal to 150 but got %ui", rgb->r);
    CTAssertEqual(test, 150, rgb->g, "Expect g to be equal to 150 but got %ui", rgb->g);
    CTAssertEqual(test, 150, rgb->b, "Expect b to be equal to 150 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testNiwaHSLRgb(ctest_t *test, void *arg) {
    struct Hsl *hsl = malloc(sizeof(struct Hsl));
    hsl->h = 193;
    hsl->s = 67;
    hsl->l = 28;
    
    struct Rgb *rgb = getRgbValueFromHsl(hsl);

    CTAssertEqual(test, 24, rgb->r, "Expect r to be equal to 24 but got %i", rgb->r);
    CTAssertEqual(test, 98, rgb->g, "Expect g to be equal to 98 but got %i", rgb->g);
    CTAssertEqual(test, 119, rgb->b, "Expect b to be equal to 119 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testComplexHslRgb(ctest_t *test, void *arg) {
    struct Hsl *hsl = malloc(sizeof(struct Hsl));
    hsl->h = 5;
    hsl->s = 10;
    hsl->l = 98;
    
    struct Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 250, rgb->r, "Expect r to be equal to 250 but got %i", rgb->r);
    CTAssertEqual(test, 249, rgb->g, "Expect g to be equal to 249 but got %i", rgb->g);
    CTAssertEqual(test, 249, rgb->b, "Expect b to be equal to 249 but got %i", rgb->b);
    
    free(rgb);
}

ctcase_t *wrapHslCreationTest() {
    ctcase_t *hslCase = ctcase("Hsl test case");
    
    // Create test
    ctest_t *simpleHslCreation  = ctest("Simple HSL creation", testHslCreation, NULL);
    ctest_t *highSatHslCreation = ctest("High saturation HSL creation", testHighSaturationHsl, NULL);
    ctest_t *lowSatHslCreation  = ctest("Low saturation HSL creation", testLowSaturationHsl, NULL);
    
    ctest_t *grayShadeCreation  = ctest("Shade of gray creation RGB", testRgbGrayCreationFromHsv, NULL);
    ctest_t *colorShadeCreation = ctest("Color shade creation RGB", testNiwaHSLRgb, NULL);
    ctest_t *colorCmplCreation  = ctest("Creation of complex RGB", testComplexHslRgb, NULL);

    // Add the test to the test case
    ctctestadd(hslCase, simpleHslCreation);
    ctctestadd(hslCase, highSatHslCreation);
    ctctestadd(hslCase, lowSatHslCreation);
    ctctestadd(hslCase, grayShadeCreation);
    ctctestadd(hslCase, colorShadeCreation);
    ctctestadd(hslCase, colorCmplCreation);
    
    return hslCase;
}
