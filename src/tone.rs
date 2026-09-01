use crate::ops::SliceOps;
use crate::rgb::Rgb;
use crate::xyz::srgb::Srgb;

/// Tone implements the computation of a tone from a given RGB input.
#[derive(Debug)]
pub struct Tone(pub f64);

impl From<Rgb> for Tone {
    fn from(rgb: Rgb) -> Self {
        // First convert the rgb to srgb
        let srgb = Srgb::from(rgb);

        // Compute the luminance by using the BT709 standard
        let y = 0.2126 * srgb.r + 0.7152 * srgb.g + 0.0722 * srgb.b;

        // Based on this formula -> https://github.com/material-foundation/material-color-utilities/blob/ec7c4da3e0774264275377cd6b7687474bad577a/dart/lib/utils/color_utils.dart#L234
        let tone = match y {
            y if y <= 216. / 24_389. => y * 903.2963,
            _ => y.cbrt() * 116. - 16.,
        };

        Self(tone)
    }
}

impl SliceOps<1> for Tone {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 1] {
        [self.0]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        vec![self.0]
    }

    fn from_slice(slice: &[Self::Item; 1]) -> Self {
        Self(slice[0])
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_get_tone_for_dark_red() {
        let rgb = Rgb { r: 128, g: 0, b: 0 };

        let tone = Tone::from(rgb);
        assert_eq!(25.531, util::roundup(tone.0, 1000.0))
    }

    #[test]
    fn expect_to_get_tone_for_red() {
        let rgb = Rgb { r: 255, g: 0, b: 0 };

        let tone = Tone::from(rgb);
        assert_eq!(53.233, util::roundup(tone.0, 1000.0))
    }

    #[test]
    fn expect_to_get_tone_for_white() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let tone = Tone::from(rgb);
        assert_eq!(100., tone.0);
    }
}
