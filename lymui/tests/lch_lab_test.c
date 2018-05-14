//
//  lch_lab_test.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "lchlab.h"

ctest_return_t testLchFromLab(ctest_t *test, void *arg) {
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = 0.51f;
    xyz->y = 0.52f;
    xyz->z = 0.55f;
    
    struct Lchlab *lch = getLchFromLab(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 4.69f, 0.01f, "Expect L to be equal to %f but got %f", 4.69f, lch->l);
    CTAssertDecimalEqual(test, lch->c, 0.68f, 0.01f, "Expect C to be equal to %f but got %f", 0.68f, lch->c);
    CTAssertDecimalEqual(test, lch->h, 19.73f, 0.01f, "Expect H to be equal to %f but got %f", 19.73f, lch->h);
    
    free(lch);
}

ctest_return_t testXyzFromLchLab(ctest_t *test, void *arg) {
    struct Xyz *xyz = malloc(sizeof(struct Xyz));
    xyz->x = 0.51f;
    xyz->y = 0.52f;
    xyz->z = 0.55f;
    
    struct Lchlab *lch = malloc(sizeof(struct Lchlab));
    lch->l = 4.697159f;
    lch->c = 0.685722f;
    lch->h = 19.739084f;
    
    struct Xyz *nXyz = getXyzFromLchlab(lch);
    
    CTAssertDecimalEqual(test, xyz->x, nXyz->x, 0.01f, "Expect X to be equal to %f but got %f", xyz->x, nXyz->x);
    CTAssertDecimalEqual(test, xyz->y, nXyz->y, 0.01f, "Expect Y to be equal to %f but got %f", xyz->y, nXyz->y);
    CTAssertDecimalEqual(test, xyz->z, nXyz->z, 0.01f, "Expect Z to be equal to %f but got %f", xyz->z, nXyz->z);

    free(nXyz);
    free(xyz);
}

ctest_return_t testLabLchNull(ctest_t *test, void *arg) {
    struct Lchlab *lch = getLchFromLab(NULL);
    
    CTAssertNull(test, lch, "Expect Lch to be NULL");
    
    free(lch);
}

ctest_return_t testXyzLchlabNull(ctest_t *test, void *arg) {
    struct Xyz *xyz = getXyzFromLchlab(NULL);
    
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
    
    free(xyz);
}


ctcase_t * wrapLchLabCreationTest() {
    ctcase_t *lchLabCase = ctcase("Lch Lab test case");
    
    // lch test case
    ctest_t *testLchLab = ctest("Creation of a LchLab struct from an Xyz struct", testLchFromLab, NULL);
    // xyz to lch test case
    ctest_t *testXyzLchlab = ctest("Creation of a Xyz struct from an Lchlab struct", testXyzFromLchLab, NULL);
    
    ctest_t *testLablchNull    = ctest("Creation of a NULL Lch from a NULL Xyz", testLabLchNull, NULL);
    ctest_t *testXyzLchlabNull = ctest("Creation of a NULL Lch from a NULL Xyz", testLabLchNull, NULL);

    ctctestadd(lchLabCase, testLchLab);
    ctctestadd(lchLabCase, testXyzLchlab);
    ctctestadd(lchLabCase, testLablchNull);
    ctctestadd(lchLabCase, testXyzLchlabNull);
    
    return lchLabCase;
}

