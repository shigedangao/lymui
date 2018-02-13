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

int main(int argc, const char * argv[]) {
    int results = run_test();
    
    if (results == OK)
        printf("Test passings \n");
    else
        printf("Test failed. \n");
    
    return results;
}

