//
//  xyz_test.c
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
#include "helper.h"

MU_TEST(xyz_srgb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    
    mu_assert_double_eq(0.0349, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0172, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.1097, roundup(xyz->z, 10000));

    free(rgb);
    free(xyz);
}

MU_TEST(xyz_argb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, adobeRgb);
    
    mu_assert_double_eq(0.0376, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0174, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.1138, roundup(xyz->z, 10000));
    
    free(rgb);
    free(xyz);
}

MU_TEST(xyz_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *Sxyz = getXyzFromRgb(rgb, srgb);
    Xyz *Axyz = getXyzFromRgb(rgb, srgb);
    
    mu_assert_double_eq(0.0, Sxyz->x);
    mu_assert_double_eq(0.0, Sxyz->y);
    mu_assert_double_eq(0.0, Sxyz->z);
    mu_assert_double_eq(0.0, Axyz->x);
    mu_assert_double_eq(0.0, Axyz->y);
    mu_assert_double_eq(0.0, Axyz->z);
    
    free(rgb);
    free(Sxyz);
    free(Axyz);
}

MU_TEST(xyz_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *Sxyz = getXyzFromRgb(rgb, srgb);
    Xyz *Axyz = getXyzFromRgb(rgb, adobeRgb);
    
    mu_assert_double_eq(0.95047, roundup(Sxyz->x, 1000000));
    mu_assert_double_eq(1.0, roundup(Sxyz->y, 1000000));
    mu_assert_double_eq(1.08883, roundup(Sxyz->z, 1000000));
    
    mu_assert_double_eq(0.95047, roundup(Axyz->x, 1000000));
    mu_assert_double_eq(1.0, roundup(Axyz->y, 1000000));
    mu_assert_double_eq(1.08883, roundup(Axyz->z, 1000000));
    
    free(rgb);
    free(Sxyz);
    free(Axyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromRgb(NULL, srgb);
    
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    free(xyz);
}

MU_TEST(rgb_srgb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Rgb *generated = getRgbFromXyz(xyz, srgb);
    
    mu_assert_int_eq(rgb->r, generated->r);
    mu_assert_int_eq(rgb->g, generated->g);
    mu_assert_int_eq(rgb->b, generated->b);
    
    free(rgb);
    free(xyz);
    free(generated);
}

MU_TEST(rgb_argb_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, adobeRgb);
    Rgb *generated = getRgbFromXyz(xyz, adobeRgb);
    
    mu_assert_int_eq(rgb->r, generated->r);
    mu_assert_int_eq(rgb->g, generated->g);
    mu_assert_int_eq(rgb->b, generated->b);
    
    free(rgb);
    free(xyz);
    free(generated);
}

MU_TEST(rgb_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *sXyz = getXyzFromRgb(rgb, srgb);
    Xyz *aXyz = getXyzFromRgb(rgb, adobeRgb);
    
    Rgb *sDark = getRgbFromXyz(sXyz, srgb);
    Rgb *aDark = getRgbFromXyz(aXyz, adobeRgb);

    mu_assert_int_eq(rgb->r, sDark->r);
    mu_assert_int_eq(rgb->g, sDark->g);
    mu_assert_int_eq(rgb->b, sDark->b);
    
    mu_assert_int_eq(rgb->r, aDark->r);
    mu_assert_int_eq(rgb->g, aDark->g);
    mu_assert_int_eq(rgb->b, aDark->b);
    
    free(rgb);
    free(sXyz);
    free(aXyz);
    free(sDark);
    free(aDark);
}


MU_TEST(rgb_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *sXyz = getXyzFromRgb(rgb, srgb);
    Xyz *aXyz = getXyzFromRgb(rgb, adobeRgb);
    
    Rgb *sBright = getRgbFromXyz(sXyz, srgb);
    Rgb *aBright = getRgbFromXyz(aXyz, adobeRgb);
    
    mu_assert_int_eq(rgb->r, sBright->r);
    mu_assert_int_eq(rgb->g, sBright->g);
    mu_assert_int_eq(rgb->b, sBright->b);
    
    mu_assert_int_eq(rgb->r, aBright->r);
    mu_assert_int_eq(rgb->g, aBright->g);
    mu_assert_int_eq(rgb->b, aBright->b);
    
    free(rgb);
    free(sXyz);
    free(aXyz);
    free(sBright);
    free(aBright);
}

MU_TEST(rgb_empty_params) {
    Rgb *rgb = getRgbFromXyz(NULL, adobeRgb);
    mu_assert_string_eq(NULL_INPUT_PARAM, rgb->error);
    
    free(rgb);
}

MU_TEST_SUITE(xyz_suite) {
    // Rgb -> Xyz
    MU_RUN_TEST(xyz_srgb_creation);
    MU_RUN_TEST(xyz_argb_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_empty_params);
    
    // Xyz -> Rgb
    MU_RUN_TEST(rgb_srgb_creation);
    MU_RUN_TEST(rgb_argb_creation);
    MU_RUN_TEST(rgb_dark_creation);
    MU_RUN_TEST(rgb_bright_creation);
    MU_RUN_TEST(rgb_empty_params);
}

void wrapXyzTest() {
    MU_RUN_SUITE(xyz_suite);
    MU_REPORT();
    printf("End of XYZ test \n");
}

