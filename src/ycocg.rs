use crate::rgb::Rgb;

// Constants
const QUARTER: f64 = 1. / 4.;
const HALF: f64 = 1. / 2.;

// Ycocg color space conversion based on the following formulas defined in this page:
// @link <https://en.wikipedia.org/wiki/YCoCg>
#[derive(Debug, Clone, Copy)]
pub struct Ycocg {
    pub y: f64,
    pub co: f64,
    pub cg: f64,
}

impl Ycocg {
    /// Creates a new `Ycocg` color from the given RGB values.
    ///
    /// # Arguments
    ///
    /// * `r` - The red component.
    /// * `g` - The green component.
    /// * `b` - The blue component.
    fn new(r: f64, g: f64, b: f64) -> Self {
        let y = r * QUARTER + g * (1. / 2.) + b * QUARTER;
        let co = r * HALF + g * 0. + b * -HALF;
        let cg = r * -QUARTER + g * HALF + b * -QUARTER;

        Self { y, co, cg }
    }
}

impl From<Rgb> for Ycocg {
    fn from(value: Rgb) -> Self {
        let (r, g, b) = value.linear_rescaling();

        Ycocg::new(r, g, b)
    }
}

impl From<Ycocg> for Rgb {
    fn from(value: Ycocg) -> Self {
        let tmp = value.y - value.cg;

        Rgb {
            r: ((tmp + value.co) * 255.) as u8,
            g: ((value.y + value.cg) * 255.) as u8,
            b: ((tmp - value.co) * 255.) as u8,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_ycocg_from_rgb() {
        let rgb = Rgb { r: 255, g: 0, b: 0 };
        let ycocg = Ycocg::from(rgb);

        assert_eq!(ycocg.y, 0.25);
        assert_eq!(ycocg.co, 0.5);
        assert_eq!(ycocg.cg, -0.25);
    }

    #[test]
    fn test_ycocg_to_rgb() {
        let ycocg = Ycocg {
            y: 0.25,
            co: 0.5,
            cg: -0.25,
        };
        let rgb = Rgb::from(ycocg);

        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 0);
    }
}
