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
    fn compute(rgb: Rgb, factor: f64) -> Result<Self, Error>
    where
        Self: Sized;
}
