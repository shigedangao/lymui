use super::rgb::Rgb;
use crate::util::{AsFloat, AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Cymk is an implementation of the Cymk color space
///
/// The implementation formula is based on the link below
/// @link https://www.rapidtables.com/convert/color/rgb-to-cmyk.html
#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug, Default, Clone, Copy)]
pub struct Cymk {
    pub c: f64,
    pub y: f64,
    pub m: f64,
    pub k: f64,
}

impl From<Rgb> for Cymk {
    fn from(rgb: Rgb) -> Self {
        let (r, g, b) = rgb.as_f64();
        let (_, max) = rgb.get_min_max();

        let k = 1_f64 - (max / 255_f64);
        let mk = 1_f64 - k;

        if k != 1_f64 {
            return Cymk {
                c: (1_f64 - (r / 255_f64) - k) / mk,
                m: (1_f64 - (g / 255_f64) - k) / mk,
                y: (1_f64 - (b / 255_f64) - k) / mk,
                k,
            };
        }

        Cymk {
            k,
            ..Default::default()
        }
    }
}

impl From<Cymk> for Rgb {
    fn from(cymk: Cymk) -> Self {
        let kv = 1_f64 - cymk.k;

        Rgb {
            r: (255_f64 * (1_f64 - cymk.c) * kv) as u8,
            g: (255_f64 * (1_f64 - cymk.m) * kv) as u8,
            b: (255_f64 * (1_f64 - cymk.y) * kv) as u8,
        }
    }
}

impl AsVec for Cymk {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.c, self.y, self.m, self.k]
    }
}

impl FromVec<f64> for Cymk {
    fn from_vec(vec: Vec<f64>) -> Self {
        Cymk {
            c: vec.first().copied().unwrap_or_default(),
            y: vec.get(1).copied().unwrap_or_default(),
            m: vec.get(2).copied().unwrap_or_default(),
            k: vec.last().copied().unwrap_or_default(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util::roundup;

    #[test]
    fn expect_to_create_cymk() {
        let rgb = Rgb {
            r: 255,
            g: 55,
            b: 102,
        };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(roundup(cymk.y, 100.0), 0.6);
        assert_eq!(roundup(cymk.m, 100.0), 0.78);
        assert_eq!(cymk.k, 0.0);
    }

    #[test]
    fn expect_to_create_dark_cymk() {
        let rgb = Rgb { r: 0, g: 0, b: 0 };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(cymk.y, 0.0);
        assert_eq!(cymk.m, 0.0);
        assert_eq!(cymk.k, 1.0);
    }

    #[test]
    fn expect_to_create_light_cymk() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(cymk.y, 0.0);
        assert_eq!(cymk.m, 0.0);
        assert_eq!(cymk.k, 0.0);
    }

    #[test]
    fn expect_to_create_rgb() {
        let cymk = Cymk {
            c: 0.973,
            y: 0.0,
            m: 0.949,
            k: 0.223,
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 5);
        assert_eq!(rgb.g, 10);
        assert_eq!(rgb.b, 198);
    }

    #[test]
    fn expect_to_create_dark_rgb() {
        let cymk = Cymk {
            c: 0.0,
            y: 0.0,
            m: 0.0,
            k: 1.0,
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 0);
    }

    #[test]
    fn expect_to_create_light_rgb() {
        let cymk = Cymk {
            c: 0.0,
            y: 0.0,
            m: 0.0,
            k: 0.0,
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 255);
        assert_eq!(rgb.b, 255);
    }
}
