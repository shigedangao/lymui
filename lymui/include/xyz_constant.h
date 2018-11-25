//
//  xyz_constant.h
//  lymui
//
//  Created by Marc Intha on 22/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef xyz_constant_h
#define xyz_constant_h

// Constant for the sRGB value to from RGB to XYZ
#define xr 0.4124564
#define xg 0.3575761
#define xb 0.1804375

#define yr 0.2126729
#define yg 0.7151522
#define yb 0.0721750

#define zr 0.0193339
#define zg 0.1191920
#define zb 0.9503041

// Constant for Adobe RGB value from RGB to XYZ
#define axr 0.5767309
#define axg 0.1855540
#define axb 0.1881852

#define ayr 0.2973769
#define ayg 0.6273491
#define ayb 0.0752741

#define azr 0.0270343
#define azg 0.0706872
#define azb 0.9911085

// Illuminant for D65
#define Xn 0.95047
#define Yn 1.000
#define Zn 1.08883

// Constant for the sRgb value from XYZ to RGB
#define xx 3.2404
#define xy -1.5371
#define xz -0.4985

#define yx -0.9692
#define yy 1.8760
#define yz 0.0415

#define zx 0.0556
#define zy -0.2040
#define zz 1.0572

// Constant for the Adobe RGB value from XYZ to RGB
#define axx 2.0413
#define axy -0.5649
#define axz -0.3446

#define ayx -0.9692
#define ayy 1.8760
#define ayz 0.0415

#define azx 0.0134
#define azy -0.1183
#define azz 1.0154

#endif /* xyz_constant_h */
