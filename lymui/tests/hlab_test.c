//
//  hlab_test.c
//  lymui
//
//  Created by Marc Intha on 26/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "hunterlab.h"
#include "rgb.h"
#include "errors.h"

MU_TEST(hunterlab_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 50;
    rgb->g = 10;
    rgb->b = 195;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    HLab *lab = getHLabFromXyz(xyz);

    mu_assert_double_eq(21.987, roundup(lab->l, 1000));
    mu_assert_double_eq(55.063, roundup(lab->a, 1000));
    mu_assert_double_eq(-130.759, roundup(lab->b, 1000));
    
    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(hunterlab_dark_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    HLab *lab = getHLabFromXyz(xyz);
    
    mu_assert_double_eq(0.0, roundup(lab->l, 1000));
    mu_assert_double_eq(0.0, roundup(lab->a, 1000));
    mu_assert_double_eq(0.0, roundup(lab->b, 1000));
    
    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(hunterlab_bright_creation) {
    Rgb *rgb = malloc(sizeof(Rgb));
    rgb->r = 255;
    rgb->g = 255;
    rgb->b = 255;
    
    Xyz *xyz = getXyzFromRgb(rgb, srgb);
    HLab *lab = getHLabFromXyz(xyz);

    mu_assert_double_eq(100.0, roundup(lab->l, 1000));
    mu_assert_double_eq(0.0, roundup(lab->a, 1000));
    mu_assert_double_eq(0.0, roundup(lab->b, 1000));
    
    free(rgb);
    free(xyz);
    free(lab);
}

MU_TEST(hlab_empty_params) {
    HLab *lab = getHLabFromXyz(NULL);
    mu_assert_string_eq(NULL_INPUT_PARAM, lab->error);
    
    free(lab);
}

MU_TEST_SUITE(hlab_suite) {
    // Xyz -> HunterLab
    MU_RUN_TEST(hunterlab_creation);
    MU_RUN_TEST(hunterlab_dark_creation);
    MU_RUN_TEST(hunterlab_bright_creation);
    MU_RUN_TEST(hlab_empty_params);
}

int wrapHLabTest() {
    MU_RUN_SUITE(hlab_suite);
    MU_REPORT();
    printf("End of Hunter Lab test \n");
    
    return minunit_fail;
}
