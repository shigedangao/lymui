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

/*!
 * @discussion convert an uint character to hex value
 * @param v a Hex char array
 * @return a char
 */
char * uintToHex(uint8_t v);

/*!
 * @discussion convert a float to a uint
 * @param value float
 * @return a uint8_t value
 */
uint8_t floatToUint(float value);

/*!
 * @discussion round a float to 1 digit
 * @param value float
 * @param factor int
 * @return a float
 */
float roundDigit(float value, int factor);

/*!
 * @discussion Update Constraint Value
 * @TODO This method need to be redone
 * @param value the float array
 * @return an array of float
 */
float * updateConstraintValue(float *value, uint8_t size);

/*!
 * @discussion Get the saturation between 2 values
 * @param min float value of the rgb struct
 * @param max float value of the rgb struct
 * @param l   float representing the luminance
 * @return float saturation
 */
float getSaturation(float min, float max, float l);

/**
 * @discussion Get degree from radian value
 * @param r float
 * @return d float
 */
float getDegFromRad(float r);

/**
 * @discussion Get radian from degree value
 * @param d float
 * @return r float
 */
float getRadFromDeg(float d);


#endif /* helper_h */
