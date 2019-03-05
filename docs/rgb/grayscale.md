## Grayscale APIs

The Grayscale API allow you to create an Grayscale color from an RGB based color.

## RGB to Grayscale

Use the method **getGrayScale**. This method return a Grayscale uint8_t value ranging from 0 to 255

### Error handling

This method will return NULL when:

- Parameter is NULL

### Parameter

- Rgb pointer struct
- Strategy enum

The Strategy enum support the following grayscale calculation options:

- Lightness,
- Average,
- Luminosity,
- bt709,
- bt2100

### Usage Example

```c
#include "rgb.h"
#include "grayscale.h"

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 255;
rgb->g = 255;
rgb->b = 255;

uint8_t gray = getGrayScale(rgb, Lightness);

// rgb will not be freed (so that you can reuse this struct)
free(rgb);
```