## Xyy APIs

The Xyy API allow you to create an Xyy color from an Xyz based color. The Xyy APIs allow you ton convert back and forth the value

## Xyz to Xyy

Use the method **getXyyFromXyz**. This method return an Xyy struct or NULL

### Error handling

This method will return NULL when:

- Xyy struct can't be allocated

This method take as a param an Xyy struct with an **error** parameter like so

```c
xyy->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "xyy.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Xyy *xyy  = getXyyFromXyz(xyz);
```

It return the Xyy struct which you can access the property like the example below

```c
double x = xyy->x;
double y = xyy->y;
double Y = xyy->Y;
char *error = Xyy->error;
```

## Xyy to Xyz

Use the method **getXyzFromXyy**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- Xyy property not passed

### Parameter

- Xyy pointer struct

### Usage Example

```c
#include "xyz.h"
#include "xyy.h"

Xyy *xyy = malloc(sizeof(Xyy));
xyy->x = 0.375;
xyy->y = 0.333;
xyy->Y = 0.8;

Xyz *xyz = getXyzFromXyy(xyy);
```

The method will return an Xyz struct which you can access it's property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = xyz->error;
```