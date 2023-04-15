use crate::hue::Hue;
use crate::rgb::Rgb;
use crate::util::AsVec;

/// Implementation of the HSL color model. The implementation is based on the article below
///
/// @link https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
/// @link https://en.wikipedia.org/wiki/HSL_and_HSV
#[derive(Debug, Clone, Copy)]
pub struct Hsl {
    pub h: f64,
    pub s: f64,
    pub l: f64,
}

impl Hsl {
    /// Compute the saturation S
    ///
    /// # Arguments
    ///
    /// * `min` - f64
    /// * `max` - f64
    /// * `l` - f64
    fn compute_saturation(min: f64, max: f64, l: f64) -> f64 {
        if l > 0.5 && (max != 1.0 || min != 1.0) {
            return (max - min) / (2.0 - max - min);
        }

        if max == 0.0 && min == 0.0 {
            0.0
        } else {
            (max - min) / (max + min)
        }
    }

    /// Compute the shade of grey based on the existing luminance
    fn compute_shade_of_grey(&self) -> u8 {
        let gray = self.l / 100.0 * 255.0;

        gray as u8
    }

    /// Compute RGB Values from hue
    ///
    /// # Arguments
    ///
    /// * `c` - f64
    fn compute_rgb_value(&self, c: f64) -> (f64, f64, f64) {
        let h = self.h / 60_f64;
        let x = c * (1_f64 - (h % 2_f64 - 1_f64).abs());

        match h.floor() {
            _h if _h < 1_f64 => (c, x, 0_f64),
            _h if _h <= 1_f64 && _h < 2_f64 => (x, c, 0_f64),
            _h if _h <= 2_f64 && _h < 3_f64 => (0_f64, c, x),
            _h if _h <= 3_f64 && _h < 4_f64 => (0_f64, x, c),
            _h if _h <= 4_f64 && _h < 5_f64 => (x, 0_f64, c),
            _h if _h <= 5_f64 && _h < 6_f64 => (c, 0_f64, x),
            _ => (0_f64, 0_f64, 0_f64),
        }
    }
}

impl From<Rgb> for Hsl {
    fn from(rgb: Rgb) -> Self {
        let (mut min, mut max) = rgb.get_min_max();
        let hue = Hue::from(rgb);

        min /= 255_f64;
        max /= 255_f64;

        let l = (min + max) / 2.0;
        let sat = Hsl::compute_saturation(min, max, l);

        Hsl {
            h: hue,
            s: sat * 100.0,
            l: l * 100.0,
        }
    }
}

impl From<Hsl> for Rgb {
    fn from(hsl: Hsl) -> Self {
        if hsl.h == 0.0 && hsl.s == 0.0 {
            let gray = hsl.compute_shade_of_grey();
            return Rgb {
                r: gray,
                g: gray,
                b: gray,
            };
        }

        let l = hsl.l / 100_f64;
        let s = hsl.s / 100_f64;

        let c = (1_f64 - (2_f64 * l - 1_f64).abs()) * s;
        // Compute the compound based on the hue
        let (_r, _g, _b) = hsl.compute_rgb_value(c);
        let m = l - (c / 2_f64);

        Rgb {
            r: ((_r + m) * 255_f64).round() as u8,
            g: ((_g + m) * 255_f64).round() as u8,
            b: ((_b + m) * 255_f64).round() as u8,
        }
    }
}

impl AsVec for Hsl {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.h, self.s, self.l]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_create_hsl() {
        let rgb = Rgb { r: 5, g: 10, b: 95 };

        let hsl = Hsl::from(rgb);
        assert_eq!(util::roundup(hsl.h, 10.0), 237.0);
        assert_eq!(util::roundup(hsl.s, 10.0), 90.0);
        assert_eq!(util::roundup(hsl.l, 10.0), 19.6);
    }

    #[test]
    fn expect_to_create_saturate_hsl() {
        let rgb = Rgb {
            r: 100,
            g: 150,
            b: 255,
        };

        let hsl = Hsl::from(rgb);
        assert_eq!(util::roundup(hsl.h, 10.0), 221.0);
        assert_eq!(util::roundup(hsl.s, 10.0), 100.0);
        assert_eq!(util::roundup(hsl.l, 10.0), 69.6);
    }

    #[test]
    fn expect_to_create_rgb_from_hsl() {
        let hsl = Hsl {
            h: 237.0,
            s: 90.0,
            l: 19.6,
        };

        let rgb = Rgb::from(hsl);
        assert_eq!(rgb.r, 5);
        assert_eq!(rgb.g, 9);
        assert_eq!(rgb.b, 95);
    }

    #[test]
    fn expect_to_create_rgb_from_hsl_navy() {
        let hsl = Hsl {
            h: 240.0,
            s: 100.0,
            l: 25.0,
        };

        let rgb = Rgb::from(hsl);
        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 128);
    }
}
