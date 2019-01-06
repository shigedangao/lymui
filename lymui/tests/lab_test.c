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
#include "test_header.h"
#include "errors.h"
#include "helper.h"
#include "xyz.h"
#include "lab.h"

ctest_return_t testLabFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 26.25, lab->l, 0.01, "Expect L to be equal to %f but got %f real value is %f", 26.25, lab->l);
    CTAssertDecimalEqual(test, 63.50, lab->a, 0.01, "Expect A to be equal to %f but got %f real value is %f", 63.50, lab->a);
    CTAssertDecimalEqual(test, -83.43, lab->b, 0.01, "Expect B to be equal to %f but got %f real value is %f", -83.43, lab->b);

    free(lab);
}

ctest_return_t testBlackLabFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 1;
    rgb->g = 1;
    rgb->b = 1;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.27, lab->l, 0.01, "Expect L to be equal to %f but got %f", 0.27, lab->l);
    CTAssertDecimalEqual(test, 0.0, lab->a, 0.01, "Expect A to be equal to %f but got %f", 0.0, lab->a);
    CTAssertDecimalEqual(test, 0.0, lab->b, 0.01, "Expect B to be equal to %f but got %f", 0.0, lab->b);

    free(lab);
}

ctest_return_t testWhiteLab(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 100.0, lab->l, 0.001, "Expect L to be equal to %f but got %f", 100.0, lab->l);
    CTAssertDecimalEqual(test, 0.0, lab->a, 0.0001, "Expect A to be equal to %f but got %f", 0.000, lab->a);
    CTAssertDecimalEqual(test, 0.0, lab->b, 0.001, "Expect B to be equal to %f but got %f", 0.0, lab->b);

    free(lab);
}

ctest_return_t testNullLab(ctest_t *test, void *arg) {
    Lab *lab = getLabFromXyz(NULL);
    CTAssertStringEqual(test, lab->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(lab);
}

ctest_return_t testXyzFromLab(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    Xyz *xyz  = getXyzFromRgb(rgb, srgb);
    Lab *lab  = getLabFromXyz(xyz);
    Xyz *nXyz = getXyzFromLab(lab);
    
    CTAssertDecimalEqual(test, xyz->x, nXyz->x, 0.001, "Expect X to be equal to %f but got %f", xyz->x, nXyz->x);
    CTAssertDecimalEqual(test, xyz->y, nXyz->y, 0.001, "Expect Y to be equal to %f but got %f", xyz->y, nXyz->y);
    CTAssertDecimalEqual(test, xyz->x, nXyz->x, 0.001,"Expect Z to be equal to %f but got %f", xyz->z, nXyz->z);

    free(nXyz);
}

ctest_return_t testXyzFromSmallLab(ctest_t *test, void *arg) {
    Lab *lab = malloc(sizeof(Lab));
    lab->l = 26.65;
    lab->a = 64.26;
    lab->b = -84.54;
    
    Xyz *xyz = getXyzFromLab(lab);
    CTAssertDecimalEqual(test, 0.1161, xyz->x, 0.0001, "Expect X to be equal to %f but got %f", 0.1161, xyz->x);
    CTAssertDecimalEqual(test, 0.0497, xyz->y, 0.0001, "Expect Y to be equal to %f but got %f", 0.0497, xyz->y);
    CTAssertDecimalEqual(test, 0.5376, xyz->z, 0.0001, "Expect Z to be equal to %f but got %f", 0.5376, xyz->z);

    free(xyz);
}

ctest_return_t testXyzFromLargeLab(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    Xyz *nXyz = getXyzFromLab(lab);
    
    CTAssertDecimalEqual(test, 0.9504, nXyz->x, 0.0001,"Expect X to be equal to current xyz %f but got %f", 0.9504, nXyz->x);
    CTAssertDecimalEqual(test, 1.0000, nXyz->y, 0.0001, "Expect Y to be equal to current xyz %f but got %f", 1.0, nXyz->y);
    CTAssertDecimalEqual(test, 1.0888, nXyz->z, 0.0001, "Expect Z to be equal to current xyz %f but got %f", 1.0888, nXyz->z);

    free(nXyz);
}

ctest_return_t testXyzNullCreation(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLab(NULL);
    CTAssertStringEqual(test, xyz->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(xyz);
}

ctest_return_t testHunterLabFromXyz(ctest_t *test, void *arg) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 239;
    rgb->g = 130;
    rgb->b = 54;
    
    Xyz *xyz  = getXyzFromRgb(rgb, srgb);
    Lab *hunterLab = getHunterLabFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 58.811, hunterLab->l, 0.01, "Expect L to be equal to %f but got %f", 58.811, hunterLab->l);
    CTAssertDecimalEqual(test, 35.07, hunterLab->a, 0.01, "Expect A to be equal to %f but got %f", 35.07, hunterLab->a);
    CTAssertDecimalEqual(test, 31.22, hunterLab->b, 0.01, "Expect B to be equal to %f but got %f", 31.22, hunterLab->b);

    free(hunterLab);
}

ctest_return_t testNullHunter(ctest_t *test, void *arg) {
    Lab *hunterLab = getHunterLabFromXyz(NULL);
    CTAssertStringEqual(test, hunterLab->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
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
