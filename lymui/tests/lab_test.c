//
//  lab_test.c
//  lymui
//
//  Created by Marc on 20/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include <math.h>
#include "helper.h"
#include "xyz.h"
#include "lab.h"

ctest_return_t testLabFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 43.0f, floorf(lab->l * 100), "Expect L to be equal to %f but got %f real value is %f", 43.0f, floorf(lab->l), lab->l);
    CTAssertEqual(test, 2.0f,  floorf(lab->a), "Expect A to be equal to %f but got %f real value is %f", 2.0f, floorf(lab->a), lab->a);
    CTAssertEqual(test, -7.0f, floorf(lab->b), "Expect B to be equal to %f but got %f real value is %f", -7.0f, floorf(lab->b), lab->b);
    
    free(lab);
}

ctest_return_t testBlackLabFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 1;
    rgb->g = 1;
    rgb->b = 1;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 0.27f, roundDigit(lab->l * 100, 100), "Expect L to be equal to %f but got %f", 0.27f, roundDigit(lab->l * 100, 100));
    CTAssertEqual(test, 0.0f, lab->a, "Expect A to be equal to %f but got %f", 0.0f, lab->a);
    CTAssertEqual(test, -0.0f, lab->b, "Expect B to be equal to %f but got %f", 0.0f, lab->b);
    
    free(lab);
}

ctest_return_t testWhiteLab(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 8.99f,  roundDigit(lab->l * 1, 1000), "Expect L to be equal to %f but got %f", 0.899f, roundDigit(lab->l * 1, 1000));
    CTAssertEqual(test, 0.001f, roundDigit(lab->a * 1, 1000), "Expect A to be equal to %f but got %f", 0.183f, roundDigit(lab->a * 1, 1000));
    CTAssertEqual(test, 1.202f, roundDigit(lab->b * 1, 1000), "Expect B to be equal to %f but got %f", 0.120f, roundDigit(lab->b * 1, 1000));
    
    free(lab);
}

ctest_return_t testNullLab(ctest_t *test, void *arg) {
    struct Lab *lab = getLabFromXyz(NULL);
    CTAssertNull(test, lab, "Expect Lab to be null");
    
    free(lab);
}

ctest_return_t testXyzFromLab(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    struct Xyz *xyz  = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab  = getLabFromXyz(xyz);
    struct Xyz *nXyz = getXyzFromLab(lab);
    
    CTAssertEqual(test, xyz->x, nXyz->x, "Expect X to be equal to %f but got %f", xyz->x, nXyz->x);
    CTAssertEqual(test, xyz->y, nXyz->y, "Expect Y to be equal to %f but got %f", xyz->y, nXyz->y);
    CTAssertEqual(test, xyz->x, nXyz->x, "Expect Z to be equal to %f but got %f", xyz->z, nXyz->z);
    
    free(xyz);
}

ctest_return_t testXyzFromSmallLab(ctest_t *test, void *arg) {
    struct Lab *lab = malloc(sizeof(struct Lab));
    lab->l = 0.274187f;
    lab->a = 0.000021f;
    lab->b = -0.00006f;
    
    struct Xyz *xyz = getXyzFromLab(lab);
    CTAssertEqual(test, 0.0289f, roundDigit(xyz->x * 1, 10000), "Expect X to be equal to %f but got %f", 0.0289f, roundDigit(xyz->x * 1, 10000));
    CTAssertEqual(test, 0.03f,   roundDigit(xyz->y * 1, 1000), "Expect Y to be equal to %f but got %f",  0.030f, roundDigit(xyz->y * 1, 1000));
    CTAssertEqual(test, 0.033f,  roundDigit(xyz->z * 1, 1000), "Expect Z to be equal to %f but got %f",  0.033f, roundDigit(xyz->z * 1, 1000));

    free(xyz);
}

