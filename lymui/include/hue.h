//
//  hue.h
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef hue_h
#define hue_h

#include <stdio.h>
#include "rgb.h"

/*!
 * @discussion Create a Hue from a struct Rgb pointer
 * @param rgb an rgb struct pointer
 * @return a float describing the Hue
 */
float getHueFromRgb(struct Rgb *rgb);

#endif /* hue_h */
