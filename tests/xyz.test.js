const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('xyz_crash.log');

describe('Creating Xyz from RGB', () => {
  it('Expect to create XYZ from RGB Object', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.0348,
      y: 0.0172,
      z: 0.1097
    });
  });

  it('Expect to create XYZ from RGB Object', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.0376,
      y: 0.0173,
      z: 0.1138
    });
  });

  it('Expect to create dark XYZ from RGB Object of type SRGB', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    });
  });

  it('Expect to create dark XYZ from RGB Object of type adobe RGB', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    });
  });

  it('Expect to create bright XYZ from RGB Object of type SRGB', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 1000);
    expect(xyz).to.be.deep.equal({
      x: 0.9504,
      y: 1,
      z: 1.0888
    });
  });

  it('Expect to create dark XYZ from RGB Object of type adobe RGB', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.9502,
      y: 0.9998,
      z: 1.0887
    });
  });

  it('Expect to throw when the color type property is missing', () => {
    const rgb = {
      r: 50,
      g: 30,
      b: 100,
    };

    expect(() => lib.getXyzFromRgb(rgb)).to.throw('Missing arguments');
  });

  it('Expect to throw when nothing is pass', () => {
    expect(() => lib.getXyzFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when the color type property is missing', () => {
    const rgb = {
      r: 50,
      b: 100,
    };

    expect(() => lib.getXyzFromRgb(rgb, "adobeRgb")).to.throw('Property not found in JS Object');
  });
});

describe('Creating RGB from XYZ', () => {
  it('Expect to create RGB from XYZ sRGB', () => {
    const xyz = {
      x: 0.0348,
      y: 0.0172,
      z: 0.1097
    };

    const rgb = lib.getRgbFromXyz(xyz, "srgb");
    expect(rgb).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    });
  });

  it('Expect to create RGB from XYZ ARGB', () => {
    const xyz = {
      x: 0.0376,
      y: 0.0173,
      z: 0.1138
    };

    const rgb = lib.getRgbFromXyz(xyz, "adobeRgb");
    expect(rgb).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    });
  });

  it('Expect to create dark RGB from XYZ Object of type SRGB', () => {
    const xyz = {
      x: 0,
      y: 0,
      z: 0
    };

    const rgb = lib.getRgbFromXyz(xyz, "srgb");
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to create dark RGB from Xyz Object of type adobe RGB', () => {
    const xyz = {
      x: 0,
      y: 0,
      z: 0
    };

    const rgb = lib.getRgbFromXyz(xyz, "adobeRgb");
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to create bright RGB from XYZ Object of type SRGB', () => {
    const xyz = {
      x: 0.9505,
      y: 1.0,
      z: 1.0887
    };

    const rgb = lib.getRgbFromXyz(xyz, "srgb");
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to create bright RGB from Xyz Object of type adobe RGB', () => {
    const xyz = {
      x: 0.9502,
      y: 0.9998,
      z: 1.0887
    };

    const rgb = lib.getRgbFromXyz(xyz, "adobeRgb");
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw an error when the matrix param is missing', () => {
    const xyz = {
      x: 0.9502,
      y: 0.9998,
      z: 1.0887
    };
    
    expect(() => lib.getRgbFromXyz(xyz)).to.throw('Missing arguments');
  });

  it('Expect to throw an error when nothing is pass', () => {   
    expect(() => lib.getRgbFromXyz()).to.throw('Missing arguments');
  });

  it('Expect to throw an error when the the xyz object is missing a value', () => {
    const xyz = {
      x: 0.9502,
      z: 1.0887
    };
    
    expect(() => lib.getRgbFromXyz(xyz, "srgb")).to.throw('Property not found in JS Object');
  });

});