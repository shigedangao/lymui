use super::srgb::Srgb;
use super::transfer::GammaCorrection;
use crate::ops::SliceOps;
use crate::xyz::oklab::OkLab;
use std::f64::consts::PI;

// Constants
const S0: f64 = 0.5;

#[derive(Debug, Clone, Copy)]
pub struct OkHSV {
    pub h: f64,
    pub s: f64,
    pub v: f64,
}

impl OkHSV {
    /// Converts an sRGB color to an OkHSV color.
    ///
    /// # Arguments
    ///
    /// * `srgb` - The sRGB color to convert.
    fn new(srgb: Srgb) -> Self {
        let r_gamma = srgb.r.compute_srgb_gamma_expanded();
        let g_gamma = srgb.g.compute_srgb_gamma_expanded();
        let b_gamma = srgb.b.compute_srgb_gamma_expanded();

        let reconstructed_srgb = Srgb::from_slice(&[r_gamma, g_gamma, b_gamma]);

        let lab = OkLab::from(reconstructed_srgb);
        let c_c = f64::sqrt(lab.a * lab.a + lab.b * lab.b);
        let a_ = lab.a / c_c;
        let b_ = lab.b / c_c;

        let mut l_l = lab.l;
        let h = 0.5 + 0.5 * f64::atan2(-lab.b, -lab.a) / PI;

        let (l, c, s_max, t_max) = OkLab::find_cusp(a_, b_);
        let k = 1. - S0 / s_max;

        let t = t_max / (c + l * t_max);
        let l_v = t * l_l;
        let c_v = t * c_c;

        let l_vt = l_v.toe_inv();
        let c_vt = c_v * l_vt / l_v;

        let rgb_scale = Srgb::from(OkLab::from_slice(&[l_vt, a_ * c_vt, b_ * c_vt]));
        let scale_l = f64::cbrt(1. / f64::max(rgb_scale.r.max(rgb_scale.g), rgb_scale.b.max(0.)));

        l_l = (l_l / scale_l).toe();

        let v = l_l / l_v;
        let s = (S0 + t_max) * c_v / ((t_max * S0) + t_max * k * c_v);

        OkHSV { h, s, v }
    }
}

impl From<Srgb> for OkHSV {
    fn from(value: Srgb) -> Self {
        Self::new(value)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_compute_okhsv() {
        let srgb = Srgb {
            r: 0.2,
            g: 0.4,
            b: 0.7019607843,
        };

        let okhsv = OkHSV::from(srgb);
        dbg!(okhsv);
    }
}
