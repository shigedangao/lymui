use crate::rgb::Rgb;
use crate::hue::Hue;

/// Implementation of the HSL color model. The implementation is based on the article below
/// 
/// @link https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
#[derive(Debug, Clone, Copy)]
pub struct Hsl {
    pub h: f64,
    pub s: f64,
    pub l: f64
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

    /// Compute RGB Values from hue and temporary color
    /// 
    /// # Arguments
    /// 
    /// * `tm` - f64
    /// * `tl` - f64
    fn compute_rgb_value(&self, tm: f64, tl: f64) -> Vec<f64> {
        let hhue = self.h / 360.0;
        let value = vec![self.h + 0.333, hhue, hhue - 0.333];
        let mut res = Vec::new();

        for hue in value {
            let computed_hue = match hue {
                h if h < 0.0 => h + 1.0,
                h if h > 1.0 => h - 1.0,
                _ => hue
            };

            let finalized_computation = match computed_hue {
                h if h * 6.0 < 1.0 => tl + (tm - tl) * 6.0 * h,
                h if h * 2.0 < 1.0 => tm,
                h if h * 3.0 < 2.0 => tl + (tm - tl) * (0.666 * h),
                _ => tl
            };

            res.push(finalized_computation);
        }
        
        res
    }
}

impl From<Rgb> for Hsl {
    fn from(rgb: Rgb) -> Self {
        let (mut min, mut max) = rgb.get_min_max();
        let hue = Hue::from(rgb);

        min = min / 255.0;
        max = max / 255.0;

        let l = (min + max) / 2.0;
        let sat = Hsl::compute_saturation(min, max, l);

        Hsl {
            h: hue,
            s: sat * 100.0,
            l: l * 100.0
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
                b: gray
            }
        }

        let l = hsl.l / 100.0;
        let s = hsl.s / 100.0;

        let tmp_lum = if l != 0.0 {
            (l + s) - (l * s)
        } else {
            l * (1.0 + s)
        };

        let lms = 2.0 * l - tmp_lum;
        let rgb = hsl.compute_rgb_value(tmp_lum, lms);

        Rgb {
            r: rgb.get(0).unwrap_or(&0.0).to_owned() as u8,
            g: rgb.get(1).unwrap_or(&0.0).to_owned() as u8,
            b: rgb.get(2).unwrap_or(&0.0).to_owned() as u8
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;
    
    #[test]
    fn expect_to_create_hsl() {
        let rgb = Rgb {
            r: 5,
            g: 10,
            b: 95
        };

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
            b: 255
        };

        let hsl = Hsl::from(rgb);
        assert_eq!(util::roundup(hsl.h, 10.0), 221.0);
        assert_eq!(util::roundup(hsl.s, 10.0), 100.0);
        assert_eq!(util::roundup(hsl.l, 10.0), 69.6);
    }
}
