//
//  hex.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hex_h
#define hex_h

#include <stdio.h>
#include "rgb.h"

// Get Hex From RGB
// Return --> char array
// Params --> struct pointer Rgb
char * getHexFromRGB(struct Rgb *c);

#endif /* hex_h */
