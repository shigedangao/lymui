//
//  hsv_test.c
//  lymui
//
//  Created by Marc on 05/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "errors.h"
#include "rgb.h"
#include "hsv.h"

ctest_return_t testNullHsvCreation(ctest_t *test, void *arg) {
    Hsv *hsv = getHsvFromRgb(NULL);
    CTAssertEqual(test, hsv->error, NULL_INPUT_PARAM, "Expect error to return a string %s", NULL_INPUT_PARAM);
    
    free(hsv);
}

ctest_return_t testHsvCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof( Rgb));
    rgb->r = 50;
    rgb->g = 100;
    rgb->b = 100;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    CTAssertDecimalEqual(test, 180.0, hsv->h, 0.1, "Expect H to be equal to 180 but got %d", hsv->h);
    CTAssertDecimalEqual(test, 50.0, hsv->s, 0.1, "Expect S to be equal to 50 but got %d", hsv->s);
    CTAssertDecimalEqual(test, 39.2, hsv->v, 0.1, "Expect V to be equal to 39.2 but got %d", hsv->v);
    
    free(hsv);
}

ctest_return_t testBlackHsvCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    CTAssertDecimalEqual(test, 0.0, hsv->h, 0.1, "Expect H to be equal to 0 but got %d", hsv->h);
    CTAssertDecimalEqual(test, 0.0, hsv->s, 0.1, "Expect S to be equal to 0 but got %d", hsv->s);
    CTAssertDecimalEqual(test, 0.0, hsv->v, 0.1, "Expect V to be equal to 0 but got %d", hsv->v);
    
    free(hsv);
}

ctest_return_t testComplexHsvCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 156;
    rgb->g = 238;
    rgb->b = 1;
    
    Hsv *hsv = getHsvFromRgb(rgb);
    CTAssertDecimalEqual(test, 81.0, hsv->h, 0.1, "Expect H to be equal to 81.0 but got %d", hsv->h);
    CTAssertDecimalEqual(test, 99.6, hsv->s, 0.1, "Expect S to be equal to 99.6 but got %d", hsv->s);
    CTAssertDecimalEqual(test, 93.3, hsv->v, 0.1, "Expect V to be equal to 93.3 but got %d", hsv->v);
    
    free(hsv);
}

ctest_return_t testCaseRgb_0(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 0.0f;
    hsv->s = 100.0f;
    hsv->v = 100.0f;
    
     Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 255, rgb->r, "Expect r to be equal to 255 but got %ui", rgb->r);
    CTAssertEqual(test, 0, rgb->g, "Expect g to be equal to 0 but got %ui", rgb->g);
    CTAssertEqual(test, 0, rgb->b, "Expect b to be equal to 0 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_1(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 81.0f;
    hsv->s = 100.0f;
    hsv->v = 93.3f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 155, rgb->r, "Expect r to be equal to 156 but got %ui", rgb->r);
    CTAssertEqual(test, 238, rgb->g, "Expect g to be equal to 238 but got %ui", rgb->g);
    CTAssertEqual(test, 0, rgb->b, "Expect b to be equal to 1 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_2(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 160.0f;
    hsv->s = 40.0f;
    hsv->v = 90.0f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 138, rgb->r, "Expect r to be equal to 168 but got %ui", rgb->r);
    CTAssertEqual(test, 230, rgb->g, "Expect g to be equal to 230 but got %ui", rgb->g);
    CTAssertEqual(test, 199, rgb->b, "Expect b to be equal to 138 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_3(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 180.0f;
    hsv->s = 20.0f;
    hsv->v = 70.0f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 143, rgb->r, "Expect r to be equal to 143 but got %ui", rgb->r);
    CTAssertEqual(test, 179, rgb->g, "Expect g to be equal to 179 but got %ui", rgb->g);
    CTAssertEqual(test, 179, rgb->b, "Expect b to be equal to 179 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_4(ctest_t *test, void *arg) {
     Hsv *hsv = malloc(sizeof( Hsv));
    hsv->h = 260.0f;
    hsv->s = 90.0f;
    hsv->v = 90.0f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 92, rgb->r, "Expect r to be equal to 92 but got %ui", rgb->r);
    CTAssertEqual(test, 23, rgb->g, "Expect g to be equal to 23 but got %ui", rgb->g);
    CTAssertEqual(test, 230, rgb->b, "Expect b to be equal to 230 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseNo_Sat(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 260.0f;
    hsv->s = 0.0f;
    hsv->v = 90.0f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 230, rgb->r, "Expect r to be equal to 230 but got %ui", rgb->r);
    CTAssertEqual(test, 230, rgb->g, "Expect g to be equal to 230 but got %ui", rgb->g);
    CTAssertEqual(test, 230, rgb->b, "Expect b to be equal to 230 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_Default(ctest_t *test, void *arg) {
    Hsv *hsv = malloc(sizeof(Hsv));
    hsv->h = 360.0f;
    hsv->s = 90.0f;
    hsv->v = 25.0f;
    
    Rgb *rgb = getRgbValueFromHsv(hsv);
    CTAssertEqual(test, 64, rgb->r, "Expect r to be equal to 92 but got %ui", rgb->r);
    CTAssertEqual(test, 6,  rgb->g, "Expect g to be equal to 6 but got %ui", rgb->g);
    CTAssertEqual(test, 6,  rgb->b, "Expect b to be equal to 7 but got %ui", rgb->b);
    
    free(rgb);
}

