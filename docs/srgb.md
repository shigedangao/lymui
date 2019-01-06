## SRgb APIs

The SRgb API allow you to create an SRgb color from an Xyz based color. The SRgb APIs allow you ton convert back and forth the value

## Xyz to SRgb

Use the method **getSRgbFromXyz**. This method return an SRgb struct or NULL

### Error handling

This method will return NULL when:

- SRgb struct can't be allocated

This method take as a param an SRgb struct with an **error** parameter like so

```c
SRgb->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "srgb.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
SRgb *srgb  = getSrgbFromXyz(xyz);

// xyz will not be freed (so that you can reuse this struct)
free(xyz);
```

It return the SRgb struct which you can access the property like the example below

```c
double r = srgb->r;
double g = srgb->g;
double b = srgb->b;
char *error = SRgb->error;
```

## SRgb to Xyz

Use the method **getXyzFromSrgb**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- SRgb property not passed

### Parameter

- SRgb pointer struct

### Usage Example

```c
#include "xyz.h"
#include "srgb.h"

SRgb *srgb = malloc(sizeof(SRgb));
srgb->r = 0.0;
srgb->g = 0.0;
srgb->b = 0.0;

// srgb is being freed automatically
Xyz *xyz = getXyzFromSrgb(srgb);
```

The method will return an Xyz struct which you can access it's property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = xyz->error;
```