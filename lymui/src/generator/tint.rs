use super::GeneratorOps;
use crate::error::Error;
use crate::rgb::Rgb;
use crate::util::AsFloat;

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Tint implement the computation of a Tint value from an RGB color
/// The tint is computed based on a factor. The factor should be a number between 0 to 1
///
/// Computation is based on the article below
/// @link https://maketintsandshades.com/about
#[derive(Debug)]
pub struct Tint(pub Vec<Rgb>);

impl GeneratorOps for Tint {
    fn compute(rgb: Rgb, factor: f64) -> Result<Tint, Error> {
        let mut tint = Vec::new();
        let (r, g, b) = rgb.as_f64();

        if !(0_f64..=1_f64).contains(&factor) {
            return Err(Error::Generator);
        }

        let mut f = factor;
        // Push the current value in the vector
        tint.push(rgb);
        while f <= 1_f64 {
            // Increase the factor by the provided factor
            tint.push(Rgb {
                r: (r + (255_f64 - r) * f) as u8,
                g: (g + (255_f64 - g) * f) as u8,
                b: (b + (255_f64 - b) * f) as u8,
            });

            f += factor;
        }

        Ok(Tint(tint))
    }
}

#[cfg(feature = "js")]
impl FromJsObject for Tint {
    fn from_js_object(object: Object) -> NapiResult<Self> {
        let objects: Vec<Object> = object.get("tint")?
            .ok_or_else(|| JsError::from_status(Status::InvalidArg))?;

        let mut rgb_vec = Vec::new();
        for obj in objects {
            let rgb = Rgb::from_js_object(obj)?;
            rgb_vec.push(rgb);
        }

        Ok(Tint(rgb_vec))
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
            b: 119,
        };

        let tint = Tint::compute(rgb, 0.1).unwrap();
        assert_eq!(tint.0.len(), 11);
    }

    #[test]
    fn expect_to_not_create_tint() {
        let rgb = Rgb {
            r: 102,
            g: 170,
            b: 119,
        };

        let tint = Tint::compute(rgb, 1.1);
        assert!(tint.is_err());
    }
}
