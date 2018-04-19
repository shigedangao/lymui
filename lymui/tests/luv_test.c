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

ctest_return_t createLuvFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertEqual(test, 0.971f, roundDigit(luv->l * 10, 1000), "Expect L to be equal to %f but got %f", 0.975f, roundDigit(luv->l * 10, 1000));
    CTAssertEqual(test, -0.029f, roundDigit(luv->u, 1000), "Expect U to be equal to %f but got %f", -0.029f, roundDigit(luv->u, 1000));
    CTAssertEqual(test, -0.352f, roundDigit(luv->v, 1000), "Expect V to be equal to %f but got %f", -0.352f, roundDigit(luv->v, 1000));
    
    free(luv);
}

ctest_return_t testSuperiorYLuvFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 200;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertEqual(test, 8.218f, roundDigit(luv->l, 1000), "Expect L to be equal to %f but got %f", 0.821f, roundDigit(luv->l, 1000));
    CTAssertEqual(test, -2.104f, roundDigit(luv->u, 1000), "Expect U to be equal to %f but got %f", -2.104f, roundDigit(luv->u, 1000));
    CTAssertEqual(test, 0.176f, roundDigit(luv->v, 1000), "Expect V to be equal to %f but got %f", 0.176f, roundDigit(luv->v, 1000));
    
    free(luv);
}

ctest_return_t testInferiorYLuvFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 5;
    rgb->g = 1;
    rgb->b = 0;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertEqual(test, 0.00488f, roundDigit(luv->l, 100000), "Expect L to be equal to %f but got %f", 0.487f, roundDigit(luv->l, 100000));
    CTAssertEqual(test, 0.00809f, roundDigit(luv->u, 100000), "Expect U to be equal to %f but got %f", 0.808f, roundDigit(luv->u, 100000));
    CTAssertEqual(test, 0.00442f, roundDigit(luv->v, 100000), "Expect V to be equal to %f but got %f", 0.442f, roundDigit(luv->v, 100000));
    
    free(luv);
}

ctest_return_t testNullLuv(ctest_t *test, void *arg) {
    struct Luv *luv = getLuvFromXyz(NULL);
    CTAssertNull(test, luv, "Expect Luv to be NULL");
    
    free(luv);
}

ctest_return_t testXyzFromLuv(ctest_t *test, void *arg) {
    struct Luv *luv = malloc(sizeof(struct Luv));
    luv->l = 5.0f;
    luv->u = 1.0f;
    luv->v = 0.0f;
    
    struct Xyz *xyz = getXyzFromLuv(luv);
    
    CTAssertEqual(test, 0.567f, roundDigit(xyz->x, 1000), "Expect X to be equal to %f but got %f", 0.567f, roundDigit(xyz->x, 1000));
    CTAssertEqual(test, 0.554f, roundDigit(xyz->y, 1000), "Expect Y to be equal to %f but got %f", 0.554f, roundDigit(xyz->y, 1000));
    CTAssertEqual(test, 0.589f, roundDigit(xyz->z, 1000), "Expect Z to be equal to %f but got %f", 0.589f, roundDigit(xyz->z, 1000));
    
    free(xyz);
}

ctest_return_t testHighXyzFromLuv(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Luv *luv = getLuvFromXyz(xyz);

    // get back the xyz
    struct Xyz *nXyz = getXyzFromLuv(luv);
    
    CTAssertEqual(test, 0.950f, roundDigit(nXyz->x, 1000), "Expect X to be equal to %f but got %f", 0.950f, roundDigit(nXyz->x, 1000));
    CTAssertEqual(test, 0.9998f, roundDigit(nXyz->y, 10000), "Expect Y to be equal to %f but got %f", 0.9998f, roundDigit(nXyz->y, 10000));
    CTAssertEqual(test, 1.0f, roundDigit(nXyz->z, 1000), "Expect Z to be equal to %f but got %f", 1.0f, roundDigit(nXyz->z, 1000));
    
    free(nXyz);
}

ctest_return_t testNullXyz(ctest_t *test, void *arg) {
    struct Xyz *xyz = getXyzFromLuv(NULL);
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}

ctcase_t * wrapLuvCreationTest() {
    ctcase_t *luvCase = ctcase("Luv creation test");
    
    // test case Xyz -> Luv
    ctest_t *testLuv     = ctest("Creation of a Luv from Xyz", createLuvFromXyz, NULL);
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


