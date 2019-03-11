---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Hunter Lab API

The Hunter Lab api allow you to create a Hunter Lab color from an [Xyz](xyz.md) color.

### Datatype

The api return a Hunter Lab struct which contain these fields (which looks like a Lab structure)

```yaml
- l: double
- a: double
- b: double
- error: char*
```

### Methods signatures

#### Xyz -> HLab

- Xyz -> Lab: getHLabFromXyz
- *Params*: Xyz* structure
- *Return*: HLab* Structure

### Example Xyz to HLab

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <hunterlab.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Xyz *xyz = getXyzFromRgb(rgb, srgb);
HLab *lab = getHLabFromXyz(xyz);
/**
 * Output
 * lab->l = 100.0
 * lab->a = 0.0
 * lab->b = 0.0
 */
```


### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```lab->error```: The hunter lab hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)