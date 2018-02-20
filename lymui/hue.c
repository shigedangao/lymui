//
//  hue.c
//  lymui
//
//  Created by Marc on 20/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include "hue.h"
#include "helper.h"

float getHueFromRgb(struct Rgb *rgb) {
    if (rgb == NULL)
        return 0.0f;
    
    float * value = malloc(sizeof(float) * 3);
    // add the value of the rgb color
    value[0] = rgb->r;
    value[1] = rgb->g;
    value[2] = rgb->b;
    
    float * minmax = getMinMaxValue(value, sizeof(value) / sizeof(value[0]));
    // might be better to have a getMinMax value for the uint directly
    uint8_t min = floatToUint(minmax[0]);
    uint8_t max = floatToUint(minmax[1]);
    
    // in case of min == max then return 0
    if (max == min)
        return 0.0f;
    
    // Create the hue variable here
    float hue = 0.0f;

    if (max == rgb->r) {
        hue = (rgb->g - rgb->b) / (max - min);
    } else if (max == rgb->g) {
        hue = 2.0f + (rgb->b - rgb->r) / (max - min);
    } else {
        hue = 4.0f + (rgb->r - rgb->g) / (max - min);
    }
     
    hue = hue * 60;
    
    if (hue < 0.0f)
        hue = hue + 360.0f;
    
    return hue;
}
