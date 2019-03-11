## Luv API

The Luv api allow you to create a Luv color from an [Xyz](xyz.md) color.

### Datatype

The api return a Luv struct which contain these fields

```yaml
- l: double
- u: double
- v: double
- error: char*
```

### Methods signatures

#### Xyz -> Luv

- Xyz -> Luv: getLuvFromXyz
- *Params*: Xyz* structure
- *Return*: Luv* Structure

#### Luv -> Xyz

- Luv -> Xyz: getLuvFromXyz
- *Params*: Luv* structure
- *Return*: Xyz* Structure

### Example Xyz to Luv

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <luv.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 5;
rgb->g = 10;
rgb->b = 95;

Xyz *xyz = getXyzFromRgb(rgb, srgb);
Luv *luv = getLuvFromXyz(xyz);
/**
 * Output
 * luv->l = 9.603
 * luv->u = -2.851
 * luv->v = -34.829
 */
```

### Example Luv to Xyz

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <xyz.h>
#include <luv.h>

Luv *luv = malloc(sizeof(Luv));
luv->l = 5.0;
luv->u = 1.0;
luv->v = 0.0;

Xyz *xyz = getXyzFromLuv(luv);
/**
 * Output
 * xyz->x = 0.00567
 * xyz->y = 0.00554
 * xyz->z = 0.00589
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```luv->error```: The luv hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)