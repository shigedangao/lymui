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

pub mod oklab {
    // Constant provided by https://bottosson.github.io/posts/oklab/
    pub(crate) const OKSR: [f64; 3] = [0.4122214708, 0.5363325363, 0.0514459929];
    pub(crate) const OKSG: [f64; 3] = [0.2119034982, 0.6806995451, 0.1073969566];
    pub(crate) const OKSB: [f64; 3] = [0.0883024619, 0.2817188376, 0.6299787005];

    pub(crate) const OKL: [f64; 3] = [0.2104542553, 0.7936177850, 0.0040720468];
    pub(crate) const OKA: [f64; 3] = [1.9779984951, 2.4285922050, 0.4505937099];
    pub(crate) const OKB: [f64; 3] = [0.0259040371, 0.7827717662, 0.8086757660];

    pub(crate) const ROL: [f64; 2] = [0.3963377774, 0.2158037573];
    pub(crate) const ROM: [f64; 2] = [0.1055613458, 0.0638541728];
    pub(crate) const ROS: [f64; 2] = [0.0894841775, 1.2914855480];

    pub(crate) const ROR: [f64; 3] = [4.0767416621, 3.3077115913, 0.2309699292];
    pub(crate) const ROG: [f64; 3] = [-1.2684380046, 2.6097574011, 0.3413193965];
    pub(crate) const ROB: [f64; 3] = [-0.0041960863, 0.7034186147, 1.7076147010];
}

pub mod rec2020 {
    // Used to convert an Xyz to a rec2020
    // Matrices can be found in the link below
    // @link https://agraphicsguynotes.com/posts/basic_color_science_for_graphcis_engineer/#rec-2020
    pub(crate) const XR: [f64; 3] = [1.716651187971267, -0.355670783776392, -0.253366281373659];
    pub(crate) const XG: [f64; 3] = [-0.666684351832489, 1.616481236634939, 0.015768545813911];
    pub(crate) const XB: [f64; 3] = [0.017639857445310, -0.042770613257808, 0.942103121235473];

    // Used to convert a rec2020 to an xyz
    pub(crate) const XX: [f64; 3] = [0.6369580, 0.1446169, 0.1688810];
    pub(crate) const XY: [f64; 3] = [0.2627002, 0.6779981, 0.0593017];
    pub(crate) const XZ: [f64; 3] = [0_f64, 0.0280727, 1.0609851];
}
