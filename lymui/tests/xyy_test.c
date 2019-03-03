//
//  xyy_test.c
//  lymui
//
//  Created by Marc on 14/05/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "errors.h"
#include "xyz.h"
#include "xyy.h"

MU_TEST(xyy_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.9;
    xyz->y = 0.8;
    xyz->z = 0.7;
    
    Xyy *xyy = getXyyFromXyz(xyz);
    
    mu_assert_double_eq(0.375, roundup(xyy->x, 1000));
    mu_assert_double_eq(0.333, roundup(xyy->y, 1000));
    mu_assert_double_eq(0.8, roundup(xyy->Y, 100));
    
    free(xyy);
    free(xyz);
}

MU_TEST(xyy_dark_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
    
    Xyy *xyy = getXyyFromXyz(xyz);
    
    mu_assert_double_eq(0.313, roundup(xyy->x, 1000));
    mu_assert_double_eq(0.329, roundup(xyy->y, 1000));
    mu_assert_double_eq(0.0, xyy->Y);
    
    free(xyy);
    free(xyz);
}

MU_TEST(xyy_bright_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.95047;
    xyz->y = 1.0;
    xyz->z = 1.08883;
    
    Xyy *xyy = getXyyFromXyz(xyz);
    
    mu_assert_double_eq(0.313, roundup(xyy->x, 1000));
    mu_assert_double_eq(0.329, roundup(xyy->y, 1000));
    mu_assert_double_eq(1.0, xyy->Y);
    
    free(xyy);
    free(xyz);
}

MU_TEST(xyy_empty_params) {
    Xyy *xyy = getXyyFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyy->error);
}

MU_TEST(xyz_creation) {
    Xyy *xyy = malloc(sizeof(Xyy));
    xyy->x = 0.375;
    xyy->y = 0.333;
    xyy->Y = 0.8;
    
    Xyz *xyz = getXyzFromXyy(xyy);
    
    mu_assert_double_eq(0.9, roundup(xyz->x, 10));
    mu_assert_double_eq(0.8, roundup(xyz->y, 10));
    mu_assert_double_eq(0.7, roundup(xyz->z, 10));
    
    free(xyz);
}

MU_TEST(xyz_bright_creation) {
    Xyy *xyy = malloc(sizeof(Xyy));
    xyy->x = 0.313;
    xyy->y = 0.329;
    xyy->Y = 1.0;
    
    Xyz *xyz = getXyzFromXyy(xyy);
    
    mu_assert_double_eq(0.95, roundup(xyz->x, 100));
    mu_assert_double_eq(1.0, roundup(xyz->y, 100));
    mu_assert_double_eq(1.09, roundup(xyz->z, 100));
    
    free(xyz);
}

MU_TEST(xyz_dark_creation) {
    Xyy *xyy = malloc(sizeof(Xyy));
    xyy->x = 0.313;
    xyy->y = 0.329;
    xyy->Y = 0.0;
    
    Xyz *xyz = getXyzFromXyy(xyy);
    
    mu_assert_double_eq(0.0, xyz->x);
    mu_assert_double_eq(0.0, xyz->y);
    mu_assert_double_eq(0.0, xyz->z);
    
    free(xyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromXyy(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(xyy_suite) {
    // Xyz -> Xyy
    MU_RUN_TEST(xyy_creation);
    MU_RUN_TEST(xyy_dark_creation);
    MU_RUN_TEST(xyy_bright_creation);
    MU_RUN_TEST(xyy_empty_params);
    
    // Xyy -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_bright_creation);
    MU_RUN_TEST(xyz_dark_creation);
    MU_RUN_TEST(xyz_empty_params);
}

int wrapXyyTest() {
    MU_RUN_SUITE(xyy_suite);
    MU_REPORT();
    printf("End of Xyy test \n");
    
    return minunit_fail;
}
