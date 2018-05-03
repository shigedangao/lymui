//
//  xyz_test.c
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
#include "helper.h"

ctest_return_t testXyzRgb(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    
    CTAssertEqual(test, 3.49f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to %f but got %f", 3.49f, roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.72f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to %f but got %f", 1.72f, roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 10.97f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to %f but got %f", 10.97f, roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t testXyzAdobeRgb(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, adobeRgb);
    
    // Though this test are kinda falsy as i didn't find any XYZ converter with the adobe RGB format online... so take it with grain of salt
    CTAssertEqual(test, 3.76f, roundDigit(xyz->x * 100, 100), "Expect X to be equal to %f but got %f", 3.76f, roundDigit(xyz->x * 100, 100));
    CTAssertEqual(test, 1.73f, roundDigit(xyz->y * 100, 100), "Expect Y to be equal to %f but got %f", 1.73f, roundDigit(xyz->y * 100, 100));
    CTAssertEqual(test, 11.38f, roundDigit(xyz->z * 100, 100), "Expect Z to be equal to %f but got %f", 11.38f, roundDigit(xyz->z * 100, 100));
    
    free(xyz);
}

ctest_return_t testXyzRgbNull(ctest_t *test, void *arg) {
    struct Xyz *xyz = generateXyzFromRgb(NULL, sRgb);
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}

ctcase_t *wrapXyzCreationTest() {
    ctcase_t *xyzCase = ctcase("Xyz test case");
    
    // xyz rgb case
    ctest_t *testRgbCase   = ctest("Creation of an Xyz with RGB case", testXyzRgb, NULL);
    ctest_t *testAdobeCase = ctest("Creation of an Xyz with Adobe value", testXyzRgbNull, NULL);
    ctest_t *testNRgbCase  = ctest("Creation of an NULL Xyz value with RGB case", testXyzAdobeRgb, NULL);
    
    // add cases
    ctctestadd(xyzCase, testRgbCase);
    ctctestadd(xyzCase, testNRgbCase);
    ctctestadd(xyzCase, testAdobeCase);
    
    return xyzCase;
}

