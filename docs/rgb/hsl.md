---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Hsl API

The Hsl api allow you to create an Hsl color from an [Rgb](rgb.md) color.

### Datatype

The api return an Hsl struct which contain these fields

```yaml
- h: double
- s: double
- l: double
- error: char*
```

### Methods signatures

#### Rgb -> Hsl

- Rgb -> Hsl: getHslFromRgb()
- *Params*: Rgb ptr
- *Return*: Hsl ptr

#### Hsl -> Rgb

- Hsl -> Rgb: getRgbFromHsl
- *Params*: Hsl ptr
- *Return*: Rgb ptr

### Example Rgb to Hsl

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hsl.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 5;
rgb->g = 10;
rgb->b = 95;

Hsl *hsl = getHslFromRgb(rgb);
/**
 * Output
 * hsl->h = 237.0
 * hsl->s = 90.0
 * hsl->l = 19.6
 */
```

### Example Hsl to RGB

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hsl.h>

Hsl *hsl = malloc(sizeof(Hsl));
hsl->h = 0.0;
hsl->s = 0.0;
hsl->l = 59.0;

Rgb *rgb = getRgbFromHsl(hsl);
/**
 * Output
 * rgb->r = 150
 * rgb->g = 150
 * rgb->b = 150
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```hsl->error```: The hsl hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
