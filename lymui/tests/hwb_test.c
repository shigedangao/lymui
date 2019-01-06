//
//  hwb_test.c
//  lymui
//
//  Created by Marc Intha on 26/12/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <cunit.h>
#include "test_header.h"
#include "hwb.h"
#include "errors.h"

ctest_return_t testRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 17;
    rgb->g = 12;
    rgb->b = 93;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 244.0f, 0.01f, "Expect H to be equal to %f but got %f", 244.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 4.7f, 0.01f, "Expect W to be equal to %f but got %f", 4.7f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 63.52f, 0.01f, "Expect B to be equal to %f but got %f", 63.5f, hwb->b);
    
    free(hwb);
    free(rgb);
}

ctest_return_t testWhiteRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 0.0f, 0.01f, "Expect H to be equal to %f but got %f", 0.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 100.0f, 0.01f, "Expect W to be equal to %f but got %f", 100.0f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 0.0f, 0.01f, "Expect B to be equal to %f but got %f", 0.0f, hwb->b);

    free(hwb);
    free(rgb);
}

ctest_return_t testBlackRgbToHwb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hwb *hwb = getHwbFromRgb(rgb);
    
    CTAssertDecimalEqual(test, hwb->h, 0.0f, 0.01f, "Expect H to be equal to %f but got %f", 0.0f, hwb->h);
    CTAssertDecimalEqual(test, hwb->w, 0.0f, 0.01f, "Expect W to be equal to %f but got %f", 0.0f, hwb->w);
    CTAssertDecimalEqual(test, hwb->b, 100.0f, 0.01f, "Expect B to be equal to %f but got %f", 100.0f, hwb->b);
    
    free(hwb);
    free(rgb);
}

ctest_return_t testHwbToRgb(ctest_t *test, void *arg) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 244.0f;
    hwb->w = 4.705f;
    hwb->b = 63.52f;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    CTAssertEqual(test, rgb->r, 17, "Expect R to be equal to %i but got %i", 17, rgb->r);
    CTAssertEqual(test, rgb->g, 12, "Expect G to be equal to %i but got %i", 12, rgb->g);
    CTAssertEqual(test, rgb->b, 93, "Expect B to be equal to %i but got %i", 93, rgb->b);

    free(rgb);
}

ctest_return_t testWhiteHwbToRgb(ctest_t *test, void *arg) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 0.0f;
    hwb->w = 100.0f;
    hwb->b = 0.0f;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    CTAssertEqual(test, rgb->r, 255, "Expect R to be equal to %i but got %i", 255, rgb->r);
    CTAssertEqual(test, rgb->g, 255, "Expect G to be equal to %i but got %i", 255, rgb->g);
    CTAssertEqual(test, rgb->b, 255, "Expect B to be equal to %i but got %i", 255, rgb->b);
    
    free(rgb);
}

ctest_return_t testBlackHwbToRgb(ctest_t *test, void *arg) {
    Hwb *hwb = malloc(sizeof(Hwb));
    hwb->h = 0.0f;
    hwb->w = 0.0f;
    hwb->b = 100.0f;
    
    Rgb *rgb = getRgbFromHwb(hwb);
    
    CTAssertEqual(test, rgb->r, 0, "Expect R to be equal to %i but got %i", 0, rgb->r);
    CTAssertEqual(test, rgb->g, 0, "Expect G to be equal to %i but got %i", 0, rgb->g);
    CTAssertEqual(test, rgb->b, 0, "Expect B to be equal to %i but got %i", 0, rgb->b);
    
    free(rgb);
}

ctest_return_t testNullRgbFromHwb(ctest_t *test, void *arg) {
    Rgb *rgb = getRgbFromHwb(NULL);
    
    CTAssertStringEqual(test, rgb->error, NULL_INPUT_PARAM, "Expect Error to be equal to %s", NULL_INPUT_PARAM);
    free(rgb);
}

ctest_return_t testNullHwbFromRgb(ctest_t *test, void *arg) {
    Hwb *hwb = getHwbFromRgb(NULL);
    
    CTAssertStringEqual(test, hwb->error, NULL_INPUT_PARAM, "Expect Error to be equal to %s", NULL_INPUT_PARAM);
    free(hwb);
}

ctcase_t *wrapHwbCreationTest() {
    ctcase_t *hwbCase = ctcase("Hwb creation test");
    
    // rgb to hwb
    ctest_t *testHwbCreation = ctest("Creation of hwb", testRgbToHwb, NULL);
    ctest_t *testHwbWhiteCreation = ctest("Creation of a white hwb", testWhiteRgbToHwb, NULL);
    ctest_t *testHwbBlackCreation = ctest("Creation of a black hwb", testBlackRgbToHwb, NULL);
    
    // hwb to rgb
    ctest_t *testRgbCreation = ctest("Creation of Rgb", testHwbToRgb, NULL);
    ctest_t *testWhiteRgbCreation = ctest("Creation of white Rgb", testWhiteHwbToRgb, NULL);
    ctest_t *testBlackRgbCreation = ctest("Creation of a black Rgb", testBlackHwbToRgb, NULL);
    
    // Null cases
    ctest_t *testNullHwb = ctest("Creation of an error if hwb is null", testNullRgbFromHwb, NULL);
    ctest_t *testNullRgb = ctest("Creation of an error if rgb is null", testNullHwbFromRgb, NULL);

    
    ctctestadd(hwbCase, testHwbCreation);
    ctctestadd(hwbCase, testHwbWhiteCreation);
    ctctestadd(hwbCase, testHwbBlackCreation);
    ctctestadd(hwbCase, testRgbCreation);
    ctctestadd(hwbCase, testWhiteRgbCreation);
    ctctestadd(hwbCase, testBlackRgbCreation);
    ctctestadd(hwbCase, testNullHwb);
    ctctestadd(hwbCase, testNullRgb);
    
    return hwbCase;
}
