use crate::ops::AsFloat;
use crate::ops::SliceOps;

// Constant
pub const ADBOBE_RGB_COMPOUND: f64 = 2.199_218_75;

/// FromRgb is a trait that allows a type T to process an RGB Color
pub trait FromRgb<T> {
    /// Convert an rgb color to something else
    fn from_rgb(rgb: Rgb, kind: T) -> Self;
}

/// Represents an RGB color.
#[derive(Debug, Default, Clone, Copy)]
pub struct Rgb {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}

impl AsFloat for Rgb {
    fn as_f64(&self) -> (f64, f64, f64) {
        (f64::from(self.r), f64::from(self.g), f64::from(self.b))
    }
}

impl Rgb {
    /// Creta a new rgb color
    ///
    /// # Arguments
    ///
    /// * `a` - u8
    /// * `b` - u8
    /// * `c` - u8
    pub fn new(a: u8, b: u8, c: u8) -> Self {
        Rgb { r: a, g: b, b: c }
    }

    /// Get the minimum and the maximum value of a RGB color representation
    pub fn get_min_max(&self) -> (f64, f64) {
        let (r_f, g_f, b_f) = self.as_f64();

        let min = b_f.min(r_f.min(g_f));
        let max = b_f.max(r_f.max(g_f));

        (min, max)
    }
}

impl SliceOps<3> for Rgb {
    type Item = u8;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.r, self.g, self.b]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        self.as_slice().to_vec()
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        Rgb {
            r: slice[0],
            g: slice[1],
            b: slice[2],
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_return_min_max() {
        let rgb = Rgb {
            r: 250,
            g: 100,
            b: 50,
        };

        let (min, max) = rgb.get_min_max();

        assert_eq!(min, 50.0);
        assert_eq!(max, 250.0);
    }
}
