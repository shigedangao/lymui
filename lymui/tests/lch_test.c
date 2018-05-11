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
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = 0.51f;
    xyz->y = 0.52f;
    xyz->z = 0.510f;
    
    struct Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 4.69f, 0.01f, "Expect L to be equal to %f but got %f", 4.69f, lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.72f, 0.01f, "Expect C to be equal to %f but got %f", 0.72f, lch->c);
    CTAssertDecimalEqual(test, lch->h, 37.5f, 0.01f, "Expect H to be equal to %f but got %f", 37.5f, lch->h);
    
    free(lch);
}

ctest_return_t testLchFromMaxXyz(ctest_t *test, void *arg) {
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = 1.0f;
    xyz->y = 1.0f;
    xyz->z = 1.0f;
    
    struct Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 8.99f, 0.01f, "Expect L to be equal to %f but got %f", 8.99f, lch->l);
    CTAssertDecimalEqual(test, lch->c, 1.60f, 0.01f, "Expect C to be equal to %f but got %f", 1.60f, lch->c);
    CTAssertDecimalEqual(test, lch->h, 22.85f, 0.01f, "Expect H to be equal to %f but got %f", 22.85f, lch->h);

    free(lch);
}

ctest_return_t testLchFromMinXyz(ctest_t *test, void *arg) {
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = 0.0f;
    xyz->y = 0.0f;
    xyz->z = 0.0f;
    
    struct Lch *lch = getLchFromXyz(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 0.0f, 0.1f, "Expect L to be equal to 0 but got %f", lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.0f, 0.1f, "Expect C to be equal to 0 but got %f", lch->c);
    CTAssertDecimalEqual(test, lch->h, 0.0f, 0.1f, "Expect H to be equal to 0 but got %f", lch->h);

    free(lch);
}

ctest_return_t testNullLch(ctest_t *test, void *arg) {
    struct Lch *lch = getLchFromXyz(NULL);
    
    CTAssertNull(test, lch, "Expect lch to be NULL");
    free(lch);
}


ctcase_t * wrapLchCreationTest() {
    ctcase_t *lchCase = ctcase("Lch test case");
    
    // Creation of Lch
    ctest_t *testLch    = ctest("Creation of a Lch from an Xyz struct", testLchFromXyz, NULL);
    ctest_t *testMaxLch = ctest("Creation of a Lch from a max value Xyz struct", testLchFromMaxXyz, NULL);
    ctest_t *testMinLch = ctest("Creation of a Lch from a min value Xyz struct", testLchFromMinXyz, NULL);
    
    // Null assertion
    ctest_t *testLchNull = ctest("Creation of a NULL Lch from a NULL Xyz", testNullLch, NULL);
    
    ctctestadd(lchCase, testLch);
    ctctestadd(lchCase, testMaxLch);
    ctctestadd(lchCase, testMinLch);
    ctctestadd(lchCase, testLchNull);
    
    return lchCase;
}

