//
//  helper.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "helper.h"
#include <stdlib.h>

// Global variable of a list of RgbHex
struct RgbHex *list;

// Ushort To Hex
char * ushortToHex(ushort v) {
    if (v > 256)
        return NULL;
    
    char HEX[] = "0123456789ABCDEF";
    char *hexa = malloc(1);
    ushort accum = 2;
    while(accum > 0) {
        hexa[accum - 1] = HEX[(v % 16)];
        v = v / 16;
        accum--;
    }
    
    return hexa;
}

struct RgbHex * getCorrespondingStruct() {
    
    struct RgbHex a = {'A', 10};
    struct RgbHex b = {'B', 11};
    struct RgbHex c = {'C', 12};
    struct RgbHex d = {'D', 13};
    struct RgbHex e = {'E', 14};
    struct RgbHex f = {'F', 15};
    
    if (list == NULL) {
        list = malloc(sizeof (struct RgbHex) * 6);
        list[0] = a;
        list[1] = b;
        list[2] = c;
        list[3] = d;
        list[4] = e;
        list[5] = f;
    }
    
    return list;
};
