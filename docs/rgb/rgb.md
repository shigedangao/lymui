---
layout: single
classes: wide
title: Lymui
sidebar:
  nav: "docs"
---

## Rgb API

The Rgb api allow you to create an RGB color from 2 endpoint. You can either pass an uint8_t array or allocate directly the color.

### Datatype

The api return an RGB struct which contains these fields

```yaml
- r: uint8_t
- g: uint8_t
- b: uint8_t
- error: char ptr
```

### Methods signatures

#### Rgb from uint8_t array

- Rgb -> Hsl: makeRGB()
- *Params*: uint8_t array
- *Params*: size_t length
- *Return*: Rgb ptr

### Example with uint8_t array

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>

uint8_t uc[] = {0, 100, 200};
Rgb *rgb = makeRGB(uc, sizeof(uc));
```

### Example with allocation

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 10;
rgb->g = 10;
rgb->b = 10;
```
### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```rgb->error```: The hsl hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
