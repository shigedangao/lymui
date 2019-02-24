//
//  hue_test.c
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cunit.h>
#include <minunit.h>
#include "test_header.h"
#include "rgb.h"
#include "hue.h"

MU_TEST(hue_creation) {
    uint8_t cvalue[3] = {255, 255, 255};
    Rgb *rgb  = makeRGB(cvalue, 3);
    
    Hue hue = getHueFromRgb(rgb);
    mu_assert_double_eq(0.0, hue);
    
    free(rgb);
}

MU_TEST(hue_purple_creation) {
    uint8_t cvalue[3] = {255, 100, 255};
    Rgb *rgb = makeRGB(cvalue, 3);
    
    Hue hue = getHueFromRgb(rgb);
    mu_assert_double_eq(300.0, roundup(hue, 10));
    
    free(rgb);
}

MU_TEST(hue_sunny_creation) {
    uint8_t cvalue[3] = {50, 10, 232};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    Hue hue = getHueFromRgb(rgb);
    mu_assert_double_eq(251.0, roundup(hue, 10));
    
    free(rgb);
}

MU_TEST(hue_foggy_creation) {
    uint8_t cvalue[3] = {222, 102, 30};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    Hue hue = getHueFromRgb(rgb);
    mu_assert_double_eq(23.0, roundup(hue, 10));

    free(rgb);
}

MU_TEST(hue_rainy_creation) {
    uint8_t cvalue[3] = {244, 100, 200};
    Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
    
    Hue hue = getHueFromRgb(rgb);
    mu_assert_double_eq(318.0, roundup(hue, 10));

    free(rgb);
}

MU_TEST(hue_empty_param) {
    Hue hue = getHueFromRgb(NULL);
    mu_assert_double_eq(0.0, hue);
}

MU_TEST_SUITE(hue_suite) {
    MU_RUN_TEST(hue_creation);
    MU_RUN_TEST(hue_purple_creation);
    MU_RUN_TEST(hue_sunny_creation);
    MU_RUN_TEST(hue_foggy_creation);
    MU_RUN_TEST(hue_rainy_creation);
    MU_RUN_TEST(hue_empty_param);
}

void wrapHueTest() {
    MU_RUN_SUITE(hue_suite);
    MU_REPORT();
    printf("End of Hue test \n");
}
