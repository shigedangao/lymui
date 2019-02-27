//
//  luv_test.c
//  lymui
//
//  Created by Marc on 10/04/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "xyz.h"
#include "luv.h"
#include "helper.h"

MU_TEST(luv_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 10;
    rgb->b = 95;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    mu_assert_double_eq(9.603, roundup(luv->l, 1000));
    mu_assert_double_eq(-2.851, roundup(luv->u, 1000));
    mu_assert_double_eq(-34.829, roundup(luv->v, 1000));

    free(rgb);
    free(xyz);
    free(luv);
}

MU_TEST(luv_superior_y_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 200;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    mu_assert_double_eq(96.417, roundup(luv->l, 1000));
    mu_assert_double_eq(-27.735, roundup(luv->u, 1000));
    mu_assert_double_eq(-5.983, roundup(luv->v, 1000));
    
    free(rgb);
    free(xyz);
    free(luv);
}

MU_TEST(luv_inferior_y_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 5;
    rgb->g = 1;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    mu_assert_double_eq(0.488, roundup(luv->l, 1000));
    mu_assert_double_eq(0.809, roundup(luv->u, 1000));
    mu_assert_double_eq(0.442, roundup(luv->v, 1000));
    
    free(rgb);
    free(xyz);
    free(luv);
}

MU_TEST(luv_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    mu_assert_double_eq(100.0, roundup(luv->l, 1000));
    mu_assert_double_eq(0.0, roundup(luv->u, 1000));
    mu_assert_double_eq(0.0, roundup(luv->v, 1000));
    
    free(rgb);
    free(xyz);
    free(luv);
}

MU_TEST(luv_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    
    mu_assert_double_eq(0.0, roundup(luv->l, 1000));
    mu_assert_double_eq(0.0, roundup(luv->u, 1000));
    mu_assert_double_eq(0.0, roundup(luv->v, 1000));
    
    free(rgb);
    free(xyz);
    free(luv);
}

MU_TEST(luv_empty_params) {
    Luv *luv = getLuvFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, luv->error);
    
    free(luv);
}

MU_TEST(xyz_creation) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 5.0;
    luv->u = 1.0;
    luv->v = 0.0;
    
    Xyz *xyz = getXyzFromLuv(luv);
    
    mu_assert_double_eq(0.00567, roundup(xyz->x, 100000));
    mu_assert_double_eq(0.00554, roundup(xyz->y, 100000));
    mu_assert_double_eq(0.00589, roundup(xyz->z, 100000));
    
    free(xyz);
}

MU_TEST(xyz_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Luv *luv = getLuvFromXyz(xyz);
    // get back the xyz
    Xyz *nXyz = getXyzFromLuv(luv);
    
    mu_assert_double_eq(0.9505, roundup(nXyz->x, 10000));
    mu_assert_double_eq(1.0000, roundup(nXyz->y, 10000));
    mu_assert_double_eq(1.0888, roundup(nXyz->z, 10000));
    
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
    Luv *luv = getLuvFromXyz(xyz);
    // get back the xyz
    Xyz *nXyz = getXyzFromLuv(luv);
    
    mu_assert_double_eq(0.0, roundup(nXyz->x, 10));
    mu_assert_double_eq(0.0, roundup(nXyz->y, 10));
    mu_assert_double_eq(0.0, roundup(nXyz->z, 10));
    
    free(rgb);
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromLuv(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(luv_suite) {
    // Xyz -> Luv
    MU_RUN_TEST(luv_creation);
    MU_RUN_TEST(luv_superior_y_creation);
    MU_RUN_TEST(luv_bright_creation);
    MU_RUN_TEST(luv_inferior_y_creation);
    MU_RUN_TEST(luv_dark_creation);
    MU_RUN_TEST(luv_empty_params);
    
    // Luv -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_empty_params);
}

void wrapLuvTest() {
    MU_RUN_SUITE(luv_suite);
    MU_REPORT();
    printf("End of Luv test \n");
}

