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
    // Create suite case
    
    wrapRgbTest();
    wrapHexTest();
    wrapHueTest();
    wrapCymkTest();
    wrapYcbcrTest();
    wrapHslTest();
    wrapHsvTest();
    wrapYuvTest();
    wrapGrayScaleTest();
    wrapHclTest();
    wrapHwbTest();
    
    wrapXyzTest();
    wrapArgbTest();
    wrapSrgbTest();
    wrapLabTest();
    wrapHLabTest();
    wrapLuvTest();
    wrapLchTest();
    wrapLchLabTest();
    wrapXyyTest();
    wrapTslTest();
    
    return 0;
}

