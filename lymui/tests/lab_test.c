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

ctest_return_t testLabCreationFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 43.0f, floorf(lab->l * 100), "Expect L to be equal to 43.0f but got %f real value is %f", floorf(lab->l), lab->l);
    CTAssertEqual(test, 2.0f, floorf(lab->a), "Expect A to be equal to 3.0f but got %f real value is %f", floorf(lab->a), lab->a);
    CTAssertEqual(test, -7.0f, floorf(lab->b), "Expect B to be equal to -7.0f but got %f real value is %f", floorf(lab->b), lab->b);
    
    free(lab);
}

ctest_return_t testBlackLabCreationFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 1;
    rgb->g = 1;
    rgb->b = 1;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 0.27f, roundDigit(lab->l * 100, 100), "Expect L to be equal to 0.27f but got %f", roundDigit(lab->l * 100, 100));
    CTAssertEqual(test, 0.0f, lab->a, "Expect A to be equal to 0.0f but got %f", lab->a);
    CTAssertEqual(test, -0.0f, lab->b, "Expect B to be equal to 0.0f but got %f", lab->b);
    
    free(lab);
}

ctest_return_t testWhiteLabCreation(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Lab *lab = getLabFromXyz(xyz);
    
    CTAssertEqual(test, 8.99f, roundDigit(lab->l * 1, 1000), "Expect L to be equal to 0.899 but got %f", roundDigit(lab->l * 1, 1000));
    CTAssertEqual(test, 0.001f, roundDigit(lab->a * 1, 1000), "Expect A to be equal to 0.183 but got %f", roundDigit(lab->a * 1, 1000));
    CTAssertEqual(test, 1.202f, roundDigit(lab->b * 1, 1000), "Expect L to be equal to 0.120 but got %f", roundDigit(lab->b * 1, 1000));
    
    free(lab);
}

ctest_return_t testNullLabCreation(ctest_t *test, void *arg) {
    struct Lab *lab = getLabFromXyz(NULL);
    CTAssertNull(test, lab, "Expect Lab to be null");
    
    free(lab);
}

ctest_return_t testXyzCreationFromLab(ctest_t *test, void *arg) {
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

ctest_return_t testXyzCreationFromSmallLab(ctest_t *test, void *arg) {
    struct Lab *lab = malloc(sizeof(struct Lab));
    lab->l = 0.274187f;
    lab->a = 0.000021f;
    lab->b = -0.00006f;
    
    struct Xyz *xyz = getXyzFromLab(lab);
    CTAssertEqual(test, 0.0289f, roundDigit(xyz->x * 1, 10000), "Expect X to be equal to 0.0289 but got %f", roundDigit(xyz->x * 1, 10000));
    CTAssertEqual(test, 0.03f,   roundDigit(xyz->y * 1, 1000), "Expect Y to be equal to 0.030 but got %f", roundDigit(xyz->y * 1, 1000));
    CTAssertEqual(test, 0.033f,  roundDigit(xyz->z * 1, 1000), "Expect Z to be equal to 0.033 but got %f", roundDigit(xyz->z * 1, 1000));

    free(xyz);
}

ctest_return_t testXyzCreationFromLargeLab(ctest_t *test, void *arg) {
    struct Lab *lab = malloc(sizeof(struct Lab));
    lab->l = 1.0f;
    lab->a = 1.0f;
    lab->b = 1.0f;
    
    struct Xyz *xyz = getXyzFromLab(lab);
    CTAssertEqual(test, xyz->x, 1.0f, "Expect X to be equal to 1.0f but got %f", xyz->x);
    CTAssertEqual(test, xyz->y, 1.0f, "Expect Y to be equal to 1.0f but got %f", xyz->y);
    CTAssertEqual(test, xyz->z, 1.0f, "Expect Z to be equal to 1.0f but got %f", xyz->z);
    
    free(xyz);
}

ctest_return_t testXyzNullCreation(ctest_t *test, void *arg) {
    struct Xyz *xyz = getXyzFromLab(NULL);
    CTAssertNull(test, xyz, "Expect XYZ to be NULL");
    
    free(xyz);
}

ctest_return_t testHunterLabCreationFromXyz(ctest_t *test, void *arg) {
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

ctest_return_t testNullHunterCreation(ctest_t *test, void *arg) {
    struct Lab *hunterLab = getHunterLabFromXyz(NULL);
    CTAssertNull(test, hunterLab, "Expect hunter lab to be NULL");
    
    free(hunterLab);
}

/**
 * @TODO, need to find a better name for whose test...
 */
ctcase_t *wrapLabCreationTest() {
    ctcase_t *labCase = ctcase("Lab creation test");
    
    ctest_t *labCreation = ctest("Lab test creation from Xyz", testLabCreationFromXyz, NULL);
    ctest_t *labBlackCreation = ctest("Lab Black color creation from Xyz", testBlackLabCreationFromXyz, NULL);
    ctest_t *labWhiteCreation = ctest("Lab White color creation from Xyz", testWhiteLabCreation, NULL);
    ctest_t *labNull = ctest("Lab null creation", testNullLabCreation, NULL);
    
    ctest_t *xyzCreation = ctest("Xyz test creation from Lab", testXyzCreationFromLab, NULL);
    ctest_t *xyzSmallCreation = ctest("Xyz test creation from small Lab", testXyzCreationFromSmallLab, NULL);
    ctest_t *xyzBigCreation = ctest("Xyz test from big lab", testXyzCreationFromLargeLab, NULL);
    ctest_t *xyzNull = ctest("Xyz test NULL", testXyzNullCreation, NULL);
    
    ctest_t *hunterCreation = ctest("Hunter Lab creation from Xyz", testHunterLabCreationFromXyz, NULL);
    ctest_t *hunterNull = ctest("NULL Hunter Lab", testNullHunterCreation, NULL);
    
    ctctestadd(labCase, labCreation);
    ctctestadd(labCase, labBlackCreation);
    ctctestadd(labCase, labWhiteCreation);
    ctctestadd(labCase, labNull);
    
    ctctestadd(labCase, xyzCreation);
    ctctestadd(labCase, xyzSmallCreation);
    //ctctestadd(labCase, xyzBigCreation);
    ctctestadd(labCase, xyzNull);
    
    ctctestadd(labCase, hunterCreation);
    ctctestadd(labCase, hunterNull);
    
    return labCase;
}
