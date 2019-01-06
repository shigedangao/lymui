## Hwb APIs

The Hwb API allow you to create an Hwb color from an RGB based color. The Hwb APIs allow you ton convert back and forth the value

## RGB to Hwb

Use the method **getHwbFromRgb**. This method return an Hwb struct or NULL

### Error handling

This method will return NULL when:

- Hwb struct can't be allocated

The method can return an error char which can be accessible within the `error` property

```c
Hwb->error = <string>
```

### Parameter

- Rgb pointer struct

### Usage Example

```c
#include "rgb.h"
#include "Hwb.h"

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Hwb *hwb = getHwbFromRgb(rgb);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```

Hsl return the Hsl struct which you can access the property like the example below

```c
double h = hwb->h;
double w = hwb->s;
double b = hwb->l;
char *error = Hwb->error;
```

## Hwb to RGB

Use the method **getRgbFromHwb**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Hsl property not passed
- When an error happened during the conversion process

### Parameter

- Hwb pointer struct

### Usage Example

```c
#include "rgb.h"
#include "Hwb.h"

Hwb *hwb = malloc(sizeof(Hwb));
hwb->h = 0.0;
hwb->w = 100.0;
hwb->b = 0.0;

// Hwb is being freed automatically
Rgb *rgb = getRgbFromHwb(Hwb);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```
