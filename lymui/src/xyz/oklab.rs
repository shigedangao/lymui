use super::matrices::oklab::*;
use super::{srgb::Srgb, Xyz};
use crate::util::{AsVec, FromVec};

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Oklab is a representation of the OkLab color space
/// The implementation is based on the following blog post
///
/// @link https://bottosson.github.io/posts/oklab/
#[cfg_attr(feature = "js", derive(FromJsObj))]
#[derive(Debug, Clone, Copy)]
pub struct OkLab {
    pub l: f64,
    pub a: f64,
    pub b: f64,
}

impl AsVec for OkLab {
    type Item = f64;

    fn as_vec(&self) -> Vec<Self::Item> {
        vec![self.l, self.a, self.b]
    }
}

impl FromVec<f64> for OkLab {
    fn from_vec(vec: Vec<f64>) -> Self {
        OkLab {
            l: vec.first().copied().unwrap_or_default(),
            a: vec.get(1).copied().unwrap_or_default(),
            b: vec.last().copied().unwrap_or_default(),
        }
    }
}

impl From<Srgb> for OkLab {
    fn from(mut rgb: Srgb) -> Self {
        rgb.as_linear();
        let Srgb { r, g, b } = rgb;

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
        assert_eq!(util::roundup(oklab.l, 100000.0), 0.26368);
        assert_eq!(util::roundup(oklab.a, 100000.0), 0.06116);
        assert_eq!(util::roundup(oklab.b, 100000.0), -0.1258);
    }

    #[test]
    fn expect_to_compute_srgb() {
        let lab = OkLab {
            l: 0.26368282277639926,
            a: 0.06116371608383586,
            b: -0.12579731956598594,
        };

        let srgb = Srgb::from(lab);
        assert_eq!(util::roundup(srgb.r, 100000.0), 0.19608);
        assert_eq!(util::roundup(srgb.g, 100000.0), 0.03922);
        assert_eq!(util::roundup(srgb.b, 100000.0), 0.37255);
    }
}
