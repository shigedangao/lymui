//
//  xyy_test.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "xyz.h"
#include "xyy.h"

ctest_return_t testXyyFromXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.9f;
    xyz->y = 0.8f;
    xyz->z = 0.7f;
    
    Xyy *xyy = getXyyFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.375f, xyy->x, 0.001f, "Expect x to be equal to 0.375 but got %f", xyy->x);
    CTAssertDecimalEqual(test, 0.333f, xyy->y, 0.001f, "Expect y to be equal to 0.333 but got %f", xyy->y);
    CTAssertDecimalEqual(test, 0.8f, xyy->Y, 0.01f, "Expect Y to be equal to 0.8 but got %f", xyy->Y);

    free(xyy);
}

ctest_return_t testXyyFromZeroXyz(ctest_t *test, void *arg) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0f;
    xyz->y = 0.0f;
    xyz->z = 0.0f;
    
    Xyy *xyy = getXyyFromXyz(xyz);
    
    CTAssertDecimalEqual(test, 0.312f, xyy->x, 0.001f, "Expect x to be equal to 0.312 but got %f", xyy->x);
    CTAssertDecimalEqual(test, 0.329f, xyy->y, 0.001f, "Expect y to be equal to 0.329 but got %f", xyy->y);
    CTAssertDecimalEqual(test, 0.0f, xyy->Y, 0.01f, "Expect Y to be equal to 0.0f but got %f", xyy->Y);
    
    free(xyy);
}

ctest_return_t testXyzFromXyy(ctest_t *test, void *arg) {
    Xyy *xyy = malloc(sizeof(Xyy));
    xyy->x = 0.375f;
    xyy->y = 0.333f;
    xyy->Y = 0.8f;
    
    Xyz *xyz = getXyzFromXyy(xyy);
    
    CTAssertDecimalEqual(test, 0.9f, xyz->x, 0.1f, "Expect X to be equal to %f but got %f", 0.9f, xyz->x);
    CTAssertDecimalEqual(test, 0.8f, xyz->y, 0.1f, "Expect Y to be equal to %f but got %f", 0.8f, xyz->y);
    CTAssertDecimalEqual(test, 0.7f, xyz->z, 0.1f, "Expect Z to be equal to %f but got %f", 0.7f, xyz->z);

    free(xyz);
}

ctest_return_t testXyzFromXyyZero(ctest_t *test, void *arg) {
    Xyy *xyy = malloc(sizeof(Xyy));
    xyy->x = 1.0f;
    xyy->y = 0.0f;
    xyy->Y = 0.9f;
    
    Xyz *xyz = getXyzFromXyy(xyy);
    
    CTAssertDecimalEqual(test, 0.0f, xyz->x, 0.1f, "Expect X to be equal to %f but got %f", 0.0f, xyz->x);
    CTAssertDecimalEqual(test, 0.0f, xyz->y, 0.1f, "Expect Y to be equal to %f but got %f", 0.0f, xyz->y);
    CTAssertDecimalEqual(test, 0.0f, xyz->z, 0.1f, "Expect Z to be equal to %f but got %f", 0.0f, xyz->z);
    
    free(xyz);
}

ctest_return_t testNullXyzXyy(ctest_t *test, void *arg) {
    Xyy *xyy = getXyyFromXyz(NULL);
    
    CTAssertNull(test, xyy, "Expect Xyy to be NULL");
}

ctest_return_t testNullXyyXyz(ctest_t *test, void *arg) {
    Xyz *xyz = getXyzFromXyy(NULL);
    
    CTAssertNull(test, xyz, "Expect Xyz to be NULL");
}

ctcase_t * wrapXyyCreationTest() {
    ctcase_t * xyyCase = ctcase("Xyy test case");
    
    // Creation of Xyy
    ctest_t *testXyzXyy  = ctest("Creation of a Xyy from a Xyz struct", testXyyFromXyz, NULL);
    ctest_t *testZeroXyy = ctest("Creation of a Xyy from a zero value Xyz struct", testXyyFromZeroXyz, NULL);
    
    // Creation of Xyz
    ctest_t *testXyz     = ctest("Creation of a Xyz from a Xyy struct", testXyzFromXyy, NULL);
    ctest_t *testZeroXyz = ctest("Creation of a Xyz from a zero Y Xyy struct", testXyzFromXyyZero, NULL);
    
    // Nullability
    ctest_t *testXyyXyzNull = ctest("Creation of a NULL Xyy", testNullXyzXyy, NULL);
    ctest_t *testXyzXyyNull = ctest("Creation of a NULL Xyz", testNullXyyXyz, NULL);

    ctctestadd(xyyCase, testXyzXyy);
    ctctestadd(xyyCase, testZeroXyy);
    ctctestadd(xyyCase, testXyz);
    ctctestadd(xyyCase, testZeroXyz);
    ctctestadd(xyyCase, testXyyXyzNull);
    ctctestadd(xyyCase, testXyzXyyNull);

    return xyyCase;
}
