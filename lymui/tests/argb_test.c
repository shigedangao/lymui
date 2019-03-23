//
//  ARgb_test.c
//  lymui
//
//  Created by Marc on 14/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "helper.h"
#include "rgb.h"
#include "xyz.h"
#include "argb.h"

MU_TEST(argb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    mu_assert_double_eq(0.196, roundup(argb->r, 1000));
    mu_assert_double_eq(0.039, roundup(argb->g, 1000));
    mu_assert_double_eq(0.372, roundup(argb->b, 1000));
    
    free(rgb);
    free(xyz);
    free(argb);
}

MU_TEST(argb_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    mu_assert_double_eq(0.0, argb->r);
    mu_assert_double_eq(0.0, argb->g);
    mu_assert_double_eq(0.0, argb->b);
    
    free(rgb);
    free(xyz);
    free(argb);
}

MU_TEST(argb_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
    Argb *argb = getARgbFromXyz(xyz);
    
    mu_assert_double_eq(1.0, roundup(argb->r, 10));
    mu_assert_double_eq(1.0, roundup(argb->g, 10));
    mu_assert_double_eq(1.0, roundup(argb->b, 10));
    
    free(rgb);
    free(xyz);
    free(argb);
}

MU_TEST(argb_empty_param) {
    Argb *argb = getARgbFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, argb->error);
    
    free(argb);
}

MU_TEST(xyz_creation) {
    Argb *argb = malloc(sizeof(Argb));
    argb->r = 0.196089;
    argb->g = 0.039087;
    argb->b = 0.372496;
    
    Xyz *xyz = getXyzFromARgb(argb);
    
    mu_assert_double_eq(0.0376, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0173, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.1138, roundup(xyz->z, 10000));

    free(xyz);
}

MU_TEST(xyz_bright_creation) {
    Argb *argb = malloc(sizeof(Argb));
    argb->r = 1.0;
    argb->g = 1.0;
    argb->b = 1.0;
    
    Xyz *xyz = getXyzFromARgb(argb);
    
    mu_assert_double_eq(0.9505, roundup(xyz->x, 10000));
    mu_assert_double_eq(1.0000, roundup(xyz->y, 10000));
    mu_assert_double_eq(1.0888, roundup(xyz->z, 10000));

    free(xyz);
}

MU_TEST(xyz_dark_creation) {
    Argb *argb = malloc(sizeof(Argb));
    argb->r = 0.0;
    argb->g = 0.0;
    argb->b = 0.0;
    
    Xyz *xyz = getXyzFromARgb(argb);
    
    mu_assert_double_eq(0.0, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.0, roundup(xyz->z, 10000));
    
    free(xyz);
}

MU_TEST(xyz_empty_param) {
    Xyz *xyz = getXyzFromARgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);

    free(xyz);
}

MU_TEST_SUITE(argb_suite) {
    // Xyz -> Argb
    MU_RUN_TEST(argb_creation);
    MU_RUN_TEST(argb_dark_creation);
    MU_RUN_TEST(argb_bright_creation);
    MU_RUN_TEST(argb_empty_param);
    
    // Argb -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_empty_param);
}

int wrapArgbTest() {
    MU_RUN_SUITE(argb_suite);
    MU_REPORT();
    printf("End of Argb test \n");
    
    return minunit_fail;
}