ctest_return_t testCaseRgb_NULL(ctest_t *test, void *arg) {
    Rgb *rgb = getRgbValueFromHsv(NULL);
    CTAssertEqual(test, rgb->error, NULL_INPUT_PARAM, "Expect error to return a string %s", NULL_INPUT_PARAM);
    
    free(rgb);
}

ctcase_t *wrapHsvCreationTest() {
    ctcase_t *hsvCase = ctcase("Hsv test case");
    
    // creation of hsv
    ctest_t *hsvNull = ctest("Hsv null from NULL Rgb", testNullHsvCreation, NULL);
    ctest_t *hsvCreation = ctest("Hsv creation test from RGB", testHsvCreation, NULL);
    ctest_t *hsvEmptyCreation = ctest("Hsv creation test from black RGB", testBlackHsvCreation, NULL);
    ctest_t *hsvComplexCreation = ctest("Hsv creation using complex RGB", testComplexHsvCreation, NULL);
    
    // creation of rgb
    ctest_t *rgbCreation0 = ctest("Creation of RGB from HSV 0", testCaseRgb_0, NULL);
    ctest_t *rgbCreation1 = ctest("Creation of RGB from HSV 1", testCaseRgb_1, NULL);
    ctest_t *rgbCreation2 = ctest("Creation of RGB from HSV 2", testCaseRgb_2, NULL);
    ctest_t *rgbCreation3 = ctest("Creation of RGB from HSV 3", testCaseRgb_3, NULL);
    ctest_t *rgbCreation4 = ctest("Creation of RGB from HSV 4", testCaseRgb_4, NULL);
    ctest_t *rgbCreationDefault = ctest("Creation of RGB from HSV Default", testCaseRgb_Default, NULL);
    ctest_t *rgbCreationNull    = ctest("Creation of a NULL RGB", testCaseRgb_NULL, NULL);
    ctest_t *rgbCreationSat     = ctest("Creation of RGB from Sat value at 0", testCaseNo_Sat, NULL);
    
    // add test related to HSV creation from RGB
    ctctestadd(hsvCase, hsvNull);
    ctctestadd(hsvCase, hsvCreation);
    ctctestadd(hsvCase, hsvEmptyCreation);
    ctctestadd(hsvCase, hsvComplexCreation);
    
    // add test related to RGB creation from HSV
    ctctestadd(hsvCase, rgbCreation0);
    ctctestadd(hsvCase, rgbCreation1);
    ctctestadd(hsvCase, rgbCreation2);
    ctctestadd(hsvCase, rgbCreation3);
    ctctestadd(hsvCase, rgbCreation4);
    
    // default test
    ctctestadd(hsvCase, rgbCreationDefault);
    ctctestadd(hsvCase, rgbCreationNull);
    ctctestadd(hsvCase, rgbCreationSat);
    
    return hsvCase;
}

