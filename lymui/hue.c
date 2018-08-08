//
//  hue.c
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "hue.h"
#include "helper.h"

Hue getHueFromRgb(Rgb *rgb) {
    if (rgb == NULL)
        return 0.0f;
    
    // might be better to have a getMinMax value for the uint directly
    float max = fmaxf(fmaxf(rgb->r, rgb->g), rgb->b);
    float min = fminf(fminf(rgb->r, rgb->g), rgb->b);
    
    // in case of min == max then return 0
    if (max == min)
        return 0.0f;
    
    // Create the hue variable here
    Hue hue = 0.0f;
    // cast the value to a float no repetition..
    float _r = (float) rgb->r;
    float _g = (float) rgb->g;
    float _b = (float) rgb->b;

    if (max == rgb->r) {
        hue = (_g - _b) / (max - min);
    } else if (max == rgb->g) {
        hue = 2.0f + (_b - _r) / (max - min);
    } else {
        hue = 4.0f + (_r - _g) / (max - min);
    }
     
    hue = hue * 60;
    
    if (hue < 0.0f)
        hue = hue + 360.0f;
    
    return roundf(hue);
}
