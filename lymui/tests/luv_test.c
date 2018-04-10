//
//  luv_test.c
//  lymui
//
//  Created by Marc on 10/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include "xyz.h"
#include "luv.h"

ctest_return_t createLuvFromXyz(ctest_t *test, void *arg) {
    struct Rgb *rgb = malloc(sizeof(struct Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 95;
    
    struct Xyz *xyz = generateXyzFromRgb(rgb, sRgb);
    struct Luv *luv = getLuvFromXyz(xyz);
    
    CTAssertEqual(test, 0.975f, luv->l, "Expect L to be equal to %f but got %f", 0.975f, luv->l);
    CTAssertEqual(test, -0.0287f, luv->u, "Expect U to be equal to %f but got %f", -0.0287f, luv->u);
    CTAssertEqual(test, -0.3521f, luv->v, "Expect V to be equal to %f but got %f", -0.3521f, luv->v);
}

ctcase_t * wrapLuvCreationTest() {
    ctcase_t *luvCase = ctcase("Luv creation test");
    
    // test case
    ctest_t *createLuv = ctest("Creation of a Luv from Xyz", createLuvFromXyz, NULL);
    
    // add test to test case
    ctctestadd(luvCase, createLuv);
    
    return luvCase;
}


