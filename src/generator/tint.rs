use crate::rgb::Rgb;
use crate::error::Error;
use crate::util::AsFloat;
use super::GeneratorOps;

/// Tint implement the computation of a Tint value from an RGB color
/// The tint is computed based on a factor. The factor should be a number between 0 to 1
/// 
/// Computation is based on the article below
/// @link https://maketintsandshades.com/about
#[derive(Debug)]
pub struct Tint(Vec<Rgb>);

impl GeneratorOps for Tint {
    fn compute(rgb: Rgb, factor: f64) -> Result<Tint, Error>  {
        let mut tint = Vec::new();
        let (r, g, b) = rgb.as_f64();

        if factor < 0_f64 || factor > 1_f64 {
            return Err(Error::Generator);
        }

        let mut f = factor;
        // Push the current value in the vector
        tint.push(rgb);
        while f <= 1_f64 {
            // Increase the factor by the provided factor
            tint.push(Rgb {
                r: (r + ((255_f64 - r)) * f) as u8,
                g: (g + ((255_f64 - g)) * f) as u8,
                b: (b + ((255_f64 - b)) * f) as u8
            });

            f += factor;
        }

        Ok(Tint(tint))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_create_tint() {
        let rgb = Rgb {
            r: 102,
            g: 170,
            b: 119
        };

        let tint = Tint::compute(rgb, 0.1).unwrap();
        assert_eq!(tint.0.len(), 11);
    }

    #[test]
    fn expect_to_not_create_tint() {
        let rgb = Rgb {
            r: 102,
            g: 170,
            b: 119
        };

        let tint = Tint::compute(rgb, 1.1);
        assert!(tint.is_err());
    }
}
