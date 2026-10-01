use super::matrices::oklab::*;
use super::{srgb::Srgb, transfer::GammaCorrection};
use crate::hue::{Hue, LmsUnit, MaxSaturationHue};
use crate::xyz::oklab::OkLab;
use std::f64::consts::PI;

// Constants
const MID: f64 = 0.8;
const MID_INV: f64 = 1.25;

#[derive(Debug, Clone, Copy)]
pub struct OkHSL {
    pub h: f64,
    pub s: f64,
    pub l: f64,
}

#[derive(Debug)]
pub struct Cs {
    pub c_0: f64,
    pub c_mid: f64,
    pub c_max: f64,
}

#[derive(Debug)]
struct CsArgs {
    a: f64,
    b: f64,
    l1: f64,
    c1: f64,
    l0: f64,
    lc_cusp: f64,
    cs_cusp: f64,
}

pub trait Halley {
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

    fn clamp(u: f64, t: f64) -> f64 {
        if u >= 0. {
            return t;
        }

        f64::MAX
    }
}

impl Halley for f64 {}

impl OkHSL {
    /// Converts an sRGB color to OkHSL color space.
    ///
    /// # Arguments
    ///
    /// * `srgb` - The sRGB color to convert.
    pub fn new(srgb: Srgb) -> Self {
        let r_gamma = srgb.r.compute_srgb_gamma_expanded();
        let g_gamma = srgb.g.compute_srgb_gamma_expanded();
        let b_gamma = srgb.b.compute_srgb_gamma_expanded();
        // Creating the associated OkLab color
        let lab = OkLab::new(r_gamma, g_gamma, b_gamma);

        let c_c = f64::sqrt(lab.a * lab.a + lab.b * lab.b);
        let a_ = lab.a / c_c;
        let b_ = lab.b / c_c;

        let h = 0.5 + 0.5 * f64::atan2(-lab.b, -lab.a) / PI;

        let cs = Cs::new(lab.l, a_, b_);
        let s = match c_c < cs.c_mid {
            true => {
                let k1 = cs.c_mid * cs.c_0;
                let k2 = 1. - k1 / cs.c_mid;

                let t = c_c / (k1 + k2 * c_c);

                t * MID
            }
            false => {
                let k1 = (1. - MID) * cs.c_mid.powf(2.) * MID_INV.powf(2.) / cs.c_0;
                let k2 = 1. - k1 / (cs.c_max - cs.c_mid);

                let t = (c_c - cs.c_mid) / (k1 + k2 * (c_c - cs.c_mid));

                MID + (1. - MID) * t
            }
        };

        Self {
            h,
            s,
            l: lab.l.toe(),
        }
    }
}

impl Cs {
    /// Creates a new `Cs` color space from the given OkLab color components.
    ///
    /// # Arguments
    ///
    /// * `l` - The lightness component of the OkLab color.
    /// * `a` - The a component of the OkLab color.
    /// * `b` - The b component of the OkLab color.
    fn new(l: f64, a: f64, b: f64) -> Self {
        let (lc, cs, s_max, t_max) = OkLab::find_cusp(a, b);
        let c_max = Self::find_gamut_intersection(CsArgs {
            a,
            b,
            l1: l,
            c1: 1.,
            l0: l,
            lc_cusp: lc,
            cs_cusp: cs,
        });

        let k = c_max / f64::min(l * s_max, (1. - l) * t_max);
        let (s_mid, t_mid) = Self::get_st_mid(a, b);

        let c_a = l * s_mid;
        let c_b = (1. - l) * t_mid;
        let c_mid = 0.9 * k * f64::sqrt(f64::sqrt(1. / (1. / c_a.powf(4.) + 1. / c_b.powf(4.))));

        let c_a0 = l * 0.4;
        let c_b0 = (1. - l) * 0.8;
        let c_0 = f64::sqrt(1. / (1. / c_a0.powf(2.) + 1. / c_b0.powf(2.)));

        Self { c_0, c_mid, c_max }
    }

    /// Finds the intersection of the gamut for upper and lower half seperately.
    ///
    /// # Arguments
    ///
    /// * `args` - The arguments for the gamut intersection calculation.
    fn find_gamut_intersection(args: CsArgs) -> f64 {
        // Find the intersection of the gamut for upper and lower half seperately.
        if (args.l1 - args.l0) * args.cs_cusp - (args.lc_cusp - args.l0) * args.c1 <= 0. {
            return args.cs_cusp * args.l0
                / (args.c1 * args.lc_cusp + args.cs_cusp * (args.l0 - args.l1));
        }

        let t = args.cs_cusp * (args.l0 - 1.)
            / (args.c1 * (args.lc_cusp - 1.) + args.cs_cusp * (args.l0 - args.l1));

        // Perform the halley method
        f64::compute_halley(args.l0, args.l1, args.c1, args.a, args.b, t)
    }

    /// Returns the midpoint of the s and t coordinates for the given a and b components.
    ///
    /// # Arguments
    ///
    /// * `a` - The a component of the OkLab color.
    /// * `b` - The b component of the OkLab color.
    fn get_st_mid(a: f64, b: f64) -> (f64, f64) {
        let s = 0.115_169_93
            + 1. / (7.447_789_70
                + 4.159_012_40 * b
                + a * (-2.195_573_47
                    + 1.751_984_01 * b
                    + a * (-2.137_049_48 - 10.023_010_43 * b
                        + a * (-4.248_945_61 + 5.387_708_19 * b + 4.698_910_13 * a))));

        let t = 0.112_396_42
            + 1. / (1.613_203_20 - 0.681_243_79 * b
                + a * (0.403_706_12
                    + 0.901_481_23 * b
                    + a * (-0.270_879_43
                        + 0.612_239_90 * b
                        + a * (0.002_992_15 - 0.453_995_68 * b - 0.146_618_72 * a))));

        (s, t)
    }
}
