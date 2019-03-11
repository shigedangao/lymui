---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Hwb API

The Hwb api allow you to create an Hwb color from an [Rgb](rgb.md) color.

### Datatype

The api return an Hwb struct which contain these fields

```yaml
- h: double
- w: double
- b: double
- error: char*
```

### Methods signatures

#### Rgb -> Hwb

- Rgb -> Hwb: getHwbFromRgb()
- *Params*: Rgb* structure
- *Return*: Hwb* Structure

#### Hwb -> Rgb

- Hwb -> Rgb: getRgbFromHwb
- *Params*: Hwb structure
- *Return*: Rgb Structure

### Example Rgb to Hwb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hwb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 17;
rgb->g = 12;
rgb->b = 93;

Hwb *hwb = getHwbFromRgb(rgb);
/**
 * Output (rounded)
 * hsl->h = 244.0
 * hsl->s = 4.7
 * hsl->l = 63.53
 */
```

### Example Hwb to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <hwb.h>

Hwb *hwb = malloc(sizeof(Hwb));
hwb->h = 0.0;
hwb->w = 0.0;
hwb->b = 100.0;

Rgb *rgb = getRgbFromHwb(hwb);
/**
 * Output
 * rgb->r = 0
 * rgb->g = 0
 * rgb->b = 0
 */
```
### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```hwb->error```: The hwb hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
