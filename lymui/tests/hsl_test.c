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
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 237.0f, hsl->h, "Expect Hue to be equal to 237 but got %f", hsl->h);
    CTAssertEqual(test, 90.0f,  hsl->s, "Expect Saturation to be equal to 90.0 but got %f", hsl->s);
    CTAssertEqual(test, 19.6f,  hsl->l, "Expect Luminance to be equal to 19.61 but got %f", hsl->l);
}

ctest_return_t testHighSaturationHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {100, 150, 255};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 221.0f, hsl->h, "Expect Hue to be equal to 237 but got %f", hsl->h);
    CTAssertEqual(test, 100.0f, hsl->s, "Expect Saturation to be equal to 100 but got %f", hsl->s);
    CTAssertEqual(test, 69.6f,  hsl->l, "Expect Luminance to be equal to 69.6 but got %f", hsl->l);
    
    free(hsl);
}

ctest_return_t testLowSaturationHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[3] = {5, 1, 9};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl *hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 270.0f, hsl->h, "Expect Hue to be equal to 270 but got %f", hsl->h);
    CTAssertEqual(test, 80.0f,  hsl->s, "Expect Saturation to be equal to 80.0 but got %f", hsl->s);
    CTAssertEqual(test, 2.0f,   hsl->l, "Expect Luminance to be equal to 2.0 but got %f", hsl->l);
    
    free(hsl);
}

ctest_return_t testBlackHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[] = {0, 0, 0};
    Rgb * rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl * hsl = getHslFromRgb(rgb);
    
    CTAssertEqual(test, 0.0f, hsl->h, "Expect H to be equal to 0 but got %f", hsl->h);
    CTAssertEqual(test, 0.0f, hsl->s, "Expect S to be equal to 0 but got %f", hsl->s);
    CTAssertEqual(test, 0.0f, hsl->l, "Expect L to be equal to 0 but got %f", hsl->l);
    
    free(hsl);
}

ctest_return_t testWhiteHsl(ctest_t *test, void *arg) {
    uint8_t cvalue[] = {255, 255, 255};
    Rgb * rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    Hsl * hsl = getHslFromRgb(rgb);
        
    CTAssertEqual(test, 0.0f, hsl->h, "Expect H to be equal to 0 but got %f", hsl->h);
    CTAssertEqual(test, 0.0f, hsl->s, "Expect S to be equal to 0 but got %f", hsl->s);
    CTAssertEqual(test, 100.0f, hsl->l, "Expect L to be equal to 100 but got %f", hsl->l);
}

