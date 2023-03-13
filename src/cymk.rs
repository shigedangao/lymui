use super::rgb::Rgb;

#[derive(Debug, Default)]
pub struct Cymk {
    c: f64,
    y: f64,
    m: f64,
    k: f64
}

impl From<Rgb> for Cymk {
    fn from(rgb: Rgb) -> Self {
        let (r, g, b) = rgb.as_f64();
        let (_, max) = rgb.get_min_max();

        let k = 1.0 - (max / 255.0);
        let mk = 1.0 - k;

        if k != 1.0 {
            return Cymk {
                c: (1.0 - (r / 255.0) - k) / mk,
                m: (1.0 - (g / 255.0) - k) / mk,
                y: (1.0 - (b / 255.0) - k) / mk,
                k
            };
        }

        Cymk {
            k,
            ..Default::default()
        }
    }
}

impl From<Cymk> for Rgb {
    fn from(cymk: Cymk) -> Self {
        let kv = 1.0 - cymk.k;
        
        Rgb {
            r: (255.0 * (1.0 - cymk.c) * kv) as u8,
            g: (255.0 * (1.0 - cymk.m) * kv) as u8,
            b: (255.0 * (1.0 - cymk.y) * kv) as u8
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::util::roundup;
    use super::*;
    
    #[test]
    fn expect_to_create_cymk() {
        let rgb = Rgb {
            r: 255,
            g: 55,
            b: 102
        };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(roundup(cymk.y, 100.0), 0.6);
        assert_eq!(roundup(cymk.m, 100.0), 0.78);
        assert_eq!(cymk.k, 0.0);
    }

    #[test]
    fn expect_to_create_dark_cymk() {
        let rgb = Rgb {
            r: 0,
            g: 0,
            b: 0
        };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(cymk.y, 0.0);
        assert_eq!(cymk.m, 0.0);
        assert_eq!(cymk.k, 1.0);
    }

    #[test]
    fn expect_to_create_light_cymk() {
        let rgb = Rgb {
            r: 255,
            g: 255,
            b: 255
        };

        let cymk = Cymk::from(rgb);

        assert_eq!(cymk.c, 0.0);
        assert_eq!(cymk.y, 0.0);
        assert_eq!(cymk.m, 0.0);
        assert_eq!(cymk.k, 0.0);
    }

    #[test]
    fn expect_to_create_rgb() {
        let cymk = Cymk {
            c: 0.973,
            y: 0.0,
            m: 0.949,
            k: 0.223
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 5);
        assert_eq!(rgb.g, 10);
        assert_eq!(rgb.b, 198);
    }

    #[test]
    fn expect_to_create_dark_rgb() {
        let cymk = Cymk {
            c: 0.0,
            y: 0.0,
            m: 0.0,
            k: 1.0
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 0);
        assert_eq!(rgb.g, 0);
        assert_eq!(rgb.b, 0);
    }

    #[test]
    fn expect_to_create_light_rgb() {
        let cymk = Cymk {
            c: 0.0,
            y: 0.0,
            m: 0.0,
            k: 0.0
        };

        let rgb = Rgb::from(cymk);

        assert_eq!(rgb.r, 255);
        assert_eq!(rgb.g, 255);
        assert_eq!(rgb.b, 255);
    }
}