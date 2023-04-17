use crate::rgb::Rgb;
use crate::util::{AsFloat, AsVec, FromVec};

/// Implementation of the Yuv color model
///
/// Formula used can be found below
/// @link https://fr.wikipedia.org/wiki/YUV#%C3%89quations
#[derive(Debug, Clone, Copy)]
pub struct Yuv {
    pub y: f64,
    pub u: f64,
    pub v: f64,
}

impl From<Rgb> for Yuv {
    fn from(rgb: Rgb) -> Self {
        let (mut r, mut g, mut b) = rgb.as_f64();
        r /= 255_f64;
        g /= 255_f64;
        b /= 255_f64;

        let y = 0.299 * r + 0.587 * g + 0.114 * b;

        Yuv {
            y,
            u: 0.492 * (b - y),
            v: 0.877 * (r - y),
        }
    }
}

impl From<Yuv> for Rgb {
    fn from(yuv: Yuv) -> Self {
        let r = yuv.y + 1.13983 * yuv.v;
        let g = yuv.y - 0.39465 * yuv.u - 0.58060 * yuv.v;
        let b = yuv.y + 2.03211 * yuv.u;

        Rgb {
            r: (r * 255_f64) as u8,
            g: (g * 255_f64) as u8,
            b: (b * 255_f64) as u8,
        }
    }
}

impl AsVec for Yuv {
    type Item = f64;

    fn as_vec(&self) -> Vec<f64> {
        vec![self.y, self.u, self.v]
    }
}

impl FromVec<f64> for Yuv {
    fn from_vec(vec: Vec<f64>) -> Self {
        Yuv {
            y: vec.first().copied().unwrap_or_default(),
            u: vec.get(1).copied().unwrap_or_default(),
            v: vec.last().copied().unwrap_or_default(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_yuv() {
        let rgb = Rgb {
            r: 50,
            g: 10,
            b: 95,
        };

        let yuv = Yuv::from(rgb);
        assert_eq!(util::roundup(yuv.y, 1000_f64), 0.124);
        assert_eq!(util::roundup(yuv.u, 1000_f64), 0.122);
        assert_eq!(util::roundup(yuv.v, 1000_f64), 0.063);
    }

    #[test]
    fn expect_to_compute_rgb() {
        let yuv = Yuv {
            y: 0.12411764705882353,
            u: 0.12222823529411765,
            v: 0.06310960784313725,
        };

        let rgb = Rgb::from(yuv);
        assert_eq!(rgb.r, 49);
        assert_eq!(rgb.g, 10);
        assert_eq!(rgb.b, 94);
    }
}
