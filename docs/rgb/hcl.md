## Hcl API

The Hcl api allow you to create an Hcl color from an [Rgb](rgb.md) color

### Datatype

The api return an Hcl struct which contains these fields

```yaml
- h: double
- c: double
- l: double
- error: char*
```

### Methods signatures

#### Rgb -> Hcl

- Rgb -> Hcl: getHslFromRgb()
- *Params*: Rgb* structure
- *Return*: Hcl* Structure

#### Hcl -> Rgb

- Hcl -> Rgb: getRgbFromHsl
- *Params*: Hcl* structure
- *Return*: Rgb* Structure

### Example Rgb to Hcl

```c
#include <stdio.h>
#include <stdlib.h>
#include <luv.h>
#include <hcl.h>

Luv *luv = malloc(sizeof(Luv));
luv->l = 9.603;
luv->u = -2.851;
luv->v = -34.829;

Hcl *hcl = getHclFromLuv(luv);
/**
 * Output (rounded)
 * hcl->h = 184.68
 * hsl->s = 34.945
 * hsl->l = 9.603
 */
```

### Example Hcl to Rgb

```c
#include <stdio.h>
#include <stdlib.h>
#include <luv.h>
#include <hcl.h>

Hcl *hcl = malloc(sizeof(Hcl));
hcl->h = 184.68;
hcl->c = 34.946;
hcl->l = 9.603;

Luv *luv = getLuvFromHcl(hcl);
/**
 * Output (rounded)
 * luv->l = 9.603
 * luv->u = -2.851
 * luv->v = -34.829
 */
```

### Handling errors

The API support 2 types of error

- ```NULL```: This mean that the library has not been able to allocate the structure

- ```hcl->error```: The hcl hold the ```error``` field which contain a stringify error. The list of errors is available [here](../errors.md)
