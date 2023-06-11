use super::GeneratorOps;
use crate::error::Error;
use crate::rgb::Rgb;
use crate::util::AsFloat;

#[cfg(feature = "js")]
use crate::js::prelude::*;

/// Shade implement the computation of a Shade value from an RGB color
/// The shade is computed based on a factor. The factor should be a number between 0 to 1
///
/// Computation is based on the article below
/// @link https://maketintsandshades.com/about
#[derive(Debug)]
pub struct Shade(pub Vec<Rgb>);

impl GeneratorOps for Shade {
    fn compute(rgb: Rgb, factor: f64) -> Result<Shade, Error> {
        let mut shade = Vec::new();
        let (r, g, b) = rgb.as_f64();

        if !(0_f64..=1_f64).contains(&factor) {
            return Err(Error::Generator);
        }

        let mut f = 1_f64;
        while f >= 0_f64 {
            shade.push(Rgb {
                r: (r * f) as u8,
                g: (g * f) as u8,
                b: (b * f) as u8,
            });

            f -= factor;
        }

        Ok(Shade(shade))
    }
}

#[cfg(feature = "js")]
impl FromJsObject for Shade {
    fn from_js_object(object: Object) -> NapiResult<Self> {
        let objects: Vec<Object> = object
            .get("shade")?
            .ok_or_else(|| JsError::from_status(Status::InvalidArg))?;

        let mut rgb_vec = Vec::new();
        for obj in objects {
            let rgb = Rgb::from_js_object(obj)?;
            rgb_vec.push(rgb);
        }

        Ok(Shade(rgb_vec))
    }
}

#[cfg(feature = "js")]
impl IntoJsObject for Shade {
    fn into_js_object(&self, env: Env) -> NapiResult<Object> {
        let mut res = env.create_object()?;

        let mut objects = Vec::new();
        for color in &self.0 {
            objects.push(color.into_js_object(env)?);
        }

        res.set("shade", objects)?;

        Ok(res)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_create_shade() {
        let rgb = Rgb {
            r: 102,
            g: 170,
            b: 119,
        };

        let shade = Shade::compute(rgb, 0.1).unwrap();
        assert_eq!(shade.0.len(), 11);
    }

    #[test]
    fn expect_to_not_create_shade() {
        let rgb = Rgb {
            r: 102,
            g: 170,
            b: 119,
        };

        let shade = Shade::compute(rgb, 1.1);
        assert!(shade.is_err());
    }
}
