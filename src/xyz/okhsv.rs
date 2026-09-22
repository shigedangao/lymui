use std::f64::consts::PI;

use crate::ops::SliceOps;
use crate::xyz::oklab::OkLab;

use super::srgb::Srgb;
use super::transfer::GammaCorrection;

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
