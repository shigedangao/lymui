use crate::hsv::Hsv;
use crate::rgb::Rgb;

/// Implement the HWB color model. The implementation is based on the provided link
///
/// @link https://en.wikipedia.org/wiki/HWB_color_model
#[derive(Debug, Clone, Copy)]
pub struct Hwb {
    pub h: f64,
    pub w: f64,
    pub b: f64,
}

impl From<Rgb> for Hwb {
    fn from(rgb: Rgb) -> Self {
        let hsv = Hsv::from(rgb);

        let s = hsv.s / 100_f64;
        let v = hsv.v / 100_f64;

        Hwb {
            h: hsv.h,
            w: ((1_f64 - s) * v) * 100_f64,
            b: (1_f64 - v) * 100_f64,
        }
    }
}

impl From<Hwb> for Rgb {
    fn from(hwb: Hwb) -> Self {
        let w = hwb.w / 100_f64;
        let b = hwb.b / 100_f64;

        let hsv = Hsv {
            h: hwb.h,
            s: (1_f64 - (w / (1_f64 - b))) * 100_f64,
            v: (1_f64 - b) * 100_f64,
        };

        Rgb::from(hsv)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_hwb() {
        let rgb = Rgb {
            r: 17,
            g: 12,
            b: 93,
        };

        let hwb = Hwb::from(rgb);
        assert_eq!(hwb.h, 244.0);
        assert_eq!(util::roundup(hwb.w, 1000.0), 4.706);
        assert_eq!(util::roundup(hwb.b, 1000.0), 63.529);
    }

    #[test]
    fn expect_to_compute_rgb() {
        let hwb = Hwb {
            h: 244.0,
            w: 4.705882352941177,
            b: 63.52941176470588,
        };

        let rgb = Rgb::from(hwb);
        assert_eq!(rgb.r, 17);
        assert_eq!(rgb.g, 12);
        assert_eq!(rgb.b, 93);
    }
}
