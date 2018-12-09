## LchLab APIs

The LchLab API allow you to create an LchLab color from an Xyz based color. The LchLab APIs allow you ton convert back and forth the value

## Xyz to LchLab

Use the method **getLchFromLab**. This method return an LchLab struct or NULL

### Error handling

This method will return NULL when:

- LchLab struct can't be allocated

This method take as a param an Lch struct with an **error** parameter like so

```c
lch->error = <string>
```

### Parameter

- Xyz pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lchlab.h"

Xyz *xyz = malloc(sizeof(Xyz));
xyz->x = 0.950470;
xyz->y = 1.0;
xyz->z = 1.088830;
    
Lch *lch  = getLchFromLab(xyz);
```

It return the Lch struct which you can access the property like the example below

```c
double l = lch->l;
double c = lch->c;
double h = lch->h;
char *error = lch->error;
```

## LchLab to Xyz

Use the method **getXyzFromLchlab**. This method return an RGB struct or NULL.

### Error handling

This method will return NULL when:

- Xyz struct can't be allocated

The method *can return an Xyz struct containing an error property*

- LchLab property not passed

### Parameter

- LchLab pointer struct

### Usage Example

```c
#include "xyz.h"
#include "lchlab.h"

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



