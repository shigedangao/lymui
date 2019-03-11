---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Lch API

The Lch api allow you to create a Lch color from an [Xyz](xyz.md) color.

### Datatype

The api return a Lch struct which contain these fields

```yaml
- l: double
- c: double
- h: double
- error: char*
```

### Methods signatures

#### Xyz -> Lch

- Xyz -> Lch: getLabFromXyz
- *Params*: Xyz* structure
- *Return*: Lch* Structure

#### Lch -> Xyz

- Lch -> Xyz: getXyzFromLab
- *Params*: Lch* structure
- *Return*: Xyz* Structure

### Example Xyz to Lch

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <lch.h>

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.51;
xyz->y = 0.52;
xyz->z = 0.510;

Lch *lch = getLchFromXyz(xyz);
/**
 * Output
 * lch->l = 77.28
 * lch->c = 12.0
 * lch->h = 37.5
 */
```

### Example Lch to Xyz

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <lch.h>

Lch *lch = malloc(sizeof(Lch));
lch->l = 0.0;
lch->c = 0.0;
lch->h = 180.0;

Xyz *xyz = getXyzFromLch(lch);
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

- ```lch->error```: The lch hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)