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

ctest_return_t testHunterLabCreationFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    struct Xyz *xyz  = generateXyzFromRgb(rgb, sRgb);
    struct Lab *hunterLab = getHunterLabFromXyz(xyz);
    
    // test undergoing using colormine lib.. but there are some strange differences...
    CTAssertEqual(test, 2.197f, hunterLab->l, "Expect L to be equal to %f but got %f", 1.0f, hunterLab->l);
    CTAssertEqual(test, 5.51f, hunterLab->a, "Expect A to be equal to %f but got %f", 1.0f, hunterLab->a);
    CTAssertEqual(test, -13.08f, hunterLab->b, "Expect B to be equal to %f but got %f", 1.0f, hunterLab->b);
}

ctcase_t *wrapLabCreationTest() {
    ctcase_t *labCase = ctcase("Lab creation test");
    
    ctest_t *labCreation = ctest("Lab test creation from Xyz", testLabCreationFromXyz, NULL);
    ctest_t *xyzCreation = ctest("Xyz test creation from Lab", testXyzCreationFromLab, NULL);
    ctest_t *hunterCreation = ctest("Hunter Lab creation from Xyz", testHunterLabCreationFromXyz, NULL);
    
    ctctestadd(labCase, labCreation);
    ctctestadd(labCase, xyzCreation);
    //ctctestadd(labCase, hunterCreation);
    
    return labCase;
}
