## Hue APIs

The Hue API allow you to create an Hue color from an RGB based color. The Hue APIs allow you ton convert back and forth the value

## RGB to Hue

Use the method **getHueFromRgb**. This method return an Hue double or NULL

### Error handling

Nil

### Parameter

- Rgb pointer struct

### Usage Example

```c
uint8_t cvalue[3] = {244, 100, 200};
Rgb *rgb = makeRGB(cvalue, sizeof(cvalue) / sizeof(cvalue[0]));    
Hue hue = getHueFromRgb(rgb);
```

### Note

When a **NULL** Rgb struct is pass the method will not fail and instead return 0.0
