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
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "helper.h"
#include "xyz.h"
#include "lab.h"

MU_TEST(lab_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    mu_assert_double_eq(26.26, roundup(lab->l, 100));
    mu_assert_double_eq(63.50, roundup(lab->a, 100));
    mu_assert_double_eq(-83.43, roundup(lab->b, 100));

    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(lab_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    mu_assert_double_eq(0.0, lab->l);
    mu_assert_double_eq(0.0, lab->a);
    mu_assert_double_eq(0.0, lab->b);
    
    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(lab_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    Lab *lab = getLabFromXyz(xyz);
    
    mu_assert_double_eq(100.0, roundup(lab->l, 100));
    mu_assert_double_eq(0.0, roundup(lab->a, 100));
    mu_assert_double_eq(0.0, roundup(lab->b, 100));
    
    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(lab_empty_params) {
    Lab *lab = getLabFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, lab->error);
    
    free(lab);
}

MU_TEST(xyz_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    Xyz *xyz  = getXyzFromRgb(rgb, srgb);
    Lab *lab  = getLabFromXyz(xyz);
    Xyz *nXyz = getXyzFromLab(lab);
    
    mu_assert_double_eq(xyz->x, nXyz->x);
    mu_assert_double_eq(xyz->y, nXyz->y);
    mu_assert_double_eq(xyz->z, nXyz->z);
    
    free(rgb);
    free(xyz);
    free(nXyz);

}

MU_TEST(xyz_small_creation) {
    Lab *lab  = malloc(sizeof(Lab));
    lab->l = 26.65;
    lab->a = 64.26;
    lab->b = -84.54;
    
    Xyz *xyz = getXyzFromLab(lab);
    
    mu_assert_double_eq(0.1161, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0497, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.5376, roundup(xyz->z, 10000));

    free(xyz);
}

MU_TEST(xyz_dark_creation) {
    Lab *lab  = malloc(sizeof(Lab));
    lab->l = 0.0;
    lab->a = 0.0;
    lab->b = 0.0;
    
    Xyz *xyz = getXyzFromLab(lab);
    
    mu_assert_double_eq(0.0, roundup(xyz->x, 10));
    mu_assert_double_eq(0.0, roundup(xyz->y, 10));
    mu_assert_double_eq(0.0, roundup(xyz->z, 10));
    
    free(xyz);
}

MU_TEST(xyz_bright_creation) {
    Lab *lab  = malloc(sizeof(Lab));
    lab->l = 100.0;
    lab->a = 0.0;
    lab->b = 0.0;
    
    Xyz *xyz = getXyzFromLab(lab);
    
    mu_assert_double_eq(0.9505, roundup(xyz->x, 10000));
    mu_assert_double_eq(1.0000, roundup(xyz->y, 10000));
    mu_assert_double_eq(1.0888, roundup(xyz->z, 10000));
    
    free(xyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromLab(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(lab_suite) {
    // Xyz -> Lab
    MU_RUN_TEST(lab_creation);
    MU_RUN_TEST(lab_dark_creation);
    MU_RUN_TEST(lab_bright_creation);
    MU_RUN_TEST(lab_empty_params);
    
    // Lab -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_small_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_empty_params);
}

int wrapLabTest() {
    MU_RUN_SUITE(lab_suite);
    MU_REPORT();
    printf("End of Lab test \n");
    
    return minunit_fail;
}