ctest_return_t testRgbGrayCreationFromHsv(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 0;
    hsl->s = 0;
    hsl->l = 59;
    
    Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 150, rgb->r, "Expect r to be equal to 150 but got %ui", rgb->r);
    CTAssertEqual(test, 150, rgb->g, "Expect g to be equal to 150 but got %ui", rgb->g);
    CTAssertEqual(test, 150, rgb->b, "Expect b to be equal to 150 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testNiwaHSLRgb(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 193;
    hsl->s = 67;
    hsl->l = 28;
    
     Rgb *rgb = getRgbValueFromHsl(hsl);

    CTAssertEqual(test, 24, rgb->r, "Expect r to be equal to 24 but got %i", rgb->r);
    CTAssertEqual(test, 98, rgb->g, "Expect g to be equal to 98 but got %i", rgb->g);
    CTAssertEqual(test, 119, rgb->b, "Expect b to be equal to 119 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testComplexHslRgb(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 5;
    hsl->s = 10;
    hsl->l = 98;
    
     Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 250, rgb->r, "Expect r to be equal to 250 but got %i", rgb->r);
    CTAssertEqual(test, 249, rgb->g, "Expect g to be equal to 249 but got %i", rgb->g);
    CTAssertEqual(test, 249, rgb->b, "Expect b to be equal to 249 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testBlackHslRgb(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 0;
    hsl->s = 0;
    hsl->l = 0;
    
    Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 0, rgb->r, "Expect r to be equal to 0 but got %i", rgb->r);
    CTAssertEqual(test, 0, rgb->g, "Expect g to be equal to 0 but got %i", rgb->g);
    CTAssertEqual(test, 0, rgb->b, "Expect b to be equal to 0 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testNegativeRgbValue(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof( Hsl));
    hsl->h = 1;
    hsl->s = 1;
    hsl->l = 1;
    
    Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 3, rgb->r, "Expect r to be equal to 3 but got %i", rgb->r);
    CTAssertEqual(test, 3, rgb->g, "Expect g to be equal to 3 but got %i", rgb->g);
    CTAssertEqual(test, 3, rgb->b, "Expect r to be equal to 3 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testPositiveRgbValue(ctest_t *test, void *arg) {
    Hsl *hsl = malloc(sizeof(Hsl));
    hsl->h = 300;
    hsl->s = 100;
    hsl->l = 56;
    
    Rgb *rgb = getRgbValueFromHsl(hsl);
    
    CTAssertEqual(test, 255, rgb->r, "Expect r to be equal to 255 but got %i", rgb->r);
    CTAssertEqual(test, 31, rgb->g, "Expect g to be equal to 31 but got %i", rgb->g);
    CTAssertEqual(test, 254, rgb->b, "Expect b to be equal to 255 but got %i", rgb->b);

    free(rgb);
}

ctest_return_t testNullRgbFromHsl(ctest_t *test, void *arg) {
    Rgb *rgb = getRgbValueFromHsl(NULL);
    
    CTAssertNull(test, rgb, "Expect RGB to be NULL");
}

ctcase_t *wrapHslCreationTest() {
    ctcase_t *hslCase = ctcase("Hsl test case");
    
    // HSL Creation
    ctest_t *simpleHslCreation  = ctest("Simple HSL creation", testHslCreation, NULL);
    ctest_t *highSatHslCreation = ctest("High saturation HSL creation", testHighSaturationHsl, NULL);
    ctest_t *lowSatHslCreation  = ctest("Low saturation HSL creation", testLowSaturationHsl, NULL);
    ctest_t *blackHslCreation   = ctest("Create Black value HSL", testBlackHsl, NULL);
    ctest_t *whiteHslCreation   = ctest("Create White value HSL", testWhiteHsl, NULL);
    
    // RGB creation
    ctest_t *grayShadeCreation  = ctest("Shade of gray creation RGB", testRgbGrayCreationFromHsv, NULL);
    ctest_t *colorShadeCreation = ctest("Color shade creation RGB", testNiwaHSLRgb, NULL);
    ctest_t *colorCmplCreation  = ctest("Creation of complex RGB", testComplexHslRgb, NULL);
    ctest_t *colorBlackCreation = ctest("Create black RGB color", testBlackHslRgb, NULL);
    ctest_t *colorNegativeRGB   = ctest("Create an RGB based on small value", testNegativeRgbValue, NULL);
    ctest_t *colorPositiveRGB   = ctest("Create an RGB based on big value", testPositiveRgbValue, NULL);
    
    // NULL Value test
    ctest_t *colorNULL = ctest("Create NULL RGB  from NULL HSL", testNullRgbFromHsl, NULL);
    
    // Add the test to the test case
    ctctestadd(hslCase, simpleHslCreation);
    ctctestadd(hslCase, highSatHslCreation);
    ctctestadd(hslCase, lowSatHslCreation);
    ctctestadd(hslCase, grayShadeCreation);
    ctctestadd(hslCase, blackHslCreation);
    ctctestadd(hslCase, whiteHslCreation);
    
    ctctestadd(hslCase, colorShadeCreation);
    ctctestadd(hslCase, colorCmplCreation);
    ctctestadd(hslCase, colorBlackCreation);
    
    ctctestadd(hslCase, colorNegativeRGB);
    ctctestadd(hslCase, colorPositiveRGB);
    
    ctctestadd(hslCase, colorNULL);
    
    return hslCase;
}
