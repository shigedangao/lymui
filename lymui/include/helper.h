//
//  helper.h
//  lymui
//
//  Created by Marc on 06/02/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include <stdio.h>
#include <stdint.h>

/**
 * @brief convert a double to an uint8_t
 * @param value doule
 * @return uint8_t
 */
uint8_t doubleToUint(double value);

/**
 * @brief Get the saturation between 2 values
 * @param min double value of the rgb struct
 * @param max double value of the rgb struct
 * @param l   double representing the luminance
 * @return double saturation
 */
double getSaturation(double min, double max, double l);

/**
 * @brief Get degree from radian value
 * @param r double
 * @return d double
 */
double getDegFromRad(double r);

/**
 * @brief Get radian from degree value
 * @param d double
 * @return r double
 */
double getRadFromDeg(double d);

/**
 * @brief Get minimum value of RGB
 * @param r double
 * @param g double
 * @param b double
 * @param operation uint
 * @return double
 */
double getMinMax(double r, double g, double b, uint8_t operation);


#endif /* helper_h */
