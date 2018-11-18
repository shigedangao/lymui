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
#include "xyz.h"
#include "luv.h"
#include "helper.h"

ctest_return_t testLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 9.603f, luv->l, 0.001f, "Expect L to be equal to %f but got %f", 9.603f, luv->l);
    CTAssertDecimalEqual(test, -2.851f, luv->u, 0.001f, "Expect u to be equal to %f but got %f", -2.851f, luv->u);
    CTAssertDecimalEqual(test, -34.829f, luv->v, 0.001f, "Expect V to be equal to %f but got %f", -34.829f, luv->v);

    free(luv);
}

ctest_return_t testSuperiorYLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 200;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 96.417f, luv->l, 0.001f, "Expect L to be equal to %f but got %f", 96.417f, luv->l);
    CTAssertDecimalEqual(test, -27.734f, luv->u, 0.001f, "Expect U to be equal to %f but got %f", -27.734f, luv->u);
    CTAssertDecimalEqual(test, -5.983f, luv->v, 0.001f, "Expect V to be equal to %f but got %f", -5.983f, luv->v);
    
    free(luv);
}

ctest_return_t testInferiorYLuvFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 1;
    rgb->b = 0;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.487f, luv->l, 0.001f, "Expect L to be equal to %f but got %f", 0.487f, luv->l);
    CTAssertDecimalEqual(test, 0.808f, luv->u, 0.001f, "Expect U to be equal to %f but got %f", 0.808f, luv->u);
    CTAssertDecimalEqual(test, 0.442f, luv->v, 0.001f, "Expect V to be equal to %f but got %f", 0.442f, luv->v);

    free(luv);
}

ctest_return_t testNullLuv(ctest_t *test, void *arg) {
    Luv *luv = getLuvFromXyz(NULL);
    CTAssertNull(test, luv, "Expect Luv to be NULL");
    
    free(luv);
}

ctest_return_t testXyzFromLuv(ctest_t *test, void *arg) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 5.0f;
    luv->u = 1.0f;
    luv->v = 0.0f;
    
    Xyz *xyz = getXyzFromLuv(luv);
    
    CTAssertDecimalEqual(test, 0.00567f, xyz->x, 0.0001f, "Expect X to be equal to %f but got %f", 0.00567f, xyz->x);
    CTAssertDecimalEqual(test, 0.00554f, xyz->y, 0.0001f, "Expect Y to be equal to %f but got %f", 0.00554f, xyz->y);
    CTAssertDecimalEqual(test, 0.00589f, xyz->z, 0.0001f, "Expect Z to be equal to %f but got %f", 0.00589f, xyz->z);
    
    free(xyz);
}

ctest_return_t testHighXyzFromLuv(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);

    // get back the xyz
    Xyz *nXyz = getXyzFromLuv(luv);
    
    CTAssertDecimalEqual(test, 0.950f, nXyz->x, 0.001f, "Expect X to be equal to %f but got %f", 0.950f, nXyz->x);
    CTAssertDecimalEqual(test, 0.9998f, nXyz->y, 0.001f, "Expect Y to be equal to %f but got %f", 0.9998f, nXyz->y);
    CTAssertDecimalEqual(test, 1.0890f, nXyz->z, 0.001f, "Expect Z to be equal to %f but got %f", 1.0890f, nXyz->z);

    free(nXyz);
}

ctest_return_t testNullXyz(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLuv(NULL);
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}

ctcase_t * wrapLuvCreationTest() {
    ctcase_t *luvCase = ctcase("Luv creation test");
    
    // test case Xyz -> Luv
    ctest_t *testLuv     = ctest("Creation of a Luv from Xyz", testLuvFromXyz, NULL);
    ctest_t *testSupLuv  = ctest("Creation of an Superior Y Luv from Xyz", testSuperiorYLuvFromXyz, NULL);
    ctest_t *testInfLuv  = ctest("Creation of an Inferior Y Luv from Xyz", testInferiorYLuvFromXyz, NULL);
    ctest_t *testEmptyLuv= ctest("Creation of an NULL Luv from an empty Xyz", testNullLuv, NULL);
    
    // test case Luv -> Xyz
    ctest_t *testXyz     = ctest("Creation of an Xyz from a Luv", testXyzFromLuv, NULL);
    ctest_t *testHighXyz = ctest("Creation of an Xyz from a Luv RGB", testHighXyzFromLuv, NULL);
    ctest_t *testEmptyXyz= ctest("Creation of an Xyz NULL", testNullXyz, NULL);
    
    // add test to test case
    ctctestadd(luvCase, testLuv);
    ctctestadd(luvCase, testSupLuv);
    ctctestadd(luvCase, testInfLuv);
    ctctestadd(luvCase, testEmptyLuv);
    
    ctctestadd(luvCase, testXyz);
    ctctestadd(luvCase, testHighXyz);
    ctctestadd(luvCase, testEmptyXyz);
    
    return luvCase;
}


