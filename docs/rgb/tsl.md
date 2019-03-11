---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Tsl API

The Tsl api allow you to create a Tsl color from an [Rgb](rgb.md) color.

### Datatype

The api return an Tsl struct which contain these fields

```yaml
- t: double
- s: double
- l: double
- error: char*
```

### Methods signatures

#### Rgb -> Tsl

- Rgb -> Tsl: getTslFromRgb
- *Params*: Rgb* structure
- *Return*: Tsl* Structure

#### Tsl -> Rgb

- Hsl -> Rgb: getRgbFromTsl
- *Params*: Tsl* structure
- *Return*: Rgb* Structure

### Example Rgb to Tsl

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <tsl.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 128;

Tsl *tsl = getTslFromRgb(rgb);
/**
 * Output
 * tsl->t = 0.788
 * tsl->s = 0.387
 * tsl->l = 35.412
 */
```

### Example Rgb to Tsl

```c
Tsl *tsl = malloc(sizeof(Tsl));
tsl->t = 0.787;
tsl->s = 0.386;
tsl->l = 35.412;

Rgb *rgb = getRgbFromTsl(tsl);
/**
 * Output
 * rgb->r = 50
 * rgb->g = 10
 * rgb->b = 128
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```tsl->error```: The tsl hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
