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
    // Create suite case
    
    suites[0] = wrapRgbTest();
    suites[1] = wrapHexTest();
    suites[2] = wrapHueTest();
    suites[3] = wrapCymkTest();
    suites[4] = wrapYcbcrTest();
    suites[5] = wrapHslTest();
    suites[6] = wrapHsvTest();
    suites[7] = wrapYuvTest();
    suites[8] = wrapGrayScaleTest();
    suites[9] = wrapHclTest();
    suites[10] = wrapHwbTest();
    
    suites[11] = wrapXyzTest();
    suites[12] = wrapArgbTest();
    suites[13] = wrapSrgbTest();
    suites[14] = wrapLabTest();
    suites[15] = wrapHLabTest();
    suites[16] = wrapLuvTest();
    suites[17] = wrapLchTest();
    suites[18] = wrapLchLabTest();
    suites[19] = wrapXyyTest();
    suites[20] = wrapTslTest();

    while (idx < sizeof(suites) / sizeof(suites[0])) {
        if (suites[idx]) {
            fail = -1;
            idx = sizeof(suites) + 2;
        }
        
        idx++;
    }
    
    return fail;
}

