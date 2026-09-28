use super::matrices::oklab::*;
use crate::hue::{Hue, LmsUnit, MaxSaturationHue};

/// Halley implements the Halley's method for any numerical number
pub trait Halley {
    /// Compute Halley compute the halley's simplification
    ///
    /// # Arguments
    ///
    /// * `l0` - f64
    /// * `l1` - f64
    /// * `c1` - f64
    /// * `a` - f64
    /// * `b` - f64
    /// * `t` - f64
    fn compute_halley(l0: f64, l1: f64, c1: f64, a: f64, b: f64, t: f64) -> f64 {
        let dl = l1 - l0;

        let k_l = 0.396_337_777_4 * a + 0.215_803_757_3 * b;
        let k_m = -0.105_561_345_8 * a - 0.063_854_172_8 * b;
        let k_s = -0.089_484_177_5 * a - 1.291_485_548_0 * b;

        let l_dt = dl + c1 * k_l;
        let m_dt = dl + c1 * k_m;
        let s_dt = dl + c1 * k_s;

        let l = l0 * (1. - t) + t * l1;
        let c = t * c1;

        let (l_, l) = Hue::compute_lms_units(LmsUnit::OkHsl(l, c, k_l));
        let (m_, m) = Hue::compute_lms_units(LmsUnit::OkHsl(l, c, k_m));
        let (s_, s) = Hue::compute_lms_units(LmsUnit::OkHsl(l, c, k_s));

        let ldt = Hue::compute_lds(3., l_, l_dt);
        let mdt = Hue::compute_lds(3., m_, m_dt);
        let sdt = Hue::compute_lds(3., s_, s_dt);

        let ldt2 = Hue::compute_lds(6., l_dt, l_);
        let mdt2 = Hue::compute_lds(6., m_dt, m_);
        let sdt2 = Hue::compute_lds(6., s_dt, s_);

        let r = ROR[0] * l - ROR[1] * m + ROR[2] * s - 1.;
        let r1 = ROR[0] * ldt - ROR[1] * mdt + ROR[2] * sdt;
        let r2 = ROR[0] * ldt2 - ROR[1] * mdt2 + ROR[2] * sdt2;

        let u_r = r1 / (r1 * r1 - 0.5 * r * r2);
        let t_r = -r * u_r;

        let g = ROG[0] * l + ROG[1] * m + ROG[2] * s - 1.;
        let g1 = ROG[0] * ldt + ROG[1] * mdt - ROG[2] * sdt;
        let g2 = ROG[0] * ldt2 + ROG[1] * mdt2 - ROG[2] * sdt2;

        let u_g = g1 / (g1 * g1 - 0.5 * g * g2);
        let t_g = -g * u_g;

        let b = ROB[0] * l - ROB[1] * m + ROB[2] * s - 1.;
        let b1 = ROB[0] * ldt - ROB[1] * mdt + ROB[2] * sdt;
        let b2 = ROB[0] * ldt2 - ROB[1] * mdt2 + ROB[2] * sdt2;

        let u_b = b1 / (b1 * b1 - 0.5 * b * b2);
        let t_b = -b * u_b;

        let t_r = Self::clamp(u_r, t_r);
        let t_g = Self::clamp(u_g, t_g);
        let t_b = Self::clamp(u_b, t_b);

        t + f64::min(t_r, f64::min(t_g, t_b))
    }

    /// Clamp between t -> f64::MAX
    ///
    /// # Arguments
    ///
    /// * `u` - f64
    /// * `t` - f64
    fn clamp(u: f64, t: f64) -> f64 {
        if u >= 0. {
            return t;
        }

        f64::MAX
    }
}

impl Halley for f64 {}
