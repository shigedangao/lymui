//
//  srgb_test.c
//  lymui
//
//  Created by Marc on 13/03/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "rgb.h"
#include "xyz.h"
#include "srgb.h"
#include "helper.h"

MU_TEST(srgb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSrgbFromXyz(xyz);
    
    mu_assert_double_eq(0.196, roundup(srgb->r, 1000));
    mu_assert_double_eq(0.039, roundup(srgb->g, 1000));
    mu_assert_double_eq(0.373, roundup(srgb->b, 1000));
    
    free(rgb);
    free(xyz);
    free(srgb);
}

MU_TEST(srgb_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSrgbFromXyz(xyz);
    
    mu_assert_double_eq(0.0, roundup(srgb->r, 1000));
    mu_assert_double_eq(0.0, roundup(srgb->g, 1000));
    mu_assert_double_eq(0.0, roundup(srgb->b, 1000));
    
    free(rgb);
    free(xyz);
    free(srgb);
}

MU_TEST(srgb_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSrgbFromXyz(xyz);
    
    mu_assert_double_eq(1.0, roundup(srgb->r, 1000));
    mu_assert_double_eq(1.0, roundup(srgb->g, 1000));
    mu_assert_double_eq(1.0, roundup(srgb->b, 1000));
    
    free(rgb);
    free(xyz);
    free(srgb);
}

MU_TEST(srgb_empty_params) {
    SRgb *srgb = getSrgbFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, srgb->error);
    
    free(srgb);
}

MU_TEST(xyz_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0376;
    xyz->y = 0.0173;
    xyz->z = 0.1138;
    
    SRgb *srgb = getSrgbFromXyz(xyz);
    Xyz *nXyz = getXyzFromSrgb(srgb);
    
    mu_assert_double_eq(xyz->x, roundup(nXyz->x, 10000));
    mu_assert_double_eq(xyz->y, roundup(nXyz->y, 10000));
    mu_assert_double_eq(xyz->z, roundup(nXyz->z, 10000));
    
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSrgbFromXyz(xyz);
    Xyz *nXyz = getXyzFromSrgb(srgb);

    mu_assert_double_eq(0.95047, roundup(nXyz->x, 100000));
    mu_assert_double_eq(1.0000, roundup(nXyz->y, 1000));
    mu_assert_double_eq(1.08883, roundup(nXyz->z, 100000));
    
    free(rgb);
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    SRgb *srgb = getSrgbFromXyz(xyz);
    Xyz *nXyz = getXyzFromSrgb(srgb);
    
    mu_assert_double_eq(xyz->x, nXyz->x);
    mu_assert_double_eq(xyz->y, nXyz->y);
    mu_assert_double_eq(xyz->z, nXyz->z);
    
    free(rgb);
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromSrgb(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(srgb_suite) {
    // Xyz -> Srgb
    MU_RUN_TEST(srgb_creation);
    MU_RUN_TEST(srgb_dark_creation);
    MU_RUN_TEST(srgb_bright_creation);
    MU_RUN_TEST(srgb_empty_params);
    
    // Srgb -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_empty_params);
}

int wrapSrgbTest() {
    MU_RUN_SUITE(srgb_suite);
    MU_REPORT();
    printf("End of Srgb test \n");
    
    return minunit_fail;
}
