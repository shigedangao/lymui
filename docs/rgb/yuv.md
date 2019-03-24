---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Yuv API

The Yuv api allow you to create a Yuv color from an [Rgb](rgb.md) color.

### Datatype

The api return a Yuv struct which contain these fields

```yaml
- y: double
- u: double
- v: double
- error: char ptr
```

### Methods signatures

#### Rgb -> Yuv

- Rgb -> Yuv: getYuvFromRgb
- *Params*: Rgb ptr
- *Return*: Yuv ptr

#### Yuv -> Rgb

- Yuv -> Rgb: getRgbFromYuv
- *Params*: Yuv ptr
- *Return*: Rgb ptr

### Example Rgb to Yuv

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <yuv.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 95;

Yuv *yuv = getYuvFromRgb(rgb);
/**
 * Output
 * yuv->y = 0.124
 * yuv->u = 0.122
 * yuv->v = 0.063
 */
```

### Example Yuv to Rgb

```c
Yuv *yuv = malloc(sizeof(Yuv));
yuv->y = 0.124;
yuv->u = 0.122;
yuv->v = 0.063;

Rgb *rgb = getRgbFromYuv(yuv);
/**
 * Output
 * rgb->r = 50
 * rgb->g = 10
 * rgb->b = 95
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```yuv->error```: The yuv hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)