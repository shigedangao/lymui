use super::hex::Hex;
use super::rgb::{FromRgb, Rgb};
use crate::error::Error;
use crate::util::AsFloat;

#[cfg(feature = "js")]
use crate::js::prelude::*;

// Constant of ansi rgb code for the lowest 16 colors
const ANSI_RGB_CODE: [&str; 16] = [
    "#000000", "#800000", "#008000", "#808000", "#000080", "#800080", "#008080", "#c0c0c0",
    "#808080", "#ff0000", "#00ff00", "#ffff00", "#0000ff", "#ff00ff", "#00ffff", "#ffffff",
];

/// Ansi is a color format that is used in terminal
/// The current implementation support the following bits formats
/// - 8 bit 256 colors
/// - 4 bit 16 colors
///
/// The implemention is based on the color-convert library
/// @link https://github.com/Qix-/color-convert/tree/master

#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug)]
pub struct Ansi(pub u8);

pub enum AnsiKind {
    C16,
    C256,
}

impl Ansi {
    /// Finalize computation from ansi to rgb
    ///
    /// # Arguments
    ///
    /// * `color` - u8
    fn finalize_computation_to_rgb(color: u8) -> u8 {
        match color {
            0 => 0,
            _ => color * 40 + 55,
        }
    }
}

impl FromRgb<AnsiKind> for Ansi {
    // Implementation based on
    // @link https://github.com/Qix-/color-convert/blob/427cbb70540bb9e5b3e94aa3bb9f97957ee5fbc0/conversions.js#L525
    fn from_rgb(rgb: Rgb, kind: AnsiKind) -> Self {
        match kind {
            AnsiKind::C16 => {
                let (r, g, b) = rgb.as_f64();
                // convert rgb to hsv
                // let hsv = Hsv::from(rgb);
                let value = f64::round(g / 50_f64);
                if value == 0_f64 {
                    return Ansi(30);
                }

                let mut ansi = 30
                    + ((f64::round(b / 255_f64) as u8) << 2
                        | (f64::round(g / 255_f64) as u8) << 1
                        | f64::round(r / 255_f64) as u8);

                if value == 2_f64 {
                    ansi += 60
                }

                Ansi(ansi)
            }
            // The 8bit (256 colors) implementation is based on the following stackoverflow post
            // @link https://stackoverflow.com/a/26665998/7489243
            AnsiKind::C256 => {
                let (r, g, b) = rgb.as_f64();

                if rgb.r == rgb.g && rgb.g == rgb.b {
                    return match rgb.r {
                        0..=8 => Ansi(16),
                        248.. => Ansi(231),
                        _ => {
                            let value = (((r - 8_f64) / 247_f64) + 232_f64).round();
                            Ansi(value as u8)
                        }
                    };
                }

                let res: f64 = 16_f64
                    + (36_f64 * (r / 255_f64 * 5_f64).round())
                    + (6_f64 * (g / 255_f64 * 5_f64).round())
                    + (b / 255_f64 * 5_f64).round();

                Ansi(res as u8)
            }
        }
    }
}

impl TryFrom<Ansi> for Rgb {
    type Error = Error;

    // Conversion based on work done by @MightyPork
    // @link https://gist.github.com/MightyPork/1d9bd3a3fd4eb1a661011560f6921b5b
    fn try_from(ansi: Ansi) -> Result<Self, Error> {
        match ansi.0 {
            0..=16 => {
                let hex_str = ANSI_RGB_CODE.get(ansi.0 as usize).unwrap();
                let hex = Hex(hex_str.to_string());
                Rgb::try_from(hex)
            }
            232..=u8::MAX => {
                let s = (ansi.0 - 232) * 10 + 8;
                Ok(Rgb { r: s, g: s, b: s })
            }
            _ => {
                let n = ansi.0 - 16;

                let mut _b = n % 6;
                let mut _g = (n - _b) / 6 % 6;
                let mut _r = (n - _b - _g * 6) / 36 % 6;

                let rgb = Rgb {
                    r: Ansi::finalize_computation_to_rgb(_r),
                    g: Ansi::finalize_computation_to_rgb(_g),
                    b: Ansi::finalize_computation_to_rgb(_b),
                };

                Ok(rgb)
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_convert_rgb_to_ansi_256_colors() {
        let rgb = Rgb {
            r: 92,
            g: 191,
            b: 84,
        };

        let ansi = Ansi::from_rgb(rgb, AnsiKind::C256);
        assert_eq!(ansi.0, 114);
    }

    #[test]
    fn expect_to_convert_rgb_to_ainsi_256_colors_same_rgb() {
        let rgb = Rgb {
            r: 250,
            g: 250,
            b: 250,
        };

        let ansi = Ansi::from_rgb(rgb, AnsiKind::C256);
        assert_eq!(ansi.0, 231);
    }

    #[test]
    fn expect_to_convert_rgb_to_ansi_8_colors() {
        let rgb = Rgb {
            r: 92,
            g: 191,
            b: 84,
        };

        let ansi = Ansi::from_rgb(rgb, AnsiKind::C16);
        assert_eq!(ansi.0, 32);
    }

    #[test]
    fn expect_to_convert_ansi_to_rgb() {
        let rgb = Rgb::try_from(Ansi(215)).unwrap();
        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 175);
        assert_eq!(rgb.b, 95);
    }

    #[test]
    fn expect_to_get_white_color_from_ansi() {
        let rgb = Rgb::try_from(Ansi(15)).unwrap();
        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 255);
        assert_eq!(rgb.b, 255);
    }

    #[test]
    fn expect_to_convert_ansi_to_rgb_grey() {
        let rgb = Rgb::try_from(Ansi(7)).unwrap();
        assert_eq!(rgb.r, 192);
        assert_eq!(rgb.g, 192);
        assert_eq!(rgb.b, 192);
    }

    #[test]
    fn expect_to_convert_ansi_to_rgb_zero() {
        let rgb = Rgb::try_from(Ansi(0)).unwrap();
        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 0);
    }
}
