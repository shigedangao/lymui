## Argb API

The Argb api allow you to create an Argb color from an [Xyz](xyz.md) color.

### Datatype

The api return an Argb struct which contain these fields

```yaml
- r: double
- g: double
- b: double
- error: char*
```

### Methods signatures

#### Xyz -> Argb

- Rgb -> Argb: getXyzFromRgb
- *Params*: Xyz* structure
- *Return*: Argb* Structure

#### Argb -> Xyz

- Argb -> Rgb: getRgbFromHsl
- *Params*: Argb* structure
- *Return*: Xyz* Structure

### Example Xyz to Argb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <argb.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 50;
rgb->g = 10;
rgb->b = 95;

Xyz *xyz   = getXyzFromRgb(rgb, adobeRgb);
Argb *argb = getARgbFromXyz(xyz);
/**
 * Output
 * argb->r = 0.196
 * argb->g = 0.039
 * argb->b = 0.372
 */
```

### Example Argb to Xyz

```c
Argb *argb = malloc(sizeof(Argb));
argb->r = 0.196089;
argb->g = 0.039087;
argb->b = 0.372496;

Xyz *xyz = getXyzFromARgb(argb);
/**
 * Output
 * xyz->x = 0.0376
 * xyz->y = 0.0173
 * xyz->z = 0.1137
 */

```
### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```argb->error```: The Argb hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)