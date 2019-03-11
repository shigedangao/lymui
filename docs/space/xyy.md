## Xyy API

The Xyy api allow you to create an Xyy color from an [Xyz](xyz.md) color.

### Datatype

The api return an Xyy struct which contain these fields

```yaml
- x: double
- y: double
- y: double
- error: char*
```

### Methods signatures

#### Xyz -> Xyy

- Rgb -> Xyy: getXyzFromRgb
- *Params*: Xyz* structure
- *Return*: Xyy* Structure

#### Xyy -> Xyz

- Xyy -> Rgb: getRgbFromHsl
- *Params*: Xyy* structure
- *Return*: Xyz* Structure

### Example Xyz to Xyy

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <xyy.h>

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.9;
xyz->y = 0.8;
xyz->z = 0.7;

Xyy *xyy = getXyyFromXyz(xyz);
/**
 * Output
 * xyy->x = 0.375
 * xyy->y = 0.333
 * xyy->Y = 0.8
 */
```

### Example Xyy to Xyz

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <xyy.h>

Xyy *xyy = malloc(sizeof(Xyy));
xyy->x = 0.313;
xyy->y = 0.329;
xyy->Y = 0.0;

Xyz *xyz = getXyzFromXyy(xyy);
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

- ```xyy->error```: The Xyy hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)