pub(crate) trait GammaCorrection {
    /// Apply gamma correction especially useful for xyz
    /// @link https://en.wikipedia.org/wiki/SRGB#From_CIE_XYZ_to_sRGB
    fn apply_srgb_gamma_correction(self) -> f64;
    /// Compute the gamma expanded value. Usually from a gamma corrected value
    /// @link https://en.wikipedia.org/wiki/SRGB#From_sRGB_to_CIE_XYZ
    fn compute_srgb_gamma_expanded(self) -> f64;
    /// Compute the gamma expanded value for an adobe rgb (linear)
    fn compute_argb_gamma(self) -> f64;
    /// Compute the argb gamma expanded
    fn compute_argb_gamma_expanded(self) -> f64;
    /// Compute the transfer gamma function for the rec709 color space
    /// @link https://www.image-engineering.de/products/charts/sort-by-type/126-library/technote/714-color-spaces-rec-709-vs-srgb
    /// @link https://en.wikipedia.org/wiki/Rec._709
    fn compute_rec709_gamma_correction(self) -> f64;
    /// Compute the inverse of the transform
    /// @link https://en.wikipedia.org/wiki/Rec._709
    fn compute_rec709_gamma_expanded(self) -> f64;
}

impl GammaCorrection for f64 {
    fn apply_srgb_gamma_correction(self) -> f64 {
        if self <= 0.0031308 {
            return self * 12.92;
        }

        1.055 * self.powf(1.0 / 2.4) - 0.055
    }

    fn compute_srgb_gamma_expanded(self) -> f64 {
        if self <= 0.04045 {
            return self / 12.92;
        }

        f64::powf((self + 0.055) / 1.055, 2.4)
    }

    fn compute_argb_gamma(self) -> f64 {
        if self <= 0_f64 {
            return 0_f64;
        }

        self.powf(2.19921875)
    }

    fn compute_argb_gamma_expanded(self) -> f64 {
        if self <= 0_f64 {
            return 0_f64;
        }

        self.powf(1.0 / 2.19921875)
    }

    fn compute_rec709_gamma_correction(self) -> f64 {
        if self < 0.018 {
            return self * 4.5;
        }

        1.099 * self.powf(0.45) - 0.099
    }

    fn compute_rec709_gamma_expanded(self) -> f64 {
        if self < 0.081 {
            return self / 4.5;
        }

        f64::powf((self + 0.099) / 1.099, 1_f64 / 0.45)
    }
}
