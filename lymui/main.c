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
#include "test_header.h"

int main(int argc, const char * argv[]) {
    uint8_t idx = 0;
    int fail = 0;
    int suites[21];
    
    // Rgb case
    suites[0] = wrapRgbTest();
    suites[1] = wrapHexTest();
    suites[2] = wrapHueTest();
    suites[3] = wrapCymkTest();
    suites[4] = wrapYcbcrTest();
    suites[5] = wrapHslTest();
    suites[6] = wrapHsvTest();
    suites[7] = wrapYuvTest();
    suites[8] = wrapGrayScaleTest();
    suites[9] = wrapHwbTest();
    suites[10] = wrapTslTest();

    // Luv case
    suites[11] = wrapHclTest();
    
    // Xyz case
    suites[12] = wrapXyzTest();
    suites[13] = wrapArgbTest();
    suites[14] = wrapSrgbTest();
    suites[15] = wrapLabTest();
    suites[16] = wrapHLabTest();
    suites[17] = wrapLuvTest();
    suites[18] = wrapLchTest();
    suites[19] = wrapLchLabTest();
    suites[20] = wrapXyyTest();

    while (idx < sizeof(suites) / sizeof(suites[0])) {
        if (suites[idx]) {
            fail = -1;
            idx = sizeof(suites) + 2;
        }
        
        idx++;
    }
    
    return fail;
}

