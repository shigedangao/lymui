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
    luv->l = 10.0f;
    luv->u = 20.0f;
    luv->v = 30.0f;
    
    struct Xyz *xyz = getXyzFromLuv(luv);
    printf("Value of x %f \n", xyz->x);
    printf("Value of y %f \n", xyz->y);
    printf("Value of z %f \n", xyz->z);
    
    CTAssertEqual(test, 0.153f, roundDigit(xyz->x, 1000), "Expect X to be equal to %f but got %f", 0.153f, roundDigit(xyz->x, 1000));
    CTAssertEqual(test, 0.123f, roundDigit(xyz->y, 1000), "Expect Y to be equal to %f but got %f", 0.123f, roundDigit(xyz->x, 1000));
    CTAssertEqual(test, 0.015f, roundDigit(xyz->z, 1000), "Expect Z to be equal to %f but got %f", 0.015f, roundDigit(xyz->z, 1000));
    
    free(xyz);
}

ctcase_t * wrapLuvCreationTest() {
    ctcase_t *luvCase = ctcase("Luv creation test");
    
    // test case Xyz -> Luv
    ctest_t *testLuv    = ctest("Creation of a Luv from Xyz", createLuvFromXyz, NULL);
    ctest_t *testSupLuv = ctest("Creation of an Superior Y Luv from Xyz", testSuperiorYLuvFromXyz, NULL);
    ctest_t *testInfLuv = ctest("Creation of an Inferior Y Luv from Xyz", testInferiorYLuvFromXyz, NULL);
    ctest_t *testNulLuv = ctest("Creation of an NULL Luv from an empty Xyz", testNullLuv, NULL);
    
    // test case Luv -> Xyz
    ctest_t *testXyz    = ctest("Creation of an Xyz from a Luv", testXyzFromLuv, NULL);
    
    // add test to test case
    ctctestadd(luvCase, testLuv);
    ctctestadd(luvCase, testSupLuv);
    ctctestadd(luvCase, testInfLuv);
    ctctestadd(luvCase, testNulLuv);
    
    ctctestadd(luvCase, testXyz);
    
    return luvCase;
}


