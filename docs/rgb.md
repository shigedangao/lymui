### RGB APIs

The library provide you 2 way of creating an RGB:
- Allocating the **Rgb** struct by yourself and set it's value
- Pass an array of **uint8_t** to the **makeRGB** method

### Examples

Example with malloc

```c
#include "rgb.h"

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 98;
```

Example with makeRGB

```c
uint8_t colors = {5, 10, 98};
Rgb *rgb = makeRGB(colors, sizeof(colors));
```

### Targeted colors

With an RGB struct you can convert to the rgb to the format below:

- hex
- cymk
- hue
- yuv
- hsl
- hsv
- ycbcr
- xyz