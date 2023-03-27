use crate::{
    rgb::Rgb,
    error::Error
};

pub mod tint;
pub mod shade;

pub trait GeneratorOps {
    fn compute(rgb: Rgb, factor: f64) -> Result<Self, Error> where Self: Sized;
}
