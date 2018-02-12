//
//  main.c
//  lymui
//
//  Created by Marc on 05/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "rgb.h"
#include "hex.h"
#include "ycbcr.h"

int main(int argc, const char * argv[]) {
    uint8_t c[] = {0, 155, 205};
    struct Rgb *color = makeRGB(c);
    
    char *hex = getHexFromRGB(color);
    printf("\ngreen is %i", color->g);
    printf("\nhex is %s\n", hex);
    
    uint8_t * cv = getRawRGBArrayValueFromHex(hex);
    struct Rgb *otherc = makeRGBFromArrPointer(cv);
    printf("\n blue value from created struct from arr is %i", otherc->b);
    
    struct Ycbcr *cb = makeYcbcr(otherc);
    printf("\n ycbcr y value is %f", cb->cb);
    
    uint8_t * rbgycb = getRawRGBArrayValueFromYcbcr(cb);
    printf("\n rgb from ycbcr value is %u\n", rbgycb[2]);

    
    return 0;
}
