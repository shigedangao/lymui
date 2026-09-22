use crate::ops::AsFloat;
use crate::rgb::Rgb;
use crate::xyz::luv::Luv;

/// Implementation of the Hue. Computation is based on the article below
///
/// @link <https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/>
pub type Hue = f64;

/// Represents the maximum saturation hue for a given `a` and `b` value.
pub trait MaxSaturationHue {
    /// Computes the maximum saturation hue for the given `a` and `b` values.
    ///
    /// # Arguments
    ///
    /// * `a` - The `a` value.
    /// * `b` - The `b` value.
    ///
    /// # Returns
    ///
    /// The maximum saturation hue as a `Hue` value.
    fn compute_max_saturation(a: f64, b: f64) -> Self;

    /// Computes the LMS units for the given `s` and `unit` values.
    ///
    /// # Arguments
    ///
    /// * `s` - The `s` value.
    /// * `unit` - The `unit` value.
    ///
    /// # Returns
    ///
    /// The LMS units as a tuple of `(s, s^3)`.
    fn compute_lms_units(s: f64, unit: f64) -> (f64, f64) {
        let formula = 1. + s * unit;

        (formula, formula.powf(3.))
    }

    /// Computes the LDS value for the given `factor`, `multiplier`, and `unit` values.
    ///
    /// # Arguments
    ///
    /// * `factor` - The `factor` value.
    /// * `multiplier` - The `multiplier` value.
    /// * `unit` - The `unit` value.
    ///
    /// # Returns
    ///
    /// The LDS value as a `f64`.
    fn compute_lds(factor: f64, multiplier: f64, unit: f64) -> f64 {
        factor * multiplier.powf(2.) * unit
    }
}

impl MaxSaturationHue for Hue {
    fn compute_max_saturation(a: f64, b: f64) -> Self {
        let (k0, k1, k2, k3, k4, wl, wm, ws) = match (a, b) {
            (a, b) if (-1.88170328 * a - 0.80936493 * b > 1.) => (
                max_saturation_hue_srgb::RED[0],
                max_saturation_hue_srgb::RED[1],
                max_saturation_hue_srgb::RED[2],
                max_saturation_hue_srgb::RED[3],
                max_saturation_hue_srgb::RED[4],
                max_saturation_hue_srgb::RED[5],
                max_saturation_hue_srgb::RED[6],
                max_saturation_hue_srgb::RED[7],
            ),
            (a, b) if (1.81444104 * a - 1.19445276 * b > 1.) => (
                max_saturation_hue_srgb::GREEN[0],
                max_saturation_hue_srgb::GREEN[1],
                max_saturation_hue_srgb::GREEN[2],
                max_saturation_hue_srgb::GREEN[3],
                max_saturation_hue_srgb::GREEN[4],
                max_saturation_hue_srgb::GREEN[5],
                max_saturation_hue_srgb::GREEN[6],
                max_saturation_hue_srgb::GREEN[7],
            ),
            _ => (
                max_saturation_hue_srgb::BLUE[0],
                max_saturation_hue_srgb::BLUE[1],
                max_saturation_hue_srgb::BLUE[2],
                max_saturation_hue_srgb::BLUE[3],
                max_saturation_hue_srgb::BLUE[4],
                max_saturation_hue_srgb::BLUE[5],
                max_saturation_hue_srgb::BLUE[6],
                max_saturation_hue_srgb::BLUE[7],
            ),
        };

        let s = k0 + k1 * a + k2 * b + k3 * a * a + k4 * a * b;

        let k_l = 0.3963377774 * a + 0.2158037573 * b;
        let k_m = -0.1055613458 * a - 0.0638541728 * b;
        let k_s = -0.0894841775 * a - 1.2914855480 * b;

        let (l_, l) = Self::compute_lms_units(s, k_l);
        let (m_, m) = Self::compute_lms_units(s, k_m);
        let (s_, s) = Self::compute_lms_units(s, k_s);

        let l_ds = Self::compute_lds(3., l_, k_l);
        let m_ds = Self::compute_lds(3., l_, k_m);
        let s_ds = Self::compute_lds(3., l_, k_s);

        let l_ds2 = Self::compute_lds(6., k_l, l_);
        let m_ds2 = Self::compute_lds(6., k_m, m_);
        let s_ds2 = Self::compute_lds(6., k_s, s_);

        let f = wl * l + wm * m + ws * s;
        let f1 = wl * l_ds + wm * m_ds + ws * s_ds;
        let f2 = wl * l_ds2 + wm * m_ds2 + ws * s_ds2;

        s - f * f1 / (f1 * f1 - 0.5 * f * f2)
    }
}

impl From<Rgb> for Hue {
    fn from(rgb: Rgb) -> Self {
        let (min, max) = rgb.get_min_max();
        if min == max {
            return 0.0;
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

impl From<Luv> for Hue {
    fn from(luv: Luv) -> Self {
        let h = luv.v.atan2(luv.u).to_degrees();

        if h > 360_f64 {
            h - 360_f64
        } else if h < 0.0 {
            h + 360_f64
        } else {
            h
        }
    }
}

/// Precomputed max saturation hue values for sRGB colors.
pub mod max_saturation_hue_srgb {
    pub(crate) const RED: [f64; 8] = [
        1.19086277,
        1.76576728,
        0.59662641,
        0.75515197,
        0.56771245,
        4.0767416621,
        -3.3077115913,
        0.2309699292,
    ];
    pub(crate) const GREEN: [f64; 8] = [
        0.73956515,
        -0.45954404,
        0.08285427,
        0.12541070,
        0.14503204,
        -1.2684380046,
        2.6097574011,
        -0.3413193965,
    ];
    pub(crate) const BLUE: [f64; 8] = [
        1.35733652,
        -0.00915799,
        -1.15130210,
        -0.50559606,
        0.00692167,
        -0.0041960863,
        -0.7034186147,
        1.7076147010,
    ];
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_hue_from_white_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let hue = Hue::from(rgb);
        assert_eq!(hue, 0.0);
    }

    #[test]
    fn expect_to_create_hue_from_purple_rgb() {
        let rgb = Rgb {
            r: 255,
            g: 100,
            b: 255,
        };

        let hue = Hue::from(rgb);
        assert_eq!(hue, 300.0);
    }
}
