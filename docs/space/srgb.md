---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Srgb API

The Srgb api allow you to create an Srgb color from an [Xyz](xyz.md) color.

### Datatype

The api return an Srgb struct which contain these fields

```yaml
- r: double
- g: double
- b: double
- error: char*
```

### Methods signatures

#### Xyz -> Srgb

- Xyz -> Srgb: getXyzFromRgb
- *Params*: Xyz* structure
- *Return*: Srgb* Structure

#### Srgb -> Xyz

- Srgb -> Xyz: getXyzFromSrgb
- *Params*: Srgb* structure
- *Return*: Xyz* Structure

### Example Xyz to Srgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <srgb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 95;

Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
Srgb *srgb = getSrgbFromXyz(xyz);
/**
 * Output
 * Srgb->r = 0.196
 * Srgb->g = 0.039
 * Srgb->b = 0.372
 */
```

### Example Srgb to Xyz

```c
Srgb *Srgb = malloc(sizeof(Srgb));
srgb->r = 0.196089;
srgb->g = 0.039087;
srgb->b = 0.372496;

Xyz *xyz = getXyzFromSrgb(Srgb);
/**
 * Output
 * xyz->x = 0.0376
 * xyz->y = 0.0173
 * xyz->z = 0.1137
 */

```
### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```srgb->error```: The srgb hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)