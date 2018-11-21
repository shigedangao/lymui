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
#include "lch.h"

ctest_return_t testLchFromXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51f;
    xyz->y = 0.52f;
    xyz->z = 0.510f;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 77.28f, 0.01f, "Expect L to be equal to %f but got %f", 77.28f, lch->l);
    CTAssertDecimalEqual(test, lch->c, 12.0f, 0.1f, "Expect C to be equal to %f but got %f", 12.0f, lch->c);
    CTAssertDecimalEqual(test, lch->h, 37.5f, 0.01f, "Expect H to be equal to %f but got %f", 37.5f, lch->h);
    
    free(lch);
}

ctest_return_t testLchFromMaxXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 1.0f;
    xyz->y = 1.0f;
    xyz->z = 1.0f;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 100.0f, 0.01f, "Expect L to be equal to %f but got %f", 100.0f, lch->l);
    CTAssertDecimalEqual(test, lch->c, 17.89f, 0.01f, "Expect C to be equal to %f but got %f", 17.89f, lch->c);
    CTAssertDecimalEqual(test, lch->h, 22.85f, 0.01f, "Expect H to be equal to %f but got %f", 22.85f, lch->h);

    free(lch);
}

ctest_return_t testLchFromMinXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0f;
    xyz->y = 0.0f;
    xyz->z = 0.0f;
    
    Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 0.0f, 0.1f, "Expect L to be equal to 0 but got %f", lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.0f, 0.1f, "Expect C to be equal to 0 but got %f", lch->c);
    CTAssertDecimalEqual(test, lch->h, 0.0f, 0.1f, "Expect H to be equal to 0 but got %f", lch->h);

    free(lch);
}

ctest_return_t testNullLch(ctest_t *test, void *arg) {
    Lch *lch = getLchFromXyz(NULL);
    
    CTAssertNull(test, lch, "Expect lch to be NULL");
    free(lch);
}

ctest_return_t testLchToXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51f;
    xyz->y = 0.52f;
    xyz->z = 0.510f;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    CTAssertDecimalEqual(test, nXyz->x, 0.51f, 0.01f, "Expect X to be equal to 0.51 but got %f", nXyz->x);
    CTAssertDecimalEqual(test, nXyz->y, 0.52f, 0.01f, "Expect Y to be equal to 0.52 but got %f", nXyz->y);
    CTAssertDecimalEqual(test, nXyz->z, 0.510f, 0.001f, "Expect Z to be equal to 0.501f but got %f", nXyz->z);
    
    free(nXyz);
}

ctest_return_t testEmptyXyz(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLch(NULL);
    
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}


ctcase_t * wrapLchCreationTest() {
    ctcase_t *lchCase = ctcase("Lch test case");
    
    // Creation of Lch
    ctest_t *testLch    = ctest("Creation of a Lch from an Xyz struct", testLchFromXyz, NULL);
    ctest_t *testMaxLch = ctest("Creation of a Lch from a max value Xyz struct", testLchFromMaxXyz, NULL);
    ctest_t *testMinLch = ctest("Creation of a Lch from a min value Xyz struct", testLchFromMinXyz, NULL);
    
    // Null assertion
    ctest_t *testLchNull = ctest("Creation of a NULL Lch from a NULL Xyz", testNullLch, NULL);
    ctest_t *testXyzNull = ctest("Creation of a NULL Xyz from a NULL Lch", testEmptyXyz, NULL);
    
    // Creation of Xyz
    ctest_t *testXyz = ctest("Creation of a Xyz from an Lch struct", testLchToXyz, NULL);
    
    ctctestadd(lchCase, testLch);
    ctctestadd(lchCase, testMaxLch);
    ctctestadd(lchCase, testMinLch);
    ctctestadd(lchCase, testLchNull);
    ctctestadd(lchCase, testXyz);
    ctctestadd(lchCase, testXyzNull);
    
    return lchCase;
}

