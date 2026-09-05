use crate::rgb::Rgb;

/// YCbCr (YDbDr) color space
/// The implementation uses the formulas below
/// @link <https://en.wikipedia.org/wiki/YDbDr>
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Ydbdr {
    pub y: f64,
    pub db: f64,
    pub dr: f64,
}

impl Ydbdr {
    pub fn new(r: f64, g: f64, b: f64) -> Self {
        Self {
            y: 0.299 * r + 0.587 * g + 0.114 * b,
            db: -0.450 * r - 0.883 * g + 1.333 * b,
            dr: -1.333 * r + 1.116 * g + 0.217 * b,
        }
    }
}

impl From<Rgb> for Ydbdr {
    fn from(rgb: Rgb) -> Self {
        let (r, g, b) = rgb.linear_rescaling();

        Self::new(r, g, b)
    }
}

impl From<Ydbdr> for Rgb {
    fn from(value: Ydbdr) -> Self {
        let r = value.y + 0.000092303716148 * value.db - 0.525912630661865 * value.dr;
        let g = value.y - 0.129132898890509 * value.db + 0.267899328207599 * value.dr;
        let b = value.y - 0.664679059978955 * value.db - 0.000079202543533 * value.dr;

        Self {
            r: r.round() as u8,
            g: g.round() as u8,
            b: b.round() as u8,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_ydbdr_and_back() {
        let rgb = Rgb {
            r: 100,
            g: 100,
            b: 100,
        };

        let ydbdr = Ydbdr::from(rgb);

        let new_rgb = Rgb::from(ydbdr);
        assert_eq!(rgb, new_rgb);
    }

    #[test]
    fn expect_to_compute_ydbdr_for_black() {
        let rgb = Rgb { r: 0, g: 0, b: 0 };

        let ydbdr = Ydbdr::from(rgb);
        assert_eq!(ydbdr.y, 0.);
        assert_eq!(ydbdr.db, 0.);
        assert_eq!(ydbdr.dr, 0.);
    }

    #[test]
    fn expect_to_compute_ydbdr_for_white() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let ydbdr = Ydbdr::from(rgb);
        assert_eq!(ydbdr.y.round(), 1.);
        assert_eq!(ydbdr.db, 0.);
        assert_eq!(ydbdr.dr, 0.);
    }
}
