use crate::rgb::Rgb;
use crate::util::{AsFloat, AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

// Constant use to compute back the RGB from an Ycbcr value
const Y: f64 = 1.164;

/// Implementation of the Ycbcr colorspace. The implementation formula is based on the links below
///
/// @link https://stackoverflow.com/a/13616564/7489243
#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug, Clone, Copy)]
pub struct Ycbcr {
    pub y: u8,
    pub cb: u8,
    pub cr: u8,
}

impl Ycbcr {
    fn calculate_indices(rgb: &Rgb, multipliers: (f64, f64, f64)) -> (f64, f64, f64) {
        let (r, g, b) = rgb.as_f64();

        (r * multipliers.0, g * multipliers.1, b * multipliers.2)
    }
}

impl AsFloat for Ycbcr {
    fn as_f64(&self) -> (f64, f64, f64) {
        (self.y as f64, self.cb as f64, self.cr as f64)
    }
}

impl AsVec for Ycbcr {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.y as f64, self.cb as f64, self.cr as f64]
    }
}

impl FromVec<u8> for Ycbcr {
    fn from_vec(vec: Vec<u8>) -> Self {
        Ycbcr {
            y: vec.first().copied().unwrap_or_default(),
            cb: vec.get(1).copied().unwrap_or_default(),
            cr: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl From<Rgb> for Ycbcr {
    fn from(rgb: Rgb) -> Self {
        let (yl, yy, ym) = Ycbcr::calculate_indices(&rgb, (0.257, 0.504, 0.098));
        let (ycl, ycy, ycm) = Ycbcr::calculate_indices(&rgb, (0.148, 0.291, 0.439));
        let (yrl, yry, yrm) = Ycbcr::calculate_indices(&rgb, (0.439, 0.368, 0.071));

        let y = (16_f64 + yl + yy + ym) as u8;
        let cb = (128_f64 + (-ycl - ycy + ycm)) as u8;
        let cr = (128_f64 + (yrl - yry - yrm)) as u8;

        Ycbcr { y, cb, cr }
    }
}

impl From<Ycbcr> for Rgb {
    fn from(cb: Ycbcr) -> Self {
        let (y, cb, cr) = cb.as_f64();

        let yy = Y * (y - 16.0);
        let r = yy + 1.596 * (cr - 128.0);
        let g = yy - 0.813 * (cr - 128.0) - 0.391 * (cb - 128.0);
        let b = yy + 2.018 * (cb - 128.0);

        Rgb {
            r: r as u8,
            g: g as u8,
            b: b as u8,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_create_ycbcr() {
        let rgb = Rgb {
            r: 0,
            g: 100,
            b: 200,
        };

        let ycbcr = Ycbcr::from(rgb);
        assert_eq!(ycbcr.y, 86);
        assert_eq!(ycbcr.cb, 186);
        assert_eq!(ycbcr.cr, 77);
    }

    #[test]
    fn expect_to_create_rgb_from_ycbcr() {
        let ycbcr = Ycbcr {
            y: 86,
            cb: 186,
            cr: 77,
        };

        let rgb = Rgb::from(ycbcr);
        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 100);
        assert_eq!(rgb.b, 198);
    }
}
