## Xyz APIs

The Xyz API allow you to create an Xyz color from an RGB based color. The Xyz APIs allow you ton convert back and forth the value

## RGB to Xyz

Use the method **getXyzFromRgb**. This method return an Xyz struct or NULL

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

This method take as a param an Xyz struct with an **error** parameter like so

```c
yyz->error = <string>
```

### Parameter

- Rgb pointer struct
- Enum Matrix m (value: srgb or adobeRgb)


### Usage Example

```c
#include "rgb.h"
#include "xyz.h"

uint8_t cvalue[3] = {100, 150, 255};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));
Xyz *Xyz = getXyzFromRgb(rgb, srgb);
```

Xyz return the Xyz struct which you can access the property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = Xyz->error;
```

## Xyz to RGB

Use the method **getRgbFromXyz**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Rgb struct can't be allocated

The method *can return an RGB struct containing an error property*

- Xyz property not passed
- When an error happened during the conversion process

### Parameter

- Xyz pointer struct
- Enum Matrix m (value: srgb or adobeRgb)


### Usage Example

```c
#include "rgb.h"
#include "xyz.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.0348,
xyz->y = 0.0172,
xyz->z = 0.1097

Rgb *rgb = getRgbFromXyz(xyz, srgb);
```

The method will return an Rgb struct which you can access it's property like the example below

```c
uint8_t r = rgb->r;
uint8_t g = rgb->g;
uint8_t b = rgb->b;
char *error = rgb->error;
```

### Targeted colors

With an Xyz struct you can convert to the color format below:

- lab
- luv
- lch
- lchlab
- xyy
- srgb
- argb



