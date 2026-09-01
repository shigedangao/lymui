/// Matrices for xyz color space
pub mod xyz {
    // Matrix to convert from RGB to XYZ for the D65 light (sRGB setting)
    pub(crate) const X65: [f64; 3] = [0.412_456_4, 0.357_576_1, 0.180_437_5];
    pub(crate) const Y65: [f64; 3] = [0.212_672_9, 0.715_152_2, 0.072_175_0];
    pub(crate) const Z65: [f64; 3] = [0.019_333_9, 0.119_192_0, 0.950_304_1];

    // srgb from Xyz to std RGB
    pub(crate) const RX65: [f64; 3] = [3.240_454_2, -1.537_138_5, -0.498_531_4];
    pub(crate) const RY65: [f64; 3] = [-0.969_266_0, 1.876_010_8, 0.041_556_0];
    pub(crate) const RZ65: [f64; 3] = [0.055_643_4, -0.204_025_9, 1.057_225_2];

    // Matrix to convert from RGB to XYZ for the D50 light (sRGB setting)
    pub(crate) const X50: [f64; 3] = [0.436_074_7, 0.385_064_9, 0.143_080_4];
    pub(crate) const Y50: [f64; 3] = [0.222_504_5, 0.716_878_6, 0.060_616_9];
    pub(crate) const Z50: [f64; 3] = [0.013_932_2, 0.097_104_5, 0.714_173_3];

    pub(crate) const RX50: [f64; 3] = [3.133_856_1, -1.616_866_7, -0.490_614_6];
    pub(crate) const RY50: [f64; 3] = [-0.978_768_4, 1.916_141_5, 0.033_454_0];
    pub(crate) const RZ50: [f64; 3] = [0.071_945_3, -0.228_991_4, 1.405_242_7];

    // Matrix to convert from RGB to XYZ with the adobe 1998 profile
    pub(crate) const AX: [f64; 3] = [0.576_730_9, 0.185_554_0, 0.188_185_2];
    pub(crate) const AY: [f64; 3] = [0.297_376_9, 0.627_349_1, 0.075_274_1];
    pub(crate) const AZ: [f64; 3] = [0.027_034_3, 0.070_687_2, 0.991_108_5];

    // srgb from Xyz to Adobe RGB
    pub(crate) const ARX: [f64; 3] = [2.041_369_0, -0.564_946_4, -0.344_694_4];
    pub(crate) const ARY: [f64; 3] = [-0.969_266_0, 1.876_010_8, 0.041_556_0];
    pub(crate) const ARZ: [f64; 3] = [0.013_447_4, -0.118_389_7, 1.015_409_6];
}

pub mod argb {
    // Constant
    // From Xyz to aRGB as defined on these specs
    //
    // @link <https://en.wikipedia.org/wiki/Adobe_RGB_color_space#cite_note-AdobeRGBColorImagingEncoding-4#Specifications>
    // @link <https://stackoverflow.com/questions/40017741/mathematical-conversion-srgb-and-adobergb>
    pub(crate) const XR: [f64; 3] = [2.041_588, -0.565_007, -0.344_731];
    pub(crate) const YG: [f64; 3] = [-0.969_244, 1.875_968, 0.041_555];
    pub(crate) const ZB: [f64; 3] = [0.013_444, -0.118_362, 1.015_175];

    // Constant provided by
    // @link <http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html>
    pub(crate) const RR: [f64; 3] = [0.576_730_9, 0.185_554_0, 0.188_185_2];
    pub(crate) const GG: [f64; 3] = [0.297_376_9, 0.627_349_1, 0.075_274_1];
    pub(crate) const BB: [f64; 3] = [0.027_034_3, 0.070_687_2, 0.991_108_5];
}

pub mod oklab {
    // Constant provided by https://bottosson.github.io/posts/oklab/
    pub(crate) const OKSR: [f64; 3] = [0.412_221_470_8, 0.536_332_536_3, 0.051_445_992_9];
    pub(crate) const OKSG: [f64; 3] = [0.211_903_498_2, 0.680_699_545_1, 0.107_396_956_6];
    pub(crate) const OKSB: [f64; 3] = [0.088_302_461_9, 0.281_718_837_6, 0.629_978_700_5];

    pub(crate) const OKL: [f64; 3] = [0.210_454_255_3, 0.793_617_785_0, 0.004_072_046_8];
    pub(crate) const OKA: [f64; 3] = [1.977_998_495_1, 2.428_592_205_0, 0.450_593_709_9];
    pub(crate) const OKB: [f64; 3] = [0.025_904_037_1, 0.782_771_766_2, 0.808_675_766_0];

    pub(crate) const ROL: [f64; 2] = [0.396_337_777_4, 0.215_803_757_3];
    pub(crate) const ROM: [f64; 2] = [0.105_561_345_8, 0.063_854_172_8];
    pub(crate) const ROS: [f64; 2] = [0.089_484_177_5, 1.291_485_548_0];

    pub(crate) const ROR: [f64; 3] = [4.076_741_662_1, 3.307_711_591_3, 0.230_969_929_2];
    pub(crate) const ROG: [f64; 3] = [-1.268_438_004_6, 2.609_757_401_1, 0.341_319_396_5];
    pub(crate) const ROB: [f64; 3] = [-0.004_196_086_3, 0.703_418_614_7, 1.707_614_701_0];
}

pub mod rec2020 {
    // Used to convert an Xyz to a rec2020
    // Matrices can be found in the link below
    // @link <https://agraphicsguynotes.com/posts/basic_color_science_for_graphcis_engineer/#rec-2020>
    pub(crate) const XR: [f64; 3] = [
        1.716_651_187_971_267,
        -0.355_670_783_776_392,
        -0.253_366_281_373_659,
    ];
    pub(crate) const XG: [f64; 3] = [
        -0.666_684_351_832_489,
        1.616_481_236_634_939,
        0.015_768_545_813_911,
    ];
    pub(crate) const XB: [f64; 3] = [
        0.017_639_857_445_310,
        -0.042_770_613_257_808,
        0.942_103_121_235_473,
    ];

    // Used to convert a rec2020 to an xyz
    pub(crate) const XX: [f64; 3] = [0.636_958_0, 0.144_616_9, 0.168_881_0];
    pub(crate) const XY: [f64; 3] = [0.262_700_2, 0.677_998_1, 0.059_301_7];
    pub(crate) const XZ: [f64; 3] = [0_f64, 0.028_072_7, 1.060_985_1];
}

pub mod aces2065 {
    // Used to convert an Xyz to an aces2065
    pub(crate) const XR: [f64; 3] = [0.952_552_395_9, 0.000_000_000_0, 0.000_093_678_6];
    pub(crate) const XG: [f64; 3] = [0.343_966_449_8, 0.728_166_096_6, -0.072_132_546_4];
    pub(crate) const XB: [f64; 3] = [0.000_000_000_0, 0.000_000_000_0, 1.008_825_184_4];

    // Used to convert an aces2065 to an xyz
    pub(crate) const XX: [f64; 3] = [1.049_811_017_5, 0.000_000_000_0, -0.0000974845];
    pub(crate) const XY: [f64; 3] = [-0.495_903_023_1, 1.373_313_045_8, 0.098_240_036_1];
    pub(crate) const XZ: [f64; 3] = [0.000_000_000_0, 0.000_000_000_0, 0.991_252_018_2];
}
