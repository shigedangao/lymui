---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Grayscale API

The grayscale api allow you to generate a GrayScale from an [RGB](rgb.md) value.

## Datatype

The api return an uint8_t which represent the grayscale value

### Methods signatures

#### Rgb -> Hsl

- Rgb -> Hsl: getHslFromRgb()
- *Params*: Rgb structure
- *Return*: Hsl Structure

### Supported algorithms

- Average
- Lightness
- Luminosity
- bt709
- bt2100

### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <grayscale.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 0;
rgb->b = 0;
uint8_t gray = getGrayScale(rgb, Lightness);

// Output 128
```