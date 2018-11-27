//
//  lch_test.c
//  lymui
//
//  Created by Marc on 11/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <cunit.h>
#include "errors.h"
#include "lch.h"

ctest_return_t testLchFromXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51;
    xyz->y = 0.52;
    xyz->z = 0.510;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 77.28, 0.01, "Expect L to be equal to %f but got %f", 77.28, lch->l);
    CTAssertDecimalEqual(test, lch->c, 12.0, 0.1, "Expect C to be equal to %f but got %f", 12.0, lch->c);
    CTAssertDecimalEqual(test, lch->h, 37.5, 0.01, "Expect H to be equal to %f but got %f", 37.5, lch->h);
    
    free(lch);
}

ctest_return_t testLchFromMaxXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 1.0;
    xyz->y = 1.0;
    xyz->z = 1.0;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 100.0, 0.01, "Expect L to be equal to %f but got %f", 100.0, lch->l);
    CTAssertDecimalEqual(test, lch->c, 17.89, 0.01, "Expect C to be equal to %f but got %f", 17.89, lch->c);
    CTAssertDecimalEqual(test, lch->h, 22.85, 0.01, "Expect H to be equal to %f but got %f", 22.85, lch->h);

    free(lch);
}

ctest_return_t testLchFromFullWhiteXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.950470;
    xyz->y = 1.0;
    xyz->z = 1.088830;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 100.0, 0.1, "Expect L to be equal to %f but got %f", 100.0, lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.0, 0.1, "Expect C to be equal to %f but got %f", 0.0, lch->c);
    CTAssertDecimalEqual(test, lch->h, 360.0, 0.1, "Expect H to be equal to %f but got %f", 360.0, lch->h);
    
    free(lch);
}

ctest_return_t testLchFromMinXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 0.0, 0.1, "Expect L to be equal to 0 but got %f", lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.0, 0.1, "Expect C to be equal to 0 but got %f", lch->c);
    CTAssertDecimalEqual(test, lch->h, 180.0, 0.1, "Expect H to be equal to 0 but got %f", lch->h);

    free(lch);
}

ctest_return_t testNullLch(ctest_t *test, void *arg) {
    Lch *lch = getLchFromXyz(NULL);
    CTAssertEqual(test, lch->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    free(lch);
}

ctest_return_t testLchToXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51;
    xyz->y = 0.52;
    xyz->z = 0.510;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    CTAssertDecimalEqual(test, nXyz->x, 0.51, 0.01, "Expect X to be equal to 0.51 but got %f", nXyz->x);
    CTAssertDecimalEqual(test, nXyz->y, 0.52, 0.01, "Expect Y to be equal to 0.52 but got %f", nXyz->y);
    CTAssertDecimalEqual(test, nXyz->z, 0.510, 0.001, "Expect Z to be equal to 0.501f but got %f", nXyz->z);
    
    free(nXyz);
}

ctest_return_t testBrightLchToXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.950470;
    xyz->y = 1.0;
    xyz->z = 1.088830;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    CTAssertDecimalEqual(test, nXyz->x, 0.95, 0.01, "Expect X to be equal to 0.95 but got %f", nXyz->x);
    CTAssertDecimalEqual(test, nXyz->y, 1.0, 0.01, "Expect Y to be equal to 1.0 but got %f", nXyz->y);
    CTAssertDecimalEqual(test, nXyz->z, 1.088, 0.001, "Expect Z to be equal to 1.088 but got %f", nXyz->z);
    
    free(nXyz);
}

ctest_return_t testDarkLchToXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0;
    xyz->y = 0;
    xyz->z = 0;
    
    printf("Dark XYZ \n");
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    CTAssertDecimalEqual(test, nXyz->x, 0, 0.01, "Expect X to be equal to 0 but got %f", nXyz->x);
    CTAssertDecimalEqual(test, nXyz->y, 0, 0.01, "Expect Y to be equal to 0 but got %f", nXyz->y);
    CTAssertDecimalEqual(test, nXyz->z, 0, 0.001, "Expect Z to be equal to 0 but got %f", nXyz->z);
    
    free(nXyz);
}


ctest_return_t testEmptyXyz(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLch(NULL);
    CTAssertEqual(test, xyz->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(xyz);
}


ctcase_t * wrapLchCreationTest() {
    ctcase_t *lchCase = ctcase("Lch test case");
    
    // Creation of Lch
    ctest_t *testLch    = ctest("Creation of a Lch from an Xyz struct", testLchFromXyz, NULL);
    ctest_t *testMaxLch = ctest("Creation of a Lch from a max value Xyz struct", testLchFromMaxXyz, NULL);
    ctest_t *testMinLch = ctest("Creation of a Lch from a min value Xyz struct", testLchFromMinXyz, NULL);
    ctest_t *testWhiteLch = ctest("Creation of a Lch from a white value Xyz struct", testLchFromFullWhiteXyz, NULL);
    
    // Null assertion
    ctest_t *testLchNull = ctest("Creation of a NULL Lch from a NULL Xyz", testNullLch, NULL);
    ctest_t *testXyzNull = ctest("Creation of a NULL Xyz from a NULL Lch", testEmptyXyz, NULL);
    
    // Creation of Xyz
    ctest_t *testXyz       = ctest("Creation of a Xyz from an Lch struct", testLchToXyz, NULL);
    ctest_t *testBrightXyz = ctest("Creation of a bright XYZ from a LCH struct", testBrightLchToXyz, NULL);
    ctest_t *testDarkXyz   = ctest("Creation of a dark XYZ from a LCH struct", testDarkLchToXyz, NULL);
    
    ctctestadd(lchCase, testLch);
    ctctestadd(lchCase, testMaxLch);
    ctctestadd(lchCase, testMinLch);
    ctctestadd(lchCase, testWhiteLch);
    ctctestadd(lchCase, testLchNull);
    ctctestadd(lchCase, testXyz);
    ctctestadd(lchCase, testXyzNull);
    ctctestadd(lchCase, testBrightXyz);
    ctctestadd(lchCase, testDarkXyz);
    
    return lchCase;
}

