//
//  darken.h
//  lymui
//
//  Created by Marc Intha on 17/03/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#ifndef darken_h
#define darken_h

#include <stdio.h>
#include "hsl.h"
#include "hsv.h"
#include "rgb.h"

Hsl **getDarkerShade(Rgb *rgb, int shadeNb);

#endif /* darken_h */
