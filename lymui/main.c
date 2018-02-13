//
//  main.c
//  lymui
//
//  Created by Marc on 05/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cunit.h>
#include <ctest.h>
#include <ctcase.h>
#include "rgb.h"
#include "hex.h"
#include "ycbcr.h"

#define OK (0)
#define FAIL (-1)

// For instance the test are done in the main file
// Test rgb creation
int test_rgb_creation() {
    uint8_t arr[] = {0, 255, 255};
    struct Rgb *rgb = makeRGB(arr);
    
    if (rgb->b != 255 && rgb->g != 255 && rgb->r != 0) {
        return FAIL;
    }
    
    return OK;
}

int run_test() {
    if (FAIL == test_rgb_creation())
        return FAIL;
    
    return OK;
}

// Test Rgb Creation
ctest_return_t testRgbCreation(ctest_t *test, void *arg) {
    uint8_t uc[] = {0, 100, 200};
    struct Rgb *rgb = makeRGB(uc);
    
    CTAssertEqual(test, 0, rgb->r, "%d is not equal to %d", 0, rgb->r);
    CTAssertEqual(test, 100, rgb->g, "%d is not equal to %d", 0, rgb->g);
    CTAssertEqual(test, 200, rgb->b, "%d is not equal to %d", 0, rgb->b);

    free(rgb);
}


int main(int argc, const char * argv[]) {
    // Create suite case
    ctsuite_t *suite = ctsuite("Lymui test");
    ctcase_t  *casetest  = ctcase("Rgb creation test case");
    
    // Create test case for rgb test
    ctest_t   *rgbCreation = ctest("Create RGB from UINT_8T Array", testRgbCreation, NULL);
    // Add test to test case
    ctctestadd(casetest, rgbCreation);
    // Launch suite
    ctscaseadd(suite, casetest);
    ctsrun(suite);
    
    int results = run_test();
    
    if (results == OK)
        printf("Test passings \n");
    else
        printf("Test failed. \n");
    
    return results;
}

