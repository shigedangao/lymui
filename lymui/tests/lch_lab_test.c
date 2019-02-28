//
//  lch_lab_test.c
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
#include "lchlab.h"

MU_TEST(lchlab_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.1161;
    xyz->y = 0.0497;
    xyz->z = 0.5376;
    
    LchLab *lch = getLchFromLab(xyz);
    
    mu_assert_double_eq(26.65, roundup(lch->l, 100));
    mu_assert_double_eq(106.19, roundup(lch->c, 100));
    mu_assert_double_eq(307.24, roundup(lch->h, 100));

    free(xyz);
    free(lch);
}

MU_TEST(lchlab_bright_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.9505;
    xyz->y = 1.0;
    xyz->z = 1.0888;
    
    LchLab *lch = getLchFromLab(xyz);
    
    mu_assert_double_eq(100.0, roundup(lch->l, 100));
    mu_assert_double_eq(0.006, roundup(lch->c, 1000));
    mu_assert_double_eq(19.25, roundup(lch->h, 100));
    
    free(xyz);
    free(lch);
}

MU_TEST(lchlab_dark_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
    
    LchLab *lch = getLchFromLab(xyz);
    
    mu_assert_double_eq(0.0, lch->l);
    mu_assert_double_eq(0.0, lch->c);
    mu_assert_double_eq(0.0, lch->h);
    
    free(xyz);
    free(lch);
}

MU_TEST(lchlab_empty_params) {
    LchLab *lch = getLchFromLab(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, lch->error);
    
    free(lch);
}

MU_TEST(xyz_creation) {
    Xyz *xyz = malloc(sizeof(Xyz));
    xyz->x = 0.1161;
    xyz->y = 0.0497;
    xyz->z = 0.5376;
    
    LchLab *lch = getLchFromLab(xyz);
    Xyz *nXyz = getXyzFromLchlab(lch);
    
    mu_assert_double_eq(0.1161, roundup(xyz->x, 10000));
    mu_assert_double_eq(0.0497, roundup(xyz->y, 10000));
    mu_assert_double_eq(0.5376, roundup(xyz->z, 10000));
    
    free(xyz);
    free(lch);
    free(nXyz);
}

MU_TEST(xyz_empty_params) {
    Xyz *xyz = getXyzFromLchlab(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, xyz->error);
    
    free(xyz);
}

MU_TEST_SUITE(lchlab_suite) {
    // Xyz -> LchLab
    MU_RUN_TEST(lchlab_creation);
    MU_RUN_TEST(lchlab_bright_creation);
    MU_RUN_TEST(lchlab_dark_creation);
    MU_RUN_TEST(lchlab_empty_params);
    
    // LchLab -> Xyz
    MU_RUN_TEST(xyz_creation);
    MU_RUN_TEST(xyz_empty_params);
}

void wrapLchLabTest() {
    MU_RUN_SUITE(lchlab_suite);
    MU_REPORT();
    printf("End of LCH_LAB test \n");
}
