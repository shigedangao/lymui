## Ycbcr API

The Ycbcr api allow you to create an Ycbcr color from an [Rgb](rgb.md) color.

### Datatype

The api return a Ycbcr struct which contain these fields

```yaml
- y: uint8_t
- cb: uint8_t
- cr: uint8_t
- error: char*
```

### Methods signatures

#### Rgb -> Ycbcr

- Rgb -> Ycbcr: getYcbcrFromRgb
- *Params*: Rgb* structure
- *Return*: Ycbcr* Structure

#### Ycbcr -> Rgb

- Ycbcr -> Rgb: getRgbFromYcbcr
- *Params*: Ycbcr* structure
- *Return*: Rgb* Structure

### Example Rgb to Ycbcr

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <ycbcr.h>

Rgb *rgb = malloc(sizeof(Rgb));
rgb->r = 0;
rgb->g = 100;
rgb->b = 200;

Ycbcr *ycbcr = getYcbcrFromRgb(rgb);
/**
 * Output
 * ycbcr->y = 86
 * ycbcr->cb = 187
 * ycbcr->cr = 77
 */
```

### Example Ycbcr to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <rgb.h>
#include <ycbcr.h>

Ycbcr *ycbcr = malloc(sizeof(Ycbcr));
ycbcr->y  = 86;
ycbcr->cb = 186;
ycbcr->cr = 77;

Rgb *rgb = getRgbFromYcbcr(ycbcr);
/**
 * Output
 * ycbcr->y = 0
 * ycbcr->cb = 100
 * ycbcr->cr = 199
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```ycbcr->error```: The ycbcr hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)

