## Lch(Lab) API

The Lch(Lab) api allow you to create a Lch color from an [Xyz](xyz.md) color.

### Datatype

The api return a Lch(Lab) struct which contain these fields

```yaml
- l: double
- c: double
- h: double
- error: char*
```

### Methods signatures

#### Xyz -> Lch(Lab)

- Xyz -> Lch: getLchFromLab
- *Params*: Xyz* structure
- *Return*: Lch* Structure

#### Lch(Lab) -> Xyz

- Lch -> Xyz: getXyzFromLchlab
- *Params*: Lch* structure
- *Return*: Xyz* Structure

### Example Xyz to Lch(Lab)

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <lchlab.h>

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.1161;
xyz->y = 0.0497;
xyz->z = 0.5376;

LchLab *lch = getLchFromLab(xyz);
/**
 * Output
 * lch->l = 26.65
 * lch->c = 106.19
 * lch->h = 307.24
 */
```

### Example Lch(Lab) to Xyz

```c
#include <stdio.h>
#include <stdlib.h>
#include <xyz.h>
#include <lchlab.h>

LchLab *lch = malloc(sizeof(LchLab));
lch->l = 0.0;
lch->c = 0.0;
lch->h = 0.0;

Xyz *xyz = getXyzFromLch(lch);
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

- ```lch->error```: The lch hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)