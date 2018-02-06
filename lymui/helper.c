//
//  helper.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "helper.h"
#include <stdlib.h>

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
