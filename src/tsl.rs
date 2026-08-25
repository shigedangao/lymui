use super::rgb::Rgb;
use std::f64::consts::PI;

/// TSL (Tint, Saturation, Lightness) computation based on the given forumlas defined on the article below
/// @link <https://en.wikipedia.org/wiki/TSL_color_space>
#[derive(Debug, Clone, Copy)]
pub struct Tsl {
    t: f64,
    s: f64,
    l: f64,
}

impl Tsl {
    /// Compute a new TSL from a given rescaled RGB value
    ///
    /// # Arguments
    ///
    /// * `r` - f64
    /// * `g` - f64
    /// * `b` - f64
    fn new(r: f64, g: f64, b: f64) -> Self {
        let r_prime = (r / (r + g + b)) - (1. / 3.);
        let g_prime = (g / (r + g + b)) - (1. / 3.);

        let t = if r_prime == 0. && g_prime == 0. {
            0.
        } else {
            0.5 - g_prime.atan2(r_prime) / (2. * PI)
        };

        Self {
            t,
            s: f64::sqrt(9. / 5. * (r_prime.powf(2.) + g_prime.powf(2.))),
            l: 0.299 * r + 0.587 * g + 0.114 * b,
        }
    }

    /// Compute an RGB from a given TSL value
    ///
    /// # Arguments
    ///
    /// * `self` - Self (TSL)
    fn compute_rgb(self) -> Rgb {
        let x = f64::tan(2. * PI * (self.t - 0.25)).powf(2.);
        let mut r_prime = f64::sqrt((5. * self.s.powf(2.)) / (9. * (x.powf(-1.) + 1.)));
        let g_prime = f64::sqrt((5. * self.s.powf(2.)) / (9. * (x + 1.)));

        match self.t {
            t if (0.0..=0.25).contains(&t) => r_prime = -r_prime,
            t if (0.75..=1.0).contains(&t) => r_prime = -r_prime,
            _ => {}
        }

        let r = r_prime + 1. / 3.;
        let g = g_prime + 1. / 3.;
        let k = self.l / (0.185 * r + 0.473 * g + 0.114);

        Rgb {
            r: ((k * r) * 255.).round() as u8,
            g: ((k * g) * 255.).round() as u8,
            b: ((k * (1. - r - g)) * 255.).round() as u8,
        }
    }
}

impl From<Rgb> for Tsl {
    fn from(rgb: Rgb) -> Self {
        let (r, g, b) = rgb.linear_rescaling();

        Self::new(r, g, b)
    }
}

impl From<Tsl> for Rgb {
    fn from(tsl: Tsl) -> Self {
        tsl.compute_rgb()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_tsl() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let tsl = Tsl::from(rgb);
        let converted_rgb = Rgb::from(tsl);

        assert_eq!(rgb, converted_rgb);
    }

    #[test]
    fn expect_to_compute_another_tsl() {
        let rgb = Rgb {
            r: 10,
            g: 20,
            b: 30,
        };

        let tsl = Tsl::from(rgb);
        let converted_rgb = Rgb::from(tsl);

        assert_eq!(rgb, converted_rgb);
    }
}
