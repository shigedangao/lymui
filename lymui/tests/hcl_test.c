//
//  hcl_test.c
//  lymui
//
//  Created by Marc Intha on 20/02/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <minunit.h>
#include "test_header.h"
#include "hcl.h"
#include "luv.h"

MU_TEST(hcl_creation) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 9.603;
    luv->u = -2.851;
    luv->v = -34.829;
    
    Hcl *hcl = getHclFromLuv(luv);
    
    mu_assert_double_eq(184.68, roundup(hcl->h, 1000));
    mu_assert_double_eq(34.946, roundup(hcl->c, 1000));
    mu_assert_double_eq(9.603, roundup(hcl->l, 1000));

    
    free(hcl);
}

MU_TEST(hcl_bright_creation) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 100.0;
    luv->u = 0.0;
    luv->v = 0.0;
    
    Hcl *hcl = getHclFromLuv(luv);
    
    mu_assert_double_eq(0.0, roundup(hcl->h, 1000));
    mu_assert_double_eq(0.0, roundup(hcl->c, 1000));
    mu_assert_double_eq(100.0, roundup(hcl->l, 1000));

    free(hcl);
}

MU_TEST(hcl_dark_creation) {
    Luv *luv = malloc(sizeof(Luv));
    luv->l = 0.0;
    luv->u = 0.0;
    luv->v = 0.0;
    
    Hcl *hcl = getHclFromLuv(luv);
    
    mu_assert_double_eq(0.0, roundup(hcl->h, 1000));
    mu_assert_double_eq(0.0, roundup(hcl->c, 1000));
    mu_assert_double_eq(0.0, roundup(hcl->l, 1000));

    free(hcl);
}

MU_TEST(hcl_null_creation) {
    Hcl *hcl = getHclFromLuv(NULL);
    
    mu_assert_string_eq(hcl->error, "The imput param is empty");
    
    free(hcl);
}

MU_TEST(luv_creation) {
    Hcl *hcl = malloc(sizeof(Hcl));
    hcl->h = 184.68;
    hcl->c = 34.946;
    hcl->l = 9.603;
    
    Luv *luv = getLuvFromHcl(hcl);
    
    mu_assert_double_eq(9.603, roundup(luv->l, 1000));
    mu_assert_double_eq(-2.851, roundup(luv->u, 1000));
    mu_assert_double_eq(-34.829, roundup(luv->v, 1000));
}

MU_TEST(luv_bright_creation) {
    Hcl *hcl = malloc(sizeof(Hcl));
    hcl->h = 0.0;
    hcl->c = 0.0;
    hcl->l = 100.0;
    
    Luv *luv = getLuvFromHcl(hcl);

    mu_assert_double_eq(100.0, roundup(luv->l, 1000));
    mu_assert_double_eq(0.0, roundup(luv->u, 1000));
    mu_assert_double_eq(0.0, roundup(luv->v, 1000));

    free(luv);
}

MU_TEST(luv_dark_creation) {
    Hcl *hcl = malloc(sizeof(Hcl));
    hcl->h = 0.0;
    hcl->c = 0.0;
    hcl->l = 0.0;
    
    Luv *luv = getLuvFromHcl(hcl);
    
    mu_assert_double_eq(0.0, roundup(luv->l, 1000));
    mu_assert_double_eq(0.0, roundup(luv->u, 1000));
    mu_assert_double_eq(0.0, roundup(luv->v, 1000));
    
    free(luv);
}

MU_TEST(luv_null_creation) {
    Luv *luv = getLuvFromHcl(NULL);
    
    mu_assert_string_eq(luv->error, "The imput param is empty");
    
    free(luv);
}

MU_TEST_SUITE(hcl_suite) {
    MU_RUN_TEST(hcl_creation);
    MU_RUN_TEST(hcl_bright_creation);
    MU_RUN_TEST(hcl_dark_creation);
    MU_RUN_TEST(hcl_null_creation);
    
    MU_RUN_TEST(luv_creation);
    MU_RUN_TEST(luv_bright_creation);
    MU_RUN_TEST(luv_dark_creation);
    MU_RUN_TEST(luv_null_creation);
}

// use minunit_status
void wrapHclTest() {
    MU_RUN_SUITE(hcl_suite);
    MU_REPORT();
}
