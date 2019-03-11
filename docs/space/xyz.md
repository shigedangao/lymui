## Xyy API

The Xyy api allow you to create an Xyy color from an [Rgb](rgb.md) color.

### Datatype

The api return an Xyz struct which contain these fields

```yaml
- x: double
- y: double
- z: double
- error: char*
```

### Methods signatures

#### Rgb -> Xyz

- Rgb -> Xyz: getXyzFromRgb
- *Params*: Rgb* structure
- *Params*: Matrix m (srgb|adobeRgb)
- *Return*: Xyz* Structure

#### Xyz -> Rgb

- Xyz -> Rgb: getRgbFromXyz
- *Params*: Xyz* structure
- *Return*: Rgb* Structure

### Example Xyz to Xyy

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <rgb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 95;

Xyz *xyz = getXyzFromRgb(rgb, srgb);
/**
 * Output
 * xyz->x = 0.0349
 * xyz->y = 0.0172
 * xyz->z = 0.1097
 */
```

### Example Xyz to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <rgb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 95;

Xyz *xyz = getXyzFromRgb(rgb, srgb);
Rgb *n = getRgbFromXyz(xyz, srgb);
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

- ```xyz->error```: The Xyz hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)