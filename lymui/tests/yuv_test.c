//
//  yuv_test.c
//  lymui
//
//  Created by Marc on 12/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "errors.h"
#include "yuv.h"

ctest_return_t testCaseCreationYuv(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Yuv *yuv = getYuvFromRgb(rgb);

    CTAssertDecimalEqual(test, 0.124, yuv->y, 0.001, "Expect Y to be equal to 0.124 but got %f", yuv->y);
    CTAssertDecimalEqual(test, 0.122, yuv->u, 0.001, "Expect U to be equal to 0.122 but got %f", yuv->u);
    CTAssertDecimalEqual(test, 0.063, yuv->v, 0.001, "Expect V to be equal to 0.124 but got %f", yuv->v);

    free(yuv);
}

ctest_return_t testWhiteRgbToYuv(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Yuv *yuv = getYuvFromRgb(rgb);
    
    CTAssertDecimalEqual(test, 1.0, yuv->y, 0.1, "Expect Y to be equal to 1.0 but got %f", yuv->y);
    CTAssertDecimalEqual(test, 0.0, yuv->u, 0.1, "Expect U to be equal to 0.0 but got %f", yuv->u);
    CTAssertDecimalEqual(test, 0.0, yuv->v, 0.1, "Expect V to be equal to 0.0 but got %f", yuv->v);
}

ctest_return_t testCaseCreationNullYuv(ctest_t *test, void *arg) {
    Yuv *yuv = getYuvFromRgb(NULL);
    CTAssertStringEqual(test, yuv->error, NULL_INPUT_PARAM ,"Expect Yuv to be equal to %s", NULL_INPUT_PARAM);
    
    free(yuv);
}

ctest_return_t testCreationRgb(ctest_t *test, void *arg) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 0.124;
    yuv->u = 0.122;
    yuv->v = 0.063;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    
    CTAssertEqual(test, 50, rgb->r, "Expect R to be equa to 50 but got %i", rgb->r);
    CTAssertEqual(test, 10, rgb->g, "Expect G to be equa to 10 but got %i", rgb->g);
    CTAssertEqual(test, 95, rgb->b, "Expect B to be equa to 95 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testWhiteYuvToRgb(ctest_t *test, void *arg) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 1.0;
    yuv->u = 0.0;
    yuv->v = 0.0;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    
    CTAssertEqual(test, 255, rgb->r, "Expect R to be equal to 255 but got %i", rgb->r);
    CTAssertEqual(test, 255, rgb->g, "Expect G to be equal to 255 but got %i", rgb->g);
    CTAssertEqual(test, 255, rgb->b, "Expect B to be equal to 255 but got %i", rgb->b);
}

ctest_return_t testCreationRgbNULL(ctest_t *test, void *arg) {
    Rgb *rgb = getRgbFromYuv(NULL);
    
    CTAssertStringEqual(test, rgb->error, NULL_INPUT_PARAM ,"Expect RGB to be equal to %s", NULL_INPUT_PARAM);
    
    free(rgb);
}

ctcase_t *wrapYuvCreationTest() {
    ctcase_t *yuvCase = ctcase("Yuv test case");
    
    // Yuv test case
    ctest_t *testYuv = ctest("Creation of a Yuv from RGB", testCaseCreationYuv, NULL);
    ctest_t *testWhiteYuv = ctest("Creation of a white Yuv from RGB", testWhiteRgbToYuv, NULL);
    ctest_t *testYuvNull = ctest("Creation of a NULL Yuv from NULL RGB", testCaseCreationNullYuv, NULL);
    
    // Rgb test case
    ctest_t *testRGB = ctest("Creation of a RGB from Yuv", testCreationRgb, NULL);
    ctest_t *testWhiteRGB = ctest("Creation of a white RGB from Yuv", testWhiteYuvToRgb, NULL);
    ctest_t *testRGBNull = ctest("Creation of a NULL Rgb from a NULL Yuv", testCreationRgbNULL, NULL);
    
    // add test case
    ctctestadd(yuvCase, testYuv);
    ctctestadd(yuvCase, testYuvNull);
    ctctestadd(yuvCase, testWhiteYuv);
    ctctestadd(yuvCase, testRGB);
    ctctestadd(yuvCase, testWhiteRGB);
    ctctestadd(yuvCase, testRGBNull);
    
    return yuvCase;
}
