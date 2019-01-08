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
#include "helper.h"
#include "errors.h"

#define X_FORMULA(t) { -1.0 / tan(2.0 * M_PI * t) }

/**
 * @brief Calculate Delta
 * @param c double
 * @param op uint8_t
 * @return delta double
 */
static double calculateDelta(double c, uint8_t op) {
    if (op) {
        return c + (1.0 / 3.0);
    }
    
    return c - (1.0 / 3.0);
}

/**
 * @brief Calculate Norm
 * @param c double
 * @param r double
 * @param g double
 * @param b double
 * @return c double
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
        
        return tsl;
    }
    
    double rNorm  = calculateNorm(_r, _r, _g, _b);
    double gNorm  = calculateNorm(_g, _r, _g, _b);
    double rDelta = calculateDelta(rNorm, 0);
    double gDelta = calculateDelta(gNorm, 0);
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
    tsl->error = NULL;
        
    return tsl;
}

/////////////// static method for converting TSL -> RGB

/**
 * @brief Calculate G Delta (based on the answer of SergGr on Stackoverflow. See .h file for the link to the answer)
 * @param tsl Tsl
 * @return g double
 */
static double calculateGDelta(Tsl *tsl) {
    double x = X_FORMULA(tsl->t);
    double g = sqrt(5.0 / (x * x + 1.0)) / 3.0 * tsl->s;
    
    if (tsl->t > 0.5) {
        return -g;
    } else {
        return g;
    }
}

/**
 * @brief Calculate R Delta
 * @param tsl Tsl
 * @param g double
 * @return r double
 */
static double calculateRDelta(Tsl *tsl, double g) {
    if (!tsl->t) {
        return sqrt(5.0) / 3.0 * tsl->s;
    }
    
    double x = X_FORMULA(tsl->t);
    return x * g;
}

Rgb *getRgbFromTsl(Tsl *tsl) {
    Rgb *rgb = initRgb();
    if (rgb == NULL) {
        return NULL;
    }
    
    if (tsl == NULL) {
        rgb->error = NULL_INPUT_PARAM;
        return rgb;
    }
    
    double gDelta = calculateGDelta(tsl);
    double _r = calculateDelta(calculateRDelta(tsl, gDelta), 1);
    double _g = calculateDelta(gDelta, 1);
    double _k = tsl->l / (0.185 * _r + 0.473 * _g + 0.114);
    
    rgb->r = doubleToUint(_k * _r);
    rgb->g = doubleToUint(_k * _g);
    rgb->b = doubleToUint(_k * (1 - _r - _g));
    rgb->error = NULL;
    
    free(tsl);
    
    return rgb;
}
