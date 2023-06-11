use crate::util::{AsFloat, AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

// Constant
pub const ADBOBE_RGB_COMPOUND: f64 = 2.19921875;

/// FromRgb is a trait that allows a type T to process an RGB Color
pub trait FromRgb<T> {
    /// Convert an rgb color to something else
    fn from_rgb(rgb: Rgb, kind: T) -> Self;
}

#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug, Default, Clone, Copy)]
pub struct Rgb {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}

impl AsFloat for Rgb {
    fn as_f64(&self) -> (f64, f64, f64) {
        (self.r as f64, self.g as f64, self.b as f64)
    }
}

impl AsVec for Rgb {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.r as f64, self.g as f64, self.b as f64]
    }
}

impl FromVec<u8> for Rgb {
    fn from_vec(vec: Vec<u8>) -> Self {
        Rgb {
            r: vec.first().copied().unwrap_or_default(),
            g: vec.get(1).copied().unwrap_or_default(),
            b: vec.last().copied().unwrap_or_default(),
        }
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
