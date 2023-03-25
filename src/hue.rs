use crate::rgb::Rgb;

/// Implementation of the Hue. Computation is based on the article below
/// 
/// @link https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
pub type Hue = f64;

impl From<Rgb> for Hue {
    fn from(rgb: Rgb) -> Self {
        let (min, max) = rgb.get_min_max();
        if min == max {
            return 0.0
        }

        let (r, g, b) = rgb.as_f64();

        let mut hue = if max == r {
            (g - b) / (max - min)
        } else if max == g {
            2.0 + (b - r) / (max - min)
        } else {
            4.0 + (r - g) / (max - min)
        };

        hue *= 60.0;
        if hue < 0.0 {
            hue += 360.0
        }

        hue.round()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_hue_from_white_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255
        };

        let hue = Hue::from(rgb);
        assert_eq!(hue, 0.0);
    }

    #[test]
    fn expect_to_create_hue_from_purple_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 100,
            b: 255
        };

        let hue = Hue::from(rgb);
        assert_eq!(hue, 300.0);
    }
}
