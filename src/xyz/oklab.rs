use super::srgb::Srgb;

/// Oklab is a representation of the OkLab color space
/// The implementation is based on the following blog post
/// 
/// @link https://bottosson.github.io/posts/oklab/
#[derive(Debug, Clone, Copy)]
pub struct OkLab {
    l: f64,
    a: f64,
    b: f64
}

impl From<Srgb> for OkLab {
    fn from(rgb: Srgb) -> Self {
        let Srgb{r, g, b} = rgb;

        let l = (0.4122214708 * r + 0.5363325363 * g + 0.0514459929 * b).cbrt();
        let m = (0.2119034982 * r + 0.6806995451 * g + 0.1073969566 * b).cbrt();
        let s = (0.0883024619 * r + 0.2817188376 * g + 0.6299787005 * b).cbrt();

        OkLab {
            l: 0.2104542553 * l + 0.7936177850 * m - 0.0040720468 * s,
            a: 1.9779984951 * l - 2.4285922050 * m + 0.4505937099 * s,
            b: 0.0259040371 * l + 0.7827717662 * m - 0.8086757660 * s
        }
    }
}

impl From<OkLab> for Srgb {
    fn from(oklab: OkLab) -> Self {
        let l = (oklab.l + 0.3963377774 * oklab.a + 0.2158037573 * oklab.b).powi(3);
        let m = (oklab.l - 0.1055613458 * oklab.a - 0.0638541728 * oklab.b).powi(3);
        let s = (oklab.l - 0.0894841775 * oklab.a - 1.2914855480 * oklab.b).powi(3);

        Srgb {
            r: 4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s,
            g: -1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s,
            b: -0.0041960863 * l - 0.7034186147 * m + 1.7076147010 * s
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::util;

    #[test]
    fn expect_to_compute_oklab() {
        let rgb = Srgb {
            r: 0.19608,
            g: 0.03922,
            b: 0.37255
        };

        let oklab = OkLab::from(rgb);
        assert_eq!(util::roundup(oklab.l, 100000.0), 0.47973);
        assert_eq!(util::roundup(oklab.a, 100000.0), 0.10967);
        assert_eq!(util::roundup(oklab.b, 100000.0), -0.13227);
    }

    #[test]
    fn expect_to_compute_srgb() {
        let lab = OkLab {
            l: 0.4797292419266419,
            a: 0.1096666836368474,
            b: -0.13227426781495677
        };

        let srgb = Srgb::from(lab);
        assert_eq!(util::roundup(srgb.r, 100000.0), 0.19608);
        assert_eq!(util::roundup(srgb.g, 100000.0), 0.03922);
        assert_eq!(util::roundup(srgb.b, 100000.0), 0.37255);
    }
}
