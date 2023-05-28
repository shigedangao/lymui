use super::rgb::{FromRgb, Rgb};
use crate::util::AsFloat;

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Ansi is a color format that is used in terminal
/// The current implementation support the following bits formats
/// - 8 bit 256 colors
/// - 4 bit 16 colors
///
/// The implemention is based on the color-convert library
/// @link https://github.com/Qix-/color-convert/tree/master

#[cfg_attr(feature = "js", derive(FromJsObj))]
#[derive(Debug)]
pub struct Ansi(pub u8);

pub enum AnsiKind {
    C16,
    C256,
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
                        },
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
}
