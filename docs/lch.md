## Lch APIs

The Lch API allow you to create an Lch color from an Xyz based color. The Lch APIs allow you ton convert back and forth the value

## Xyz to Lch

Use the method **getLchFromXyz**. This method return an Lch struct or NULL

### Error handling

This method will return NULL when:

- Lch struct can't be allocated

This method take as a param an Lch struct with an **error** parameter like so

```c
Lch->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lch.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Lch *lch  = getLchFromXyz(xyz);
```

It return the Lch struct which you can access the property like the example below

```c
double l = lch->l;
double c = lch->c;
double h = lch->h;
char *error = lch->error;
```

## Lch to Xyz

Use the method **getXyzFromLch**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- Lch property not passed

### Parameter

- Lch pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lch.h"

Lch *lch = malloc(sizeof(Lch));
lch->l = 100;
lch->c = 0;
lch->h = 360;

```

The method will return an Xyz struct which you can access it's property like the example below

```c
double x = xyz->x;
double y = xyz->y;
double z = xyz->z;
char *error = xyz->error;
```



