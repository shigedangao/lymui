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
#include "errors.h"
#include "lchlab.h"

ctest_return_t testLchFromLab(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.1161;
    xyz->y = 0.0497;
    xyz->z = 0.5376;
    
    LchLab *lch = getLchFromLab(xyz);
    
    CTAssertDecimalEqual(test, lch->l, 26.64, 0.01, "Expect L to be equal to %f but got %f", 26.64, lch->l);
    CTAssertDecimalEqual(test, lch->c, 106.18, 0.01, "Expect C to be equal to %f but got %f", 106.18, lch->c);
    CTAssertDecimalEqual(test, lch->h, 359.9, 0.1, "Expect H to be equal to %f but got %f", 359.9, lch->h);
    
    free(lch);
}

ctest_return_t testXyzFromLchLab(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51;
    xyz->y = 0.52;
    xyz->z = 0.55;
    
    LchLab *lch = getLchFromLab(xyz);
    Xyz *nXyz = getXyzFromLchlab(lch);
    
    CTAssertDecimalEqual(test, 0.51, nXyz->x, 0.01, "Expect X to be equal to %f but got %f", 0.51, nXyz->x);
    CTAssertDecimalEqual(test, 0.52, nXyz->y, 0.01, "Expect Y to be equal to %f but got %f", 0.52, nXyz->y);
    CTAssertDecimalEqual(test, 0.56, nXyz->z, 0.01, "Expect Z to be equal to %f but got %f", 0.56, nXyz->z);

    free(nXyz);
}

ctest_return_t testLabLchNull(ctest_t *test, void *arg) {
    LchLab *lch = getLchFromLab(NULL);
    CTAssertEqual(test, lch->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);
    
    free(lch);
}

ctest_return_t testXyzLchlabNull(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromLchlab(NULL);
    CTAssertEqual(test, xyz->error, NULL_INPUT_STRUCT, "Expect Error to be equal to %s", NULL_INPUT_STRUCT);

    free(xyz);
}


ctcase_t * wrapLchLabCreationTest() {
    ctcase_t *lchLabCase = ctcase("Lch Lab test case");
    
    // lch test case
    ctest_t *testLchLab = ctest("Creation of a LchLab from an Xyz struct", testLchFromLab, NULL);
    // xyz to lch test case
    ctest_t *testXyzLchlab = ctest("Creation of a Xyz from an Lchlab struct", testXyzFromLchLab, NULL);
    
    ctest_t *testLablchNull    = ctest("Creation of a NULL Lch from a NULL Xyz", testLabLchNull, NULL);
    ctest_t *testXyzLchlabNull = ctest("Creation of a NULL Lch from a NULL Xyz", testLabLchNull, NULL);

    ctctestadd(lchLabCase, testLchLab);
    ctctestadd(lchLabCase, testXyzLchlab);
    ctctestadd(lchLabCase, testLablchNull);
    ctctestadd(lchLabCase, testXyzLchlabNull);
    
    return lchLabCase;
}

