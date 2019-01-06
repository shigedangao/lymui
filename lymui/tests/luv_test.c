//
//  luv_test.c
//  lymui
//
//  Created by Marc on 10/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "test_header.h"
#include "errors.h"
#include "xyz.h"
#include "luv.h"
#include "helper.h"

ctest_return_t testLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 9.603, luv->l, 0.001, "Expect L to be equal to %f but got %f", 9.603, luv->l);
    CTAssertDecimalEqual(test, -2.851, luv->u, 0.001, "Expect u to be equal to %f but got %f", -2.851, luv->u);
    CTAssertDecimalEqual(test, -34.829, luv->v, 0.001, "Expect V to be equal to %f but got %f", -34.829, luv->v);

    free(luv);
    free(rgb);
    free(xyz);
}

ctest_return_t testSuperiorYLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 200;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 96.417, luv->l, 0.001, "Expect L to be equal to %f but got %f", 96.417, luv->l);
    CTAssertDecimalEqual(test, -27.734, luv->u, 0.001, "Expect U to be equal to %f but got %f", -27.734, luv->u);
    CTAssertDecimalEqual(test, -5.983, luv->v, 0.001, "Expect V to be equal to %f but got %f", -5.983, luv->v);
    
    free(luv);
    free(rgb);
    free(xyz);
}

ctest_return_t testWhiteLuvFromXyz(ctest_t *test, void *arg) {
    Rgb * rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 100.0, luv->l, 0.01, "Expect L to be equal to %f but got %f", 100.0, luv->l);
    CTAssertDecimalEqual(test, 0.0, luv->u, 0.01, "Expect U to be equal to %f but got %f", 0.0, luv->u);
    CTAssertDecimalEqual(test, 0.0, luv->v, 0.01, "Expect V to be equal to %f but got %f", 0.0, luv->v);

    free(luv);
    free(rgb);
    free(xyz);
}

ctest_return_t testInferiorYLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 1;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.487, luv->l, 0.001, "Expect L to be equal to %f but got %f", 0.487, luv->l);
    CTAssertDecimalEqual(test, 0.808, luv->u, 0.001, "Expect U to be equal to %f but got %f", 0.808, luv->u);
    CTAssertDecimalEqual(test, 0.442, luv->v, 0.001, "Expect V to be equal to %f but got %f", 0.442, luv->v);

    free(luv);
    free(rgb);
    free(xyz);
}

ctest_return_t testNullLuv(ctest_t *test, void *arg) {
    Luv *luv = getLuvFromXyz(NULL);
    CTAssertStringEqual(test, luv->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(luv);
}

ctest_return_t testXyzFromLuv(ctest_t *test, void *arg) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 5.0;
    luv->u = 1.0;
    luv->v = 0.0;
    
    Xyz *xyz = getXyzFromLuv(luv);
    
    CTAssertDecimalEqual(test, 0.00567, xyz->x, 0.0001, "Expect X to be equal to %f but got %f", 0.00567, xyz->x);
    CTAssertDecimalEqual(test, 0.00554, xyz->y, 0.0001, "Expect Y to be equal to %f but got %f", 0.00554, xyz->y);
    CTAssertDecimalEqual(test, 0.00589, xyz->z, 0.0001, "Expect Z to be equal to %f but got %f", 0.00589, xyz->z);
    
    free(xyz);
}

ctest_return_t testHighXyzFromLuv(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);

    // get back the xyz
    Xyz *nXyz = getXyzFromLuv(luv);
    
    CTAssertDecimalEqual(test, 0.950, nXyz->x, 0.001, "Expect X to be equal to %f but got %f", 0.950, nXyz->x);
    CTAssertDecimalEqual(test, 0.9998, nXyz->y, 0.001, "Expect Y to be equal to %f but got %f", 0.9998, nXyz->y);
    CTAssertDecimalEqual(test, 1.0890, nXyz->z, 0.001, "Expect Z to be equal to %f but got %f", 1.0890, nXyz->z);

    free(nXyz);
    free(rgb);
    free(xyz);
}

ctest_return_t testNullXyz(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLuv(NULL);
    CTAssertStringEqual(test, xyz->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);

    
    free(xyz);
}

ctcase_t * wrapLuvCreationTest() {
    ctcase_t *luvCase = ctcase("Luv creation test");
    
    // test case Xyz -> Luv
    ctest_t *testLuv      = ctest("Creation of a Luv from Xyz", testLuvFromXyz, NULL);
    ctest_t *testSupLuv   = ctest("Creation of an Superior Y Luv from Xyz", testSuperiorYLuvFromXyz, NULL);
    ctest_t *testInfLuv   = ctest("Creation of an Inferior Y Luv from Xyz", testInferiorYLuvFromXyz, NULL);
    ctest_t *testEmptyLuv = ctest("Creation of an NULL Luv from an empty Xyz", testNullLuv, NULL);
    ctest_t *testWhiteLuv = ctest("Creation of a White Luv from a White RGB", testWhiteLuvFromXyz, NULL);
    
    // test case Luv -> Xyz
    ctest_t *testXyz     = ctest("Creation of an Xyz from a Luv", testXyzFromLuv, NULL);
    ctest_t *testHighXyz = ctest("Creation of an Xyz from a Luv RGB", testHighXyzFromLuv, NULL);
    ctest_t *testEmptyXyz= ctest("Creation of an Xyz NULL", testNullXyz, NULL);
    
    // add test to test case
    ctctestadd(luvCase, testLuv);
    ctctestadd(luvCase, testSupLuv);
    ctctestadd(luvCase, testInfLuv);
    ctctestadd(luvCase, testEmptyLuv);
    ctctestadd(luvCase, testWhiteLuv);
    
    ctctestadd(luvCase, testXyz);
    ctctestadd(luvCase, testHighXyz);
    ctctestadd(luvCase, testEmptyXyz);
    
    return luvCase;
}


