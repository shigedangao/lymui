---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Lab API

The Lab api allow you to create a Lab color from an [Xyz](xyz.md) color.

### Datatype

The api return a Lab struct which contain these fields

```yaml
- l: double
- a: double
- b: double
- error: char ptr
```

### Methods signatures

#### Xyz -> Lab

- Xyz -> Lab: getLabFromXyz
- *Params*: Xyz ptr
- *Return*: Lab ptr

#### Lab -> Xyz

- Lab -> Xyz: getXyzFromLab
- *Params*: Lab ptr
- *Return*: Xyz ptr

### Example Xyz to Lab

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <lab.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Xyz *xyz = getXyzFromRgb(rgb, srgb);
Lab *lab = getLabFromXyz(xyz);
/**
 * Output
 * lab->l = 100.0
 * lab->a = 0.0
 * lab->b = 0.0
 */
```

### Example Lab to Xyz

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <lab.h>

Lab *lab  = malloc(sizeof(Lab));
lab->l = 0.0;
lab->a = 0.0;
lab->b = 0.0;

Xyz *xyz = getXyzFromLab(lab);
/**
 * Output
 * xyz->x = 0.0
 * xyz->y = 0.0
 * xyz->z = 0.0
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```lab->error```: The lab hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)