use super::srgb::Srgb;
use super::transfer::GammaCorrection;
use crate::ops::SliceOps;
use crate::xyz::oklab::OkLab;
use std::f64::consts::PI;

// Constants
const SO: f64 = 0.5;

#[derive(Debug, Clone, Copy)]
pub struct OkHSV {
    pub h: f64,
    pub s: f64,
    pub v: f64,
}

impl OkHSV {
    fn new(srgb: Srgb) -> Self {
        let r_gamma = srgb.r.compute_srgb_gamma_expanded();
        let g_gamma = srgb.g.compute_srgb_gamma_expanded();
        let b_gamma = srgb.b.compute_srgb_gamma_expanded();

        let reconstructed_srgb = Srgb::from_slice(&[r_gamma, g_gamma, b_gamma]);

        let lab = OkLab::from(reconstructed_srgb);
        let c = f64::sqrt(lab.a * lab.a + lab.b * lab.b);
        let a_ = lab.a / c;
        let b_ = lab.b / c;

        let l = lab.l;
        let h = 0.5 + 0.5 * f64::atan2(-lab.b, -lab.a) / PI;

        let (l, c, s_max, t_max) = OkLab::find_cusp(a_, b_);
        let k = 1. - SO / s_max;

        let t = t_max / (c + l * t_max);
        let l_v = t * l;
        let c_v = t * c;

        let l_vt = l_v.toe_inv();
        let c_vt = c_v * l_vt / l_v;

        let rgb_scale = Srgb::from(OkLab::from_slice(&[l_vt, a_ * c_vt, b_ * c_vt]));

        OkHSV {
            h: 0.,
            s: 0.,
            v: 0.,
        }
    }
}

impl From<Srgb> for OkHSV {
    fn from(value: Srgb) -> Self {
        Self::new(value)
    }
}
