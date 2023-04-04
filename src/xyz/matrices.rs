/// Matrices for xyz color space
pub mod xyz {
    // Matrix to convert from RGB to XYZ for the D65 light (sRGB setting)
    pub(crate) const X65: [f64; 3] = [0.4124564, 0.3575761, 0.1804375];
    pub(crate) const Y65: [f64; 3] = [0.2126729, 0.7151522, 0.0721750];
    pub(crate) const Z65: [f64; 3] = [0.0193339, 0.1191920, 0.9503041];

    // srgb from Xyz to std RGB
    pub(crate) const RX65: [f64; 3] = [3.2404542, -1.5371385, -0.4985314];
    pub(crate) const RY65: [f64; 3] = [-0.9692660, 1.8760108, 0.0415560];
    pub(crate) const RZ65: [f64; 3] = [0.0556434, -0.2040259, 1.0572252];

    // Matrix to convert from RGB to XYZ for the D50 light (sRGB setting)
    pub(crate) const X50: [f64; 3] = [0.4360747, 0.3850649, 0.1430804];
    pub(crate) const Y50: [f64; 3] = [0.2225045, 0.7168786, 0.0606169];
    pub(crate) const Z50: [f64; 3] = [0.0139322, 0.0971045, 0.7141733];

    pub(crate) const RX50: [f64; 3] = [3.1338561, -1.6168667, -0.4906146];
    pub(crate) const RY50: [f64; 3] = [-0.9787684, 1.9161415, 0.0334540];
    pub(crate) const RZ50: [f64; 3] = [0.0719453, -0.2289914, 1.4052427];

    // Matrix to convert from RGB to XYZ with the adobe 1998 profile
    pub(crate) const AX: [f64; 3] = [0.5767309, 0.1855540, 0.1881852];
    pub(crate) const AY: [f64; 3] = [0.2973769, 0.6273491, 0.0752741];
    pub(crate) const AZ: [f64; 3] = [0.0270343, 0.0706872, 0.9911085];

    // srgb from Xyz to Adobe RGB
    pub(crate) const ARX: [f64; 3] = [2.0413690, -0.5649464, -0.3446944];
    pub(crate) const ARY: [f64; 3] = [-0.9692660, 1.8760108, 0.0415560];
    pub(crate) const ARZ: [f64; 3] = [0.0134474, -0.1183897, 1.0154096];
}

pub mod argb {
    // Constant
    // From Xyz to aRGB as defined on these specs
    //
    // @link https://en.wikipedia.org/wiki/Adobe_RGB_color_space#cite_note-AdobeRGBColorImagingEncoding-4#Specifications
    // @link https://stackoverflow.com/questions/40017741/mathematical-conversion-srgb-and-adobergb
    pub(crate) const XR: [f64; 3] = [2.041588, -0.565007, -0.344731];
    pub(crate) const YG: [f64; 3] = [-0.969244, 1.875968, 0.041555];
    pub(crate) const ZB: [f64; 3] = [0.013444, -0.118362, 1.015175];

    // Constant provided by
    // @link http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
    pub(crate) const RR: [f64; 3] = [0.5767309, 0.1855540, 0.1881852];
    pub(crate) const GG: [f64; 3] = [0.2973769, 0.6273491, 0.0752741];
    pub(crate) const BB: [f64; 3] = [0.0270343, 0.0706872, 0.9911085];
}
