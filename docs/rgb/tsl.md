## Tsl APIs

The Tsl API allow you to create an Tsl color from an RGB based color. The Tsl APIs allow you ton convert back and forth the value

## RGB to Tsl

Use the method **getTslFromRgb**. This method return an Tsl struct or NULL

### Error handling

This method will return NULL when:

- Tsl struct can't be allocated

The method can return an error char which can be accessible within the `error` property

```c
tsl->error = <string>
```

### Parameter

- Rgb pointer struct

### Usage Example

```c
#include "rgb.h"
#include "tsl.h"

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

Tsl *tsl = getTslFromRgb(rgb);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```

Hsl return the Hsl struct which you can access the property like the example below

```c
double t = tsl->h;
double s = tsl->s;
double l = tsl->l;
char *error = tsl->error;
```

## Tsl to RGB

Use the method **getRgbFromTsl**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Hsl property not passed
- When an error happened during the conversion process

### Parameter

- Tsl pointer struct

### Usage Example

```c
#include "rgb.h"
#include "tsl.h"

Tsl *tsl = malloc(sizeof(Tsl));
tsl->t = 0.0;
tsl->s = 0.0;
tsl->l = 255.0;

// tsl is being freed automatically
Rgb *rgb = getRgbFromTsl(tsl);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```



