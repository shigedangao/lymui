use crate::{error::Error, rgb::Rgb};

pub mod shade;
pub mod tint;

pub trait GeneratorOps {
    /// Allow to compute either a Tint or a Shade
    ///
    /// # Arguments
    ///
    /// * `rgb` - Rgb
    /// * `factor` - f64
    ///
    /// # Errors
    ///
    /// Returns an error if the computation of the generator (shade or tint) fails.
    fn compute(rgb: Rgb, factor: f64) -> Result<Self, Error>
    where
        Self: Sized;
}
