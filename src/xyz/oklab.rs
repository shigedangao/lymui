use super::matrices::oklab::*;
use super::{Xyz, srgb::Srgb};
use crate::hue::{Hue, MaxSaturationHue};
use crate::ops::{AsFloat, SliceOps};

/// Oklab is a representation of the OkLab color space
/// The implementation is based on the following blog post
///
/// @link <https://bottosson.github.io/posts/oklab/>
#[derive(Debug, Clone, Copy)]
pub struct OkLab {
    pub l: f64,
    pub a: f64,
    pub b: f64,
}

impl OkLab {
    /// Finds the cusp point of the OkLab color space for the given `a` and `b` values.
    ///
    /// # Arguments
    ///
    /// * `a` - The `a` value of the OkLab color space.
    /// * `b` - The `b` value of the OkLab color space.
    pub fn find_cusp(a: f64, b: f64) -> (f64, f64, f64, f64) {
        let s_cusp = Hue::compute_max_saturation(a, b);

        let oklab = Self {
            l: 1.,
            a: s_cusp * a,
            b: s_cusp * b,
        };

        let rgb_at_max = Srgb::from(oklab);
        let l_cusp = f64::cbrt(1. / f64::max(rgb_at_max.r.max(rgb_at_max.g), rgb_at_max.b));
        let c_cusp = l_cusp * s_cusp;
        let s = c_cusp / l_cusp;
        let t = c_cusp / (1. - l_cusp);

        (l_cusp, c_cusp, s, t)
    }
}

impl SliceOps<3> for OkLab {
    type Item = f64;

    fn as_slice(&self) -> [Self::Item; 3] {
        [self.l, self.a, self.b]
    }

    fn to_vec(&self) -> Vec<Self::Item> {
        self.as_slice().to_vec()
    }

    fn from_slice(slice: &[Self::Item; 3]) -> Self {
        OkLab {
            l: slice[0],
            a: slice[1],
            b: slice[2],
        }
    }
}

impl From<Srgb> for OkLab {
    fn from(mut rgb: Srgb) -> Self {
        let (r, g, b) = rgb.as_linear().as_f64();

        let l = (OKSR[0] * r + OKSR[1] * g + OKSR[2] * b).cbrt();
        let m = (OKSG[0] * r + OKSG[1] * g + OKSG[2] * b).cbrt();
        let s = (OKSB[0] * r + OKSB[1] * g + OKSB[2] * b).cbrt();

        OkLab {
            l: OKL[0] * l + OKL[1] * m - OKL[2] * s,
            a: OKA[0] * l - OKA[1] * m + OKA[2] * s,
            b: OKB[0] * l + OKB[1] * m - OKB[2] * s,
        }
    }
}

impl From<OkLab> for Srgb {
    fn from(oklab: OkLab) -> Self {
        let OkLab { l, a, b } = oklab;

        let _l = (l + ROL[0] * a + ROL[1] * b).powi(3);
        let _m = (l - ROM[0] * a - ROM[1] * b).powi(3);
        let _s = (l - ROS[0] * a - ROS[1] * b).powi(3);

        let mut srgb = Srgb {
            r: ROR[0] * _l - ROR[1] * _m + ROR[2] * _s,
            g: ROG[0] * _l + ROG[1] * _m - ROG[2] * _s,
            b: ROB[0] * _l - ROB[1] * _m + ROB[2] * _s,
        };

        srgb.as_non_linear();
        srgb
    }
}

impl From<Xyz> for OkLab {
    fn from(xyz: Xyz) -> Self {
        let srgb = Srgb::from(xyz);

        OkLab::from(srgb)
    }
}

impl From<OkLab> for Xyz {
    fn from(oklab: OkLab) -> Self {
        let srgb = Srgb::from(oklab);

        Xyz::from(srgb)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_oklab() {
        let rgb = Srgb {
            r: 0.19608,
            g: 0.03922,
            b: 0.37255,
        };

        let oklab = OkLab::from(rgb);
        util::assert_approx!(oklab.l, 0.26368, 1e-5);
        util::assert_approx!(oklab.a, 0.06116, 1e-5);
        util::assert_approx!(oklab.b, -0.1258, 1e-5);
    }

    #[test]
    fn expect_to_compute_srgb() {
        let lab = OkLab {
            l: 0.26368282277639926,
            a: 0.06116371608383586,
            b: -0.12579731956598594,
        };

        let srgb = Srgb::from(lab);
        util::assert_approx!(srgb.r, 0.19608, 1e-5);
        util::assert_approx!(srgb.g, 0.03922, 1e-5);
        util::assert_approx!(srgb.b, 0.37255, 1e-5);
    }
}
