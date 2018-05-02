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
#include "rgb.h"
#include "xyz.h"
#include "srgb.h"
#include "helper.h"

ctest_return_t testSRgbCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct sRgb *srgb = getSRgbFromXyz(xyz);
    
    CTAssertEqual(test, 1.9f, roundDigit(srgb->r * 10, 10), "Expect r to be equal to be equal to 1.8 but got %f", roundDigit(srgb->r * 10, 10));
    CTAssertEqual(test, 0.3f, roundDigit(srgb->g * 10, 10), "Expect g to be equal to be equal to 0.3 but got %f", roundDigit(srgb->g * 10, 10));
    CTAssertEqual(test, 3.7f, roundDigit(srgb->b * 10, 10), "Expect r to be equal to be equal to 3.7 but got %f", roundDigit(srgb->b * 10, 10));
}

ctest_return_t testNullSRgbCreation(ctest_t *test, void *arg) {
    struct sRgb *srgb = getSRgbFromXyz(NULL);
    CTAssertNull(test, srgb, "Expect sRgb to be NULL");
    
    free(srgb);
}

ctcase_t *wrapSRgbCreationTest() {
    ctcase_t *sRgbCase = ctcase("sRGB test case");
    
    //test regarding the creation of srgb
    ctest_t *srgb  = ctest("Creation of an sRGB from Rgb struct", testSRgbCreation, NULL);
    ctest_t *nSrgb = ctest("Creating of an NULL sRGB from an empty Rgb struct", testNullSRgbCreation, NULL);
    
    ctctestadd(sRgbCase, srgb);
    ctctestadd(sRgbCase, nSrgb);
    
    return sRgbCase;
}
