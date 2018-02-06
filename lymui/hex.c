//
//  hex.c
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "hex.h"
#include "helper.h"
#include <stdlib.h>
#include <string.h>

// Get Hex From RGB
char * getHexFromRGB(struct Rgb *c) {
    char *r = ushortToHex(c->r);
    char *g = ushortToHex(c->g);
    char *b = ushortToHex(c->b);
    
    // create a char array of hex value
    char *hex = malloc(sizeof(char) * 5);
    snprintf(hex, sizeof(hex), "%s%s%s", r, g, b);
    return hex;
}
