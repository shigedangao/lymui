// Constant
pub const ADBOBE_RGB_COMPOUND: f64 = 2.19921875;

/// FromRgb is a trait that allows a type T to process an RGB Color
pub trait FromRgb<T> {
    /// Convert an rgb color to something else
    fn from_rgb(rgb: Rgb, kind: T) -> Self;
}

#[derive(Debug, Default, Clone, Copy)]
pub struct Rgb {
    pub r: u8,
    pub g: u8,
    pub b: u8
}

impl Rgb {
    /// Creta a new rgb color
    /// 
    /// # Arguments
    /// 
    /// * `a` - u8
    /// * `b` - u8
    /// * `c` - u8
    pub fn new(a: u8, b: u8, c: u8) -> Self {
        Rgb {
            r: a,
            g: b,
            b: c
        }
    }
    /// Return the RGB color representation as a f64
    pub fn as_f64(&self) -> (f64, f64, f64) {
        (
            self.r as f64,
            self.g as f64,
            self.b as f64
        )
    }
    
    /// Get the minimum and the maximum value of a RGB color representation
    pub fn get_min_max(&self) -> (f64, f64) {
        let (r_f, g_f, b_f) = self.as_f64();

        let min = b_f.min(r_f.min(g_f));
        let max = b_f.max(r_f.max(g_f));

        (min, max)
    }

    /// Convert the RGB Value into a linear rgb value
    pub fn pivot_rgb(&self) -> Vec<f64> {
        let colors = vec![self.r, self.g, self.b];
        
        colors
            .into_iter()
            .map(|c| {
                let color = c as f64 / 255.0;
                if color <= 0.04045 {
                    return color / 12.92;
                }

                f64::powf((color + 0.055) / 1.055, 2.4)
            })
            .collect()
    }

    /// Convert an RGB value into a linear Adobe RGB Value
    pub fn pivot_adobe_rgb(&self) -> Vec<f64> {
        let colors = vec![self.r, self.g, self.b];

        colors
            .into_iter()
            .map(|c| {
                let color = c as f64 / 255.0;
                if color <= 0.0 {
                    return 0.0
                }

                color.powf(ADBOBE_RGB_COMPOUND)
            })
            .collect()
    }
}


#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn expect_to_return_min_max() {
        let rgb = Rgb{r: 250, g: 100, b: 50};

        let (min, max) = rgb.get_min_max();

        assert_eq!(min, 50.0);
        assert_eq!(max, 250.0);
    }
}
