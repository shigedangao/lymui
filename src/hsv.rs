use crate::rgb::Rgb;
use crate::hue::Hue;

/// Implement the HSV color model. The implementation is based on the formula below
/// 
/// @link https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html
#[derive(Debug, Clone, Copy)]
pub struct Hsv {
    pub h: f64,
    pub s: f64,
    pub v: f64
}

impl From<Rgb> for Hsv {
    fn from(rgb: Rgb) -> Self {
        let (min, max) = rgb.get_min_max();
        let hue = Hue::from(rgb);

        let delta = max - min;
        let s;

        if max > 0.0 {
            s = (delta / max) * 100.0;
        } else {
            s = 0.0;
        }

        Hsv {
            h: hue,
            s,
            v: (max / 255_f64) * 100_f64
        }
    }
}

impl From<Hsv> for Rgb {
    fn from(hsv: Hsv) -> Self {
        if hsv.s == 0.0 {
            return Rgb {
                r: hsv.v as u8,
                g: hsv.v as u8,
                b: hsv.v as u8
            };
        }

        let hue = hsv.h / 60.0;
        let i = hue as i64;
        let factor = hue - i as f64;

        let v = hsv.v / 100.0;
        let s = hsv.s / 100.0;

        let p = v * (1.0 - s);
        let q = v * (1.0 - (s * factor));
        let t = v * (1.0 - (1.0 - factor) * s);

        let up = (p * 255.0) as u8;
        let uq = (q * 255.0) as u8;
        let ut = (t * 255.0) as u8;
        let uv = (v * 255.0) as u8;

        match i {
            0 => Rgb::new(uv, ut, up),
            1 => Rgb::new(uq, uv, up),
            2 => Rgb::new(up, uv, ut),
            3 => Rgb::new(up, uq, uv),
            4 => Rgb::new(ut, up, uv),
            _ => Rgb::default()
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_hsv_from_rgb() {
        let rgb = Rgb {
            r: 50,
            g: 100,
            b: 100
        };

        let hsv = Hsv::from(rgb);
        assert_eq!(hsv.h, 180.0);
        assert_eq!(hsv.s, 50.0);
        assert_eq!(util::roundup(hsv.v, 1000_f64), 39.216);
    }

    #[test]
    fn expect_to_create_hsv_from_black_rgb() {
        let rgb = Rgb {
            r: 0,
            g: 0,
            b: 0
        };

        let hsv = Hsv::from(rgb);
        assert_eq!(hsv.h, 0_f64);
        assert_eq!(hsv.s, 0_f64);
        assert_eq!(hsv.v, 0_f64);
    }

    #[test]
    fn expect_to_create_rgb_from_hsv() {
        let hsv = Hsv {
            h: 180.0,
            s: 50.0,
            v: 39.21568627450981
        };

        let rgb = Rgb::from(hsv);
        assert_eq!(rgb.r, 50);
        assert_eq!(rgb.g, 100);
        assert_eq!(rgb.b, 100);
    }

    #[test]
    fn expect_to_create_rgb_from_black_hsv() {
        let hsv = Hsv {
            h: 0_f64,
            s: 0_f64,
            v: 0_f64
        };

        let rgb = Rgb::from(hsv);
        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 0);
    }
}
