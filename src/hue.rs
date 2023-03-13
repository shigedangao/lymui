use crate::rgb::Rgb;

pub type Hue = f64;

impl From<Rgb> for Hue {
    fn from(rgb: Rgb) -> Self {
        let (min, max) = rgb.get_min_max();
        if min == max {
            return 0.0
        }

        let (r, g, b) = rgb.as_f64();

        let mut hue = if max == r {
            (g - b) / (max - min)
        } else if max == g {
            2.0 + (b - r) / (max - min)
        } else {
            4.0 + (r - g) / (max - min)
        };

        hue *= 60.0;
        if hue < 0.0 {
            hue += 360.0
        }

        hue.round()
    }
}
