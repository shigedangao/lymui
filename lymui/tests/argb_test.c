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
#include "test_header.h"
#include "errors.h"
#include "helper.h"
#include "rgb.h"
#include "xyz.h"
#include "argb.h"

ctest_return_t testARgbCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.19, argb->r, 0.01, "Expect r to be equal to be equal to 0.19 but got %f", argb->r);
    CTAssertDecimalEqual(test, 0.03, argb->g, 0.01, "Expect g to be equal to be equal to 0.03 but got %f", argb->g);
    CTAssertDecimalEqual(test, 0.37, argb->b, 0.01, "Expect b to be equal to be equal to 0.37 but got %f", argb->b);
    
    free(argb);
    free(xyz);
}

ctest_return_t testARgbEmpty(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.0, argb->r, 0.1, "Expect r to be equal to be equal to 0 but got %f", argb->r);
    CTAssertDecimalEqual(test, 0.0, argb->g, 0.1, "Expect g to be equal to be equal to 0 but got %f", argb->g);
    CTAssertDecimalEqual(test, 0.0, argb->b, 0.1, "Expect b to be equal to be equal to 0 but got %f", argb->b);
    
    free(argb);
    free(xyz);
    free(rgb);
}

ctest_return_t testMaxARgb(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 1.0, argb->r, 0.1, "Expect r to be equal to be equal to 0 but got %f", argb->r);
    CTAssertDecimalEqual(test, 1.0, argb->g, 0.1, "Expect g to be equal to be equal to 0 but got %f", argb->g);
    CTAssertDecimalEqual(test, 1.0, argb->b, 0.1, "Expect b to be equal to be equal to 0 but got %f", argb->b);
    
    free(argb);
    free(xyz);
    free(rgb);
}

ctest_return_t testNullARgb(ctest_t *test, void *arg) {
    Argb *argb = getARgbFromXyz(NULL);
    CTAssertStringEqual(test, argb->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(argb);
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
