## Luv APIs

The Luv API allow you to create an Luv color from an Xyz based color. The Luv APIs allow you ton convert back and forth the value

## Xyz to Luv

Use the method **getLuvFromXyz**. This method return an Luv struct or NULL

### Error handling

This method will return NULL when:

- Luv struct can't be allocated

This method take as a param an Luv struct with an **error** parameter like so

```c
luv->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "luv.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Luv *luv  = getLuvFromXyz(xyz);
```

It return the Luv struct which you can access the property like the example below

```c
double l = luv->l;
double u = luv->u;
double v = luv->v;
char *error = luv->error;
```

## Luv to Xyz

Use the method **getXyzFromLuv**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- Luv property not passed

### Parameter

- Luv pointer struct

### Usage Example

```c
#include "xyz.h"
#include "luv.h"

Luv *luv = malloc(sizeof(Luv));
luv->l = 5.0;
luv->u = 1.0;
luv->v = 0.0;

Xyz *xyz = getXyzFromLuv(Luv);
```

The method will return an Xyz struct which you can access it's property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = xyz->error;
```