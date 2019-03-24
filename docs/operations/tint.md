---
layout: single
classes: wide
title: Tint
sidebar:
  nav: "docs"
---

## Tint API

The library allow you to generate set of HSL tint from a [RGB](../rgb/rgb.md) value.

## Datatype

The API return a Tint struct which represent the generated tint. It contain these fields

```yaml
- tint: array of Hsl (Hsl **)
- error: char *
```

### Methods signatures

### Rgb -> Tint

- *Params*: Rgb ptr struct
- *Return*: Tint ptr struct

### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <tint.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Tint *tint = getTint(rgb);
/**
 * Output (rounded)
 * tint->tint[0]->h = 0.0
 * tint->tint[0]->s = 0.0
 * tint->tint[0]->l = 100.0 
 */
```

### Handling errors

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```tint->error```: The tint hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
