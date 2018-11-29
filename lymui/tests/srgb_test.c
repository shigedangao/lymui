//
//  srgb_test.c
//  lymui
//
//  Created by Marc on 13/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "errors.h"
#include "rgb.h"
#include "xyz.h"
#include "srgb.h"
#include "helper.h"

ctest_return_t testSRgbCreation(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = generateXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSRgbFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.19, srgb->r, 0.01, "Expect r to be equal to be equal to 0.19 but got %f", srgb->r);
    CTAssertDecimalEqual(test, 0.03, srgb->g, 0.01, "Expect g to be equal to be equal to 0.03 but got %f", srgb->g);
    CTAssertDecimalEqual(test, 0.37, srgb->b, 0.01, "Expect b to be equal to be equal to 0.37 but got %f", srgb->b);

    free(srgb);
}

ctest_return_t testXyzCreation(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0376;
    xyz->y = 0.0173;
    xyz->z = 0.1138;
    
    SRgb *srgb = getSRgbFromXyz(xyz);
    Xyz *nXyz = getXyzFromSrgb(srgb);
    
    CTAssertDecimalEqual(test, 0.0376, nXyz->x, 0.01, "Expect x to be equal to be equal to 0.0376 but got %f", nXyz->x);
    CTAssertDecimalEqual(test, 0.0173, nXyz->y, 0.01, "Expect y to be equal to be equal to 0.0173 but got %f", nXyz->y);
    CTAssertDecimalEqual(test, 0.1138, nXyz->z, 0.01, "Expect z to be equal to be equal to 0.1138 but got %f", nXyz->z);
    
    free(nXyz);
}

ctest_return_t testNullSRgbCreation(ctest_t *test, void *arg) {
    SRgb *srgb = getSRgbFromXyz(NULL);
    CTAssertEqual(test, srgb->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);

    free(srgb);
}

ctcase_t *wrapSRgbCreationTest() {
    ctcase_t *sRgbCase = ctcase("sRGB test case");
    
    //test regarding the creation of srgb
    ctest_t *srgb  = ctest("Creation of an sRGB from Rgb struct", testSRgbCreation, NULL);
    ctest_t *xyz   = ctest("Creation of an XYZ from an SRGB struct", testXyzCreation, NULL);
    ctest_t *nSrgb = ctest("Creating of an NULL sRGB from an empty Rgb struct", testNullSRgbCreation, NULL);
    
    ctctestadd(sRgbCase, srgb);
    ctctestadd(sRgbCase, xyz);
    ctctestadd(sRgbCase, nSrgb);
    
    return sRgbCase;
}
