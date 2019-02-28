//
//  lch_test.c
//  lymui
//
//  Created by Marc on 11/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "lch.h"

MU_TEST(lch_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51;
    xyz->y = 0.52;
    xyz->z = 0.510;
    
    Lch *lch = getLchFromXyz(xyz);
    
    mu_assert_double_eq(77.28, roundup(lch->l, 100));
    mu_assert_double_eq(12.0, roundup(lch->c, 100));
    mu_assert_double_eq(37.5, roundup(lch->h, 100));
    
    free(xyz);
    free(lch);
}

MU_TEST(lch_full_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 1.0;
    xyz->y = 1.0;
    xyz->z = 1.0;
    
    Lch *lch = getLchFromXyz(xyz);
    
    mu_assert_double_eq(100.0, roundup(lch->l, 100));
    mu_assert_double_eq(17.9, roundup(lch->c, 100));
    mu_assert_double_eq(22.86, roundup(lch->h, 100));
    
    free(xyz);
    free(lch);
}

MU_TEST(lch_bright_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.950470;
    xyz->y = 1.0;
    xyz->z = 1.088830;
    
    Lch *lch = getLchFromXyz(xyz);
    
    mu_assert_double_eq(100.0, roundup(lch->l, 100));
    mu_assert_double_eq(0.0, roundup(lch->c, 100));
    mu_assert_double_eq(360.0, roundup(lch->h, 100));
    
    free(xyz);
    free(lch);
}

MU_TEST(lch_dark_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
    
    Lch *lch = getLchFromXyz(xyz);
    
    mu_assert_double_eq(0.0, roundup(lch->l, 100));
    mu_assert_double_eq(0.0, roundup(lch->c, 100));
    mu_assert_double_eq(180.0, roundup(lch->h, 100));
    
    free(xyz);
    free(lch);
}

MU_TEST(lch_empty_params) {
    Lch *lch = getLchFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, lch->error);
    
    free(lch);
}

MU_TEST(xyz_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.51;
    xyz->y = 0.52;
    xyz->z = 0.510;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    mu_assert_double_eq(0.510, roundup(nXyz->x, 100));
    mu_assert_double_eq(0.520, roundup(nXyz->y, 100));
    mu_assert_double_eq(0.510, roundup(nXyz->z, 100));
    
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_bright_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.950470;
    xyz->y = 1.0;
    xyz->z = 1.088830;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    mu_assert_double_eq(0.950, roundup(nXyz->x, 1000));
    mu_assert_double_eq(1.0, roundup(nXyz->y, 1000));
    mu_assert_double_eq(1.089, roundup(nXyz->z, 1000));
    
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_dark_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
    
    Lch *lch  = getLchFromXyz(xyz);
    Xyz *nXyz = getXyzFromLch(lch);
    
    mu_assert_double_eq(0.0, nXyz->x);
    mu_assert_double_eq(0.0, nXyz->y);
    mu_assert_double_eq(0.0, nXyz->z);
    
    free(xyz);
    free(nXyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromLch(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(lch_suite) {
    // Xyz -> Lch
    MU_RUN_TEST(lch_creation);
    MU_RUN_TEST(lch_full_creation);
    MU_RUN_TEST(lch_bright_creation);
    MU_RUN_TEST(lch_dark_creation);
    MU_RUN_TEST(lch_empty_params);
    
    // Lch -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_empty_params);
}

void wrapLchTest() {
    MU_RUN_SUITE(lch_suite);
    MU_REPORT();
    printf("End of LCH test \n");
}
