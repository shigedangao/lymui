use crate::ops::SliceOps;
use crate::rgb::Rgb;

/// Yiq implements the [YIQ color space](https://en.wikipedia.org/wiki/YIQ)
/// Most notably the FCC NTSC Standard (SMPTE C) standard.
#[derive(Debug, Clone, Copy)]
pub struct Yiq {
    pub y: f64,
    pub i: f64,
    pub q: f64,
}

impl Yiq {
    /// Creates a new [`Yiq`] color from the given linear rescaled RGB values.
    ///
    /// # Arguments
    ///
    /// * `r` - The red component, in the range `[0, 255]`.
    /// * `g` - The green component, in the range `[0, 255]`.
    /// * `b` - The blue component, in the range `[0, 255]`.
    fn new(r: f64, g: f64, b: f64) -> Self {
        let y = 0.30 * r + 0.59 * g + 0.11 * b;
        let i = 0.599 * r - 0.2773 * g - 0.3217 * b;
        let q = 0.213 * r - 0.5251 * g + 0.3121 * b;

        Self { y, i, q }
    }
}

impl From<Rgb> for Yiq {
    fn from(value: Rgb) -> Self {
        let (r, g, b) = value.linear_rescaling();

        Self::new(r, g, b)
    }
}

impl From<Yiq> for Rgb {
    fn from(value: Yiq) -> Self {
        let r = 1. * value.y + 0.9469 * value.i + 0.6236 * value.q;
        let g = 1. * value.y - 0.2748 * value.i - 0.6357 * value.q;
        let b = 1. * value.y - 1.1000 * value.i + 1.7000 * value.q;

        Self {
            r: (r * 255.) as u8,
            g: (g * 255.) as u8,
            b: (b * 255.) as u8,
        }
    }
}

impl SliceOps<3> for Yiq {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.y, self.i, self.q]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        vec![self.y, self.i, self.q]
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        Self {
            y: slice[0],
            i: slice[1],
            q: slice[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_convert_rgb_to_yiq() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let yiq = Yiq::from(rgb);

        util::assert_approx!(yiq.y, 1., 1e-2);
        util::assert_approx!(yiq.i, 0., 1e-2);
        util::assert_approx!(yiq.q, 0., 1e-2);
    }

    #[test]
    fn expect_to_convert_yiq_to_rgb() {
        let yiq = Yiq {
            y: 1.,
            i: 0.,
            q: 0.,
        };

        let rgb = Rgb::from(yiq);
        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 255);
        assert_eq!(rgb.b, 255);
    }
}
