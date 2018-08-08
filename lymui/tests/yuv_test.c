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
#include "yuv.h"

ctest_return_t testCaseCreationYuv(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Yuv *yuv = getYuvFromRgb(rgb);
    
    CTAssertEqual(test, 0.124f, yuv->y, "Expect Y to be equal to 0.124 but got %f", yuv->y);
    CTAssertEqual(test, 0.122f, yuv->u, "Expect U to be equal to 0.122 but got %f", yuv->u);
    CTAssertEqual(test, 0.063f, yuv->v, "Expect V to be equal to 0.063 but got %f", yuv->v);
    
    free(yuv);
}

ctest_return_t testCaseCreationNullYuv(ctest_t *test, void *arg) {
    Yuv *yuv = getYuvFromRgb(NULL);
    CTAssertNull(test, yuv, "Expect Yuv to be NULL");
}

ctest_return_t testCreationRgb(ctest_t *test, void *arg) {
    Yuv *yuv = malloc(sizeof(Yuv));
    yuv->y = 0.124f;
    yuv->u = 0.122f;
    yuv->v = 0.063f;
    
    Rgb *rgb = getRgbFromYuv(yuv);
    
    CTAssertEqual(test, 50, rgb->r, "Expect R to be equa to 50 but got %i", rgb->r);
    CTAssertEqual(test, 10, rgb->g, "Expect G to be equa to 10 but got %i", rgb->g);
    CTAssertEqual(test, 95, rgb->b, "Expect B to be equa to 95 but got %i", rgb->b);
    
    free(rgb);
}

ctest_return_t testCreationRgbNULL(ctest_t *test, void *arg) {
    Rgb *rgb = getRgbFromYuv(NULL);
    
    CTAssertNull(test, rgb, "Expect RGB to be NULL");
    free(rgb);
}

ctcase_t *wrapYuvCreationTest() {
    ctcase_t *yuvCase = ctcase("Yuv test case");
    
    // Yuv test case
    ctest_t *testYuv = ctest("Creation of a Yuv from RGB", testCaseCreationYuv, NULL);
    ctest_t *testYuvNull = ctest("Creation of a NULL Yuv from NULL RGB", testCaseCreationNullYuv, NULL);
    
    // Rgb test case
    ctest_t *testRGB = ctest("Creation of a RGB from Yuv", testCreationRgb, NULL);
    ctest_t *testRGBNull = ctest("Creation of a NULL Rgb from a NULL Yuv", testCreationRgbNULL, NULL);
    
    // add test case
    ctctestadd(yuvCase, testYuv);
    ctctestadd(yuvCase, testYuvNull);
    ctctestadd(yuvCase, testRGB);
    ctctestadd(yuvCase, testRGBNull);
    
    return yuvCase;
}
