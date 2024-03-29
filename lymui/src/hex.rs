use crate::error::Error;
use crate::rgb::Rgb;

#[cfg(feature = "js")]
use crate::js::prelude::*;

#[cfg_attr(feature = "js", derive(FromJsObj, IntoJsObject))]
#[derive(Debug)]
pub struct Hex(pub String);

trait HexOps {
    /// Remove the # in front of an Hex if exist
    fn strip(&mut self) -> &mut Self;
    /// Unshorten an short Hex such as #6A7 which transform into #66AA77
    fn unshorten(&mut self) -> &mut Self;
    /// Convert the hex into u8 part which can be used to construct an RGB struct
    ///
    /// # Description
    /// Considering this example #FFEEAA we're going to parse each hexa value by a batch of two
    /// As a result we're going to convert the following hexa into an u8 value
    /// - FF -> 102
    /// - EE -> 170
    /// - AA -> 119
    fn get_u8_parts(&mut self) -> Result<(u8, u8, u8), Error>;
    /// Convert an RGB to into a short hexadecimal value
    ///
    /// # Arguments
    ///
    /// * `rgb` - Rgb
    fn into_short_hex(rgb: Rgb) -> Result<Self, Error>
    where
        Self: Sized;
}

impl HexOps for Hex {
    fn strip(&mut self) -> &mut Self {
        let hex = self.0.strip_prefix('#').unwrap_or(&self.0);

        self.0 = hex.to_string();

        self
    }

    fn unshorten(&mut self) -> &mut Self {
        // Basically copy each part from the hex into 6
        self.strip();
        let unshorten: String =
            self.0
                .chars()
                .map(|c| (c, c))
                .fold(String::new(), |mut acc, (a, b)| {
                    acc.push(a);
                    acc.push(b);

                    acc
                });

        self.0 = unshorten;

        self
    }

    fn get_u8_parts(&mut self) -> Result<(u8, u8, u8), Error> {
        self.strip();

        let r_s = self.0.get(0..2);
        let g_s = self.0.get(2..4);
        let b_s = self.0.get(4..6);

        if let (Some(r), Some(g), Some(b)) = (r_s, g_s, b_s) {
            let r_u = u8::from_str_radix(r, 16).ok().unwrap_or_default();
            let g_u = u8::from_str_radix(g, 16).ok().unwrap_or_default();
            let b_u = u8::from_str_radix(b, 16).ok().unwrap_or_default();

            return Ok((r_u, g_u, b_u));
        }

        Err(Error::Hex("Some color could not be parsed".to_string()))
    }

    fn into_short_hex(rgb: Rgb) -> Result<Self, Error> {
        let hex_chars = Hex::from(rgb).strip().0.chars().collect::<Vec<_>>();

        let short_hex = hex_chars
            .into_iter()
            .enumerate()
            .try_fold(vec![], |mut acc, (idx, item)| {
                if idx % 2 == 0 {
                    acc.push(item);
                    return Ok(acc);
                }

                // This should never fail as there will be always one item in the acc
                let last = acc.last().unwrap();
                if *last != item {
                    return Err(Error::Hex(
                        "Unable to convert hex to short hex as the tripplet aren't the same".into(),
                    ));
                }

                Ok(acc)
            })
            .map(|res| res.iter().collect::<String>())?;

        Ok(Hex(format!("#{short_hex}")))
    }
}

impl From<Rgb> for Hex {
    fn from(value: Rgb) -> Self {
        let hex_vec = vec![
            format!("{:x}", value.r),
            format!("{:x}", value.g),
            format!("{:x}", value.b),
        ];

        let hex = hex_vec
            .into_iter()
            .map(|v| if v.len() == 1 { format!("0{v}") } else { v })
            .collect::<Vec<_>>()
            .join("");

        Hex(format!("#{hex}"))
    }
}

impl TryFrom<Hex> for Rgb {
    type Error = Error;

    fn try_from(h: Hex) -> Result<Self, Self::Error> {
        let mut hex = h;
        if hex.0.len() <= 4 {
            hex.unshorten();
        }

        // get the u8 representation of an RGB
        let (r, g, b) = hex.get_u8_parts()?;

        Ok(Rgb { r, g, b })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_to_convert_rgb_to_hex() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255,
        };

        let hex = Hex::from(rgb);

        assert_eq!(hex.0, "#ffffff");
    }

    #[test]
    fn expect_to_unshorten_hex_with_prefix() {
        let mut hex: Hex = Hex("#6A7".to_string());
        let res = hex.unshorten();

        assert_eq!(res.0, "66AA77");
    }

    #[test]
    fn expect_to_convert_hex_to_rgb() {
        let hex: Hex = Hex("#66AA77".to_string());
        let rgb = Rgb::try_from(hex).unwrap();

        assert_eq!(rgb.r, 102);
        assert_eq!(rgb.g, 170);
        assert_eq!(rgb.b, 119);
    }

    #[test]
    fn expect_to_convert_short_hex_to_rgb() {
        let hex: Hex = Hex("#6A7".to_string());
        let rgb = Rgb::try_from(hex).unwrap();

        assert_eq!(rgb.r, 102);
        assert_eq!(rgb.g, 170);
        assert_eq!(rgb.b, 119);
    }

    #[test]
    fn expect_to_convert_rgb_into_short_hex() {
        let rgb = Rgb {
            r: 17,
            g: 255,
            b: 17,
        };

        let short_hex = Hex::into_short_hex(rgb);
        assert!(short_hex.is_ok());
        assert_eq!(short_hex.unwrap().0, "#1f1");
    }

    #[test]
    fn expect_to_convert_rgb_into_short_hex_to_fail() {
        let rgb = Rgb {
            r: 17,
            g: 255,
            b: 99,
        };

        let short_hex = Hex::into_short_hex(rgb);
        assert!(short_hex.is_err());
    }
}
