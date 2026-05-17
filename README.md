## Lymui 🌈
 
Lymui is a color library which allows you to convert an RGB color to an other color (see the supported list of colors below).

### Supported colors

| Color         | Supported |
|---------------|-----------|
| Rgb           |   ✅      |
| Ansi          |   ✅      |
| Cymk          |   ✅      |
| Grayscale     |   ✅      |
| Hex           |   ✅      |
| Hsl           |   ✅      |
| Hue           |   ✅      |
| Hwb           |   ✅      |
| Ycbcr         |   ✅      |
| Yuv           |   ✅      |
| Xyz           |   ✅      |
| Adobe RGB     |   ✅      |
| sRGB          |   ✅      |
| Hcl           |   ✅      |
| Hunter lab    |   ✅      |
| Cie Lab       |   ✅      |
| Lch Lab       |   ✅      |
| Luv           |   ✅      |
| Oklab         |   ✅      |
| Oklach        |   ✅      |
| rec.709       |   ✅      |
| rec.2020      |   ✅      |
| rec.2100 (PQ) |   ✅      |
| Xyy           |   ✅      |

### Usage

All colors start from the `Rgb` compatible color type. You can then convert it to any other color type using the `From` trait. For an `Xyz` color, you can convert it to any type based on the lumens type e.g: `D65`, `D50`, `D75`.

```toml
[dependencies]
lymui = "0.2.0"
```

Below is a code example of converting an `Rgb` color to `Xyz` using the `D65` lumens type.

```rust
use lymui::prelude::*;

fn main() {
    let rgb = Rgb {
        r: 255,
        g: 255,
        b: 255,
    };

    let xyz = Xyz::from_rgb(rgb, Kind::D65);
}
```

### Examples

An example is available in the example folder. You can run it by using the command below

```sh
cargo run --example example
```