ctest_return_t testXyzFromLargeLab(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    struct Xyz *nXyz = getXyzFromLab(lab);
    
    CTAssertEqual(test, xyz->x, nXyz->x, "Expect X to be equal to current xyz %f but got %f", xyz->x, nXyz->x);
    CTAssertEqual(test, xyz->x, nXyz->x, "Expect Y to be equal to current xyz %f but got %f", xyz->y, nXyz->y);
    CTAssertEqual(test, xyz->x, nXyz->x, "Expect Z to be equal to current xyz %f but got %f", xyz->z, nXyz->z);

    free(nXyz);
}

ctest_return_t testXyzNullCreation(ctest_t *test, void *arg) {
    struct Xyz *xyz = getXyzFromLab(NULL);
    CTAssertNull(test, xyz, "Expect XYZ to be NULL");
    
    free(xyz);
}

ctest_return_t testHunterLabFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 239;
    rgb->g = 130;
    rgb->b = 54;
    
    struct Xyz *xyz  = generateXyzFromRgb(rgb, sRgb);
    struct Lab *hunterLab = getHunterLabFromXyz(xyz);
    
    // test undergoing using colormine lib.. but there are some strange differences...
    CTAssertEqual(test, 588.0f, roundf(hunterLab->l * 100), "Expect L to be equal to %f but got %f", 588.0f, roundf(hunterLab->l * 100));
    CTAssertEqual(test, 351.0f, roundf(hunterLab->a * 100), "Expect A to be equal to %f but got %f", 351.0f, roundf(hunterLab->a * 100));
    CTAssertEqual(test, 312.0f, roundf(hunterLab->b * 100), "Expect B to be equal to %f but got %f", 312.0f, roundf(hunterLab->b * 100));
    
    free(hunterLab);
}

ctest_return_t testNullHunter(ctest_t *test, void *arg) {
    struct Lab *hunterLab = getHunterLabFromXyz(NULL);
    CTAssertNull(test, hunterLab, "Expect hunter lab to be NULL");
    
    free(hunterLab);
}

/**
 * @TODO, need to find a better name for whose test...
 */
ctcase_t *wrapLabCreationTest() {
    ctcase_t *labCase = ctcase("Lab creation test");
    
    ctest_t *labCreation      = ctest("Creation of an Lab from Xyz struct", testLabFromXyz, NULL);
    ctest_t *labBlackCreation = ctest("Creation of an Lab Black color from Xyz struct", testBlackLabFromXyz, NULL);
    ctest_t *labWhiteCreation = ctest("Creation of an Lab White color from Xyz struct", testWhiteLab, NULL);
    ctest_t *labNull          = ctest("Creation of an NULL Lab from empty Xyz struct", testNullLab, NULL);
    
    ctest_t *xyzCreation      = ctest("Creation of an Xyz from Lab struct", testXyzFromLab, NULL);
    ctest_t *xyzSmallCreation = ctest("Creation of an Xyz from low value Lab struct", testXyzFromSmallLab, NULL);
    ctest_t *xyzBigCreation   = ctest("Creation of an Xyz from high value Lab struct", testXyzFromLargeLab, NULL);
    ctest_t *xyzNull          = ctest("Creation of an NULL Xyz from NULL Lab struct", testXyzNullCreation, NULL);
    
    ctest_t *hunterCreation = ctest("Creation of an Hunter Lab from Xyz struct", testHunterLabFromXyz, NULL);
    ctest_t *hunterNull     = ctest("Creation of an NULL Hunter Lab from NULL Xyz struct", testNullHunter, NULL);
    
    ctctestadd(labCase, labCreation);
    ctctestadd(labCase, labBlackCreation);
    ctctestadd(labCase, labWhiteCreation);
    ctctestadd(labCase, labNull);
    
    ctctestadd(labCase, xyzCreation);
    ctctestadd(labCase, xyzSmallCreation);
    ctctestadd(labCase, xyzBigCreation);
    ctctestadd(labCase, xyzNull);
    
    ctctestadd(labCase, hunterCreation);
    ctctestadd(labCase, hunterNull);
    
    return labCase;
}
