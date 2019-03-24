---
layout: single
classes: wide
title: Shade
sidebar:
  nav: "docs"
---

## Shade API

The library allow you to generate set of HSL shade from a [RGB](../rgb/rgb.md) value.

## Datatype

The API return a Shade struct which represent the generated shade. It contain these fields

```yaml
- shade: array of Hsl (Hsl **)
- error: char *
```

### Methods signatures

### Rgb -> Shade

- *Params*: Rgb ptr struct
- *Return*: Shade ptr struct

### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <shade.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Shade *shade = getShade(rgb);
/**
 * Output (rounded)
 * shade->shade[0]->h = 221.0
 * shade->shade[0]->s = 100.0
 * shade->shade[0]->l = 69.91 
 */
```

### Handling errors

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```shade->error```: The shade hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
