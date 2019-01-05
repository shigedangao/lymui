//
//  tsl.c
//  lymui
//
//  Created by Marc Intha on 05/01/2019.
//  Copyright © 2019 Marc. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "tsl.h"
#include "errors.h"

/**
 * @brief Calculate Delta
 * @param c double
 * @return delta double
 */
static double calculateDelta(double c) {
    return c - (1.0 / 3.0);
}

/**
 * @brief Calculate Norm
 * @param c double
 * @param r double
 * @param g double
 * @param b double
 */
static double calculateNorm(double c, double r, double g, double b) {
    return c / (r + g + b);
}

Tsl *getTslFromRgb(Rgb *rgb) {
    Tsl *tsl = malloc(sizeof(Tsl));
    if (tsl == NULL) {
        return NULL;
    }
    
    if (rgb == NULL) {
        tsl->error = NULL_INPUT_PARAM;
        return tsl;
    }
    
    double _r = (double) rgb->r;
    double _g = (double) rgb->g;
    double _b = (double) rgb->b;
    
    if (!_r && !_g && !_b) {
        tsl->t = 0.0;
        tsl->s = 0.0;
        tsl->l = 0.0;
    }
    
    double rNorm  = calculateNorm(_r, _r, _g, _b);
    double gNorm  = calculateNorm(_g, _r, _g, _b);
    double rDelta = calculateDelta(rNorm);
    double gDelta = calculateDelta(gNorm);
    double d_pi = 1.0 / (M_PI * 2.0);
    
    if (gDelta > 0.0) {
        tsl->t = d_pi * atan(rDelta / gDelta) + 0.25;
    } else if (gDelta < 0.0) {
        tsl->t = d_pi * atan(rDelta / gDelta) + 0.75;
    } else {
        tsl->t = 0.0;
    }
    
    tsl->s = sqrt((9.0 / 5.0) * (powf(rDelta, 2.0) + powf(gDelta, 2.0)));
    tsl->l = 0.299 * _r + 0.587 * _g + 0.114 * _b;
    
    return tsl;
}
