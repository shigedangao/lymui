use crate::rgb::{Rgb, FromRgb};
use crate::util::AsFloat;

pub type GrayScale = u8;

pub enum Kind {
    Lightness,
    Average,
    Luminosity,
    BT709,
    BT2100
}

impl FromRgb<Kind> for GrayScale {
    fn from_rgb(rgb: Rgb, kind: Kind) -> Self {
        let (r, g, b) = rgb.as_f64();

        let grayscale = match kind {
            Kind::Lightness => {
                let (min, max) = rgb.get_min_max();
                (min + max) / 2.0
            },
            Kind::Average => (r + g + b) / 3.0,
            Kind::Luminosity => 0.21 * r + 0.72 * g + 0.07 * b,
            Kind::BT709 => 0.2126 * r + 0.7152 * g + 0.0722 * b,
            Kind::BT2100 => 0.2627 * r + 0.6780 * g + 0.0593 * b
        };

        grayscale as u8
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_create_grayscale_lightness() {
        let rgb = Rgb {
            r: 255,
            g: 0,
            b: 0
        };

        let g = GrayScale::from_rgb(rgb, Kind::Lightness);
        assert_eq!(g, 127);
    }

    #[test]
    fn expect_to_create_grayscale_average() {
        let rgb = Rgb {
            r: 255,
            g: 0,
            b: 0
        };

        let g = GrayScale::from_rgb(rgb, Kind::Average);
        assert_eq!(g, 85);
    }

    #[test]
    fn expect_to_create_grayscale_luminosity() {
        let rgb = Rgb {
            r: 255,
            g: 0,
            b: 0
        };

        let g = GrayScale::from_rgb(rgb, Kind::Luminosity);
        assert_eq!(g, 53);
    }

    #[test]
    fn expect_to_create_grayscale_bt709() {
        let rgb = Rgb {
            r: 255,
            g: 0,
            b: 0
        };

        let g = GrayScale::from_rgb(rgb, Kind::BT709);
        assert_eq!(g, 54);
    }

    #[test]
    fn expect_to_create_grayscale_bt2100() {
        let rgb = Rgb {
            r: 255,
            g: 0,
            b: 0
        };

        let g = GrayScale::from_rgb(rgb, Kind::BT2100);
        assert_eq!(g, 66);
    }
}
